/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

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

/**
 * @file
 *   @brief Definition of class MainWindow
 *   @author Lorenz Meier <mavteam@student.ethz.ch>
 *
 */

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QStatusBar>
#include <QStackedWidget>
#include <QSettings>
#include <qlist.h>

#include "ui_MainWindow.h"
#include "LinkManager.h"
#include "LinkInterface.h"
#include "UASInterface.h"
#include "UASManager.h"
#include "UASControlWidget.h"
#include "UASInfoWidget.h"
#include "WaypointList.h"
#include "CameraView.h"
#include "UASListWidget.h"
#include "MAVLinkSimulationLink.h"
#include "input/JoystickInput.h"
#if (defined QGC_MOUSE_ENABLED_WIN) | (defined QGC_MOUSE_ENABLED_LINUX)
#include "Mouse6dofInput.h"
#endif // QGC_MOUSE_ENABLED_WIN
#include "DebugConsole.h"
#include "ParameterInterface.h"
#include "HDDisplay.h"
#include "HSIDisplay.h"
#include "opmapcontrol.h"
#ifdef QGC_GOOGLE_EARTH_ENABLED
#include "QGCGoogleEarthView.h"
#endif
#include "MainToolBar.h"
#include "QGCToolBar.h"
#include "LogCompressor.h"

#include "QGCMAVLinkInspector.h"
#include "QGCMAVLinkLogPlayer.h"
#include "MAVLinkDecoder.h"
#include "QGCUASFileViewMulti.h"
#include "QGCFlightGearLink.h"
#include "QGCToolWidget.h"

class QGCMapTool;
class QGCMAVLinkMessageSender;
class QGCFirmwareUpdate;
class QSplashScreen;
class QGCStatusBar;
class Linecharts;
class QGCDataPlot2D;
class QGCUASFileViewMulti;

/**
 * @brief Main Application Window
 *
 **/
class MainWindow : public QMainWindow
{
    friend class MainToolBar;
    Q_OBJECT

public:
    /// @brief Returns the MainWindow singleton. Will not create the MainWindow if it has not already
    ///         been created.
    static MainWindow* instance(void);

    /// @brief Deletes the MainWindow singleton
    void deleteInstance(void);

    /// @brief Creates the MainWindow singleton. Should only be called once by QGCApplication.
    static MainWindow* _create(QSplashScreen* splashScreen);

    /// @brief Called to indicate that splash screen is no longer being displayed.
    void splashScreenFinished(void) { _splashScreen = NULL; }

    ~MainWindow();


    /** @brief Get auto link reconnect setting */
    bool autoReconnectEnabled() const
    {
        return _autoReconnect;
    }

    /** @brief Get low power mode setting */
    bool lowPowerModeEnabled() const
    {
        return _lowPowerMode;
    }

    void hideSplashScreen(void);

    /// @brief Saves the last used connection
    void saveLastUsedConnection(const QString connection);

    /// @brief Restore (and connects) the last used connection (if any)
    void restoreLastUsedConnection();
    
    /// @brief Gets a pointer to the Main Tool Bar
    MainToolBar* getMainToolBar(void) { return _mainToolBar; }

public slots:
    /** @brief Show the application settings */
    void showSettings();
    /** @brief Simulate a link */
    void simulateLink(bool simulate);
    /** @brief Set the currently controlled UAS */
    void setActiveUAS(UASInterface* uas);

    /** @brief Add a new UAS */
    void UASCreated(UASInterface* uas);
    /** Delete an UAS */
    void UASDeleted(UASInterface* uas);
    /** @brief Update system specs of a UAS */
    void UASSpecsChanged(int uas);
    void startVideoCapture();
    void stopVideoCapture();
    void saveScreen();

    void handleMisconfiguration(UASInterface* uas);
    /** @brief Load configuration views */
    void loadSetupView();
    /** @brief Load view for pilot */
    void loadPilotView();
    /** @brief Load view for simulation */
    void loadSimulationView();
    /** @brief Load view for engineer */
    void loadEngineerView();
    /** @brief Load view for operator */
    void loadOperatorView();
    /** @brief Load Terminal Console views */
    void loadTerminalView();
    /** @brief Load Google Earth View */
    void loadGoogleEarthView();
    /** @brief Load local 3D view */
    void loadLocal3DView();
    /** @brief Manage Links */
    void manageLinks();

