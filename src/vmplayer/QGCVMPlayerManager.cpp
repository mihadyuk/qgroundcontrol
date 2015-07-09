#include "QGCVMPlayerManager.h"

//#include <zmq.h>

#include <QDebug>

//#include "QGCMessageBox.h"
#include <QMessageBox>

//#include "QGC.h"


//QGCVMPlayerManager::QGCVMPlayerManager(QWidget *firstwinid, QWidget *secondwinid, QWidget *thirdwinid, QObject *parent) : QObject(parent)
QGCVMPlayerManager::QGCVMPlayerManager(quint32 firstwinid, quint32 secondwinid, quint32 thirdwinid/*, QObject *parent*/)/* : QObject(parent)*/
{

//    firstWinID = (quint32)(firstwinid->winId());
//    secondWinID = (quint32)(secondwinid->winId());
//    thirdWinID = (quint32)(thirdwinid->winId());


    zmqConnectState = false;
    p_stop = false;
    clearCommand();

    firstWinID = firstwinid;
    secondWinID = secondwinid;
    thirdWinID = thirdwinid;

    qDebug()<<"WIN IDS: "<<firstWinID<<secondWinID<<thirdWinID;

//    zmq_context = zmq_ctx_new();

//    zmq_command = zmq_socket(zmq_context, ZMQ_REQ);

    socket = new ZmqSocket(ZMQ_REQ, this);


    connect(socket, &ZmqSocket::readyRead, this, &QGCVMPlayerManager::onSocketAnswer);




//    int linger = 0;
    //zmq_setsockopt(zmq_command, ZMQ_LINGER, &linger, sizeof(linger));
//    int rc = zmq_connect(zmq_command, "tcp://localhost:70000");
//    if (rc != 0)
//        qFatal("zmq_bind error %s", zmq_strerror(errno));



    QString program = VMPLAYER_PATH VMPLAYER_NAME;
    QStringList arguments;

    arguments << "-s" << "network" << "-u" << "10" <<
                 "-a" << QString::number(firstWinID) << "-1" << "4" <<
                 "-b" << QString::number(secondWinID) <<  "-2" << "5" <<
                 "-c" << QString::number(thirdWinID) << "-3" << "6";

    qDebug() << "win1 " << firstWinID << " win2 " << secondWinID << " win3 " << thirdWinID;

    moveToThread(this);

    process = new QProcess(/*this*/);
    //process->moveToThread(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setWorkingDirectory(VMPLAYER_PATH);

    process->start(program, arguments);

    update();

    timer = new QTimer(/*this*/);
    //timer->moveToThread(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setSingleShot(false);

    timer->start(100);

    qDebug()<<"VMPLAYERMANAGER CREATED"<<isRunning();

}

QGCVMPlayerManager::~QGCVMPlayerManager()
{    
    if(zmqConnectState == true)
        sendCmdExit();

    delete socket;
    //zmq_close(zmq_command);
    //zmq_ctx_destroy(zmq_context);

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

    if(isRunning()){
        stopMutex.lock();
        p_stop = true;
        stopMutex.unlock();
    }

    quit();
    wait();


//    terminate();
    delete process;
    delete timer;
    this->deleteLater();//?

}

void QGCVMPlayerManager::update()
{
//    QTextStream out(stdout, QIODevice::WriteOnly);

//    QByteArray data;

//    data.append(process->readAll());

//    if (data.length())
//        out << data.data();
}

bool QGCVMPlayerManager::sendCmd(bool start, int ch)
{
//    if(zmqConnectState == true){

//    }

//    zmq_pollitem_t item =  { zmq_command, 0, ZMQ_POLLIN, 0 };

    QString str = QString("{ \"cmd\": \"%1\", \"channel\": %2 }")
            .arg(start ? "start" : "stop")
            .arg(ch);

    socket->send(str.toLatin1().constData());

//    zmq_send(zmq_command, str.toLatin1().constData(), str.toLatin1().length(), 0);
    qDebug() << "Command: " << str;
    qDebug() << "Commandb: " << str.toLatin1().constData();
//    zmq_poll (&item, 1, REQUEST_TIMEOUT);


//    if (item.revents & ZMQ_POLLIN){

//        char buf[3];
//        zmq_recv(zmq_command, buf, sizeof(buf), 0);
//        //zmq_recv(zmq_command, buf, sizeof(buf), ZMQ_DONTWAIT);
//        qDebug() << "Answer: " << buf;
//        return true;

//    }
//    else return false;
    return true;
}

