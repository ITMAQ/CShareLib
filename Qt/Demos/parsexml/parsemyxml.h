#ifndef PARSEMYXML_H
#define PARSEMYXML_H
#include <QtXml/QDomDocument>

class ParseMyXML
{
public:
    ParseMyXML();
    static bool bGetSNSuccess(const QString xmlstr);
    static bool bUpdateSNSuccess(const QString xmlstr);

private:


};

#endif // PARSEMYXML_H
