#ifndef QGCVIDEOVIEW_H
#define QGCVIDEOVIEW_H

#include <QWidget>
#include <QProcess>
#include <QCloseEvent>

namespace Ui {
class QGCVideoView;
}

class QGCVideoView : public QWidget
{
    Q_OBJECT

public:
    explicit QGCVideoView(QWidget *parent = 0);
    ~QGCVideoView();



private:
    Ui::QGCVideoView *ui;
    QProcess proc;

    void closeEvent(QCloseEvent *event);
};

#endif // QGCVIDEOVIEW_H
