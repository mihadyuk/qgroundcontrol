#ifndef QGCVIDEOVIEW_H
#define QGCVIDEOVIEW_H

#include <QWidget>
#include <QProcess>
#include <QCloseEvent>
#include <QMoveEvent>

#include <QTimer>

namespace Ui {
class QGCVideoView;
}

class QGCVideoView : public QWidget
{
    Q_OBJECT

public:
    explicit QGCVideoView(QWidget *parent = 0);
    ~QGCVideoView();

public slots:
    void elapsed();


private:
    Ui::QGCVideoView *ui;
    QProcess proc;
    QTimer *timer;

    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // QGCVIDEOVIEW_H
