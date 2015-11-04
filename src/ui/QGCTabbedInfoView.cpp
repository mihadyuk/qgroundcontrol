#include "QGCTabbedInfoView.h"
#include "QGCApplication.h"

QGCTabbedInfoView::QGCTabbedInfoView(const QString& title, QAction* action, QWidget *parent)
    : QGCDockWidget(title, action, parent)
{
    ui.setupUi(this);
    messageView = new UASMessageViewWidget(qgcApp()->toolbox()->uasMessageHandler(), this);
    //actionsWidget = new UASActionsWidget(this);

    quicktabView = new UASQuickTabView(this);
    ui.tabWidget->addTab(quicktabView,tr("QuickTab"));

    quickView = new UASQuickView(this);
    //rawView = new UASRawStatusView(this);
    ui.tabWidget->addTab(quickView,tr("Quick"));
    //ui.tabWidget->addTab(actionsWidget,"Actions");
    //ui.tabWidget->addTab(rawView,"Status");
    ui.tabWidget->addTab(messageView,tr("Messages"));
    
    loadSettings();
}
void QGCTabbedInfoView::addSource(MAVLinkDecoder *decoder)
{
    m_decoder = decoder;
    quickView->addSource(decoder);
    quicktabView->addSource(decoder);
}

QGCTabbedInfoView::~QGCTabbedInfoView()
{
}
