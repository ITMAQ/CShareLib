#include "sqloper.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCoreApplication>
#include <QVariant>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QtSql/qsqlrecord.h>
#include <QFile>
#include <QDir>
#include "fileoper.h"

SQLOper::SQLOper(QString dbname)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      m_DataBase = QSqlDatabase::database("qt_sql_default_connection");
    else
      m_DataBase = QSqlDatabase::addDatabase("QSQLITE");

    m_DataBase.setHostName("127.0.0.1");
    m_dbDir = PathOper::GetDBPath();
    QDir dbDir;
    dbDir.setPath(m_dbDir);
    if(!dbDir.exists()){
        dbDir.mkpath(m_dbDir);
        qDebug()<<"mkpath"<<m_dbDir;
    }
    m_dbPath = m_dbDir+"/"+dbname;
    //m_dbPath = "//home//vr//3glasses//db//3glasses.db";
    QString dbpath = m_dbPath;
    qDebug() <<dbpath;
    m_DataBase.setDatabaseName(dbpath);
    m_DataBase.setUserName("root");
    m_DataBase.setPassword("123456");
}

bool SQLOper::IsEmptyDb()
{
    bool bRet = true;
    if (!m_DataBase.open()) {
        qDebug()<<"Open db failed";
        return false;
    }
    QSqlQuery query(m_DataBase);
    query.exec(QString("select count(*) from sqlite_master where type='table'"));    //关键的判断
    if (query.next())
    {
        qDebug()<<"Tables:"<<query.value(0).toInt();
        if (query.value(0).toInt() > 0)
        {
            bRet = false;
            return bRet;
        }
    }
    query.clear();
    m_DataBase.close();

    return bRet;
}

bool SQLOper::IsExitTab(QString tablename)
{
    bool bRet = false;
    if (!m_DataBase.open()) {
        return bRet;
    }
    QSqlQuery query(m_DataBase);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tablename));    //关键的判断
    if (query.next())
    {
        if (query.value(0).toInt() > 0)
        {
            bRet = true;
        }
    }

    return bRet;
}

bool SQLOper::CreateTabByNoExist(QString tableStr,QString createsqlStr)
{
    if(IsExitTab(tableStr))return true;
    return ExcuteSql(createsqlStr);
}

bool SQLOper::Init()
{
    return initTabs();
}

bool SQLOper::ExcuteSql(QString sqlstr)
{
    qDebug()<<sqlstr;
    if(!m_DataBase.open())return false;

    QSqlQuery query(m_DataBase);
    query.prepare(sqlstr);
    bool success = query.exec();
    //bool success = query.exec(sqlstr);
    if(success)return true;

    QSqlError lastError = query.lastError();
    QString err = lastError.driverText();
    qDebug() << err;
    m_DataBase.close();

    return false;
}

int SQLOper::Excute_sql_file(QString sql_file_path)
{
    int iRet = 0;
    qDebug()<<"sql_file_path"<<sql_file_path;
    QFile qfile(sql_file_path);
    if (!qfile.exists()) {
        return -1;
    }
    if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"open db failed";
        return -1;
    }
    QTextStream in(&qfile);
    in.setCodec("UTF-8");
    QString qstr_file_data = in.readAll();
    if(!m_DataBase.open())return false;
    QSqlQuery qsql(m_DataBase);
    qDebug()<<m_DataBase.databaseName();
    QStringList qstrlist_sql =  qstr_file_data.split(";");
    for (int i = 0; i < qstrlist_sql.size() - 1; i++) {
        QString qstr_sql_part = qstrlist_sql.at(i).toUtf8();
        qDebug()<<"SQL:"<<qstr_sql_part;

        //bool sql_result = qsql.exec(qstr_sql_part);
        qsql.prepare(qstr_sql_part);
        bool sql_result = qsql.exec();

        if (!sql_result) {
            QSqlError sql_error = qsql.lastError();
            qDebug()<<sql_error.driverText();

            iRet = -1;
            break;
        }
    }

    return iRet;
}

bool SQLOper::GetInfo(QString sqlstr,QVector<QVector<QString>> &InfoData)
{
    if(!m_DataBase.open())return false;

    QSqlQuery query(m_DataBase);
    //query.prepare(sqlstr);
    bool bRst = query.exec(sqlstr);
    if(!bRst){
        QSqlError sql_error = query.lastError();
        qDebug()<<sql_error.driverText();

        return bRst;
    }


    QSqlRecord rec = query.record();

    int nOneLineCount = query.size();
    int nRecordCount = rec.count();
    qDebug() << "表的列数：" << nRecordCount;         // 表一共有多少列
    qDebug() << "表的行数：" << sqlSize(query);       // 表一共有多少行
    while (query.next())
    {
        QVector<QString> Item;
        for(int j = 0;j < nRecordCount;j++){
            Item.push_back(query.value(j).toString());
        }

        InfoData.push_back(Item);
    }

    return bRst;
}

int SQLOper::sqlSize(QSqlQuery query)
{
    int initialPos = query.at();
    // Very strange but for no records .at() returns -2
    int pos = 0;
    if (query.last())
        pos = query.at() + 1;
    else
        pos = 0;
    // Important to restore initial pos
    query.seek(initialPos);
    return pos;
}
