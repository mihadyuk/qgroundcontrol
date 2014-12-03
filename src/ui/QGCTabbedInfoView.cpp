#include "QGCTabbedInfoView.h"

QGCTabbedInfoView::QGCTabbedInfoView(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    messageView = new QGCMessageView(this);
    //actionsWidget = new UASActionsWidget(this);

    quicktabView = new UASQuickTabView(this);
    ui.tabWidget->addTab(quicktabView,tr("QuickTab"));

    quickView = new UASQuickView(this);
    //rawView = new UASRawStatusView(this);
    ui.tabWidget->addTab(quickView,tr("Quick"));
    //ui.tabWidget->addTab(actionsWidget,"Actions");
    //ui.tabWidget->addTab(rawView,"Status");
    ui.tabWidget->addTab(messageView,tr("Messages"));
}
void QGCTabbedInfoView::addSource(MAVLinkDecoder *decoder)
{
    m_decoder = decoder;
    //rawView->addSource(decoder);
    quickView->addSource(decoder);
    quicktabView->addSource(decoder);
}

QGCTabbedInfoView::~QGCTabbedInfoView()
{
}
