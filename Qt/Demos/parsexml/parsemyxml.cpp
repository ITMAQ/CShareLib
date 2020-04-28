#include "parsemyxml.h"
#include <QDebug>

ParseMyXML::ParseMyXML()
{

}

bool ParseMyXML::bGetSNSuccess(const QString xmlstr)
{
    QString parseStr_s = "<xml>\r\n  "
                       "<table row=\"1\" col=\"22\">\r\n    "
                       "<row0 SN=\"XA6100650013\" HardwareId=\"XA6100650013\" FirmwareVer=\"X1V1.18\" ProgrammingTool=\"JLINK\" ManufacturerID=\"\" ManufactureDate=\"2019/7/12 14:22:30\" BatchNumber=\"\" CheckResult=\"\" Barcode=\"X1A199KK0000909\" OrderCode=\"零域（上海）科技有限公司\" OrderDate=\"2020/4/8 13:36:09\" SdkVer=\"\" AppVer=\"\" OS=\"\" IP=\"\" UnknowDevice=\"\" Enable=\"\" UpdateUser=\"WH\" UpdateTime=\"2020/4/8 13:36:09\" Description=\"\" FixCount=\"1\" WaybillNumber=\"\" />\r\n  "
                       "</table>\r\n  "
                       "<query>\r\n    "
                       "<result>ok</result>\r\n  "
                       "</query>\r\n"
                       "</xml>";

    QString parseStr_f = "<xml>\r\n  "
                         "<query>\r\n    "
                         "<result>ok</result>\r\n  "
                         "</query>\r\n</xml>";

    bool bHaveTable = false;
    bool bResultOk = false;
    QDomDocument pxmlReader;
    pxmlReader.setContent(xmlstr);
    qDebug()<<pxmlReader.toString();

    QDomElement docElem = pxmlReader.documentElement();
    qDebug()<<docElem.nodeName();   // xml
    QDomNode node = docElem.firstChild();

    while(!node.isNull()){
        qDebug()<<node.nodeName();   // query table

        if(node.nodeName() == "query"){
            QDomNode queryChildnode = node.firstChild();
            while (!queryChildnode.isNull()) {
                qDebug()<<queryChildnode.nodeName();
                if(queryChildnode.nodeName() == "result"){
                    QDomElement ele = queryChildnode.toElement();

                    qDebug()<<ele.text();
                    if(ele.text() == "ok"){
                        bResultOk = true;
                    }else{
                        return false;
                    }
                }
                queryChildnode = queryChildnode.nextSibling();
            }
        }
        if(node.nodeName() == "table"){
            bHaveTable = true;
        }

        node = node.nextSibling();

    }

    if(bHaveTable && bResultOk)return true;

    return false;
}

bool ParseMyXML::bUpdateSNSuccess(const QString xmlstr)
{
    QString parseStr_s = "";
    QString parseStr_f = "<xml>\r\n  "
                         "<update>\r\n    "
                         "<result>failed</result>\r\n  "
                         "</update>\r\n  "
                         "<msgbox>错误，没有找到这台机器的记录！！！！</msgbox>\r\n"
                         "</xml>";
}
