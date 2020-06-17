#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "encodefiledlg.h"
#include "decodefiledlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onEncodeFile(bool b)
{
    EncodeFileDlg *pEncodeDlg = new EncodeFileDlg(this);
    pEncodeDlg->show();
    this->hide();
}

void MainWindow::onDecodeFile(bool b)
{
    DecodeFileDlg *pDecodeDlg = new DecodeFileDlg(this);
    pDecodeDlg->show();
    this->hide();
}
