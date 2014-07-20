#ifndef QGCPX4TUNINGCONFIG_H
#define QGCPX4TUNINGCONFIG_H

#include <QWidget>

namespace Ui {
class QGCPX4TuningConfig;
}

class QGCPX4TuningConfig : public QWidget
{
    Q_OBJECT

public:
    explicit QGCPX4TuningConfig(QWidget *parent = 0);
    ~QGCPX4TuningConfig();

private:
    Ui::QGCPX4TuningConfig *ui;
};

#endif // QGCPX4TUNINGCONFIG_H
