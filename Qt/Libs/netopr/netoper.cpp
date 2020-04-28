#include "netoper.h"

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
        return false;
    }

    //QObject::connect(pSTcp_,SIGNAL(readyRead()),this,SLOT(ReadData()));
    QObject::connect(pSTcp_,&QTcpSocket::readyRead,this,&NetOper::ReadNetData);
    //QObject::connect(pSTcp_,&QTcpSocket::readyRead,this,&NetOper::DisConnected);
    qDebug()<<"Connect Succes";
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
