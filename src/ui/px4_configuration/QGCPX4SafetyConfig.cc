#include "QGCPX4SafetyConfig.h"
#include "ui_QGCPX4SafetyConfig.h"

QGCPX4SafetyConfig::QGCPX4SafetyConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGCPX4SafetyConfig)
{
    ui->setupUi(this);
}

QGCPX4SafetyConfig::~QGCPX4SafetyConfig()
{
    delete ui;
}
