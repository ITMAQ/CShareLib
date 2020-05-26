#ifndef NETOPER_H
#define NETOPER_H
#include <QTcpSocket>
#include <QProcess>
#include <QThread>

//#define SERVER_IP  "192.168.200.46"
#define SERVER_IP "211.162.72.65"
//#define SERVER_IP  "182.168.200.46"
#define SERVER_PORT 6065
#define CONNECT_TIME_OUT 6

// 处理接收的数据
typedef void (*DEALRECVDATA)(QString);
class CheckNetStateThread;
class NetOper:public QObject
{
    Q_OBJECT

    friend CheckNetStateThread;
private:
    NetOper(){};

public:
    ~NetOper(){
        if(pSTcp_->isOpen()){
            pSTcp_->disconnect();
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


public:
    // 注册接收数据的回调函数
    void RegisterRecvFun(DEALRECVDATA recvfun);
    bool Connect(QString ip = SERVER_IP,int uPort = SERVER_PORT);
    void SendData(QString &data);
    bool isConnected(){return bIsConnect_;}


    // 设置Connect的状态
    bool SetConnetState(bool bIsconnect){
        if(!bIsconnect){
            pSTcp_->disconnect();
            pSTcp_->close();
        }
        bIsConnect_ = bIsconnect;
    }

private slots:
    void ReadNetData();
    //void onNetConnectCheck();

private:
    QTcpSocket *pSTcp_ = nullptr;
    DEALRECVDATA pRecvDataFun_ = nullptr;
    bool bIsConnect_ = false;

public:

    static NetOper *_pThis;
};

// 初始化提交数据到网络
class CheckNetStateThread:public QThread{
    Q_OBJECT
public:
    CheckNetStateThread(NetOper *pData){_pobj = pData;}
private:
    void run() override;
protected:

private:
    NetOper *_pobj;
};

#endif // NETOPER_H
