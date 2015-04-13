#include "qgcvideoview.h"
#include "ui_qgcvideoview.h"
#include "QDebug"

using namespace Global;

QGCVideoView::QGCVideoView(MplayerWindow * wind, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCVideoView)
{
    ui->setupUi(this);
    global_init(qApp->applicationDirPath());



    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    videoLayout = new QVBoxLayout(this);
    mainLayout->addLayout(videoLayout);

    buttonLayout = new QHBoxLayout(this);
    //ui->mainLayout->addWidget(buttonToolBar);


    mainLayout->addLayout(buttonLayout);
    //proc = new QProcess(this);
    videoWidget = wind;//new MplayerWindow(this);
    //videoWidget->setMinimumSize(600,300);
#if USE_COLORKEY
    videoWidget->setColorKey( pref->color_key );
#endif
    videoWidget->allowVideoMovement( pref->allow_video_movement );
    videoWidget->delayLeftClick(pref->delay_left_click);

    core = new Core(videoWidget, this);
    connect( core, SIGNAL(menusNeedInitialize()),
             this, SLOT(initializeMenus()) );
    connect( core, SIGNAL(widgetsNeedUpdate()),
             this, SLOT(updateWidgets()) );

    videoLayout->addWidget(videoWidget);

    startVideoButton = new QPushButton("Play", this);
    startVideoButton->setFixedSize(110, 30);
    buttonLayout->addWidget(startVideoButton);
    connect(startVideoButton, SIGNAL(clicked()), this, SLOT(playVideo()));

    selectVideoButton = new QPushButton("Select video", this);
    selectVideoButton->setFixedSize(110, 30);
    buttonLayout->addWidget(selectVideoButton);

    //core->openStream("udp://127.0.0.1:1300");

//    QString prog = "C:/Program Files (x86)/MPlayer for Windows/mplayer/mplayer";
//    QStringList args;
//    args << "-wid" <<
//            QString::number((int)(this->winId())) <<
//            "C:/Users/stepanenko/Desktop/cats.mpe";

    //QString prog = "mplayer";
    //QString prog = "/home/stepanenko/PROJECTAS/mpv/mpv-build/mpv/build/mpv";

    //QStringList args;
    //args.append("-wid");
    //args.append(QString::number((int)(videoWidget->winId())));
    //args.append("udp://127.0.0.1:1300");
    //qDebug()<<videoWidget->winId();
    //args << "-wid" << QString::number((int)(ui->videoWidget->winId())) << "udp://127.0.0.1:1300";




    //videotrack_menu = new QMenu();
    videotrack_menu = new QMenu(this);
    videotrack_menu->menuAction()->setObjectName("videotrack_menu");


    // Video track
    videoTrackGroup = new MyActionGroup(this);
    connect( videoTrackGroup, SIGNAL(activated(int)),
             core, SLOT(changeVideo(int)) );

    //proc->start(prog ,args);

    //select_video = new QPushButton(this);
    //select_video->setMenu( videotrack_menu );
    //toolbar2->addWidget(select_video);
    selectVideoButton->setMenu( videotrack_menu );

}

QGCVideoView::~QGCVideoView()
{
    delete ui;
    delete videoTrackGroup;
    delete videotrack_menu;

    if (core->state() != Core::Stopped) {
        core->stop();
    }

    delete core;
    global_end();
}

void QGCVideoView::initializeMenus(){

    videoTrackGroup->clear(true);
    if (core->mdat.videos.numItems()==0) {
        QAction * a = videoTrackGroup->addAction( tr("<empty>") );
        a->setEnabled(false);
    } else {
        for (int n=0; n < core->mdat.videos.numItems(); n++) {
            QAction *a = new QAction(videoTrackGroup);
            a->setCheckable(true);
            a->setText(core->mdat.videos.itemAt(n).displayName());
            a->setData(core->mdat.videos.itemAt(n).ID());
            qDebug()<<"VIDEO!!! : "<<a->text()<<" : "<<a->data();
        }
    }
    videotrack_menu->addActions( videoTrackGroup->actions() );
}

void QGCVideoView::updateWidgets(){
    // Video menu
    videoTrackGroup->setChecked( core->mset.current_video_id );
}


void QGCVideoView::playVideo(){
    core->openStream("udp://127.0.0.1:1300");
}
