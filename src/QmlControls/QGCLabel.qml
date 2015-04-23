import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import QGroundControl.Palette 1.0
import QGroundControl.ScreenTools 1.0

Text {
    QGCPalette { id: __qgcPal; colorGroupEnabled: enabled }
    property ScreenTools __screenTools: ScreenTools { }

    property bool enabled: true

    font.pointSize: __screenTools.defaultFontPointSize
    color:          __qgcPal.text
    antialiasing:   true
}
