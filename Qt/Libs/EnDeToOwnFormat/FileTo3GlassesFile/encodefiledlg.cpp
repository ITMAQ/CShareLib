#include "encodefiledlg.h"
#include "ui_encodefiledlg.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QMessageBox>

EncodeFileDlg::EncodeFileDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EncodeFileDlg)
{
    ui->setupUi(this);
    ui->reserved->setText("");
}

EncodeFileDlg::~EncodeFileDlg()
{
    delete ui;
}

void EncodeFileDlg::selectFile(bool b)
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开文件"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    //fileDialog->setNameFilter(tr("更新程序(*.bin)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    if(fileDialog->exec()){
        //ui->PathEdit->setText(fileDialog->selectedFiles().at(0));
        ui->SrcFile->setText(fileDialog->selectedFiles().at(0));
        ui->DestFile->setText(fileDialog->selectedFiles().at(0)+".3glasses");
    }

    QFileInfo info( ui->SrcFile->text());
    ui->dateTimeEdit->setDateTime(info.created());
    info.size();
    ui->FileSizeEdit->setText(QString::number(info.size()));

}

void EncodeFileDlg::EncodeFile(bool b)
{
   En3GlassesFile enFile = En3GlassesFile(ui->SrcFile->text());
   enFile.SetOutPutFile(ui->DestFile->text());
   THREEGLASS_HEAD header;
   memset(&header,0,sizeof(header));
   char *pData = (char *)&header;
   //header.application_version
   //header.manufacturer = "3Glasses";
   const char srcmanufacturer[] = {"3Glasses"};
   memset(header.manufacturer,0,8);
   //strcpy_s(header.manufacturer,8,srcmanufacturer);
   memcpy(header.manufacturer,srcmanufacturer,8);
   //header.firmware_type =
   pData = (char *)&header.firmware_type;
   *pData = ui->firmwaretype->currentText().at(0).toLatin1();
   pData++;
   *pData = ui->firmwaretype->currentText().at(1).toLatin1();
   // header.bootloader_version
   pData = (char *)&header.bootloader_version;
   *pData = ui->BootLoaderH->text().toInt();
   pData++;
   *pData = ui->BootLoaderL->text().toInt();
   // header.application_version
   pData = (char *)&header.application_version;
   *pData = ui->AppHV->text().toInt();
   pData++;
   *pData = ui->AppLV->text().toInt();
   // header.hardware_version
   int hardversion[] = {0x0000,0x001,0x0002,0x00003,0x0004,0x0005,0x0100};
   header.hardware_version = hardversion[ui->hardwarev->currentIndex()];
   // firmware_size
   header.firmware_size = ui->FileSizeEdit->text().toInt();
   // firmware_time
   pData = (char *)&header.firmware_time;
   QDateTime firmwaretime = ui->dateTimeEdit->dateTime();
   *pData = firmwaretime.date().year()%100;
   pData++;
   *pData = firmwaretime.date().month();
    pData++;
   *pData = firmwaretime.date().day();
    pData++;
   *pData = firmwaretime.time().hour();
    pData++;
   *pData = firmwaretime.time().minute();
    pData++;
   *pData = firmwaretime.time().second();
    pData++;

   // user
    pData = (char *)&header.user;
   *pData = ui->user->currentIndex();

   // reserved
    QString reservedstr = "";
    reservedstr = ui->reserved->placeholderText();
    //header.reserved = reservedstr;
   //strcpy_s(header.reserved,97,reservedstr.toLocal8Bit().data());
   memcpy(header.reserved,reservedstr.toLocal8Bit().data(),reservedstr.length());

   // user
   char *pcrc = (char*)&header;
   for(int i = 0;i < 124;i++){
       header.crc += (int)*pcrc;
       pcrc++;
   }

   enFile.SetHeader(header);

   enFile.EncodeFile();

   QMessageBox::information(this, "Title", "加密成功", QMessageBox::Yes, QMessageBox::Yes);

}