    /** @brief Show the online help for users */
    void showHelp();
    /** @brief Show the authors / credits */
    void showCredits();
    /** @brief Show the project roadmap */
    void showRoadMap();

    /** @brief Automatically reconnect last link */
    void enableAutoReconnect(bool enabled);

    /** @brief Save power by reducing update rates */
    void enableLowPowerMode(bool enabled) { _lowPowerMode = enabled; }

    void closeEvent(QCloseEvent* event);

    /** @brief Update the window name */
    void configureWindowName();

    void commsWidgetDestroyed(QObject *obj);

protected slots:
    /**
     * @brief Unchecks the normalActionItem.
     * Used as a triggered() callback by the fullScreenAction to make sure only one of it or the
     * normalAction are checked at a time, as they're mutually exclusive.
     */
    void fullScreenActionItemCallback();
    /**
     * @brief Unchecks the fullScreenActionItem.
     * Used as a triggered() callback by the normalAction to make sure only one of it or the
     * fullScreenAction are checked at a time, as they're mutually exclusive.
     */
    void normalActionItemCallback();

signals:
    void initStatusChanged(const QString& message, int alignment, const QColor &color);
    /** Emitted when any value changes from any source */
    void valueChanged(const int uasId, const QString& name, const QString& unit, const QVariant& value, const quint64 msec);
    /** Emitted when any the Canvas elements within QML wudgets need updating */
    void repaintCanvas();

#ifdef QGC_MOUSE_ENABLED_LINUX
    /** @brief Forward X11Event to catch 3DMouse inputs */
    void x11EventOccured(XEvent *event);
#endif //QGC_MOUSE_ENABLED_LINUX

public:
    QGCMAVLinkLogPlayer* getLogPlayer()
    {
        return logPlayer;
    }

protected:

    typedef enum _VIEW_SECTIONS
    {
        VIEW_ENGINEER,         // Engineering/Analyze view mode. Used for analyzing data and modifying onboard parameters
        VIEW_MISSION,          // Mission/Map/Plan view mode. Used for setting mission waypoints and high-level system commands.
        VIEW_FLIGHT,           // Flight/Fly/Operate view mode. Used for 1st-person observation of the vehicle.
        VIEW_SIMULATION,       // HIL Simulation view. Useful overview of the entire system when doing hardware-in-the-loop simulations.
        VIEW_SETUP,            // Setup view. Used for initializing the system for operation. Includes UI for calibration, firmware updating/checking, and parameter modifcation.
        VIEW_TERMINAL,         // Terminal interface. Used for communicating with the remote system, usually in a special configuration input mode.
        VIEW_LOCAL3D,          // A local 3D view. Provides a local 3D view that makes visualizing 3D attitude/orientation/pose easy while in operation.
        VIEW_GOOGLEEARTH       // 3D Google Earth view. A 3D terrain view, though the vehicle is still 2D.
    } VIEW_SECTIONS;

    /** @brief Catch window resize events */
    void resizeEvent(QResizeEvent * event);

    void connectCommonActions();

    void loadSettings();
    void storeSettings();


    QSettings settings;

    // Center widgets
    QPointer<Linecharts> linechartWidget;
#ifdef QGC_OSG_ENABLED
    QPointer<QWidget> q3DWidget;
#endif
#ifdef QGC_GOOGLE_EARTH_ENABLED
    QPointer<QGCGoogleEarthView> earthWidget;
#endif
    QPointer<QGCFirmwareUpdate> firmwareUpdateWidget;

    QPointer<MainToolBar> _mainToolBar;
    QPointer<QGCToolBar> toolBar;

    QPointer<QDockWidget> mavlinkInspectorWidget;
    QPointer<MAVLinkDecoder> mavlinkDecoder;
    QPointer<QDockWidget> mavlinkSenderWidget;
    QGCMAVLinkLogPlayer* logPlayer;

    QPointer<QGCUASFileViewMulti> fileWidget;

