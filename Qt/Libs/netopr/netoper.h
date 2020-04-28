#ifndef NETOPER_H
#define NETOPER_H
#include <QTcpSocket>

#define SERVER_IP  "192.168.200.46"
//#define SERVER_IP "211.162.72.65"
#define SERVER_PORT 6065
#define CONNECT_TIME_OUT 30000

// 处理接收的数据
typedef void (*DEALRECVDATA)(QString);
class NetOper:public QObject
{
    Q_OBJECT

private:
    NetOper(){};

public:
    ~NetOper(){
        if(pSTcp_->isOpen()){
            pSTcp_->close();
        }
    }

public:
    // 唯一实例
    static NetOper *Instance(){
        if(_pThis == nullptr){
            _pThis = new NetOper();
        }

        return _pThis;
    }

    // 删除唯一实例子



public:
    // 注册接收数据的回调函数
    void RegisterRecvFun(DEALRECVDATA recvfun);
    bool Connect(QString ip = SERVER_IP,int uPort = SERVER_PORT);
    void SendData(QString &data);

private slots:
    void ReadNetData();

private:
    QTcpSocket *pSTcp_ = nullptr;
    DEALRECVDATA pRecvDataFun_ = nullptr;

public:

    static NetOper *_pThis;
};

#endif // NETOPER_H
