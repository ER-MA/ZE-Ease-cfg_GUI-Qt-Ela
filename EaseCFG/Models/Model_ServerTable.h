#ifndef SERVERTABLEMODEL_H
#define SERVERTABLEMODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QString>

class Model_ServerTable : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit Model_ServerTable(QObject *parent = nullptr);
    // 其他构造函数和成员函数声明...

    // 必需的重载函数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    void fetchData(const QJsonDocument &serverListJson); // 添加的槽函数声明

private:
    QVector<QStringList> m_data; // 数据存储
};

#endif // SERVERTABLEMODEL_H
