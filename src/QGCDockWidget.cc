/*=====================================================================
 
 QGroundControl Open Source Ground Control Station
 
 (c) 2009 - 2014 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 
 This file is part of the QGROUNDCONTROL project
 
 QGROUNDCONTROL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 QGROUNDCONTROL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
 
 ======================================================================*/

#include "QGCDockWidget.h"

#include <QCloseEvent>
#include <QDebug>

QGCDockWidget::QGCDockWidget(const QString& title, QWidget *parent, Qt::WindowFlags flags) :
    QDockWidget(title, parent, flags)
{
    
}

// Instead of destroying the widget just hide it
void QGCDockWidget::closeEvent(QCloseEvent* event)
{
    qDebug()<<this->widget()->metaObject()->className();
    if(QString(this->widget()->metaObject()->className()) == "QGCVideoView")
    {
        this->widget()->close();
    }
    setVisible(false);
    event->ignore();
    emit hided(this);
}
