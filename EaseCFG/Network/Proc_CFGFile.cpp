#include "Proc_CFGFile.h"

Proc_CFGFile::Proc_CFGFile(Keybind_DB* keybindDB, QObject* parent)
    : QObject(parent),
    _keybindDB(keybindDB)
{

}

Proc_CFGFile::~Proc_CFGFile()
{
    
}

QFileInfo Proc_CFGFile::getCSGO2DirPath()
{
    QString dirPath = "E:/GameLibrary/SteamLibrary/steamapps/common/Counter-Strike Global Offensive";
    return QFileInfo(dirPath);
}

QFileInfo Proc_CFGFile::getCSGO2CFGDirPath()
{
    QFileInfo dirPath = getCSGO2DirPath();
    dirPath.setFile(dirPath.absoluteFilePath() + "/game/csgo/cfg");
    return dirPath;
}
