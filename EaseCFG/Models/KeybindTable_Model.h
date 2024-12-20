#ifndef KEYBIND_TABLE_MODEL_H
#define KEYBIND_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#include <QVector>
#include <QString>

class KeybindTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit KeybindTableModel(QObject* parent = nullptr);

    // 返回行数
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    // 返回列数
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    // 返回单元格数据
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // 返回表头数据
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    // 从服务器获取数据并刷新表格
    void fetchData(const QJsonDocument& jsonDoc);

private:
    QVector<QStringList> m_data; // 数据存储
};

#endif // KEYBIND_TABLE_MODEL_H
