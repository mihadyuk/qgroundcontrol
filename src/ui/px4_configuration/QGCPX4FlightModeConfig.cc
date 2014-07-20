#include "QGCPX4FlightModeConfig.h"
#include "ui_QGCPX4FlightModeConfig.h"

QGCPX4FlightModeConfig::QGCPX4FlightModeConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCPX4FlightModeConfig)
{
    ui->setupUi(this);
}

QGCPX4FlightModeConfig::~QGCPX4FlightModeConfig()
{
    delete ui;
}
