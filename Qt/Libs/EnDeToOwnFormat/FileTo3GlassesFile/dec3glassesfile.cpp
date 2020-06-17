#include "dec3glassesfile.h"
#include <QFile>
#include <Windows.h>
#include <QString>
#include <QDataStream>

Dec3GlassesFile::Dec3GlassesFile()
{

}

Dec3GlassesFile::Dec3GlassesFile(QString Filename)
{
    FileName_ = Filename;
}

void Dec3GlassesFile::SetSrcFile(QString FileName)
{
    FileName_ = FileName;
}

void Dec3GlassesFile::SetOutPutFile(QString Filename)
{
    OutPutFileName_ = Filename;
}

void Dec3GlassesFile::GetHeader(THREEGLASS_HEAD &header)
{
    QFile *file = new QFile(FileName_);
    if(!file->open(QIODevice::ReadOnly)){
        return;
    }

    char pBuffer[1024];
    ZeroMemory(pBuffer,1024);
    uint length = sizeof(THREEGLASS_HEAD);

    int nLength = file->read(pBuffer,length);
    ZeroMemory(&header,sizeof(THREEGLASS_HEAD));
    memcpy(&header,pBuffer,sizeof(THREEGLASS_HEAD));

    file->close();
}

void Dec3GlassesFile::Save2Output()
{
    QFile *file = new QFile(OutPutFileName_);
    file->open(QIODevice::ReadWrite);
    //QDataStream output(file);

    QFile *srcFile = new QFile(FileName_);
    srcFile->open(QIODevice::ReadOnly);
    srcFile->seek(sizeof(THREEGLASS_HEAD));
    while(!srcFile->atEnd()){
        char buffer[1024] = "";
        int nReadLength = srcFile->read(buffer,1024);
        file->write(buffer,nReadLength);
    }

    srcFile->close();
    file->close();
}

bool Dec3GlassesFile::CheckFileIsRight()
{
    THREEGLASS_HEAD header;
    GetHeader(header);
    char *pBaseAddr = (char *)&header;

    int crc = header.crc;
    int culcrl = 0;
    for(int i = 0;i < 124;i++){
        culcrl += pBaseAddr[i];
    }

    return crc == culcrl;
}

QString Dec3GlassesFile::Getmanufacturer()
{
    THREEGLASS_HEAD header;
    GetHeader(header);

    char buffer[16] = {0};
    memcpy(buffer,header.manufacturer,8);
    QString manufacturer = buffer;

    return manufacturer;
}

HADRWARE_VERION Dec3GlassesFile::GetHardwareVersion()
{
    THREEGLASS_HEAD header;
    GetHeader(header);
    char *pBaseAddr = (char *)&header;

    short hardversion = 0;
    memcpy(&hardversion,pBaseAddr+14,2);

    return (HADRWARE_VERION)hardversion;

}
