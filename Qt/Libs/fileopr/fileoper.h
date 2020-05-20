#ifndef FILEOPER_H
#define FILEOPER_H
#include <QString>

#define THREEGLASSESCONFIG_ENVNAME "THREEGLASSESCONFIG_PATH"
#define FACOTYTESTTOOL_ENVNAME "FACTORYTESTTOOLINSTALL_PATH"
#define THREEGLASSDB_ENVNAME "THREEGLASSESDB_PATH"
#define FACTORYTESTTOOLCONFIG_ENVNAME "FACTORYTESTTOOLCONFIG_PATH"

class FileOper
{
public:
    FileOper();
public:
    void AppendFile(QString filepath,QString filename,QString context);

};

class LogOper
{
public:
    LogOper(){};
    LogOper(const QString FileName);
    void SetLogPath(const QString LogPath);
    LogOper operator<<(const QString msg);
private:
    void SaveLog(const QString msg);

private:
    QString logFile_;
};

class PathOper
{
public:
    static QString GetCurrentAppPath();
    static QString GetPudctionPath();
    static QString GetPudctionConfigPath();
    static QString GetDBPath();
};

#endif // FILEOPER_H
