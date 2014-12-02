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
        QTableWidgetItem* item = new QTableWidgetItem();
        Q_ASSERT(item);
        if (item) {
			item->setText(nameList.at(i));
			qDebug()<<"Text in item: "<<item->text();
			tableNameList.append(item);
			item->setFont(tableFont);
			ui->tableWidget->setItem(i, 0, item);
			qDebug()<<"Text in item in table: "<<ui->tableWidget->itemAt(i,0)->text();
        }
    }
}

UASQuickTabView::~UASQuickTabView()
{
    delete ui;
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
    ui->gridLayout->setColumnMinimumWidth(0, (this->width() - 2));
    ui->gridLayout->setRowMinimumHeight(0, (this->height() - 2));
   // ui->gridLayout->setColumnStretch(0,);
    ui->tableWidget->setColumnWidth(0, (ui->gridLayout->columnMinimumWidth(0)/2));
    ui->tableWidget->setColumnWidth(1, (ui->gridLayout->columnMinimumWidth(0)/2));

    for(int i = 0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->setRowHeight(i, (ui->gridLayout->rowMinimumHeight(0))/6);
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

