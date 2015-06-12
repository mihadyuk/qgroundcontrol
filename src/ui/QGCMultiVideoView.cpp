#include "QGCMultiVideoView.h"
#include "ui_QGCMultiVideoView.h"
#include <QDebug>

QGCMultiVideoView::QGCMultiVideoView(/*QWidget *first, QWidget *second, */QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCMultiVideoView)
{
    ui->setupUi(this);

    connectionEnabled = false;

    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    first = new QWidget(this);
    second = new QWidget(this);

    videoLayout = new QHBoxLayout(this);
    videoLayout->addWidget(first);
    videoLayout->addWidget(second);

    mainLayout->addLayout(videoLayout);

    buttonLayout = new QHBoxLayout(this);

    connectButton = new QPushButton("Connect", this);
    connectButton->setFixedSize(100, 30);
    connect(connectButton, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));

    enableVideo1Button = new QPushButton("Video1 On", this);
    enableVideo1Button->setFixedSize(100, 30);
    connect(enableVideo1Button, SIGNAL(clicked()), this, SLOT(onEnableVideo1Clicked()));

    disableVideo1Button = new QPushButton("Video1 Off", this);
    disableVideo1Button->setFixedSize(100, 30);
    connect(disableVideo1Button, SIGNAL(clicked()), this, SLOT(onDisableVideo1Clicked()));

    enableVideo2Button = new QPushButton("Video2 On", this);
    enableVideo2Button->setFixedSize(100, 30);
    connect(enableVideo2Button, SIGNAL(clicked()), this, SLOT(onEnableVideo2Clicked()));


    disableVideo2Button = new QPushButton("Video2 Off", this);
    disableVideo2Button->setFixedSize(100, 30);
    connect(disableVideo2Button, SIGNAL(clicked()), this, SLOT(onDisableVideo2Clicked()));

    buttonLayout->addWidget(connectButton);
    buttonLayout->addWidget(enableVideo1Button);
    buttonLayout->addWidget(disableVideo1Button);
    buttonLayout->addWidget(enableVideo2Button);
    buttonLayout->addWidget(disableVideo2Button);

    mainLayout->addLayout(buttonLayout);

}

void QGCMultiVideoView::onEnableVideo1Clicked(){
    emit sendCommand(true, 1);
}

void QGCMultiVideoView::onDisableVideo1Clicked(){
    emit sendCommand(false, 1);
}

void QGCMultiVideoView::onEnableVideo2Clicked(){
    emit sendCommand(true, 2);
}

void QGCMultiVideoView::onDisableVideo2Clicked(){
    emit sendCommand(false, 2);
}


void QGCMultiVideoView::onConnectButtonClicked(){
    if(connectionEnabled == false)
        emit enableConnection(true);
    else emit enableConnection(false);
    qDebug()<<"ENABLE CONNECTION EMITTED";
}

void QGCMultiVideoView::changeConnectState(bool state){

    connectionEnabled = state;
    if(connectionEnabled == true){
        connectButton->setText("Disconnect");
    }
    else connectButton->setText("Connect");
    connectButton->repaint();
    qDebug()<<"CONNECT STATE CHANGED"<<connectionEnabled;
}

void QGCMultiVideoView::displayCommandException(QString title, QString text){
    QMessageBox::warning(this, title, text);
}


quint32 QGCMultiVideoView::getFirstWinId(){
    return (quint32)first->winId();
}

quint32 QGCMultiVideoView::getSecondWinId(){
    return (quint32)second->winId();
}

QGCMultiVideoView::~QGCMultiVideoView()
{
    delete ui;
}
