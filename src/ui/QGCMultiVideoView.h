#ifndef QGCMULTIVIDEOVIEW_H
#define QGCMULTIVIDEOVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include <QMessageBox>

namespace Ui {
class QGCMultiVideoView;
}

class QGCMultiVideoView : public QWidget
{
    Q_OBJECT

public:
    explicit QGCMultiVideoView(/*QWidget *first, QWidget *second, */QWidget *parent = 0);
    ~QGCMultiVideoView();

    quint32 getFirstWinId();
    quint32 getSecondWinId();

public slots:
    void changeConnectState(bool state);
    void displayCommandException(QString title, QString text);

signals:
    void sendCommand(bool, int);
    void enableConnection(bool state);

private:
    Ui::QGCMultiVideoView *ui;

    QVBoxLayout * mainLayout;
    QHBoxLayout * videoLayout;
    QHBoxLayout * buttonLayout;
    QPushButton * enableVideo1Button;
    QPushButton * disableVideo1Button;
    QPushButton * enableVideo2Button;
    QPushButton * disableVideo2Button;

    QPushButton * connectButton;

    QWidget * first;
    QWidget * second;


    bool connectionEnabled;

private slots:
    void onEnableVideo1Clicked();
    void onDisableVideo1Clicked();
    void onEnableVideo2Clicked();
    void onDisableVideo2Clicked();
    void onConnectButtonClicked();

};

#endif // QGCMULTIVIDEOVIEW_H
