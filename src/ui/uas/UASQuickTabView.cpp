#include "UASQuickTabView.h"
#include "ui_UASQuickTabView.h"
#include <QTextCodec>
#include <QDebug>
#include <QTableWidget>


UASQuickTabView::UASQuickTabView(QWidget *parent) :
    ui(new Ui::UASQuickTabView)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);

	QStringList nameList;// = new QStringList();
	nameList.append("Широта:");
	nameList.append("Долгота:");
	nameList.append("Высота:");
	nameList.append("Курс:");
	nameList.append("Крен:");
	nameList.append("Тангаж:");

    fieldNameList << "M24:GLOBAL_POSITION_INT.lat"
                  << "M24:GLOBAL_POSITION_INT.lon"
                  << "M24:GLOBAL_POSITION_INT.alt"
                  << "M24:ATTITUDE.roll"
                  << "M24:ATTITUDE.pitch"
                  << "M24:ATTITUDE.yaw";

    foreach(QString str, fieldNameList){
        uasPropertyValueMap.insert(str, 0.0);
    }

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setLineWidth(1);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableWidget->setStyleSheet("gridline-color : gray");

    //tableFont = new QFont("Times New Roman", 14, 3);
    tableFont.setFamily("Times New Roman");
    tableFont.setPixelSize(14);
    tableFont.setBold(3);

    for(int i = 0; i < nameList.count(); i++) {
        /* Add first column that shows lable names.*/
        QTableWidgetItem* item = new QTableWidgetItem();
        Q_ASSERT(item);
        if (item) {
            item->setText(nameList.at(i));
            tableNameList.append(item);
            item->setFont(tableFont);
            ui->tableWidget->setItem(i, 0, item);
        }

        /* Add column with values.*/
        item = new QTableWidgetItem();
        Q_ASSERT(item);
        if (item) {
            tableValueList.append(item);
            item->setFont(tableFont);
            item->setText("0.0");
            ui->tableWidget->setItem(i, 1, item);
        }
    }

    updateTimer = new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateTimerTick()));
    updateTimer->start(1000);

//    testTimerValue = true;
//    testTimer = new QTimer(this);
//    testTimer->setSingleShot(false);
//    connect(testTimer,SIGNAL(timeout()),this,SLOT(testTimerExpired()));
//    testTimer->start(750);

}

UASQuickTabView::~UASQuickTabView()
{
    delete ui;
    foreach (QTableWidgetItem* item, tableNameList) {
        delete item;
    }
    foreach (QTableWidgetItem* item, tableValueList) {
        delete item;
    }
    delete updateTimer;
}

void UASQuickTabView::addSource(MAVLinkDecoder *decoder)
{
    connect(decoder,SIGNAL(valueChanged(int,QString,QString,QVariant,quint64)),this,SLOT(valueChanged(int,QString,QString,QVariant,quint64)));
}

void UASQuickTabView::valueChanged(const int uasId, const QString& name, const QString& unit, const QVariant &variant, const quint64 msec)
{
    Q_UNUSED(uasId);
    Q_UNUSED(unit);
    Q_UNUSED(msec);

    bool ok;
    double value = variant.toDouble(&ok);
    QMetaType::Type metaType = static_cast<QMetaType::Type>(variant.type());
    if(!ok || metaType == QMetaType::QString || metaType == QMetaType::QByteArray)
        return;
    //qDebug()<<name<<" "<<value;
//    if (!uasPropertyValueMap.contains(name))
//    {
//        if (quickViewSelectDialog)
//        {
//            quickViewSelectDialog->addItem(name);
//        }
//    }

    if((name == "M24:GLOBAL_POSITION_INT.lat")||(name == "M24:GLOBAL_POSITION_INT.lon"))
        uasPropertyValueMap[name] = value/10000000;
    else if(name == "M24:GLOBAL_POSITION_INT.alt")
        uasPropertyValueMap[name] = value/1000;
    else if((name == "M24:ATTITUDE.roll")||(name == "M24:ATTITUDE.pitch")||(name == "M24:ATTITUDE.yaw"))
        uasPropertyValueMap[name] = value/M_PI*180;
}

void UASQuickTabView::updateTimerTick()
{
    for(int i = 0; i < fieldNameList.size(); i++){
        //QString str = QString::number(uasPropertyValueMap[fieldNameList.at(i)]);
        QString str = formText(fieldNameList.at(i), uasPropertyValueMap[fieldNameList.at(i)]);
        ui->tableWidget->item(i,1)->setText(str);
    }
}

//void UASQuickTabView::testTimerExpired(){
//    if(testTimerValue == true){
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.lat","unit",538893530,0);
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.lon","unit",275296780,0);
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.alt","unit",272000,0);
//        valueChanged(0,"M24:ATTITUDE.roll","unit",0.36814,0);
//        valueChanged(0,"M24:ATTITUDE.pitch","unit",0.56715,0);
//        valueChanged(0,"M24:ATTITUDE.yaw","unit",0.24715,0);
//        testTimerValue = false;
//    }
//    else{
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.lat","unit",549993530,0);
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.lon","unit",277796780,0);
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.alt","unit",284000,0);
//        valueChanged(0,"M24:ATTITUDE.roll","unit",0.35614,0);
//        valueChanged(0,"M24:ATTITUDE.pitch","unit",0.46815,0);
//        valueChanged(0,"M24:ATTITUDE.yaw","unit",0.67895,0);
//        testTimerValue = true;
//    }
//}

void UASQuickTabView::setTableGeometry(){

    ui->tableWidget->setColumnWidth(0, ((this->width() - 5)/2));
    ui->tableWidget->setColumnWidth(1, ((this->width())/2));

    for(int i = 0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->setRowHeight(i, (this->height() - 2)/6);
        //qDebug()<<"qgridrowminimumheight: "<<ui->gridLayout->rowMinimumHeight(0);
    }

}

QString UASQuickTabView::formText(QString name, double value){

    QString str;

    if(name == "M24:GLOBAL_POSITION_INT.lat"){
        str = QString::number(value,'f',5);
        str += 0x00B0;
        str +="с.ш.";
    }
    else if(name == "M24:GLOBAL_POSITION_INT.lon"){
        str = QString::number(value,'f',5);
        str += 0x00B0;
        str +="в.д.";
    }
    else if(name == "M24:GLOBAL_POSITION_INT.alt"){
        str = QString::number(value,'f',1);
        str +="м.";
    }
    else if((name == "M24:ATTITUDE.roll")||(name == "M24:ATTITUDE.pitch")||(name == "M24:ATTITUDE.yaw")){
        str = QString::number(value,'f',2);
        str += 0x00B0;
    }
    return str;
}

void UASQuickTabView::resizeEvent(QResizeEvent *event){
    setTableGeometry();
}

