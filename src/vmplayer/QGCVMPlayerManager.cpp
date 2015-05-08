#include "QGCVMPlayerManager.h"

#include <zmq.h>

QGCVMPlayerManager::QGCVMPlayerManager(int firstwinid, int secondwinid, int thirdwinid, QObject *parent) : QObject(parent)
{

    firstWinID = firstwinid;
    secondWinID = secondwinid;
    thirdWinID = thirdwinid;

    zmq_context = zmq_ctx_new();

    zmq_command = zmq_socket(zmq_context, ZMQ_REQ);
    int rc = zmq_connect(zmq_command, "tcp://localhost:70000");
    if (rc != 0)
        qFatal("zmq_bind error %s", zmq_strerror(errno));


    QString program = VMPLAYER_PATH VMPLAYER_NAME;
    QStringList arguments;

    arguments << "-s" << "network" << "-u" << "10" <<
                 "-a" << QString::number(firstWinID) << "-1" << "4" <<
                 "-b" << QString::number(secondWinID) <<  "-2" << "5" <<
                 "-c" << QString::number(thirdWinID) << "-3" << "6";

    qDebug() << "win1 " << firstWinID << " win2 " << secondWinID << " win3 " << thirdWinID;

    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setWorkingDirectory(VMPLAYER_PATH);
    process->start(program, arguments);

    update();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

}

QGCVMPlayerManager::~QGCVMPlayerManager()
{

    zmq_close(zmq_command);
    zmq_ctx_destroy(zmq_context);

    timer->stop();

    if (process->state() != QProcess::NotRunning)
    {
        qDebug("terminating vmplayer");
        process->terminate();

        if (!process->waitForFinished(1000))
        {
            qDebug("killing vmplayer");
            process->kill();
        }
    }
    else
    {
        qDebug("vmplayer already terminated");
    }

}

void QGCVMPlayerManager::update()
{
    QTextStream out(stdout, QIODevice::WriteOnly);

    QByteArray data;

    data.append(process->readAll());

    if (data.length())
        out << data.data();
}

void QGCVMPlayerManager::sendCmd(bool start, int ch)
{
    QString str = QString("{ \"cmd\": \"%1\", \"channel\": %2 }")
            .arg(start ? "start" : "stop")
            .arg(ch);
    zmq_send(zmq_command, str.toLatin1().constData(), str.toLatin1().length(), 0);
    qDebug() << "Command: " << str;
    char buf[3];
    zmq_recv(zmq_command, buf, sizeof(buf), 0);
    qDebug() << "Answer: " << buf;
}

void QGCVMPlayerManager::sendCmdExit()
{
    QString str("{ \"cmd\": \"exit\" }");
    zmq_send(zmq_command, str.toLatin1().constData(), str.toLatin1().length(), 0);
    qDebug() << "Command: " << str;
    char buf[3];
    zmq_recv(zmq_command, buf, sizeof(buf), 0);
    qDebug() << "Answer: " << buf;
}

void QGCVMPlayerManager::setFirstWinID(int winid){
    firstWinID = winid;
}

void QGCVMPlayerManager::setSecondWinID(int winid){
    secondWinID = winid;
}

void QGCVMPlayerManager::setThirdWinID(int winid){
    thirdWinID = winid;
}

