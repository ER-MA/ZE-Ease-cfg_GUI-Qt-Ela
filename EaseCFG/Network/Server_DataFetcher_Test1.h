//#ifndef SERVER_DATAFETCHER_H
//#define SERVER_DATAFETCHER_H
//
//#include <QObject>
//#include <QTimer>
//#include <QJsonDocument>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QNetworkRequest>
//
//
//class Server_DataFetcher : public QObject
//{
//    Q_OBJECT
//
//public:
//    explicit Server_DataFetcher(QObject *parent = nullptr);
//    ~Server_DataFetcher();
//
//    void setFetchServer(int index);
//    void setFetchInterval(int intervalSeconds);
//    void startFetch();
//    void stopFetch();
//
//    QJsonDocument fetchExGServerStatus(); // 获取ExG服务器状态
//    QJsonDocument fetchFYSServerStatus(); // 获取FYS(风云社)服务器状态
//    QJsonDocument fetchZeDServerStatus(); // 获取ZombieDen(僵尸乐园)服务器状态
//    QJsonDocument fetchUBServerStatus(); // 获取UB服务器状态
//
//    void handleNetworkReply(QNetworkReply* reply);
//
//    QJsonDocument exgServerStatus2ServerListJson(QJsonDocument exgServerStatus); // ExG服务器状态数据转ServerList所需的Json数据
//    QJsonDocument fysServerStatus2ServerListJson(QJsonDocument fysServerStatus); // FYS服务器状态数据转ServerList所需的Json数据
//    QJsonDocument zedServerStatus2ServerListJson(QJsonDocument zedServerStatus); // ZombieDen服务器状态数据转ServerList所需的Json数据
//    QJsonDocument ubServerStatus2ServerListJson(QJsonDocument ubServerStatus); // UB服务器状态数据转ServerList所需的Json数据
//
//signals:
//    void dataFetched(const QJsonDocument &jsonDoc); // 获取到数据信号
//
//private slots:
//    void fetchData(); // 获取数据的槽函数
//
//private:
//    int _fetchServerIndex; // 要获取数据的服务器索引
//    QTimer *_fetchTimer; // 定时器
//    int _fetchInterval; // 定时器间隔时间
//
//    QNetworkAccessManager *_networkManager; // 网络管理器
//
//    QByteArray _exgServerCachedData;
//    QByteArray _fysServerCachedData;
//    QByteArray _zedServerCachedData;
//    QByteArray _ubServerCachedData;
//
//    QJsonDocument _exgServerStatus; // ExG服务器状态数据
//    QJsonDocument _fysServerStatus; // FYS服务器状态数据
//    QJsonDocument _zedServerStatus; // ZombieDen服务器状态数据
//    QJsonDocument _ubServerStatus; // UB服务器状态数据
//
//    QJsonDocument _exgServerListJson; // 客户端ExG服务器列表数据
//    QJsonDocument _fysServerListJson; // 客户端FYS服务器列表数据
//    QJsonDocument _zedServerListJson; // 客户端ZombieDen服务器列表数据
//    QJsonDocument _ubServerListJson; // 客户端UB服务器列表数据
//};
//
//#endif // SERVER_DATAFETCHER_H
