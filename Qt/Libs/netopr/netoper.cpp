#include "netoper.h"
#include <QProcess>
#include <QTimer>
#include <QMessageBox>

NetOper *NetOper::_pThis = nullptr;

bool NetOper::Connect(QString ip, int uPort)
{
    if(pSTcp_ == nullptr){
        pSTcp_ = new QTcpSocket();
    }

    // 取消所有的连接
    pSTcp_->abort();
    pSTcp_->connectToHost(ip,uPort);
    if(!pSTcp_->waitForConnected(CONNECT_TIME_OUT)){
        // 连接超时
        qDebug()<<"Connect fail";
        bIsConnect_ = false;

        QMessageBox::information(NULL, "提示", "连接服务器失败,请检查网络或联系管理员", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }

    bIsConnect_ = true;
    //QObject::connect(pSTcp_,SIGNAL(readyRead()),this,SLOT(ReadData()));
    QObject::connect(pSTcp_,&QTcpSocket::readyRead,this,&NetOper::ReadNetData);
    //QObject::connect(pSTcp_,&QTcpSocket::readyRead,this,&NetOper::DisConnected);
    qDebug()<<"Connect Succes";

    //CheckNetStateThread *pCheckthread = new CheckNetStateThread(this);
    //pCheckthread->start();
    // 设置定时器，检测网络状态
    //QTimer *timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(onNetConnectCheck()));
    //timer->start(1000);

    return true;


}

void NetOper::SendData(QString &data)
{
    // 也许数据发送之前对Socket还有其他的校验
    if(pSTcp_){
         pSTcp_->write(data.toStdString().c_str());
         pSTcp_->flush();
    }

}

//void NetOper::onNetConnectCheck()
//{

//}

//bool NetOper::isConnected()
//{
//    return bIsConnect_;
//}

void NetOper::ReadNetData()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = pSTcp_->readAll();

    if(!buffer.isEmpty())
    {
        pRecvDataFun_(tr(buffer));
    }
}

// 使用该类的去注册
void NetOper::RegisterRecvFun(DEALRECVDATA recvfun)
{
    pRecvDataFun_ = recvfun;
}

void CheckNetStateThread::run()
{
    QProcess *cmd = nullptr;
    if(nullptr == cmd)cmd = new QProcess();
    while(true){
        cmd->start(QString("ping ")+SERVER_IP);
        // 等待ping 的结果
        if (cmd->waitForFinished())
        {
            qDebug()<<"ping success!";
            _pobj->SetConnetState(true);
            //bIsConnect_ = true;
        }else{
            qDebug()<<"ping fail!";
            //bIsConnect_ = false;
            _pobj->SetConnetState(false);
        }

        sleep(100);
    }

}
