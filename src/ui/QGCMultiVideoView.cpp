#include "QGCMultiVideoView.h"
#include "ui_QGCMultiVideoView.h"

QGCMultiVideoView::QGCMultiVideoView(QWidget *first, QWidget *second, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCMultiVideoView)
{
    ui->setupUi(this);

    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

//    first = new QWidget(this);
//    second = new QWidget(this);

    videoLayout = new QHBoxLayout(this);
    videoLayout->addWidget(first);
    videoLayout->addWidget(second);

    mainLayout->addLayout(videoLayout);

    buttonLayout = new QHBoxLayout(this);

    enableVideo1Button = new QPushButton("Video1 On", this);
    enableVideo1Button->setFixedSize(110, 30);
    connect(enableVideo1Button, SIGNAL(clicked()), this, SLOT(onEnableVideo1Clicked()));

    disableVideo1Button = new QPushButton("Video1 Off", this);
    disableVideo1Button->setFixedSize(110, 30);
    connect(disableVideo1Button, SIGNAL(clicked()), this, SLOT(onDisableVideo1Clicked()));

    enableVideo2Button = new QPushButton("Video2 On", this);
    enableVideo2Button->setFixedSize(110, 30);
    connect(enableVideo2Button, SIGNAL(clicked()), this, SLOT(onEnableVideo2Clicked()));


    disableVideo2Button = new QPushButton("Video2 Off", this);
    disableVideo2Button->setFixedSize(110, 30);
    connect(disableVideo2Button, SIGNAL(clicked()), this, SLOT(onDisableVideo2Clicked()));

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

QGCMultiVideoView::~QGCMultiVideoView()
{
    delete ui;
}