bool QGCVMPlayerManager::sendCmdExit()
{
//    zmq_pollitem_t item =  { zmq_command, 0, ZMQ_POLLIN, 0 };

    //QString str("{ \"cmd\": \"exit\" }");
    QByteArray ba = "{ \"cmd\": \"exit\" }";

    socket->send(ba);

 //   zmq_send(zmq_command, str.toLatin1().constData(), str.toLatin1().length(), 0);
    qDebug() << "Command: " << ba;

//    int resp = 0;
//    resp = zmq_poll (&item, 1, REQUEST_TIMEOUT);

//    if (item.revents & ZMQ_POLLIN){

//        char buf[3];
//        zmq_recv(zmq_command, buf, sizeof(buf), 0);
//        //zmq_recv(zmq_command, buf, sizeof(buf), ZMQ_DONTWAIT);
//        qDebug() << "Answer: " << buf;
//        return true;

//    }

//    else return false;
    return true;
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


void QGCVMPlayerManager::changeConnectState(bool state){


    qDebug()<<"CHANGING CONNECT STATE";
    //int rc;
    bool rc = false;
    if(state == true){

        if(isRunning() == false){

//            stopMutex.lock();

//            //connectState = true;
//            p_stop = false;
//            stopMutex.unlock();

//            rc = zmq_connect(zmq_command, "tcp://localhost:70000");
            rc = socket->connectTo("tcp://localhost:70000");
            if (!rc)
                qFatal("zmq_bind error"/* %s", zmq_strerror(errno)*/);
            else zmqConnectState = true;

            start(LowPriority);
            emit connectStateChanged(true);

        }

    }
    else if(state == false){

        if(isRunning() == true){
//            stopMutex.lock();
//            //connectState = false;
//            p_stop = true;
//            stopMutex.unlock();

            quit();
            wait();

//            terminate();

            rc = socket->disconnectOf("tcp://localhost:70000");
            if (!rc)
                qFatal("zmq_unbind error"/* %s", zmq_strerror(errno)*/);
            else zmqConnectState = false;

            clearCommand();
            emit connectStateChanged(false);
        }

    }
    qDebug()<<"CONNECT STATE CHANGED"<<!p_stop<<"isRunning"<<isRunning();

}

void QGCVMPlayerManager::onSocketAnswer(){
    QList<QByteArray> r = socket->recv();
    for(QList<QByteArray>::const_iterator i=r.constBegin(); i!=r.constEnd(); ++i) {
      qDebug() << "Received " << *i;
    }
}

void QGCVMPlayerManager::clearCommand(){
    comStruct.channelNum = 0;
    comStruct.start = false;
    comStruct.isValid = false;
}

void QGCVMPlayerManager::run(){

//    forever{

//        if (p_stop) {
//            stopMutex.lock();
//            p_stop = false;
//            stopMutex.unlock();
//            break; // exit the thread
//        }

//        if(comStruct.isValid == true){
//            comMutex.lock();

//            if(sendCmd(comStruct.start, comStruct.channelNum) == false){

//                emit commandException("Error", "Error while sending command.");

//            }
//            comStruct.isValid = false;

//            comMutex.unlock();

//        }

        exec();

        //msleep(POLL_INTERVAL);
        //QGC::SLEEP::msleep(POLL_INTERVAL);



     //   exec();
//        exit();
//        continue;
//    }

}

void QGCVMPlayerManager::parseCommand(bool start, int ch){

    if(comStruct.isValid == false){
        comMutex.lock();
        comStruct.start = start;
        comStruct.channelNum = ch;
        comStruct.isValid = true;
        comMutex.unlock();
    }
    //else QGCMessageBox::warning(/*(QObject*)this, */"Please wait", "Please wait for executing previous command");
    //else QMessageBox::warning(NULL, "Please wait", "Please wait for executing previous command");
    else emit commandException("Please wait", "Please wait for executing previous command");

}

//int main () {
//    zmq::context_t context (1);

//    zmq::socket_t * client = s_client_socket (context);

//    int sequence = 0;
//    int retries_left = REQUEST_RETRIES;

//    while (retries_left) {
//        std::stringstream request;
//        request << ++sequence;
//        s_send (*client, request.str());
//        sleep (1);

//        bool expect_reply = true;
//        while (expect_reply) {
//            //  Poll socket for a reply, with timeout
//            zmq::pollitem_t items[] = { { *client, 0, ZMQ_POLLIN, 0 } };
//            zmq::poll (&items[0], 1, REQUEST_TIMEOUT);

//            //  If we got a reply, process it
//            if (items[0].revents & ZMQ_POLLIN) {
//                //  We got a reply from the server, must match sequence
//                std::string reply = s_recv (*client);
//                if (atoi (reply.c_str ()) == sequence) {
//                    std::cout << "I: server replied OK (" << reply << ")" << std::endl;
//                    retries_left = REQUEST_RETRIES;
//                    expect_reply = false;
//                }
//                else {
//                    std::cout << "E: malformed reply from server: " << reply << std::endl;
//                }
//            }
//            else
//            if (--retries_left == 0) {
//                std::cout << "E: server seems to be offline, abandoning" << std::endl;
//                expect_reply = false;
//                break;
//            }
//            else {
//                std::cout << "W: no response from server, retrying…" << std::endl;
//                //  Old socket will be confused; close it and open a new one
//                delete client;
//                client = s_client_socket (context);
//                //  Send request again, on new socket
//                s_send (*client, request.str());
//            }
//        }
//    }
//    delete client;
//    return 0;
//}
