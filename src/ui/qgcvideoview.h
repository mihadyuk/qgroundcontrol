#ifndef QGCVIDEOVIEW_H
#define QGCVIDEOVIEW_H

#include <QWidget>
#include <QProcess>
#include <QMenu>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolBar>


#include "smplayer/myactiongroup.h"
//#include "smplayer/mediadata.h"
#include "smplayer/mplayercore.h"
#include "smplayer/mplayerwindow.h"
#include "smplayer/preferences.h"
#include "smplayer/global.h"

namespace Ui {
class QGCVideoView;
}

class QGCVideoView : public QWidget
{
    Q_OBJECT

public:
    explicit QGCVideoView(MplayerWindow *wind, QWidget *parent = 0);
    ~QGCVideoView();

protected slots:
    void initializeMenus();
    void updateWidgets();

    void playVideo();

private:
    Ui::QGCVideoView *ui;
    //QProcess *proc;
    MplayerCore *core;
    MplayerWindow *videoWidget;

    MyActionGroup * videoTrackGroup;
//    MediaData * mdat;

    QVBoxLayout * mainLayout;
    QMenu *videotrack_menu;
    QVBoxLayout * videoLayout;
    //QToolBar * buttonToolBar;
    QHBoxLayout * buttonLayout;
    QPushButton * selectVideoButton;
    QPushButton * startVideoButton;

};

#endif // QGCVIDEOVIEW_H
