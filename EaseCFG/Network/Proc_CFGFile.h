#ifndef PROC_CFGFILE_H
#define PROC_CFGFILE_H

#include <QObject>
#include <QFile>
#include <QResource>

#include "Keybind_DB.h"

class Proc_CFGFile : public QObject
{
    Q_OBJECT
public:
    explicit Proc_CFGFile(Keybind_DB* keybindDB, QObject* parent = nullptr);
    ~Proc_CFGFile();

    QFileInfo getCSGO2DirPath();
    QFileInfo getCSGO2CFGDirPath();

private:
    Keybind_DB _keybindDB;

};

#endif // PROC_CFGFILE_H
