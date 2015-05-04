#ifndef QGCVMPLAYERMANAGER_H
#define QGCVMPLAYERMANAGER_H

#include <QObject>
#include <QTextStream>
#include <QDebug>
#include <QProcess>
#include <QTimer>

//#include <zmq.h>

#define VMPLAYER_PATH "/home/stepanenko/vmplayer-dist/src/src/"
#define VMPLAYER_NAME "vmplayer"

class QGCVMPlayerManager : public QObject
{
    Q_OBJECT
public:
    explicit QGCVMPlayerManager(int firstwinid, int secondwinid, int thirdwinid, QObject *parent = 0);
    ~QGCVMPlayerManager();

void setFirstWinID(int winid);
void setSecondWinID(int winid);
void setThirdWinID(int winid);

signals:

public slots:
    void sendCmd(bool start, int ch);
    void sendCmdExit();

private:
    QProcess *process;
    QTimer *timer;
    void *zmq_context;
    void *zmq_command;

    int firstWinID;
    int secondWinID;
    int thirdWinID;


private slots:
    void update();
};

#endif // QGCVMPLAYERMANAGER_H
