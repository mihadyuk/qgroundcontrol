#include "qgcvideoview.h"
#include "ui_qgcvideoview.h"
#include <QDebug>

QGCVideoView::QGCVideoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCVideoView)
{
    QString prog = "mplayer";
    QStringList args;
    args << "-wid" <<
            QString::number((int)(this->winId())) <<
            "/home/stepanenko/1234.mp4";

    ui->setupUi(this);
    proc.start(prog ,args);
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
