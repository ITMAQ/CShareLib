#include "fileoper.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
FileOper::FileOper()
{

}

void FileOper::AppendFile(QString Dirpath, QString filename,QString context)
{
    // 保存文件
    QDir *dir = new QDir(Dirpath);
    if(!dir->exists())dir->mkpath(Dirpath);

    QFile *file = new QFile(Dirpath+filename);//此路径下没有就会自己创建一个
    file->open(QIODevice::ReadWrite | QIODevice::Append);//以读写切追加写入的方式操作文本
    QTextStream txtOutput(file);
    txtOutput << context;

    file->close();
}

LogOper::LogOper(const QString FileName)
{
    SetLogPath(FileName);
}

void LogOper::SetLogPath(const QString FileName)
{
    int lastFlagPos = FileName.lastIndexOf('/')==-1?FileName.lastIndexOf('\\'):FileName.lastIndexOf('/');
    QString DirPath = FileName.mid(0,lastFlagPos);
    QDir dir(DirPath);
    if(!dir.exists())dir.mkpath(DirPath);
    logFile_ = FileName;
}

void LogOper::SaveLog(const QString msg)
{
    QFile outputFile(logFile_);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&outputFile);
    qDebug()<<msg;
    textStream<<QString("[%1]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    textStream << msg;
    textStream << "\r\n";
    outputFile.flush();
    outputFile.close();
}

LogOper LogOper::operator<<(const QString msg)
{
    SaveLog(msg);

    return *this;
}

QString PathOper::GetCurrentAppPath()
{
    if(qEnvironmentVariableIsEmpty(FACOTYTESTTOOL_ENVNAME)){
        QMessageBox::information(NULL, "错误", QString("未找到环境变量:")+FACOTYTESTTOOL_ENVNAME, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        return "";
    }

    return qEnvironmentVariable(FACOTYTESTTOOL_ENVNAME);
}

QString PathOper::GetPudctionPath()
{
    if(qEnvironmentVariableIsEmpty(THREEGLASSESCONFIG_ENVNAME)){
        QMessageBox::information(NULL, "错误", QString("未找到环境变量:")+THREEGLASSESCONFIG_ENVNAME, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        return "";
    }

    return qEnvironmentVariable(THREEGLASSESCONFIG_ENVNAME);
}

QString PathOper::GetPudctionConfigPath()
{

    if(qEnvironmentVariableIsEmpty(FACTORYTESTTOOLCONFIG_ENVNAME)){
        QMessageBox::information(NULL, "错误", QString("未找到环境变量:")+FACTORYTESTTOOLCONFIG_ENVNAME, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        return "";
    }

    return qEnvironmentVariable(FACTORYTESTTOOLCONFIG_ENVNAME);
}

QString PathOper::GetDBPath()
{
    if(qEnvironmentVariableIsEmpty(THREEGLASSDB_ENVNAME)){
        QMessageBox::information(NULL, "错误", QString("未找到环境变量:")+THREEGLASSDB_ENVNAME, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        return "";
    }

    return qEnvironmentVariable(THREEGLASSDB_ENVNAME);
}
