#ifndef SQLOPER_H
#define SQLOPER_H
#include <QString>
#include <QtSql/qsqldatabase.h>

class SQLOper
{
public:
    SQLOper(QString dbname = "3glasses.db");

private:

    bool IsExitTab(QString tablename);

protected:
    virtual bool initTabs() = 0;
    bool CreateTabByNoExist(QString tableStr,QString createsqlStr);

public:
    bool IsEmptyDb();
    bool Init();
    bool ExcuteSql(QString sqlstr);
    int Excute_sql_file(QString sqlfile);
    bool GetInfo(QString sqlstr,QVector<QVector<QString>> &InfoData);
    //QString GetDbPath(){return  m_dbPath;}
    //QString GetDbDir(){return m_dbDir;}
    //QSqlRecord

private:
    int sqlSize(QSqlQuery query);

private:
    QSqlDatabase m_DataBase;
    QString m_dbDir = "";
    QString m_dbPath = "";
    QString m_dbName = "";
};

#endif // SQLOPER_H
