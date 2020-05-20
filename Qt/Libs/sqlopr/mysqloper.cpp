#include "mysqloper.h"
#include "fileoper.h"

bool MySqlOper::initTabs()
{
    //if(IsEmptyDb()){
        Excute_sql_file(PathOper::GetPudctionConfigPath()+"/config/FactoryTestToolBase.sql");
    //}

    return true;
}
