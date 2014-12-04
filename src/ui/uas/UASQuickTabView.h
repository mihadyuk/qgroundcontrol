#ifndef UASQUICKTABVIEW_H
#define UASQUICKTABVIEW_H

#include <QTableWidget>
#include <QStandardItemModel>
#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include <QFont>
#include "MAVLinkDecoder.h"

namespace Ui {
class UASQuickTabView;
}

class UASQuickTabView : public QWidget
{
    Q_OBJECT

public:
    explicit UASQuickTabView(QWidget *parent = 0);
    ~UASQuickTabView();
    void addSource(MAVLinkDecoder *decoder);

private:
    Ui::UASQuickTabView *ui;
    /** Timer for updating the UI */
    QTimer *updateTimer;

//    QTimer *testTimer;
//    bool testTimerValue;

    QFont tableFont;

    //QTableWidget* tableWidget;
    void setTableGeometry();
    void resizeEvent(QResizeEvent *event);
    QString formText(QString name, double value);

//    QStandardItemModel* model;
    QList<QTableWidgetItem*> tableNameList;
    QList<QTableWidgetItem*> tableValueList;
    QStringList fieldNameList;

    /** Maps from the property name to the current value */
    QMap<QString,double> uasPropertyValueMap;

public slots:
    void valueChanged(const int uasid, const QString& name, const QString& unit, const QVariant& value,const quint64 msecs);
    void updateTimerTick();
    //void testTimerExpired();
};

#endif // UASQUICKTABVIEW_H
