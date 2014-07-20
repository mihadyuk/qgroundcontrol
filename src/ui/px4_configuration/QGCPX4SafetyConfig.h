#ifndef QGCPX4SAFETYCONFIG_H
#define QGCPX4SAFETYCONFIG_H

#include <QWidget>

namespace Ui {
class QGCPX4SafetyConfig;
}

class QGCPX4SafetyConfig : public QWidget
{
    Q_OBJECT

public:
    explicit QGCPX4SafetyConfig(QWidget *parent = 0);
    ~QGCPX4SafetyConfig();

private:
    Ui::QGCPX4SafetyConfig *ui;
};

#endif // QGCPX4SAFETYCONFIG_H
