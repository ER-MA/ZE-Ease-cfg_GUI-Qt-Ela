//#include "Server_DataFetcher_Test1.h"
//
//#include <QTimer>
//#include <QFile>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QDebug>
//
//Server_DataFetcher::Server_DataFetcher(QObject* parent) :
//    QObject(parent)
//{
//    _fetchTimer = new QTimer(this);
//    connect(_fetchTimer, &QTimer::timeout, this, &Server_DataFetcher::fetchData);
//
//    setFetchServer(0); // 默认获取第一个服务器数据
//    setFetchInterval(5); // 默认每5秒获取一次数据
//}
//
//Server_DataFetcher::~Server_DataFetcher()
//{
//    stopFetch(); // 确保在析构时停止定时器
//}
//
//void Server_DataFetcher::setFetchServer(int index)
//{
//    qDebug() << "[Server_DataFetcher] index:" << index;
//    _fetchServerIndex = index;
//}
//
//void Server_DataFetcher::setFetchInterval(int intervalSeconds)
//{
//    if (intervalSeconds <= 0) {
//        qDebug() << "[Server_DataFetcher] 间隔时间必须大于0!!!";
//        return;
//    }
//    _fetchInterval = intervalSeconds * 1000; // 转换为毫秒
//    _fetchTimer->setInterval(_fetchInterval); // 设置定时器间隔
//}
//
//void Server_DataFetcher::startFetch()
//{
//    qDebug() << "[Server_DataFetcher] 开始获取服务器数据";
//    _fetchTimer->start(); // 启动定时器
//}
//
//void Server_DataFetcher::stopFetch()
//{
//    qDebug() << "[Server_DataFetcher] 停止获取服务器数据";
//    _fetchTimer->stop(); // 停止定时器
//}
//
//void Server_DataFetcher::fetchData()
//{
//    qDebug() << "[Server_DataFetcher] 正在获取服务器数据";
//    //QFile file(":/Resource/Data/CurrentCs2ServerStatus.json");
//    //if (!file.open(QIODevice::ReadOnly)) {
//    //    qDebug() << "[Server_DataFetcher] 无法打开文件!!!";
//    //    return;
//    //}
//    //
//    //QByteArray data = file.readAll();
//    //file.close();
//    //
//    //QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//    //if (jsonDoc.isNull()) {
//    //    qDebug() << "[Server_DataFetcher] JSON格式错误!!!";
//    //    return;
//    //}
//
//    if (_fetchServerIndex == 0) {
//        fetchExGServerStatus();
//        //emit dataFetched(exgServerStatus2ServerListJson(fetchExGServerStatus()));  // 发出获取到的数据
//    }
//
//    
//}
//
//// ExG
//QJsonDocument Server_DataFetcher::fetchExGServerStatus()
//{
//    qDebug() << "[Server_DataFetcher] 获取ExG服务器状态";
//    QNetworkRequest request(QUrl("https://list.darkrp.cn:9000/ServerList/CurrentStatus"));
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain; charset=utf-8");
//    _networkManager = new QNetworkAccessManager(this);
//    connect(_networkManager, &QNetworkAccessManager::finished, this, &Server_DataFetcher::handleNetworkReply);
//    _networkManager->get(request);
//    return _exgServerStatus;
//}
//
//void Server_DataFetcher::handleNetworkReply(QNetworkReply* reply) {
//    if (reply->error()) {
//        qDebug() << "[Server_DataFetcher] 网络请求错误：" << reply->errorString();
//        reply->deleteLater();
//        return;
//    }
//
//    const QByteArray response = reply->readAll();
//    QJsonParseError error;
//    _exgServerStatus = QJsonDocument::fromJson(response, &error);
//    if (error.error != QJsonParseError::NoError) {
//        qDebug() << "[Server_DataFetcher] JSON解析错误：" << error.errorString();
//    }
//    else {
//        // 可以在这里发出信号，通知数据已经更新
//        emit dataFetched(exgServerStatus2ServerListJson(_exgServerStatus));
//    }
//
//    reply->deleteLater();
//}
//
//QJsonDocument Server_DataFetcher::exgServerStatus2ServerListJson(QJsonDocument exgServerStatus)
//{
//    qDebug() << "[Server_DataFetcher] ExG服务器状态数据转ServerList所需的Json数据";
//    qDebug() << _exgServerStatus;
//    return _exgServerListJson;
//}
//
//// FYS
//QJsonDocument Server_DataFetcher::fetchFYSServerStatus()
//{
//    qDebug() << "[Server_DataFetcher] 获取FYS服务器状态";
//    return _fysServerStatus;
//}
//
//QJsonDocument Server_DataFetcher::fysServerStatus2ServerListJson(QJsonDocument fysServerStatus)
//{
//    qDebug() << "[Server_DataFetcher] FYS服务器状态数据转ServerList所需的Json数据";
//    return _fysServerListJson;
//}
//
//// ZombieDen
//QJsonDocument Server_DataFetcher::fetchZeDServerStatus()
//{
//    qDebug() << "[Server_DataFetcher] 获取ZombieDen服务器状态";
//    return _zedServerStatus;
//}
//
//QJsonDocument Server_DataFetcher::zedServerStatus2ServerListJson(QJsonDocument zedServerStatus)
//{
//    qDebug() << "[Server_DataFetcher] ZombieDen服务器状态数据转ServerList所需的Json数据";
//    return _zedServerListJson;
//}
//
//// UB
//QJsonDocument Server_DataFetcher::fetchUBServerStatus()
//{
//    qDebug() << "[Server_DataFetcher] 获取UB服务器状态";
//    return _ubServerStatus;
//}
//
//QJsonDocument Server_DataFetcher::ubServerStatus2ServerListJson(QJsonDocument ubServerStatus)
//{
//    qDebug() << "[Server_DataFetcher] UB服务器状态数据转ServerList所需的Json数据";
//    return _ubServerListJson;
//}
