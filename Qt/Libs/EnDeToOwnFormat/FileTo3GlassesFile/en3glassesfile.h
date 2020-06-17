#ifndef EN3GLASSESFILE_H
#define EN3GLASSESFILE_H
#include <QString>
#include "public.h"

class En3GlassesFile
{
public:
    En3GlassesFile(QString fName);
    void SetOutPutFile(QString fName);
    void SetHeader(const THREEGLASS_HEAD &header);
    void EncodeFile();

private:
    QString FileName_;
    QString FileOutputName_;
    THREEGLASS_HEAD header_;
};

#endif // EN3GLASSESFILE_H
