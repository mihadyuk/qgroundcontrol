#include "qgcvideoview.h"
#include "ui_qgcvideoview.h"
#include <QDebug>


QGCVideoView::QGCVideoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCVideoView)
{
//    QString prog = "mplayer";
//    QStringList args;
//    args << "-wid" <<
//            QString::number((int)(this->winId())) <<
//            "/home/stepanenko/1234.mp4";

    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(elapsed()));


    //proc.start(prog ,args);

    timer->start(1000);


//    this->repaint();
//    this->update();
}

QGCVideoView::~QGCVideoView()
{
    delete ui;
    proc.waitForFinished();
}

void QGCVideoView::closeEvent(QCloseEvent *event){
    qDebug()<<"FINISHED";
    proc.kill();
    //this->deleteLater();
    event->ignore();

}

void QGCVideoView::mouseMoveEvent(QMouseEvent *event){
    event->ignore();
}

void QGCVideoView::elapsed(){
//    QString prog = "/home/stepanenko/PROJECTAS/mpv/mpv-build/mpv/build/mpv";
//    QStringList args;
//    args << "-wid" <<
//            QString::number((int)(this->winId())) <<
//            "/home/stepanenko/1234.mp4";

    QString prog = "/home/stepanenko/PROJECTAS/mpv/mpv-build/mpv/build/mpv";
    QStringList args;
    args << "-wid" <<
            QString::number((int)(this->winId())) <<
            "udp://127.0.0.1:1300";

    proc.start(prog ,args);
}
