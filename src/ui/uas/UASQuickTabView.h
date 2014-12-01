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

    QFont tableFont;

    //QTableWidget* tableWidget;
    void setTableGeometry();
    void resizeEvent(QResizeEvent *event);
    void setItemText(int row, int column, QString text);

//    QStandardItemModel* model;
    QList<QTableWidgetItem*> tableNameList;
    QList<QTableWidgetItem*> tableValueList;

public slots:
    void valueChanged(const int uasid, const QString& name, const QString& unit, const QVariant& value,const quint64 msecs);
    //void updateTimerTick();
};

#endif // UASQUICKTABVIEW_H
