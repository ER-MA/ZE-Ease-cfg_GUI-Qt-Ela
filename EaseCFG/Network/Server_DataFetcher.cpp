#include "Server_DataFetcher.h"

#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Server_DataFetcher::Server_DataFetcher(QObject* parent) :
    QObject(parent)
{
    _serverNetworkManager = new QNetworkAccessManager(this);

    _fetchTimer = new QTimer(this);
    connect(_fetchTimer, &QTimer::timeout, this, &Server_DataFetcher::fetchData);

    setFetchServer(0); // 默认获取第一个服务器数据
    setFetchIntervalSeconds(5000); // 默认每5秒获取一次数据
}

Server_DataFetcher::~Server_DataFetcher()
{
    stopFetch(); // 确保在析构时停止定时器
}

void Server_DataFetcher::setFetchServer(int index)
{
    _fetchServerIndex = index;

    if (_fetchServerIndex == -1) {
        qDebug() << "[Server_DataFetcher] 未选择服务器！！！";
        _serverRequest.setUrl(QUrl(""));
        _serverRequest.setHeader(QNetworkRequest::ContentTypeHeader, "");
    }
    else if (_fetchServerIndex == 0) {
        qDebug() << "[Server_DataFetcher] 已选中服务器：ExG";
        _serverRequest.setUrl(QUrl("https://list.darkrp.cn:9000/ServerList/CurrentStatus"));
        _serverRequest.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain; charset=utf-8");
    }
    else if (_fetchServerIndex == 1) {
        qDebug() << "[Server_DataFetcher] 已选中服务器：FYS";
    }
    else if (_fetchServerIndex == 2) {
        qDebug() << "[Server_DataFetcher] 已选中服务器：ZombieDen";
    }
    else if (_fetchServerIndex == 3) {
        qDebug() << "[Server_DataFetcher] 已选中服务器：UB";
    }
    else {
        qDebug() << "[Server_DataFetcher] 未知服务器！！！";
        _serverRequest.setUrl(QUrl(""));
        _serverRequest.setHeader(QNetworkRequest::ContentTypeHeader, "");
    }
}

void Server_DataFetcher::setFetchIntervalSeconds(int intervalSeconds)
{
    if (intervalSeconds <= 0) {
        qDebug() << "[Server_DataFetcher] 间隔时间必须大于0!!!";
        return;
    }
    _fetchIntervalSeconds = intervalSeconds;
    _fetchTimer->setInterval(_fetchIntervalSeconds); // 设置定时器间隔
}

void Server_DataFetcher::startFetch()
{
    qDebug() << "[Server_DataFetcher] 开始获取服务器数据";
    _fetchTimer->start(); // 启动定时器
}

void Server_DataFetcher::stopFetch()
{
    qDebug() << "[Server_DataFetcher] 停止获取服务器数据";
    _fetchTimer->stop(); // 停止定时器
}

void Server_DataFetcher::fetchData()
{
    qDebug() << "[Server_DataFetcher] ...服务器数据获取中...";

    if (_fetchServerIndex == 0) {
        fetchExGServerStatus();
    }
    else if (_fetchServerIndex == 1) {
        // TODO: 处理FYS服务器数据获取
    }
    else if (_fetchServerIndex == 2) {
        // TODO: 处理ZombieDen服务器数据获取
    }
    else if (_fetchServerIndex == 3) {
        // TODO: 处理UB服务器数据获取
    }
    else {
        qDebug() << "[Server_DataFetcher] 未知服务器！！！";
    }
}

void Server_DataFetcher::fetchExGServerStatus()
{
    qDebug() << "[Server_DataFetcher] ...正在连接到ExG服务器";

    QNetworkReply* reply = _serverNetworkManager->get(_serverRequest);
    connect(reply, &QNetworkReply::finished, this, &Server_DataFetcher::handleNetworkReply);
}

void Server_DataFetcher::handleNetworkReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    if (reply->error()) {
        qDebug() << "[Server_DataFetcher] 网络请求错误：" << reply->errorString();
    }
    else {
        QByteArray _exgServerCachedData = reply->readAll();
        QJsonParseError error;
        _exgServerStatus = QJsonDocument::fromJson(_exgServerCachedData, &error);
        if (error.error != QJsonParseError::NoError) {
            qDebug() << "[Server_DataFetcher] JSON解析错误：" << error.errorString();
        }
        else {
            exgServerStatus2ServerListJson();
        }
    }

    reply->deleteLater();
}

void Server_DataFetcher::exgServerStatus2ServerListJson()
{
    qDebug() << "[Server_DataFetcher] ...正在解析ExG服务器数据";
    // 还可以优化，但是优化个Der。以后再说

    // 解析 JSON 数据
    QJsonArray jsonArray = _exgServerStatus.array();
    QJsonArray serverListArray;

    // 填充数据
    for (int i = 0; i < jsonArray.count(); i++) {
        QJsonObject serverObject = jsonArray[i].toObject()["Server"].toObject();
        QJsonObject statusObject = jsonArray[i].toObject()["Status"].toObject();

        QString displayName = serverObject["DisplayName"].toString();
        QString mapName = statusObject["Map"].toString();
        QString mapDisplayName = statusObject["MapDisplayName"].toString();
        if (mapDisplayName.isEmpty()) {
            mapDisplayName = "(无)";
        }
        int currentPlayers = statusObject["CurrentPlayers"].toInt();
        int maxPlayers = statusObject["MaxPlayers"].toInt();
        QString playerCount = QString("%1/%2\t(%3)").arg(currentPlayers).arg(maxPlayers).arg(maxPlayers - currentPlayers);

        QJsonObject serverEntry;
        serverEntry["DisplayName"] = displayName;
        serverEntry["MapName"] = mapName;
        serverEntry["MapDisplayName"] = mapDisplayName;
        serverEntry["PlayerCount"] = playerCount;

        serverListArray.append(serverEntry);
    }

    // 将处理后的数据存储在 _exgServerListJson 成员变量中
    _exgServerListJson = QJsonDocument(serverListArray);

    // 发送信号，将数据传递给 fetchData
    emit dataFetched(_exgServerListJson);
}

QString Server_DataFetcher::getServerAddressByRow(int row)
{
    // 确保索引在有效范围内
    if (row < 0 || row >= _exgServerStatus.array().count()) {
        return "";
    }

    if (_fetchServerIndex == -1) {
        return "";
    }
    else if (_fetchServerIndex == 0) {
        // 获取服务器 IP 地址
        QJsonArray jsonArray = _exgServerStatus.array();
        QJsonObject serverObject = jsonArray[row].toObject()["Server"].toObject();
        QString serverIP = serverObject["Ip"].toString();
        int serverPort = serverObject["Port"].toInt(); // 先转换为 int
        QString serverPortStr = QString::number(serverPort); // 然后转换为 QString

        // 组装完整的服务器地址
        QString serverAddress = serverIP + ":" + serverPortStr;

        return serverAddress;
    }
    else {
        // TODO: 处理其他服务器数据获取
        return "";
    }
}
