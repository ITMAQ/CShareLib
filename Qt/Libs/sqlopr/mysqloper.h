#ifndef MYSQLOPER_H
#define MYSQLOPER_H
#include "sqloper.h"

class MySqlOper:public SQLOper
{
public:
    MySqlOper(QString dbname="3glasses.db"):SQLOper(dbname){};

protected:
    virtual bool initTabs();
};

#endif // MYSQLOPER_H
