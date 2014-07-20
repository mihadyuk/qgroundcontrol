#include "QGCPX4TuningConfig.h"
#include "ui_QGCPX4TuningConfig.h"

QGCPX4TuningConfig::QGCPX4TuningConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCPX4TuningConfig)
{
    ui->setupUi(this);
}

QGCPX4TuningConfig::~QGCPX4TuningConfig()
{
    delete ui;
}
