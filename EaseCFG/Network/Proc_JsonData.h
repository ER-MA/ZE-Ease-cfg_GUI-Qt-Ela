#ifndef PROC_JSONDATA_H
#define PROC_JSONDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QResource>

class Proc_JsonData : public QObject
{
    Q_OBJECT
public:
    Proc_JsonData(QObject *parent = nullptr);
    ~Proc_JsonData();
    bool loadJson(const QString& filePath);
    bool saveJson(const QString& filePath);
    QJsonObject getJsonObject() const;
    void setJsonObject(const QJsonObject& jsonObj);

    QJsonObject readJsonObj(const QString& filePath);
    QJsonObject readJsonObj(const QFileInfo& fileInfo);
    QJsonObject readJsonObj(const QResource& resource);

private:
    QJsonObject m_jsonObj;
};

#endif // PROC_JSONDATA_H
