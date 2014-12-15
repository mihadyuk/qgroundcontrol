#include "UASQuickTabView.h"
#include "ui_UASQuickTabView.h"
#include <QTextCodec>
#include <QDebug>
#include <QTableWidget>
#include <QtGui>


UASQuickTabView::UASQuickTabView(QWidget *parent) :
    ui(new Ui::UASQuickTabView)
{
    ui->setupUi(this);
//    this->setLayout(ui->gridLayout);
//    ui->gridLayout->setContentsMargins(0,0,0,0);
//    ui->gridLayout->setHorizontalSpacing(0);
//    ui->gridLayout->setVerticalSpacing(0);
//    ui->gridLayout->setSpacing(0);
//    ui->gridLayout->setMargin(0);






	QStringList nameList;// = new QStringList();
//	nameList.append("Широта:");
//	nameList.append("Долгота:");
//	nameList.append("Высота:");
//	nameList.append("Курс:");
//	nameList.append("Крен:");
//	nameList.append("Тангаж:");

    nameList.append(tr("Latitude:"));
    nameList.append(tr("Longitude:"));
    nameList.append(tr("Altitude:"));
    nameList.append(tr("Roll:"));
    nameList.append(tr("Pitch:"));
    nameList.append(tr("Yaw:"));

    fieldNameList << "M20:GLOBAL_POSITION_INT.lat"
                  << "M20:GLOBAL_POSITION_INT.lon"
                  << "M20:GLOBAL_POSITION_INT.alt"
                  << "M20:ATTITUDE.roll"
                  << "M20:ATTITUDE.pitch"
                  << "M20:ATTITUDE.yaw";

    foreach(QString str, fieldNameList){
        uasPropertyValueMap.insert(str, 0.0);
    }

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(nameList.count());
    ui->tableWidget->setLineWidth(1);
    ui->tableWidget->setFrameStyle(QFrame::NoFrame);
    //ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableWidget->setStyleSheet("gridline-color : dimgray");
    ui->tableWidget->setWindowFlags(/*ui->tableWidget->windowFlags()*/Qt::Widget | Qt::FramelessWindowHint);




    //tableFont = new QFont("Times New Roman", 14, 3);
//    tableFont.setFamily("Times New Roman");
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
            item->setFlags(item->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
            ui->tableWidget->setItem(i, 0, item);
        }

        /* Add column with values.*/
        item = new QTableWidgetItem();
        Q_ASSERT(item);
        if (item) {
            tableValueList.append(item);
            item->setFont(tableFont);
            item->setText("0.0");
            item->setFlags(item->flags() ^ Qt::ItemIsEditable ^ Qt::ItemIsSelectable);
            ui->tableWidget->setItem(i, 1, item);
        }
    }

    setTableGeometry();

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

    if((name == "M20:GLOBAL_POSITION_INT.lat")||(name == "M20:GLOBAL_POSITION_INT.lon"))
        uasPropertyValueMap[name] = value/10000000;
    else if(name == "M20:GLOBAL_POSITION_INT.alt")
        uasPropertyValueMap[name] = value/1000;
    else if((name == "M20:ATTITUDE.roll")||(name == "M20:ATTITUDE.pitch")||(name == "M20:ATTITUDE.yaw"))
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
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.lat","unit",-549993530,0);
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.lon","unit",-277796780,0);
//        valueChanged(0,"M24:GLOBAL_POSITION_INT.alt","unit",284000,0);
//        valueChanged(0,"M24:ATTITUDE.roll","unit",0.35614,0);
//        valueChanged(0,"M24:ATTITUDE.pitch","unit",0.46815,0);
//        valueChanged(0,"M24:ATTITUDE.yaw","unit",0.67895,0);
//        testTimerValue = true;
//    }
//}

void UASQuickTabView::setTableGeometry(){

    ui->tableWidget->resize(this->width(), this->height());

    ui->tableWidget->setColumnWidth(0, ((ui->tableWidget->width())/2));
    ui->tableWidget->setColumnWidth(1, ((ui->tableWidget->width())/2 + (ui->tableWidget->width())%2));

    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0; i < rowCount - 1; i++) {

        ui->tableWidget->setRowHeight(i, (ui->tableWidget->height()) / rowCount);
        //ui->tableWidget->setRowHeight(i, (ui->tableWidget->height())/6);
    }
    ui->tableWidget->setRowHeight(rowCount - 1, ((ui->tableWidget->height()) / rowCount) + ((ui->tableWidget->height()) % rowCount));
}

QString UASQuickTabView::formText(QString name, double value){

    QString str;

    if(name == "M20:GLOBAL_POSITION_INT.lat"){
        if(value >= 0){
            str = QString::number(value,'f',5);
            str += 0x00B0;
             str += tr(" N");
        }
        else if(value < 0){
            value *=-1;
            str = QString::number(value,'f',5);
            str += 0x00B0;
            str += tr(" S");
        }
    }

    else if(name == "M20:GLOBAL_POSITION_INT.lon"){
        if(value >= 0){
            str = QString::number(value,'f',5);
            str += 0x00B0;
             str += tr(" E");
        }
        else if(value < 0){
            value *=-1;
            str = QString::number(value,'f',5);
            str += 0x00B0;
            str += tr(" W");
        }
    }

    else if(name == "M20:GLOBAL_POSITION_INT.alt"){
        str = QString::number(value,'f',1);
        str +=tr(" m.");
    }
    else if((name == "M20:ATTITUDE.roll")||(name == "M20:ATTITUDE.pitch")||(name == "M20:ATTITUDE.yaw")){
        str = QString::number(value,'f',2);
        str += 0x00B0;
    }
    return str;
}

void UASQuickTabView::resizeEvent(QResizeEvent *event){
    setTableGeometry();
}