    JoystickInput* joystick; ///< The joystick manager for QGC

#ifdef QGC_MOUSE_ENABLED_WIN
    /** @brief 3d Mouse support (WIN only) */
    Mouse3DInput* mouseInput;               ///< 3dConnexion 3dMouse SDK
    Mouse6dofInput* mouse;                  ///< Implementation for 3dMouse input
#endif // QGC_MOUSE_ENABLED_WIN

#ifdef QGC_MOUSE_ENABLED_LINUX
    /** @brief Reimplementation of X11Event to handle 3dMouse Events (magellan) */
    bool x11Event(XEvent *event);
    Mouse6dofInput* mouse;                  ///< Implementation for 3dMouse input
#endif // QGC_MOUSE_ENABLED_LINUX

    /** User interface actions **/
    QAction* connectUASAct;
    QAction* disconnectUASAct;
    QAction* startUASAct;
    QAction* returnUASAct;
    QAction* stopUASAct;
    QAction* killUASAct;
    QAction* simulateUASAct;


    LogCompressor* comp;
    QTimer* videoTimer;
    QGCFlightGearLink* fgLink;
    QTimer windowNameUpdateTimer;

private slots:
    void _showDockWidgetAction(bool show);
    void _loadCustomWidgetFromFile(void);
    void _createNewCustomWidget(void);
#ifdef UNITTEST_BUILD
    void _showQmlTestWidget(void);
#endif
    
private:
    /// Constructor is private since all creation should be through MainWindow::_create
    MainWindow(QSplashScreen* splashScreen);

    void _openUrl(const QString& url, const QString& errorMessage);

    // Center widgets
    QPointer<QWidget> _plannerView;
    QPointer<QWidget> _pilotView;
    QPointer<QWidget> _setupView;
    QPointer<QWidget> _engineeringView;
    QPointer<QWidget> _simView;
    QPointer<QWidget> _terminalView;
    QPointer<QWidget> _googleEarthView;
    QPointer<QWidget> _local3DView;

    // Dock widget names
    static const char* _uasControlDockWidgetName;
    static const char* _uasListDockWidgetName;
    static const char* _waypointsDockWidgetName;
    static const char* _mavlinkDockWidgetName;
    static const char* _parametersDockWidgetName;
    static const char* _filesDockWidgetName;
    static const char* _uasStatusDetailsDockWidgetName;
    static const char* _mapViewDockWidgetName;
    static const char* _hsiDockWidgetName;
    static const char* _hdd1DockWidgetName;
    static const char* _hdd2DockWidgetName;
    static const char* _pfdDockWidgetName;
    static const char* _hudDockWidgetName;
    static const char* _uasInfoViewDockWidgetName;
    static const char* _debugConsoleDockWidgetName;

    QMap<QString, QDockWidget*>     _mapName2DockWidget;
    QMap<int, QDockWidget*>         _mapUasId2HilDockWidget;
    QMap<QDockWidget*, QAction*>    _mapDockWidget2Action;

    void _buildPlannerView(void);
    void _buildPilotView(void);
    void _buildSetupView(void);
    void _buildEngineeringView(void);
    void _buildSimView(void);
    void _buildTerminalView(void);
    void _buildGoogleEarthView(void);
    void _buildLocal3DView(void);

    void _storeCurrentViewState(void);
    void _loadCurrentViewState(void);

    void _createDockWidget(const QString& title, const QString& name, Qt::DockWidgetArea area, QWidget* innerWidget);
    void _createInnerDockWidget(const QString& widgetName);
    void _buildCustomWidgets(void);
    void _buildCommonWidgets(void);
    void _hideAllHilDockWidgets(void);
    void _hideAllDockWidgets(void);
    void _showDockWidget(const QString &name, bool show);
    void _showHILConfigurationWidgets(void);

    bool                    _autoReconnect;
    bool                    _lowPowerMode;           ///< If enabled, QGC reduces the update rates of all widgets
    QActionGroup*           _centerStackActionGroup;
    MAVLinkSimulationLink*  _simulationLink;
    QList<QGCToolWidget*>   _customWidgets;
    QVBoxLayout*            _centralLayout;
    QList<QObject*>         _commsWidgetList;
    QWidget*                _currentViewWidget;     ///< Currently displayed view widget
    QSplashScreen*          _splashScreen;          ///< Splash screen, NULL is splash screen not currently being shown
    VIEW_SECTIONS           _currentView;           ///< Currently displayed view
    Ui::MainWindow          _ui;
    QString                 _screenFileName;

    QString _getWindowStateKey();
    QString _getWindowGeometryKey();


};

#endif /* _MAINWINDOW_H_ */
