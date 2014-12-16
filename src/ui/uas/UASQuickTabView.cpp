#include "UASQuickTabView.h"
#include "ui_UASQuickTabView.h"
#include <QTextCodec>
#include <QDebug>
#include <QTableWidget>


UASQuickTabView::UASQuickTabView(QWidget *parent) :
    ui(new Ui::UASQuickTabView)
{
    ui->setupUi(this);

    QTextCodec* cyr = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(cyr);

//    tableWidget = new QTableWidget(this);
//    tableWidget->setColumnCount(2);
//    tableWidget->setRowCount(6);
//    tableWidget->setLineWidth(1);
//    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    tableWidget->verticalHeader()->setFixedSize(0,0);
//    tableWidget->horizontalHeader()->setFixedSize(0,0);
//    tableWidget->setStyleSheet("gridline-color : gray");

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setLineWidth(1);
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    ui->tableWidget->verticalHeader()->setFixedSize(0,0);
//    ui->tableWidget->horizontalHeader()->setFixedSize(0,0);
    ui->tableWidget->setStyleSheet("gridline-color : gray");

    //tableFont = new QFont("Times New Roman", 14, 3);
    tableFont.setFamily("Times New Roman");
    tableFont.setPixelSize(14);
    tableFont.setBold(3);


//    this->setColumnCount(2);
//    this->setRowCount(6);
//    this->setLineWidth(1);
//    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



//    model = new QStandardItemModel(6,2,this);
//    this->setModel(model);


    //this->verticalHeader()->setFixedSize(0,0);
    //this->horizontalHeader()->setFixedSize(0,0);

    ui->tableWidget->setStyleSheet("gridline-color : gray");

    QStringList nameList;// = new QStringList();
    nameList.append("Широта:");
    nameList.append("Долгота:");
    nameList.append("Высота:");
    nameList.append("Курс:");
    nameList.append("Крен:");
    nameList.append("Тангаж:");
//    for(int i = 0; i < nameList.size(); i++){
//        qDebug()<<nameList.at(i);
//    }
//    <<"Широта:"
//           <<"Долгота:"
//          <<"Высота:"
//         <<"Курс:"
//        <<"Крен:"
//       <<"Тангаж:";

    for(int i = 0; i < 6; i++){
        QTableWidgetItem* item = new QTableWidgetItem();
        Q_ASSERT(item);
        if (item) {
        item->setText(nameList.at(i));
        qDebug()<<"Text in item: "<<item->text();
        //qDebug()<<i;
        tableNameList.append(item);
        //qDebug()<<nameList.at(i);
        item->setFont(tableFont);
        //item->setSelected(true);
        ui->tableWidget->setItem(i, 0, item);
        qDebug()<<"Text in item in table: "<<ui->tableWidget->itemAt(i,0)->text();
        //qDebug()<<i;
        }


//        QStandardItem *item = new QStandardItem(nameList.at(i));
//        model->setItem(i,0,item);
//        model->set
//        item->set
//        item->setEditable(false);


    }

    //delete nameList;


    //setItemText(0,0,"Широта:");

//    this->item(0,0)->setText("Широта:");
//    this->item(1,0)->setText("Долгота:");
//    this->item(2,0)->setText("Высота:");

//    this->item(3,0)->setText("Курс:");
//    this->item(4,0)->setText("Крен:");
//    this->item(5,0)->setText("Тангаж:");


//    QGridLayout* gridLayout = new QGridLayout(this);
//    this->setLayout(gridLayout);
//    gridLayout->addWidget(tableWidget, 0, 0, -1, -1, Qt::AlignCenter);

    //this->setColumnWidth();
}

UASQuickTabView::~UASQuickTabView()
{
    delete ui;
    //delete tableFont;
    //delete model;
}

void UASQuickTabView::addSource(MAVLinkDecoder *decoder)
{
    connect(decoder,SIGNAL(valueChanged(int,QString,QString,QVariant,quint64)),this,SLOT(valueChanged(int,QString,QString,QVariant,quint64)));
}

void UASQuickTabView::valueChanged(const int uasId, const QString& name, const QString& unit, const QVariant &variant, const quint64 msec)
{
/*    Q_UNUSED(uasId);
    Q_UNUSED(unit);
    Q_UNUSED(msec);

    bool ok;
    double value = variant.toDouble(&ok);
    QMetaType::Type metaType = static_cast<QMetaType::Type>(variant.type());
    if(!ok || metaType == QMetaType::QString || metaType == QMetaType::QByteArray)
        return;
    //qDebug()<<name<<" "<<value;
    if (!uasPropertyValueMap.contains(name))
    {
        if (quickViewSelectDialog)
        {
            quickViewSelectDialog->addItem(name);
        }
    }
    if((name == "M24:GLOBAL_POSITION_INT.lat")||(name == "M24:GLOBAL_POSITION_INT.lon"))
        uasPropertyValueMap[name] = value/10000000;
    else if(name == "M24:GLOBAL_POSITION_INT.alt")
        uasPropertyValueMap[name] = value/1000;
    else if((name == "M24:ATTITUDE.roll")||(name == "M24:ATTITUDE.pitch")||(name == "M24:ATTITUDE.yaw"))
        uasPropertyValueMap[name] = value/M_PI*180;*/
}

void UASQuickTabView::setTableGeometry(){
    ui->tableWidget->setColumnWidth(0, (ui->tableWidget->width()-ui->tableWidget->verticalHeader()->width())/2);
    ui->tableWidget->setColumnWidth(1, (ui->tableWidget->width()-ui->tableWidget->verticalHeader()->width())/2);
    for(int i = 0; i < 6; i++){
        ui->tableWidget->setRowHeight(i, (ui->tableWidget->width()/*-this->horizontalHeader()->width()*/)/6);
    }

}

void UASQuickTabView::setItemText(int row, int column, QString text){
//    QTableWidgetItem* item = new QTableWidgetItem(text);
//    item->setText(text);
//    this->setItem(row, column, item);
}

void UASQuickTabView::resizeEvent(QResizeEvent *event){
    setTableGeometry();
}

