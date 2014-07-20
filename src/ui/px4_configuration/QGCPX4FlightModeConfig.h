#ifndef QGCPX4FLIGHTMODECONFIG_H
#define QGCPX4FLIGHTMODECONFIG_H

#include <QWidget>

namespace Ui {
class QGCPX4FlightModeConfig;
}

class QGCPX4FlightModeConfig : public QWidget
{
    Q_OBJECT

public:
    explicit QGCPX4FlightModeConfig(QWidget *parent = 0);
    ~QGCPX4FlightModeConfig();

private:
    Ui::QGCPX4FlightModeConfig *ui;
};

#endif // QGCPX4FLIGHTMODECONFIG_H
