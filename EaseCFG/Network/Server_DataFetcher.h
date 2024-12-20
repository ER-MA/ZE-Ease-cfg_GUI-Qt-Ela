#ifndef SERVER_DATAFETCHER_H
#define SERVER_DATAFETCHER_H

#include <QObject>
#include <QTimer>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


class Server_DataFetcher : public QObject
{
    Q_OBJECT

public:
    explicit Server_DataFetcher(QObject *parent = nullptr);
    ~Server_DataFetcher();

    void setFetchServer(int index);
    void setFetchIntervalSeconds(int intervalSeconds);
    void startFetch();
    void stopFetch();

    void fetchExGServerStatus(); // 获取ExG服务器状态
    void handleNetworkReply();
    void exgServerStatus2ServerListJson(); // ExG服务器状态数据转ServerList所需的Json数据

    QString getServerAddressByRow(int row); // 获取行索引所对应的服务器地址

signals:
    void dataFetched(const QJsonDocument &jsonDoc); // 获取到数据信号

private slots:
    void fetchData(); // 获取数据的槽函数

private:
    int _fetchServerIndex = -1; // 要获取数据的服务器索引
    QTimer *_fetchTimer = nullptr; // 定时器
    int _fetchIntervalSeconds = 5000; // 定时器间隔时间

    QNetworkRequest _serverRequest; // 服务器状态请求
    QNetworkAccessManager *_serverNetworkManager = nullptr; // 网络管理器

    QByteArray _exgServerCachedData; // 缓存ExG服务器状态数据
    QJsonDocument _exgServerStatus; // ExG服务器状态数据
    QJsonDocument _exgServerListJson; // 客户端ExG服务器列表数据
};

#endif // SERVER_DATAFETCHER_H
