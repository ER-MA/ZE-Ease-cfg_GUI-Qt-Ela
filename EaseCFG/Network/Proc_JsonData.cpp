#include "Proc_JsonData.h"

Proc_JsonData::Proc_JsonData(QObject *parent) : QObject(parent)
{

}

Proc_JsonData::~Proc_JsonData()
{

}


QJsonObject Proc_JsonData::readJsonObj(const QString& filePath)
{
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("[Proc_JsonData::readJsonObj] Unable to open file: %s", qPrintable(filePath));
        return QJsonObject();
    }

    QByteArray jsonData = configFile.readAll();
    configFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning("[Proc_JsonData::readJsonObj] JSON parse error at offset %d: %s", jsonError.offset, qPrintable(jsonError.errorString()));
        return QJsonObject();
    }

    return jsonDoc.object();
}

QJsonObject Proc_JsonData::readJsonObj(const QFileInfo& fileInfo)
{
    if (!fileInfo.exists()) {
        qWarning("[Proc_JsonData::readJsonObj] File does not exist: %s", qPrintable(fileInfo.absoluteFilePath()));
        return QJsonObject();
    }
    return readJsonObj(fileInfo.absoluteFilePath());
}

QJsonObject Proc_JsonData::readJsonObj(const QResource& qrcFileRes)
{
    if (!qrcFileRes.isValid()) {
        qWarning("[Proc_JsonData::readJsonObj] Resource is not valid: %s", qPrintable(qrcFileRes.absoluteFilePath()));
        return QJsonObject();
    }

    QByteArray jsonData;
    QResource::Compression compression = qrcFileRes.compressionAlgorithm();
    if (compression != QResource::NoCompression) {
        // 如果资源被压缩，使用适当的解压缩方法
        if (compression == QResource::ZlibCompression) {
            jsonData = qUncompress(qrcFileRes.data(), qrcFileRes.size());
        }
        else if (compression == QResource::ZstdCompression) {
            // 需要包含zstd库并链接到它
            // jsonData = ZSTD_decompress(qrcFileRes.data(), qrcFileRes.uncompressedSize());
            qWarning("[Proc_JsonData::readJsonObj] Zstd compression is not supported.");
            return QJsonObject();
        }
        else {
            qWarning("[Proc_JsonData::readJsonObj] Unknown compression algorithm.");
            return QJsonObject();
        }
    }
    else {
        // 如果资源未压缩，直接读取数据
        jsonData = QByteArray(reinterpret_cast<const char*>(qrcFileRes.data()), qrcFileRes.size());
    }

    if (jsonData.isEmpty()) {
        qWarning("[Proc_JsonData::readJsonObj] Resource data is empty.");
        return QJsonObject();
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning("[Proc_JsonData::readJsonObj] JSON parse error: %s", qPrintable(jsonError.errorString()));
        return QJsonObject();
    }

    return jsonDoc.object();
}
