#ifndef QGCVMPLAYERMANAGER_H
#define QGCVMPLAYERMANAGER_H

#include <QObject>
#include <QTextStream>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QProcess>
#include <QTimer>
#include <QWidget>
//#include "QGCMessageBox.h"

//#include <zmq.h>

#include "ZmqSocket.h"
#include "ZmqMessage.h"


#define VMPLAYER_PATH "/home/stepanenko/vmplayer-dist/src/src/"
#define VMPLAYER_NAME "vmplayer"

#define REQUEST_TIMEOUT 2500

#define POLL_INTERVAL 10

class QGCVMPlayerManager : public QThread
{
    Q_OBJECT
public:
    explicit QGCVMPlayerManager(quint32 firstwinid, quint32 secondwinid, quint32 thirdwinid/*, QObject *parent = 0*/);
    //explicit QGCVMPlayerManager(QWidget *firstwinid, QWidget *secondwinid, QWidget *thirdwinid, QObject *parent = 0);
    ~QGCVMPlayerManager();

void setFirstWinID(int winid);
void setSecondWinID(int winid);
void setThirdWinID(int winid);


void run();


signals:
    void connectStateChanged(bool state);
    void commandException(QString title, QString text);


public slots:

    void parseCommand(bool start, int ch);

    void changeConnectState(bool state);

    bool sendCmd(bool start, int ch);

private:
    QProcess *process;
    QTimer *timer;
//    void *zmq_context;
//    void *zmq_command;

    ZmqSocket *socket;
///    QByteArray key;


    quint32 firstWinID;
    quint32 secondWinID;
    quint32 thirdWinID;



    bool zmqConnectState;//socket is connected
    bool p_stop;//variable for start/stop thread

    struct command{
        bool start;
        int channelNum;
        bool isValid;
    };

    command comStruct;

    QMutex comMutex;
    QMutex stopMutex;
    //QMutex comValidMutex;


    void clearCommand();

    //bool sendCmd(bool start, int ch);
    bool sendCmdExit();


private slots:
    void update();
    void onSocketAnswer();

};

#endif // QGCVMPLAYERMANAGER_H
