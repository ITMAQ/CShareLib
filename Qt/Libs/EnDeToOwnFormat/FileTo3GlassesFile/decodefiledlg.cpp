#include "decodefiledlg.h"
#include "ui_decodefiledlg.h"
#include "dec3glassesfile.h"
#include <QFileDialog>
#include <QMessageBox>
DecodeFileDlg::DecodeFileDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DecodeFileDlg)
{
    ui->setupUi(this);
}

DecodeFileDlg::~DecodeFileDlg()
{
    delete ui;
}

void DecodeFileDlg::selectFile(bool b)
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开文件"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("3glasses文件(*.3glasses)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec()){
        SrcFileName_ = fileDialog->selectedFiles().at(0);
        DstFileName_ = SrcFileName_.left(SrcFileName_.indexOf(".3glasses"));
        ui->SrcFile->setText(SrcFileName_);
        ui->DestFile->setText(DstFileName_);
    }

    //decodfile_ = Dec3GlassesFile(SrcFileName_);
    decodfile_.SetSrcFile(SrcFileName_);
    decodfile_.SetOutPutFile(DstFileName_);

    THREEGLASS_HEAD header;
    memset(&header,0,sizeof(THREEGLASS_HEAD));
    decodfile_.GetHeader(header);
    char *pBaseAddr = (char *)&header;

    QString InfoStr = "";
    char buffer[16] = {0};
    memcpy(buffer,header.manufacturer,8);
    QString manufacturer = buffer;
    InfoStr += QString("制造商名称:")+manufacturer + "\n\r";

    //QStringList firmware_typeList = {"X1","X2","K1","D3","D4"};
    char pfirmware_type[4] = {0};
    memcpy(pfirmware_type,pBaseAddr+8,2);
    InfoStr +=  QString("固件设备名称:")+QString::fromLatin1(pfirmware_type) + "\n\r";

    //char *pData = (char *)&header;
    //pData += 10;
    InfoStr +=  QString("BootLoader固件版本信息:")+ QString::number(pBaseAddr[10])+"."+QString::number(pBaseAddr[11]) + "\n\r";
    //char appversion[4] = {0};
    //memcpy(appversion,&header.application_version,2);
    InfoStr +=  QString("Application固件版本信息:")+ QString::number(pBaseAddr[12])+"."+QString::number(pBaseAddr[13]) + "\n\r";
    //char hardwareversion[4] = {0};
    //memcpy(hardwareversion,&header.hardware_version,2);
    //InfoStr +=  QString("硬件版本信息:")+ QString::number(hardwareversion[0])+"."+QString::number(hardwareversion[1]) + "\n\r";

    short hardversion = 0;
    memcpy(&hardversion,pBaseAddr+14,2);
    InfoStr +=  QString("硬件版本信息:")+ QString::number(hardversion) + "\n\r";

    //InfoStr +=  QString("升级固件的大小:")+ QString::number(header.firmware_size) + "\n\r";
    int firmwaresize = 0;
    memcpy(&firmwaresize,pBaseAddr+16,4);
    InfoStr +=  QString("升级固件的大小:")+ QString::number(firmwaresize) + "\n\r";

    //QString firmwaretime=QString("20%1/%2/%3 %4:%5:%6").arg((int)header.firmware_time[0]).arg((int)header.firmware_time[1]).arg((int)header.firmware_time[2]).arg((int)header.firmware_time[3]).arg((int)header.firmware_time[4]).arg((int)header.firmware_time[5]);
    QString firmwaretime=QString("20%1/%2/%3 %4:%5:%6").arg((int)pBaseAddr[20]).arg((int)pBaseAddr[21]).arg((int)pBaseAddr[22]).arg((int)pBaseAddr[23]).arg((int)pBaseAddr[24]).arg((int)pBaseAddr[25]);
    InfoStr +=  QString("固件生成时间:")+ firmwaretime + "\n\r";
    QStringList user={"ZZZ","LDF","WF","MAQ"};
    InfoStr +=  QString("固件更新操作人:")+ user.at(header.user) + "\n\r";
    InfoStr +=  QString("保留数据:暂时不显示\n\r");
    InfoStr +=  QString("数据校验码:")+ QString::number(header.crc) + "\n\r";

    ui->info->setText(InfoStr);

}

void DecodeFileDlg::DecodeFile(bool b)
{
    decodfile_.Save2Output();
    QMessageBox::information(this, "Title", QString("解码成功"), QMessageBox::Yes, QMessageBox::Yes);

}
