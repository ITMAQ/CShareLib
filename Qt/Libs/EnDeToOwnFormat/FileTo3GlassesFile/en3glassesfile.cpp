#include "en3glassesfile.h"
#include <Windows.h>
#include <QDateTime>
#include <QFile>
#include <QDataStream>
#include <QFileInfo>

En3GlassesFile::En3GlassesFile(QString fName)
{
    FileName_ = fName;
    FileOutputName_ = fName+QString("3glasses");
}

void En3GlassesFile::SetOutPutFile(QString fName)
{
    FileOutputName_ = fName;
}

void En3GlassesFile::SetHeader(const THREEGLASS_HEAD &header)
{
    CopyMemory(&header_,&header,sizeof(THREEGLASS_HEAD));
 //   QDateTime curTime = QDateTime::currentDateTime();

//    header_.crc = 0;
//    header_.firmware_time[0] = curTime.date().year()%100;   // byte20
//    header_.firmware_time[1] = curTime.date().month();      // byte21
//    header_.firmware_time[2] = curTime.date().day();        // byte22
//    header_.firmware_time[3] = curTime.time().hour();       // byte23
//    header_.firmware_time[4] = curTime.time().minute();     // byte24
//    header_.firmware_time[5] = curTime.time().second();     // byte25

//    byte *pData = (byte*)&header_;
//    for(int i = 0;i < 124;i++){
//        header_.crc += *pData;
//        pData++;
//    }

}

void En3GlassesFile::EncodeFile()
{
    QFile *file = new QFile(FileOutputName_);//此路径下没有就会自己创建一个
    file->remove();
    file->open(QIODevice::ReadWrite);
    //QDataStream txtOutput(file);
    file->seek(0);
    char pData[1024] = {0};
    memcpy(pData,&header_,sizeof(header_));
    //pData[0] = '3';
    //pData[1] = 'G';
    //txtOutput.writeBytes((char*)pData,sizeof(header_));
    //txtOutput.writeBytes((char*)pData,2);
    //txtOutput << pData;
    file->write(pData,sizeof(header_));

    QFile *srcFile = new QFile(FileName_);
    //QString buffer;
    srcFile->open(QIODevice::ReadOnly);

    while(!srcFile->atEnd()){
        char buffer[1024] = "";
        int nReadLength = srcFile->read(buffer,1024);
        file->write(buffer,nReadLength);
    }

//    QDataStream input(srcFile);
//    while (!input.atEnd()) {
//        char buffer[1024] = "";
//        int readlength = input.readRawData(buffer,1024);
//       //input >> buffer;
//        txtOutput.writeBytes(buffer,readlength);
//       //txtOutput << buffer;
//    }

    srcFile->close();
    file->close();

}
