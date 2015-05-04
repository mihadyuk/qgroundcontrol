#ifndef QGCMULTIVIDEOVIEW_H
#define QGCMULTIVIDEOVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class QGCMultiVideoView;
}

class QGCMultiVideoView : public QWidget
{
    Q_OBJECT

public:
    explicit QGCMultiVideoView(QWidget *first, QWidget *second, QWidget *parent = 0);
    ~QGCMultiVideoView();

signals:
    void sendCommand(bool, int);

private:
    Ui::QGCMultiVideoView *ui;

    QVBoxLayout * mainLayout;
    QHBoxLayout * videoLayout;
    QHBoxLayout * buttonLayout;
    QPushButton * enableVideo1Button;
    QPushButton * disableVideo1Button;
    QPushButton * enableVideo2Button;
    QPushButton * disableVideo2Button;

    QWidget * first;
    QWidget * second;

private slots:
    void onEnableVideo1Clicked();
    void onDisableVideo1Clicked();
    void onEnableVideo2Clicked();
    void onDisableVideo2Clicked();

};

#endif // QGCMULTIVIDEOVIEW_H
