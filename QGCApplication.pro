# -------------------------------------------------
# QGroundControl - Micro Air Vehicle Groundstation
# Please see our website at <http://qgroundcontrol.org>
# Maintainer:
# Lorenz Meier <lm@inf.ethz.ch>
# (c) 2009-2014 QGroundControl Developers
# This file is part of the open groundstation project
# QGroundControl is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# QGroundControl is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with QGroundControl. If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------

include(QGCCommon.pri)

TARGET = qgroundcontrol

# Load additional config flags from user_config.pri
exists(user_config.pri):infile(user_config.pri, CONFIG) {
    CONFIG += $$fromfile(user_config.pri, CONFIG)
    message($$sprintf("Using user-supplied additional config: '%1' specified in user_config.pri", $$fromfile(user_config.pri, CONFIG)))
}

LinuxBuild {
    CONFIG += link_pkgconfig
}

message(BASEDIR $$BASEDIR DESTDIR $$DESTDIR TARGET $$TARGET)

# QGC QtLocation plugin

LIBS += -L$${LOCATION_PLUGIN_DESTDIR}
LIBS += -l$${LOCATION_PLUGIN_NAME}

LinuxBuild|MacBuild {
    PRE_TARGETDEPS += $${LOCATION_PLUGIN_DESTDIR}/lib$${LOCATION_PLUGIN_NAME}.a
}

WindowsBuild {
    PRE_TARGETDEPS += $${LOCATION_PLUGIN_DESTDIR}/$${LOCATION_PLUGIN_NAME}.lib
}

# Qt configuration

CONFIG += qt \
    thread

QT += network \
    opengl \
    svg \
    xml \
    concurrent \
    widgets \
    gui \
    serialport \
    sql \
    printsupport \
    qml \
    quick \
    quickwidgets \
    location \
    positioning

contains(DEFINES, QGC_NOTIFY_TUNES_ENABLED) {
    QT += multimedia
}

#  testlib is needed even in release flavor for QSignalSpy support
QT += testlib

#
# OS Specific settings
#

MacBuild {
    QMAKE_INFO_PLIST = Custom-Info.plist
    ICON = $$BASEDIR/resources/icons/macx.icns
    QT += quickwidgets
}

LinuxBuild {
    CONFIG += qesp_linux_udev
}

WindowsBuild {
	RC_FILE = $$BASEDIR/qgroundcontrol.rc
}

#
# Build-specific settings
#

DebugBuild {
    CONFIG += console
}

# qextserialport should not be used by general QGroundControl code. Use QSerialPort instead. This is only
# here to support special case Firmware Upgrade code.
include(libs/qextserialport/src/qextserialport.pri)

#
# External library configuration
#

include(QGCExternalLibs.pri)

#
# Post link configuration
#

include(QGCSetup.pri)

#
# Installer targets
#

include(QGCInstaller.pri)

#
# Main QGroundControl portion of project file
#

RESOURCES += qgroundcontrol.qrc

TRANSLATIONS += \
    es-MX.ts \
    en-US.ts \
    en-ru.ts
    
DEPENDPATH += \
    . \
    plugins

INCLUDEPATH += .

INCLUDEPATH += \
    src \
    src/ui \
    src/ui/linechart \
    src/ui/uas \
    src/ui/map \
    src/uas \
    src/comm \
    src/audio \
    include/ui \
    src/input \
    src/lib/qmapcontrol \
    src/ui/mavlink \
    src/ui/param \
    src/ui/map3D \
    src/ui/mission \
    src/ui/designer \
    src/ui/configuration \
    src/ui/px4_configuration \
    src/ui/main \
    src/ui/toolbar \
    src/ui/flightdisplay \
    src/VehicleSetup \
    src/AutoPilotPlugins \
    src/QmlControls \
    src/smplayer

FORMS += \
    src/ui/MainWindow.ui \
    src/ui/SerialSettings.ui \
    src/ui/UASControl.ui \
    src/ui/UASList.ui \
    src/ui/UASInfo.ui \
    src/ui/Linechart.ui \
    src/ui/UASView.ui \
    src/ui/ParameterInterface.ui \
    src/ui/WaypointList.ui \
    src/ui/JoystickWidget.ui \
    src/ui/DebugConsole.ui \
    src/ui/HDDisplay.ui \
    src/ui/MAVLinkSettingsWidget.ui \
    src/ui/QGCSensorSettingsWidget.ui \
    src/ui/QGCDataPlot2D.ui \
    src/ui/QMap3D.ui \
    src/ui/uas/QGCUnconnectedInfoWidget.ui \
    src/ui/designer/QGCToolWidget.ui \
    src/ui/designer/QGCParamSlider.ui \
    src/ui/designer/QGCActionButton.ui \
    src/ui/designer/QGCCommandButton.ui \
    src/ui/designer/QGCToolWidgetComboBox.ui \
    src/ui/designer/QGCTextLabel.ui \
    src/ui/designer/QGCXYPlot.ui \
    src/ui/QGCMAVLinkLogPlayer.ui \
    src/ui/QGCWaypointListMulti.ui \
    src/ui/QGCUASFileViewMulti.ui \
    src/ui/QGCTCPLinkConfiguration.ui \
    src/ui/SettingsDialog.ui \
    src/ui/map/QGCMapTool.ui \
    src/ui/map/QGCMapToolBar.ui \
    src/ui/QGCMAVLinkInspector.ui \
    src/ui/WaypointViewOnlyView.ui \
    src/ui/WaypointEditableView.ui \
    src/ui/mavlink/QGCMAVLinkMessageSender.ui \
    src/ui/QGCPluginHost.ui \
    src/ui/mission/QGCMissionOther.ui \
    src/ui/mission/QGCMissionNavWaypoint.ui \
    src/ui/mission/QGCMissionDoJump.ui \
    src/ui/mission/QGCMissionConditionDelay.ui \
    src/ui/mission/QGCMissionNavLoiterUnlim.ui \
    src/ui/mission/QGCMissionNavLoiterTurns.ui \
    src/ui/mission/QGCMissionNavLoiterTime.ui \
    src/ui/mission/QGCMissionNavReturnToLaunch.ui \
    src/ui/mission/QGCMissionNavLand.ui \
    src/ui/mission/QGCMissionNavTakeoff.ui \
    src/ui/mission/QGCMissionNavSweep.ui \
    src/ui/mission/QGCMissionDoStartSearch.ui \
    src/ui/mission/QGCMissionDoFinishSearch.ui \
    src/ui/QGCHilConfiguration.ui \
    src/ui/QGCHilFlightGearConfiguration.ui \
    src/ui/QGCHilJSBSimConfiguration.ui \
    src/ui/QGCHilXPlaneConfiguration.ui \
    src/ui/uas/UASQuickView.ui \
    src/ui/uas/UASQuickViewItemSelect.ui \
    src/ui/QGCTabbedInfoView.ui \
    src/ui/UASRawStatusView.ui \
    src/ui/uas/UASMessageView.ui \
    src/ui/JoystickButton.ui \
    src/ui/JoystickAxis.ui \
    src/ui/configuration/terminalconsole.ui \
    src/ui/configuration/SerialSettingsDialog.ui \
    src/ui/px4_configuration/PX4RCCalibration.ui \
    src/ui/QGCUASFileView.ui \
    src/ui/uas/UASQuickTabView.ui \
    src/QGCQmlWidgetHolder.ui \
    src/ui/QGCMapRCToParamDialog.ui \
    src/ui/QGCLinkConfiguration.ui \
    src/ui/QGCCommConfiguration.ui \
    src/ui/QGCUDPLinkConfiguration.ui \
    src/ui/qgcvideoview.ui


HEADERS += \
    src/MG.h \
    src/QGCApplication.h \
    src/QGCSingleton.h \
    src/uas/UASInterface.h \
    src/uas/UAS.h \
    src/uas/UASManager.h \
    src/comm/LinkManager.h \
    src/comm/LinkInterface.h \
    src/comm/SerialLink.h \
    src/comm/ProtocolInterface.h \
    src/comm/MAVLinkProtocol.h \
    src/comm/QGCFlightGearLink.h \
    src/comm/QGCJSBSimLink.h \
    src/comm/QGCXPlaneLink.h \
    src/ui/SerialConfigurationWindow.h \
    src/ui/MainWindow.h \
    src/ui/uas/UASControlWidget.h \
    src/ui/uas/UASListWidget.h \
    src/ui/uas/UASInfoWidget.h \
    src/ui/HUD.h \
    src/ui/linechart/LinechartWidget.h \
    src/ui/linechart/LinechartPlot.h \
    src/ui/linechart/Scrollbar.h \
    src/ui/linechart/ScrollZoomer.h \
    src/QGCConfig.h \
    src/ui/uas/UASView.h \
    src/ui/CameraView.h \
    src/comm/MAVLinkSimulationLink.h \
    src/comm/UDPLink.h \
    src/comm/TCPLink.h \
    src/ui/ParameterInterface.h \
    src/ui/WaypointList.h \
    src/Waypoint.h \
    src/input/JoystickInput.h \
    src/ui/JoystickWidget.h \
    src/ui/DebugConsole.h \
    src/ui/HDDisplay.h \
    src/ui/MAVLinkSettingsWidget.h \
    src/GAudioOutput.h \
    src/LogCompressor.h \
    src/ui/QGCParamWidget.h \
    src/ui/QGCSensorSettingsWidget.h \
    src/ui/linechart/Linecharts.h \
    src/uas/UASWaypointManager.h \
    src/ui/HSIDisplay.h \
    src/QGC.h \
    src/ui/QGCDataPlot2D.h \
    src/ui/linechart/IncrementalPlot.h \
    src/comm/QGCMAVLink.h \
    src/ui/QGCMainWindowAPConfigurator.h \
    src/comm/MAVLinkSwarmSimulationLink.h \
    src/ui/uas/QGCUnconnectedInfoWidget.h \
    src/ui/designer/QGCToolWidget.h \
    src/ui/designer/QGCParamSlider.h \
    src/ui/designer/QGCCommandButton.h \
    src/ui/designer/QGCToolWidgetItem.h \
    src/ui/designer/QGCToolWidgetComboBox.h \
    src/ui/designer/QGCTextLabel.h \
    src/ui/designer/QGCRadioChannelDisplay.h \
    src/ui/designer/QGCXYPlot.h \
    src/ui/designer/RCChannelWidget.h \
    src/ui/QGCMAVLinkLogPlayer.h \
    src/comm/MAVLinkSimulationWaypointPlanner.h \
    src/comm/MAVLinkSimulationMAV.h \
    src/uas/QGCMAVLinkUASFactory.h \
    src/ui/QGCWaypointListMulti.h \
    src/ui/QGCUASFileViewMulti.h \
    src/ui/QGCTCPLinkConfiguration.h \
    src/ui/SettingsDialog.h \
    src/uas/QGCUASParamManager.h \
    src/ui/map/QGCMapWidget.h \
    src/ui/map/MAV2DIcon.h \
    src/ui/map/Waypoint2DIcon.h \
    src/ui/map/QGCMapTool.h \
    src/ui/map/QGCMapToolBar.h \
    src/QGCGeo.h \
    src/ui/QGCMAVLinkInspector.h \
    src/ui/MAVLinkDecoder.h \
    src/ui/WaypointViewOnlyView.h \
    src/ui/WaypointEditableView.h \
    src/ui/QGCRGBDView.h \
    src/ui/mavlink/QGCMAVLinkMessageSender.h \
    src/ui/QGCPluginHost.h \
    src/ui/mission/QGCMissionOther.h \
    src/ui/mission/QGCMissionNavWaypoint.h \
    src/ui/mission/QGCMissionDoJump.h \
    src/ui/mission/QGCMissionConditionDelay.h \
    src/ui/mission/QGCMissionNavLoiterUnlim.h \
    src/ui/mission/QGCMissionNavLoiterTurns.h \
    src/ui/mission/QGCMissionNavLoiterTime.h \
    src/ui/mission/QGCMissionNavReturnToLaunch.h \
    src/ui/mission/QGCMissionNavLand.h \
    src/ui/mission/QGCMissionNavTakeoff.h \
    src/ui/mission/QGCMissionNavSweep.h \
    src/ui/mission/QGCMissionDoStartSearch.h \
    src/ui/mission/QGCMissionDoFinishSearch.h \
    src/comm/QGCHilLink.h \
    src/ui/QGCHilConfiguration.h \
    src/ui/QGCHilFlightGearConfiguration.h \
    src/ui/QGCHilJSBSimConfiguration.h \
    src/ui/QGCHilXPlaneConfiguration.h \
    src/ui/uas/UASQuickView.h \
    src/ui/uas/UASQuickViewItem.h \
    src/ui/linechart/ChartPlot.h \
    src/ui/uas/UASQuickViewItemSelect.h \
    src/ui/uas/UASQuickViewTextItem.h \
    src/ui/uas/UASQuickViewGaugeItem.h \
    src/ui/QGCTabbedInfoView.h \
    src/ui/UASRawStatusView.h \
    src/ui/PrimaryFlightDisplay.h \
    src/ui/uas/UASMessageView.h \
    src/ui/JoystickButton.h \
    src/ui/JoystickAxis.h \
    src/ui/configuration/console.h \
    src/ui/configuration/SerialSettingsDialog.h \
    src/ui/configuration/terminalconsole.h \
    src/ui/configuration/ApmHighlighter.h \
    src/uas/UASParameterDataModel.h \
    src/uas/UASParameterCommsMgr.h \
    src/ui/QGCPendingParamWidget.h \
    src/ui/QGCBaseParamWidget.h \
    src/ui/px4_configuration/PX4RCCalibration.h \
    src/ui/px4_configuration/RCValueWidget.h \
    src/uas/UASManagerInterface.h \
    src/uas/QGCUASParamManagerInterface.h \
    src/uas/QGCUASFileManager.h \
    src/ui/QGCUASFileView.h \
    src/CmdLineOptParser.h \
    src/QGCFileDialog.h \
    src/QGCMessageBox.h \
    src/ui/uas/UASQuickTabView.h \
    src/QGCComboBox.h \
    src/QGCTemporaryFile.h \
    src/audio/QGCAudioWorker.h \
    src/QGCQuickWidget.h \
    src/QGCPalette.h \
    src/QGCQmlWidgetHolder.h \
    src/ui/QGCParamTreeWidget.h \
    src/ui/QGCMapRCToParamDialog.h \
    src/QGCDockWidget.h \
    src/ui/QGCLinkConfiguration.h \
    src/comm/LinkConfiguration.h \
    src/ui/QGCCommConfiguration.h \
    src/ui/QGCUDPLinkConfiguration.h \
    src/uas/UASMessageHandler.h \
    src/ui/toolbar/MainToolBar.h \
    src/QmlControls/ScreenTools.h \
    src/QGCLoggingCategory.h \
    src/ui/qgcvideoview.h \
    src/ui/flightdisplay/QGCFlightDisplay.h \
    libs/eigen/Eigen/src/Cholesky/LDLT.h \
    libs/eigen/Eigen/src/Cholesky/LLT.h \
    libs/eigen/Eigen/src/Cholesky/LLT_MKL.h \
    libs/eigen/Eigen/src/CholmodSupport/CholmodSupport.h \
    libs/eigen/Eigen/src/Core/arch/AltiVec/Complex.h \
    libs/eigen/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    libs/eigen/Eigen/src/Core/arch/Default/Settings.h \
    libs/eigen/Eigen/src/Core/arch/NEON/Complex.h \
    libs/eigen/Eigen/src/Core/arch/NEON/PacketMath.h \
    libs/eigen/Eigen/src/Core/arch/SSE/Complex.h \
    libs/eigen/Eigen/src/Core/arch/SSE/MathFunctions.h \
    libs/eigen/Eigen/src/Core/arch/SSE/PacketMath.h \
    libs/eigen/Eigen/src/Core/products/CoeffBasedProduct.h \
    libs/eigen/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    libs/eigen/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    libs/eigen/Eigen/src/Core/products/GeneralMatrixMatrix_MKL.h \
    libs/eigen/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    libs/eigen/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_MKL.h \
    libs/eigen/Eigen/src/Core/products/GeneralMatrixVector.h \
    libs/eigen/Eigen/src/Core/products/GeneralMatrixVector_MKL.h \
    libs/eigen/Eigen/src/Core/products/Parallelizer.h \
    libs/eigen/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    libs/eigen/Eigen/src/Core/products/SelfadjointMatrixMatrix_MKL.h \
    libs/eigen/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    libs/eigen/Eigen/src/Core/products/SelfadjointMatrixVector_MKL.h \
    libs/eigen/Eigen/src/Core/products/SelfadjointProduct.h \
    libs/eigen/Eigen/src/Core/products/SelfadjointRank2Update.h \
    libs/eigen/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    libs/eigen/Eigen/src/Core/products/TriangularMatrixMatrix_MKL.h \
    libs/eigen/Eigen/src/Core/products/TriangularMatrixVector.h \
    libs/eigen/Eigen/src/Core/products/TriangularMatrixVector_MKL.h \
    libs/eigen/Eigen/src/Core/products/TriangularSolverMatrix.h \
    libs/eigen/Eigen/src/Core/products/TriangularSolverMatrix_MKL.h \
    libs/eigen/Eigen/src/Core/products/TriangularSolverVector.h \
    libs/eigen/Eigen/src/Core/util/BlasUtil.h \
    libs/eigen/Eigen/src/Core/util/Constants.h \
    libs/eigen/Eigen/src/Core/util/DisableStupidWarnings.h \
    libs/eigen/Eigen/src/Core/util/ForwardDeclarations.h \
    libs/eigen/Eigen/src/Core/util/Macros.h \
    libs/eigen/Eigen/src/Core/util/Memory.h \
    libs/eigen/Eigen/src/Core/util/Meta.h \
    libs/eigen/Eigen/src/Core/util/MKL_support.h \
    libs/eigen/Eigen/src/Core/util/NonMPL2.h \
    libs/eigen/Eigen/src/Core/util/ReenableStupidWarnings.h \
    libs/eigen/Eigen/src/Core/util/StaticAssert.h \
    libs/eigen/Eigen/src/Core/util/XprHelper.h \
    libs/eigen/Eigen/src/Core/Array.h \
    libs/eigen/Eigen/src/Core/ArrayBase.h \
    libs/eigen/Eigen/src/Core/ArrayWrapper.h \
    libs/eigen/Eigen/src/Core/Assign.h \
    libs/eigen/Eigen/src/Core/Assign_MKL.h \
    libs/eigen/Eigen/src/Core/BandMatrix.h \
    libs/eigen/Eigen/src/Core/Block.h \
    libs/eigen/Eigen/src/Core/BooleanRedux.h \
    libs/eigen/Eigen/src/Core/CommaInitializer.h \
    libs/eigen/Eigen/src/Core/CoreIterators.h \
    libs/eigen/Eigen/src/Core/CwiseBinaryOp.h \
    libs/eigen/Eigen/src/Core/CwiseNullaryOp.h \
    libs/eigen/Eigen/src/Core/CwiseUnaryOp.h \
    libs/eigen/Eigen/src/Core/CwiseUnaryView.h \
    libs/eigen/Eigen/src/Core/DenseBase.h \
    libs/eigen/Eigen/src/Core/DenseCoeffsBase.h \
    libs/eigen/Eigen/src/Core/DenseStorage.h \
    libs/eigen/Eigen/src/Core/Diagonal.h \
    libs/eigen/Eigen/src/Core/DiagonalMatrix.h \
    libs/eigen/Eigen/src/Core/DiagonalProduct.h \
    libs/eigen/Eigen/src/Core/Dot.h \
    libs/eigen/Eigen/src/Core/EigenBase.h \
    libs/eigen/Eigen/src/Core/Flagged.h \
    libs/eigen/Eigen/src/Core/ForceAlignedAccess.h \
    libs/eigen/Eigen/src/Core/Functors.h \
    libs/eigen/Eigen/src/Core/Fuzzy.h \
    libs/eigen/Eigen/src/Core/GeneralProduct.h \
    libs/eigen/Eigen/src/Core/GenericPacketMath.h \
    libs/eigen/Eigen/src/Core/GlobalFunctions.h \
    libs/eigen/Eigen/src/Core/IO.h \
    libs/eigen/Eigen/src/Core/Map.h \
    libs/eigen/Eigen/src/Core/MapBase.h \
    libs/eigen/Eigen/src/Core/MathFunctions.h \
    libs/eigen/Eigen/src/Core/Matrix.h \
    libs/eigen/Eigen/src/Core/MatrixBase.h \
    libs/eigen/Eigen/src/Core/NestByValue.h \
    libs/eigen/Eigen/src/Core/NoAlias.h \
    libs/eigen/Eigen/src/Core/NumTraits.h \
    libs/eigen/Eigen/src/Core/PermutationMatrix.h \
    libs/eigen/Eigen/src/Core/PlainObjectBase.h \
    libs/eigen/Eigen/src/Core/ProductBase.h \
    libs/eigen/Eigen/src/Core/Random.h \
    libs/eigen/Eigen/src/Core/Redux.h \
    libs/eigen/Eigen/src/Core/Ref.h \
    libs/eigen/Eigen/src/Core/Replicate.h \
    libs/eigen/Eigen/src/Core/ReturnByValue.h \
    libs/eigen/Eigen/src/Core/Reverse.h \
    libs/eigen/Eigen/src/Core/Select.h \
    libs/eigen/Eigen/src/Core/SelfAdjointView.h \
    libs/eigen/Eigen/src/Core/SelfCwiseBinaryOp.h \
    libs/eigen/Eigen/src/Core/SolveTriangular.h \
    libs/eigen/Eigen/src/Core/StableNorm.h \
    libs/eigen/Eigen/src/Core/Stride.h \
    libs/eigen/Eigen/src/Core/Swap.h \
    libs/eigen/Eigen/src/Core/Transpose.h \
    libs/eigen/Eigen/src/Core/Transpositions.h \
    libs/eigen/Eigen/src/Core/TriangularMatrix.h \
    libs/eigen/Eigen/src/Core/VectorBlock.h \
    libs/eigen/Eigen/src/Core/VectorwiseOp.h \
    libs/eigen/Eigen/src/Core/Visitor.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/AlignedBox.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/All.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/AngleAxis.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/Hyperplane.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/Quaternion.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/Rotation2D.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/RotationBase.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/Scaling.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/Transform.h \
    libs/eigen/Eigen/src/Eigen2Support/Geometry/Translation.h \
    libs/eigen/Eigen/src/Eigen2Support/Block.h \
    libs/eigen/Eigen/src/Eigen2Support/Cwise.h \
    libs/eigen/Eigen/src/Eigen2Support/CwiseOperators.h \
    libs/eigen/Eigen/src/Eigen2Support/Lazy.h \
    libs/eigen/Eigen/src/Eigen2Support/LeastSquares.h \
    libs/eigen/Eigen/src/Eigen2Support/LU.h \
    libs/eigen/Eigen/src/Eigen2Support/Macros.h \
    libs/eigen/Eigen/src/Eigen2Support/MathFunctions.h \
    libs/eigen/Eigen/src/Eigen2Support/Memory.h \
    libs/eigen/Eigen/src/Eigen2Support/Meta.h \
    libs/eigen/Eigen/src/Eigen2Support/Minor.h \
    libs/eigen/Eigen/src/Eigen2Support/QR.h \
    libs/eigen/Eigen/src/Eigen2Support/SVD.h \
    libs/eigen/Eigen/src/Eigen2Support/TriangularSolver.h \
    libs/eigen/Eigen/src/Eigen2Support/VectorBlock.h \
    libs/eigen/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    libs/eigen/Eigen/src/Eigenvalues/ComplexSchur.h \
    libs/eigen/Eigen/src/Eigenvalues/ComplexSchur_MKL.h \
    libs/eigen/Eigen/src/Eigenvalues/EigenSolver.h \
    libs/eigen/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    libs/eigen/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    libs/eigen/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    libs/eigen/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    libs/eigen/Eigen/src/Eigenvalues/RealQZ.h \
    libs/eigen/Eigen/src/Eigenvalues/RealSchur.h \
    libs/eigen/Eigen/src/Eigenvalues/RealSchur_MKL.h \
    libs/eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    libs/eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h \
    libs/eigen/Eigen/src/Eigenvalues/Tridiagonalization.h \
    libs/eigen/Eigen/src/Geometry/arch/Geometry_SSE.h \
    libs/eigen/Eigen/src/Geometry/AlignedBox.h \
    libs/eigen/Eigen/src/Geometry/AngleAxis.h \
    libs/eigen/Eigen/src/Geometry/EulerAngles.h \
    libs/eigen/Eigen/src/Geometry/Homogeneous.h \
    libs/eigen/Eigen/src/Geometry/Hyperplane.h \
    libs/eigen/Eigen/src/Geometry/OrthoMethods.h \
    libs/eigen/Eigen/src/Geometry/ParametrizedLine.h \
    libs/eigen/Eigen/src/Geometry/Quaternion.h \
    libs/eigen/Eigen/src/Geometry/Rotation2D.h \
    libs/eigen/Eigen/src/Geometry/RotationBase.h \
    libs/eigen/Eigen/src/Geometry/Scaling.h \
    libs/eigen/Eigen/src/Geometry/Transform.h \
    libs/eigen/Eigen/src/Geometry/Translation.h \
    libs/eigen/Eigen/src/Geometry/Umeyama.h \
    libs/eigen/Eigen/src/Householder/BlockHouseholder.h \
    libs/eigen/Eigen/src/Householder/Householder.h \
    libs/eigen/Eigen/src/Householder/HouseholderSequence.h \
    libs/eigen/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    libs/eigen/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    libs/eigen/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    libs/eigen/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    libs/eigen/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    libs/eigen/Eigen/src/Jacobi/Jacobi.h \
    libs/eigen/Eigen/src/LU/arch/Inverse_SSE.h \
    libs/eigen/Eigen/src/LU/Determinant.h \
    libs/eigen/Eigen/src/LU/FullPivLU.h \
    libs/eigen/Eigen/src/LU/Inverse.h \
    libs/eigen/Eigen/src/LU/PartialPivLU.h \
    libs/eigen/Eigen/src/LU/PartialPivLU_MKL.h \
    libs/eigen/Eigen/src/MetisSupport/MetisSupport.h \
    libs/eigen/Eigen/src/misc/blas.h \
    libs/eigen/Eigen/src/misc/Image.h \
    libs/eigen/Eigen/src/misc/Kernel.h \
    libs/eigen/Eigen/src/misc/Solve.h \
    libs/eigen/Eigen/src/misc/SparseSolve.h \
    libs/eigen/Eigen/src/OrderingMethods/Amd.h \
    libs/eigen/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    libs/eigen/Eigen/src/OrderingMethods/Ordering.h \
    libs/eigen/Eigen/src/PardisoSupport/PardisoSupport.h \
    libs/eigen/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    libs/eigen/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    libs/eigen/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    libs/eigen/Eigen/src/plugins/BlockMethods.h \
    libs/eigen/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    libs/eigen/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    libs/eigen/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    libs/eigen/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    libs/eigen/Eigen/src/QR/ColPivHouseholderQR.h \
    libs/eigen/Eigen/src/QR/ColPivHouseholderQR_MKL.h \
    libs/eigen/Eigen/src/QR/FullPivHouseholderQR.h \
    libs/eigen/Eigen/src/QR/HouseholderQR.h \
    libs/eigen/Eigen/src/QR/HouseholderQR_MKL.h \
    libs/eigen/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    libs/eigen/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    libs/eigen/Eigen/src/SparseCore/AmbiVector.h \
    libs/eigen/Eigen/src/SparseCore/CompressedStorage.h \
    libs/eigen/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    libs/eigen/Eigen/src/SparseCore/MappedSparseMatrix.h \
    libs/eigen/Eigen/src/SparseCore/SparseBlock.h \
    libs/eigen/Eigen/src/SparseCore/SparseColEtree.h \
    libs/eigen/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    libs/eigen/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    libs/eigen/Eigen/src/SparseCore/SparseDenseProduct.h \
    libs/eigen/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    libs/eigen/Eigen/src/SparseCore/SparseDot.h \
    libs/eigen/Eigen/src/SparseCore/SparseFuzzy.h \
    libs/eigen/Eigen/src/SparseCore/SparseMatrix.h \
    libs/eigen/Eigen/src/SparseCore/SparseMatrixBase.h \
    libs/eigen/Eigen/src/SparseCore/SparsePermutation.h \
    libs/eigen/Eigen/src/SparseCore/SparseProduct.h \
    libs/eigen/Eigen/src/SparseCore/SparseRedux.h \
    libs/eigen/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    libs/eigen/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    libs/eigen/Eigen/src/SparseCore/SparseTranspose.h \
    libs/eigen/Eigen/src/SparseCore/SparseTriangularView.h \
    libs/eigen/Eigen/src/SparseCore/SparseUtil.h \
    libs/eigen/Eigen/src/SparseCore/SparseVector.h \
    libs/eigen/Eigen/src/SparseCore/SparseView.h \
    libs/eigen/Eigen/src/SparseCore/TriangularSolver.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_Memory.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_pivotL.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_pruneL.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_Structs.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    libs/eigen/Eigen/src/SparseLU/SparseLU_Utils.h \
    libs/eigen/Eigen/src/SparseLU/SparseLUImpl.h \
    libs/eigen/Eigen/src/SparseQR/SparseQR.h \
    libs/eigen/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    libs/eigen/Eigen/src/StlSupport/details.h \
    libs/eigen/Eigen/src/StlSupport/StdDeque.h \
    libs/eigen/Eigen/src/StlSupport/StdList.h \
    libs/eigen/Eigen/src/StlSupport/StdVector.h \
    libs/eigen/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    libs/eigen/Eigen/src/SVD/JacobiSVD.h \
    libs/eigen/Eigen/src/SVD/JacobiSVD_MKL.h \
    libs/eigen/Eigen/src/SVD/UpperBidiagonalization.h \
    libs/eigen/Eigen/src/UmfPackSupport/UmfPackSupport.h \
    libs/lib/Frameworks/SDL.framework/Headers/begin_code.h \
    libs/lib/Frameworks/SDL.framework/Headers/close_code.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_active.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_audio.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_byteorder.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_cdrom.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_config.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_config_dreamcast.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_config_macos.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_config_macosx.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_config_os2.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_config_win32.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_copying.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_cpuinfo.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_endian.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_error.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_events.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_getenv.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_joystick.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_keyboard.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_keysym.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_loadso.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_main.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_mouse.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_mutex.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_name.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_opengl.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_platform.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_quit.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_rwops.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_stdinc.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_syswm.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_thread.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_timer.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_types.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_version.h \
    libs/lib/Frameworks/SDL.framework/Headers/SDL_video.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/begin_code.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/close_code.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_active.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_audio.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_byteorder.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_cdrom.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_config.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_config_dreamcast.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_config_macos.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_config_macosx.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_config_os2.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_config_win32.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_copying.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_cpuinfo.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_endian.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_error.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_events.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_getenv.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_joystick.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_keyboard.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_keysym.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_loadso.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_main.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_mouse.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_mutex.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_name.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_opengl.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_platform.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_quit.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_rwops.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_stdinc.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_syswm.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_thread.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_timer.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_types.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_version.h \
    libs/lib/Frameworks/SDL.framework/Versions/A/Headers/SDL_video.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/begin_code.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/close_code.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_active.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_audio.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_byteorder.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_cdrom.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_config.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_config_dreamcast.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_config_macos.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_config_macosx.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_config_os2.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_config_win32.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_copying.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_cpuinfo.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_endian.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_error.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_events.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_getenv.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_joystick.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_keyboard.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_keysym.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_loadso.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_main.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_mouse.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_mutex.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_name.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_opengl.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_platform.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_quit.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_rwops.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_stdinc.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_syswm.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_thread.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_timer.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_types.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_version.h \
    libs/lib/Frameworks/SDL.framework/Versions/Current/Headers/SDL_video.h \
    libs/lib/msinttypes/inttypes.h \
    libs/lib/msinttypes/stdint.h \
    libs/lib/sdl/include/SDL/begin_code.h \
    libs/lib/sdl/include/SDL/close_code.h \
    libs/lib/sdl/include/SDL/SDL.h \
    libs/lib/sdl/include/SDL/SDL_active.h \
    libs/lib/sdl/include/SDL/SDL_audio.h \
    libs/lib/sdl/include/SDL/SDL_byteorder.h \
    libs/lib/sdl/include/SDL/SDL_cdrom.h \
    libs/lib/sdl/include/SDL/SDL_config.h \
    libs/lib/sdl/include/SDL/SDL_copying.h \
    libs/lib/sdl/include/SDL/SDL_cpuinfo.h \
    libs/lib/sdl/include/SDL/SDL_endian.h \
    libs/lib/sdl/include/SDL/SDL_error.h \
    libs/lib/sdl/include/SDL/SDL_events.h \
    libs/lib/sdl/include/SDL/SDL_getenv.h \
    libs/lib/sdl/include/SDL/SDL_joystick.h \
    libs/lib/sdl/include/SDL/SDL_keyboard.h \
    libs/lib/sdl/include/SDL/SDL_keysym.h \
    libs/lib/sdl/include/SDL/SDL_loadso.h \
    libs/lib/sdl/include/SDL/SDL_main.h \
    libs/lib/sdl/include/SDL/SDL_mouse.h \
    libs/lib/sdl/include/SDL/SDL_mutex.h \
    libs/lib/sdl/include/SDL/SDL_name.h \
    libs/lib/sdl/include/SDL/SDL_opengl.h \
    libs/lib/sdl/include/SDL/SDL_platform.h \
    libs/lib/sdl/include/SDL/SDL_quit.h \
    libs/lib/sdl/include/SDL/SDL_rwops.h \
    libs/lib/sdl/include/SDL/SDL_stdinc.h \
    libs/lib/sdl/include/SDL/SDL_syswm.h \
    libs/lib/sdl/include/SDL/SDL_thread.h \
    libs/lib/sdl/include/SDL/SDL_timer.h \
    libs/lib/sdl/include/SDL/SDL_types.h \
    libs/lib/sdl/include/SDL/SDL_version.h \
    libs/lib/sdl/include/SDL/SDL_video.h \
    libs/lib/sdl/msvc/include/SDL/begin_code.h \
    libs/lib/sdl/msvc/include/SDL/close_code.h \
    libs/lib/sdl/msvc/include/SDL/SDL.h \
    libs/lib/sdl/msvc/include/SDL/SDL_active.h \
    libs/lib/sdl/msvc/include/SDL/SDL_audio.h \
    libs/lib/sdl/msvc/include/SDL/SDL_byteorder.h \
    libs/lib/sdl/msvc/include/SDL/SDL_cdrom.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_amiga.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_dreamcast.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_macos.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_macosx.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_minimal.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_nds.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_os2.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_symbian.h \
    libs/lib/sdl/msvc/include/SDL/SDL_config_win32.h \
    libs/lib/sdl/msvc/include/SDL/SDL_copying.h \
    libs/lib/sdl/msvc/include/SDL/SDL_cpuinfo.h \
    libs/lib/sdl/msvc/include/SDL/SDL_endian.h \
    libs/lib/sdl/msvc/include/SDL/SDL_error.h \
    libs/lib/sdl/msvc/include/SDL/SDL_events.h \
    libs/lib/sdl/msvc/include/SDL/SDL_getenv.h \
    libs/lib/sdl/msvc/include/SDL/SDL_joystick.h \
    libs/lib/sdl/msvc/include/SDL/SDL_keyboard.h \
    libs/lib/sdl/msvc/include/SDL/SDL_keysym.h \
    libs/lib/sdl/msvc/include/SDL/SDL_loadso.h \
    libs/lib/sdl/msvc/include/SDL/SDL_main.h \
    libs/lib/sdl/msvc/include/SDL/SDL_mouse.h \
    libs/lib/sdl/msvc/include/SDL/SDL_mutex.h \
    libs/lib/sdl/msvc/include/SDL/SDL_name.h \
    libs/lib/sdl/msvc/include/SDL/SDL_opengl.h \
    libs/lib/sdl/msvc/include/SDL/SDL_platform.h \
    libs/lib/sdl/msvc/include/SDL/SDL_quit.h \
    libs/lib/sdl/msvc/include/SDL/SDL_rwops.h \
    libs/lib/sdl/msvc/include/SDL/SDL_stdinc.h \
    libs/lib/sdl/msvc/include/SDL/SDL_syswm.h \
    libs/lib/sdl/msvc/include/SDL/SDL_thread.h \
    libs/lib/sdl/msvc/include/SDL/SDL_timer.h \
    libs/lib/sdl/msvc/include/SDL/SDL_types.h \
    libs/lib/sdl/msvc/include/SDL/SDL_version.h \
    libs/lib/sdl/msvc/include/SDL/SDL_video.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/ardupilotmega.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_ahrs.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_ahrs2.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_ahrs3.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_airspeed_autocal.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_ap_adc.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_autopilot_version_request.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_battery2.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_camera_feedback.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_camera_status.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_compassmot_status.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_data16.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_data32.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_data64.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_data96.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_digicam_configure.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_digicam_control.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_fence_fetch_point.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_fence_point.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_fence_status.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_gimbal_control.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_gimbal_report.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_hwstatus.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_limits_status.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_meminfo.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_mount_configure.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_mount_control.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_mount_status.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_radio.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_rally_fetch_point.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_rally_point.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_rangefinder.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_sensor_offsets.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_set_mag_offsets.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_simstate.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/mavlink_msg_wind.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/ardupilotmega/version.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/ASLUAV.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_asl_obctrl.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_aslctrl_data.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_aslctrl_debug.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_asluav_status.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_ekf_ext.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_sens_atmos.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_sens_mppt.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/mavlink_msg_sens_power.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/ASLUAV/version.h \
    libs/mavlink/include/mavlink/v1.0/autoquad/autoquad.h \
    libs/mavlink/include/mavlink/v1.0/autoquad/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/autoquad/mavlink_msg_aq_telemetry_f.h \
    libs/mavlink/include/mavlink/v1.0/autoquad/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/autoquad/version.h \
    libs/mavlink/include/mavlink/v1.0/common/common.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_actuator_control_target.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_att_pos_mocap.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_attitude.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_attitude_quaternion.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_attitude_quaternion_cov.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_attitude_target.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_auth_key.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_autopilot_version.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_battery_status.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_change_operator_control.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_change_operator_control_ack.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_command_ack.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_command_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_command_long.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_data_stream.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_data_transmission_handshake.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_debug.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_debug_vect.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_distance_sensor.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_encapsulated_data.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_file_transfer_protocol.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_global_position_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_global_position_int_cov.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_global_vision_position_estimate.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps2_raw.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps2_rtk.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps_global_origin.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps_inject_data.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps_raw_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps_rtk.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_gps_status.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_heartbeat.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_highres_imu.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_controls.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_gps.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_optical_flow.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_rc_inputs_raw.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_sensor.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_state.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_hil_state_quaternion.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_local_position_ned.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_local_position_ned_cov.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_local_position_ned_system_global_offset.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_log_data.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_log_entry.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_log_erase.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_log_request_data.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_log_request_end.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_log_request_list.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_manual_control.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_manual_setpoint.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_memory_vect.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_ack.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_clear_all.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_count.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_current.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_item.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_item_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_item_reached.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_request.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_request_list.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_request_partial_list.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_set_current.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_mission_write_partial_list.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_named_value_float.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_named_value_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_nav_controller_output.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_optical_flow.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_optical_flow_rad.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_param_map_rc.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_param_request_list.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_param_request_read.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_param_set.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_param_value.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_ping.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_position_target_global_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_position_target_local_ned.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_power_status.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_radio_status.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_raw_imu.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_raw_pressure.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_rc_channels.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_rc_channels_override.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_rc_channels_raw.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_rc_channels_scaled.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_request_data_stream.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_safety_allowed_area.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_safety_set_allowed_area.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_scaled_imu.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_scaled_imu2.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_scaled_pressure.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_scaled_pressure2.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_serial_control.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_servo_output_raw.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_set_actuator_control_target.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_set_attitude_target.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_set_gps_global_origin.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_set_mode.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_set_position_target_global_int.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_set_position_target_local_ned.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_sim_state.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_statustext.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_sys_status.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_system_time.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_terrain_check.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_terrain_data.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_terrain_report.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_terrain_request.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_timesync.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_v2_extension.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_vfr_hud.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_vicon_position_estimate.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_vision_position_estimate.h \
    libs/mavlink/include/mavlink/v1.0/common/mavlink_msg_vision_speed_estimate.h \
    libs/mavlink/include/mavlink/v1.0/common/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/common/version.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/matrixpilot.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_airspeeds.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_altitudes.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_buffer_function.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_buffer_function_ack.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_command.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_command_ack.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_directory.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_directory_ack.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_read_req.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_flexifunction_set.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f13.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f14.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f15.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f16.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f2_a.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f2_b.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f4.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f5.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f6.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f7.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/mavlink_msg_serial_udb_extra_f8.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/matrixpilot/version.h \
    libs/mavlink/include/mavlink/v1.0/minimal/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/minimal/mavlink_msg_heartbeat.h \
    libs/mavlink/include/mavlink/v1.0/minimal/minimal.h \
    libs/mavlink/include/mavlink/v1.0/minimal/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/minimal/version.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_attitude_control.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_brief_feature.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_detection_stats.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_image_available.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_image_trigger_control.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_image_triggered.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_marker.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_onboard_health.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_pattern_detected.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_point_of_interest.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_point_of_interest_connection.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_position_control_setpoint.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_raw_aux.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_set_cam_shutter.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_set_position_control_offset.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_watchdog_command.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_watchdog_heartbeat.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_watchdog_process_info.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/mavlink_msg_watchdog_process_status.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/pixhawk.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/pixhawk/version.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_boot.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_control_surface.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_cpu_load.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_ctrl_srfc_pt.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_data_log.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_diagnostic.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_gps_date_time.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_isr_location.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_mid_lvl_cmds.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_novatel_diag.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_ptz_status.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_sensor_bias.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_sensor_diag.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_slugs_camera_order.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_slugs_configuration_camera.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_slugs_mobile_location.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_slugs_navigation.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_status_gps.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_uav_status.h \
    libs/mavlink/include/mavlink/v1.0/slugs/mavlink_msg_volt_sensor.h \
    libs/mavlink/include/mavlink/v1.0/slugs/slugs.h \
    libs/mavlink/include/mavlink/v1.0/slugs/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/slugs/version.h \
    libs/mavlink/include/mavlink/v1.0/test/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/test/mavlink_msg_test_types.h \
    libs/mavlink/include/mavlink/v1.0/test/test.h \
    libs/mavlink/include/mavlink/v1.0/test/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/test/version.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/mavlink.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/mavlink_msg_nav_filter_bias.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/mavlink_msg_radio_calibration.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/mavlink_msg_ualberta_sys_status.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/testsuite.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/ualberta.h \
    libs/mavlink/include/mavlink/v1.0/ualberta/version.h \
    libs/mavlink/include/mavlink/v1.0/checksum.h \
    libs/mavlink/include/mavlink/v1.0/mavlink_conversions.h \
    libs/mavlink/include/mavlink/v1.0/mavlink_helpers.h \
    libs/mavlink/include/mavlink/v1.0/mavlink_types.h \
    libs/mavlink/include/mavlink/v1.0/protocol.h \
    libs/qextserialport/examples/event/PortListener.h \
    libs/qextserialport/examples/qespta/MainWindow.h \
    libs/qextserialport/examples/qespta/MessageWindow.h \
    libs/qextserialport/examples/qespta/QespTest.h \
    libs/qextserialport/examples/uartassistant/dialog.h \
    libs/qextserialport/examples/uartassistant/hled.h \
    libs/qwt/qwt_array.h \
    libs/qwt/qwt_column_symbol.h \
    libs/qwt/qwt_compat.h \
    libs/qwt/qwt_data.h \
    libs/qwt/qwt_date.h \
    libs/qwt/qwt_date_scale_draw.h \
    libs/qwt/qwt_date_scale_engine.h \
    libs/qwt/qwt_double_interval.h \
    libs/qwt/qwt_double_range.h \
    libs/qwt/qwt_double_rect.h \
    libs/qwt/qwt_interval_data.h \
    libs/qwt/qwt_interval_symbol.h \
    libs/qwt/qwt_layout_metrics.h \
    libs/qwt/qwt_legend_item.h \
    libs/qwt/qwt_legend_itemmanager.h \
    libs/qwt/qwt_matrix_raster_data.h \
    libs/qwt/qwt_paint_buffer.h \
    libs/qwt/qwt_plot_abstract_barchart.h \
    libs/qwt/qwt_plot_barchart.h \
    libs/qwt/qwt_plot_directpainter.h \
    libs/qwt/qwt_plot_glcanvas.h \
    libs/qwt/qwt_plot_histogram.h \
    libs/qwt/qwt_plot_intervalcurve.h \
    libs/qwt/qwt_plot_legenditem.h \
    libs/qwt/qwt_plot_multi_barchart.h \
    libs/qwt/qwt_plot_printfilter.h \
    libs/qwt/qwt_plot_renderer.h \
    libs/qwt/qwt_plot_rescaler.h \
    libs/qwt/qwt_plot_shapeitem.h \
    libs/qwt/qwt_plot_spectrocurve.h \
    libs/qwt/qwt_plot_textlabel.h \
    libs/qwt/qwt_plot_tradingcurve.h \
    libs/qwt/qwt_plot_zoneitem.h \
    libs/qwt/qwt_point_3d.h \
    libs/qwt/qwt_point_polar.h \
    libs/qwt/qwt_polygon.h \
    libs/qwt/qwt_rect.h \
    libs/qwt/qwt_samples.h \
    libs/qwt/qwt_sampling_thread.h \
    libs/qwt/qwt_series_store.h \
    libs/qwt/qwt_system_clock.h \
    libs/qwt/qwt_valuelist.h \
    libs/thirdParty/libxbee/xsys/linux.h \
    libs/thirdParty/libxbee/xsys/win32.h \
    libs/thirdParty/libxbee/api.h \
    libs/thirdParty/libxbee/xbee.h \
    src/apps/qgcvideo/QGCVideoApp.h \
    src/apps/qgcvideo/QGCVideoMainWindow.h \
    src/apps/qgcvideo/QGCVideoWidget.h \
    src/comm/SerialInterface.h \
    src/qgcunittest/UASUnitTest.h \
    src/QtLocationPlugin/OpenPilotMaps.h \
    src/QtLocationPlugin/qgeocodereplyqgc.h \
    src/QtLocationPlugin/qgeocodingmanagerengineqgc.h \
    src/QtLocationPlugin/qgeomapreplyqgc.h \
    src/QtLocationPlugin/qgeoserviceproviderpluginqgc.h \
    src/QtLocationPlugin/qgeotiledmappingmanagerengineqgc.h \
    src/QtLocationPlugin/qgeotilefetcherqgc.h \
    src/smplayer/assstyles.h \
    src/smplayer/audioequalizerlist.h \
    src/smplayer/autohidewidget.h \
    src/smplayer/chapters.h \
    src/smplayer/colorutils.h \
    src/smplayer/config.h \
    src/smplayer/constants.h \
    src/smplayer/core.h \
    src/smplayer/desktopinfo.h \
    src/smplayer/discname.h \
    src/smplayer/extensions.h \
    src/smplayer/filehash.h \
    src/smplayer/filesettings.h \
    src/smplayer/filesettingsbase.h \
    src/smplayer/filesettingshash.h \
    src/smplayer/filters.h \
    src/smplayer/global.h \
    src/smplayer/helper.h \
    src/smplayer/images.h \
    src/smplayer/mediadata.h \
    src/smplayer/mediasettings.h \
    src/smplayer/mplayerprocess.h \
    src/smplayer/mplayerversion.h \
    src/smplayer/mplayerwindow.h \
    src/smplayer/myaction.h \
    src/smplayer/myactiongroup.h \
    src/smplayer/myprocess.h \
    src/smplayer/paths.h \
    src/smplayer/preferences.h \
    src/smplayer/recents.h \
    src/smplayer/subtracks.h \
    src/smplayer/titletracks.h \
    src/smplayer/tracks.h \
    src/smplayer/translator.h \
    src/smplayer/tvsettings.h \
    src/smplayer/urlhistory.h \
    src/ui/configuration/ParamWidget.h \
    src/ui/map3D/GLOverlayGeode.h \
    src/ui/map3D/ObstacleGroupNode.h \
    src/ui/map3D/QGCGlut.h \
    src/ui/map3D/QGCWebPage.h \
    src/ui/map3D/QMap3D.h \
    src/ui/MapWidget.h \
    src/ui/OgreWidget.h \
    src/ui/QGCWebView.h \
    CodingStyle.h

SOURCES += \
    src/main.cc \
    src/QGCApplication.cc \
    src/QGCSingleton.cc \
    src/uas/UASManager.cc \
    src/uas/UAS.cc \
    src/comm/LinkManager.cc \
    src/comm/SerialLink.cc \
    src/comm/MAVLinkProtocol.cc \
    src/comm/QGCFlightGearLink.cc \
    src/comm/QGCJSBSimLink.cc \
    src/comm/QGCXPlaneLink.cc \
    src/ui/SerialConfigurationWindow.cc \
    src/ui/MainWindow.cc \
    src/ui/uas/UASControlWidget.cc \
    src/ui/uas/UASListWidget.cc \
    src/ui/uas/UASInfoWidget.cc \
    src/ui/HUD.cc \
    src/ui/linechart/LinechartWidget.cc \
    src/ui/linechart/LinechartPlot.cc \
    src/ui/linechart/Scrollbar.cc \
    src/ui/linechart/ScrollZoomer.cc \
    src/ui/uas/UASView.cc \
    src/ui/CameraView.cc \
    src/comm/MAVLinkSimulationLink.cc \
    src/comm/UDPLink.cc \
    src/comm/TCPLink.cc \
    src/ui/ParameterInterface.cc \
    src/ui/WaypointList.cc \
    src/Waypoint.cc \
    src/input/JoystickInput.cc \
    src/ui/JoystickWidget.cc \
    src/ui/DebugConsole.cc \
    src/ui/HDDisplay.cc \
    src/ui/MAVLinkSettingsWidget.cc \
    src/GAudioOutput.cc \
    src/LogCompressor.cc \
    src/ui/QGCParamWidget.cc \
    src/ui/QGCSensorSettingsWidget.cc \
    src/ui/linechart/Linecharts.cc \
    src/uas/UASWaypointManager.cc \
    src/ui/HSIDisplay.cc \
    src/QGC.cc \
    src/ui/QGCDataPlot2D.cc \
    src/ui/linechart/IncrementalPlot.cc \
    src/ui/QGCMainWindowAPConfigurator.cc \
    src/comm/MAVLinkSwarmSimulationLink.cc \
    src/ui/uas/QGCUnconnectedInfoWidget.cc \
    src/ui/designer/QGCToolWidget.cc \
    src/ui/designer/QGCParamSlider.cc \
    src/ui/designer/QGCCommandButton.cc \
    src/ui/designer/QGCToolWidgetItem.cc \
    src/ui/designer/QGCToolWidgetComboBox.cc \
    src/ui/designer/QGCTextLabel.cc \
    src/ui/designer/QGCRadioChannelDisplay.cpp \
    src/ui/designer/QGCXYPlot.cc \
    src/ui/designer/RCChannelWidget.cc \
    src/ui/QGCMAVLinkLogPlayer.cc \
    src/comm/MAVLinkSimulationWaypointPlanner.cc \
    src/comm/MAVLinkSimulationMAV.cc \
    src/uas/QGCMAVLinkUASFactory.cc \
    src/ui/QGCWaypointListMulti.cc \
    src/ui/QGCUASFileViewMulti.cc \
    src/ui/QGCTCPLinkConfiguration.cc \
    src/ui/SettingsDialog.cc \
    src/uas/QGCUASParamManager.cc \
    src/ui/map/QGCMapWidget.cc \
    src/ui/map/MAV2DIcon.cc \
    src/ui/map/Waypoint2DIcon.cc \
    src/ui/map/QGCMapTool.cc \
    src/ui/map/QGCMapToolBar.cc \
    src/ui/QGCMAVLinkInspector.cc \
    src/ui/MAVLinkDecoder.cc \
    src/ui/WaypointViewOnlyView.cc \
    src/ui/WaypointEditableView.cc \
    src/ui/QGCRGBDView.cc \
    src/ui/mavlink/QGCMAVLinkMessageSender.cc \
    src/ui/QGCPluginHost.cc \
    src/ui/mission/QGCMissionOther.cc \
    src/ui/mission/QGCMissionNavWaypoint.cc \
    src/ui/mission/QGCMissionDoJump.cc \
    src/ui/mission/QGCMissionConditionDelay.cc \
    src/ui/mission/QGCMissionNavLoiterUnlim.cc \
    src/ui/mission/QGCMissionNavLoiterTurns.cc \
    src/ui/mission/QGCMissionNavLoiterTime.cc \
    src/ui/mission/QGCMissionNavReturnToLaunch.cc \
    src/ui/mission/QGCMissionNavLand.cc \
    src/ui/mission/QGCMissionNavTakeoff.cc \
    src/ui/mission/QGCMissionNavSweep.cc \
    src/ui/mission/QGCMissionDoStartSearch.cc \
    src/ui/mission/QGCMissionDoFinishSearch.cc \
    src/ui/QGCHilConfiguration.cc \
    src/ui/QGCHilFlightGearConfiguration.cc \
    src/ui/QGCHilJSBSimConfiguration.cc \
    src/ui/QGCHilXPlaneConfiguration.cc \
    src/ui/uas/UASQuickViewItem.cc \
    src/ui/uas/UASQuickView.cc \
    src/ui/linechart/ChartPlot.cc \
    src/ui/uas/UASQuickViewTextItem.cc \
    src/ui/uas/UASQuickViewGaugeItem.cc \
    src/ui/uas/UASQuickViewItemSelect.cc \
    src/ui/QGCTabbedInfoView.cpp \
    src/ui/UASRawStatusView.cpp \
    src/ui/PrimaryFlightDisplay.cc \
    src/ui/JoystickButton.cc \
    src/ui/JoystickAxis.cc \
    src/ui/uas/UASMessageView.cc \
    src/ui/configuration/terminalconsole.cpp \
    src/ui/configuration/console.cpp \
    src/ui/configuration/SerialSettingsDialog.cc \
    src/ui/configuration/ApmHighlighter.cc \
    src/uas/UASParameterDataModel.cc \
    src/uas/UASParameterCommsMgr.cc \
    src/ui/QGCPendingParamWidget.cc \
    src/ui/QGCBaseParamWidget.cc \
    src/ui/px4_configuration/PX4RCCalibration.cc \
    src/ui/px4_configuration/RCValueWidget.cc \
    src/uas/QGCUASFileManager.cc \
    src/ui/QGCUASFileView.cc \
    src/CmdLineOptParser.cc \
    src/QGCFileDialog.cc \
    src/ui/uas/UASQuickTabView.cpp \
    src/QGCComboBox.cc \
    src/QGCTemporaryFile.cc \
    src/audio/QGCAudioWorker.cpp \
    src/QGCQuickWidget.cc \
    src/QGCPalette.cc \
    src/QGCQmlWidgetHolder.cpp \
    src/ui/QGCParamTreeWidget.cpp \
    src/ui/QGCMapRCToParamDialog.cpp \
    src/QGCDockWidget.cc \
    src/ui/QGCLinkConfiguration.cc \
    src/comm/LinkConfiguration.cc \
    src/ui/QGCCommConfiguration.cc \
    src/ui/QGCUDPLinkConfiguration.cc \
    src/uas/UASMessageHandler.cc \
    src/ui/toolbar/MainToolBar.cc \
    src/QmlControls/ScreenTools.cc \
    src/QGCLoggingCategory.cc \
    src/ui/qgcvideoview.cpp \
    src/ui/flightdisplay/QGCFlightDisplay.cc \
    libs/qextserialport/examples/enumerator/main.cpp \
    libs/qextserialport/examples/event/main.cpp \
    libs/qextserialport/examples/event/PortListener.cpp \
    libs/qextserialport/examples/qespta/main.cpp \
    libs/qextserialport/examples/qespta/MainWindow.cpp \
    libs/qextserialport/examples/qespta/MessageWindow.cpp \
    libs/qextserialport/examples/qespta/QespTest.cpp \
    libs/qextserialport/examples/uartassistant/dialog.cpp \
    libs/qextserialport/examples/uartassistant/hled.cpp \
    libs/qextserialport/examples/uartassistant/main.cpp \
    libs/qwt/qwt_column_symbol.cpp \
    libs/qwt/qwt_data.cpp \
    libs/qwt/qwt_date.cpp \
    libs/qwt/qwt_date_scale_draw.cpp \
    libs/qwt/qwt_date_scale_engine.cpp \
    libs/qwt/qwt_double_interval.cpp \
    libs/qwt/qwt_double_range.cpp \
    libs/qwt/qwt_double_rect.cpp \
    libs/qwt/qwt_interval_data.cpp \
    libs/qwt/qwt_interval_symbol.cpp \
    libs/qwt/qwt_layout_metrics.cpp \
    libs/qwt/qwt_legend_item.cpp \
    libs/qwt/qwt_matrix_raster_data.cpp \
    libs/qwt/qwt_paint_buffer.cpp \
    libs/qwt/qwt_plot_abstract_barchart.cpp \
    libs/qwt/qwt_plot_barchart.cpp \
    libs/qwt/qwt_plot_directpainter.cpp \
    libs/qwt/qwt_plot_glcanvas.cpp \
    libs/qwt/qwt_plot_histogram.cpp \
    libs/qwt/qwt_plot_intervalcurve.cpp \
    libs/qwt/qwt_plot_legenditem.cpp \
    libs/qwt/qwt_plot_multi_barchart.cpp \
    libs/qwt/qwt_plot_print.cpp \
    libs/qwt/qwt_plot_printfilter.cpp \
    libs/qwt/qwt_plot_renderer.cpp \
    libs/qwt/qwt_plot_rescaler.cpp \
    libs/qwt/qwt_plot_shapeitem.cpp \
    libs/qwt/qwt_plot_spectrocurve.cpp \
    libs/qwt/qwt_plot_textlabel.cpp \
    libs/qwt/qwt_plot_tradingcurve.cpp \
    libs/qwt/qwt_plot_zoneitem.cpp \
    libs/qwt/qwt_point_3d.cpp \
    libs/qwt/qwt_point_polar.cpp \
    libs/qwt/qwt_rect.cpp \
    libs/qwt/qwt_sampling_thread.cpp \
    libs/qwt/qwt_system_clock.cpp \
    src/apps/qgcvideo/main.cc \
    src/apps/qgcvideo/QGCVideoApp.cc \
    src/apps/qgcvideo/QGCVideoMainWindow.cc \
    src/apps/qgcvideo/QGCVideoWidget.cc \
    src/qgcunittest/MockMavlinkInterface.cc \
    src/qgcunittest/UASUnitTest.cc \
    src/QtLocationPlugin/OpenPilotMaps.cc \
    src/QtLocationPlugin/qgeocodereplyqgc.cpp \
    src/QtLocationPlugin/qgeocodingmanagerengineqgc.cpp \
    src/QtLocationPlugin/qgeomapreplyqgc.cpp \
    src/QtLocationPlugin/qgeoserviceproviderpluginqgc.cpp \
    src/QtLocationPlugin/qgeotiledmappingmanagerengineqgc.cpp \
    src/QtLocationPlugin/qgeotilefetcherqgc.cpp \
    src/smplayer/assstyles.cpp \
    src/smplayer/autohidewidget.cpp \
    src/smplayer/chapters.cpp \
    src/smplayer/colorutils.cpp \
    src/smplayer/core.cpp \
    src/smplayer/desktopinfo.cpp \
    src/smplayer/discname.cpp \
    src/smplayer/extensions.cpp \
    src/smplayer/filehash.cpp \
    src/smplayer/filesettings.cpp \
    src/smplayer/filesettingsbase.cpp \
    src/smplayer/filesettingshash.cpp \
    src/smplayer/filters.cpp \
    src/smplayer/global.cpp \
    src/smplayer/helper.cpp \
    src/smplayer/images.cpp \
    src/smplayer/mediadata.cpp \
    src/smplayer/mediasettings.cpp \
    src/smplayer/mplayerprocess.cpp \
    src/smplayer/mplayerversion.cpp \
    src/smplayer/mplayerwindow.cpp \
    src/smplayer/myaction.cpp \
    src/smplayer/myactiongroup.cpp \
    src/smplayer/myprocess.cpp \
    src/smplayer/paths.cpp \
    src/smplayer/preferences.cpp \
    src/smplayer/recents.cpp \
    src/smplayer/subtracks.cpp \
    src/smplayer/titletracks.cpp \
    src/smplayer/tracks.cpp \
    src/smplayer/translator.cpp \
    src/smplayer/tvsettings.cpp \
    src/smplayer/urlhistory.cpp \
    src/ui/configuration/ParamWidget.cc \
    src/ui/configuration/TerminalConsole.cc \
    src/ui/designer/QGCParamSliderPlugin.cc \
    src/ui/map3D/GLOverlayGeode.cc \
    src/ui/map3D/ObstacleGroupNode.cc \
    src/ui/map3D/QGCWebPage.cc \
    src/ui/InputConfiguration.cc \
    src/ui/MapWidget.cc \
    src/ui/OgreWidget.cc \
    src/ui/QGCWebView.cc \
    CodingStyle.cc \
    libs/thirdParty/libxbee/sample/analog.c \
    libs/thirdParty/libxbee/sample/api.c \
    libs/thirdParty/libxbee/sample/atis.c \
    libs/thirdParty/libxbee/sample/atsetup.c \
    libs/thirdParty/libxbee/sample/callback.c \
    libs/thirdParty/libxbee/sample/digital.c \
    libs/thirdParty/libxbee/sample/digitalout.c \
    libs/thirdParty/libxbee/sample/multi.c \
    libs/thirdParty/libxbee/sample/scan.c \
    libs/thirdParty/libxbee/sample/scan_adv.c \
    libs/thirdParty/libxbee/sample/simple.c \
    libs/thirdParty/libxbee/sample/talk_to_me.c \
    libs/thirdParty/libxbee/sample/xbee2_rx.c \
    libs/thirdParty/libxbee/sample/xbee2_tx.c \
    libs/thirdParty/libxbee/xsys/linux.c \
    libs/thirdParty/libxbee/xsys/win32.c \
    libs/thirdParty/libxbee/xsys/win32.dll.c \
    libs/thirdParty/libxbee/api.c \
    libs/thirdParty/libxbee/main.c

#FORMS += libs/qextserialport/examples/uartassistant/dialog.ui

#
# Unit Test specific configuration goes here
#
# We have to special case Windows debug_and_release builds because you can't have files
# which are only in the debug variant [QTBUG-40351]. So in this case we include unit tests
# even in the release variant. If you want a Windows release build with no unit tests run
# qmake with CONFIG-=debug_and_release CONFIG+=release.
#

DebugBuild|WindowsDebugAndRelease {

INCLUDEPATH += \
	src/qgcunittest

HEADERS += \
    src/qgcunittest/UnitTest.h \
    src/qgcunittest/MessageBoxTest.h \
    src/qgcunittest/FileDialogTest.h \
    src/qgcunittest/MockLink.h \
    src/qgcunittest/MockLinkMissionItemHandler.h \
	src/qgcunittest/MockUASManager.h \
	src/qgcunittest/MockUAS.h \
	src/qgcunittest/MockQGCUASParamManager.h \
	src/qgcunittest/MockMavlinkInterface.h \
	src/qgcunittest/MockMavlinkFileServer.h \
	src/qgcunittest/MultiSignalSpy.h \
	src/qgcunittest/FlightGearTest.h \
	src/qgcunittest/TCPLinkTest.h \
	src/qgcunittest/TCPLoopBackServer.h \
	src/qgcunittest/QGCUASFileManagerTest.h \
    src/qgcunittest/PX4RCCalibrationTest.h \
    src/qgcunittest/LinkManagerTest.h \
    src/qgcunittest/MainWindowTest.h \
    src/qgcunittest/MavlinkLogTest.h \
    src/FactSystem/FactSystemTestBase.h \
    src/FactSystem/FactSystemTestPX4.h \
    src/FactSystem/FactSystemTestGeneric.h \
    src/QmlControls/QmlTestWidget.h \
    src/VehicleSetup/SetupViewTest.h \

SOURCES += \
    src/qgcunittest/UnitTest.cc \
    src/qgcunittest/MessageBoxTest.cc \
    src/qgcunittest/FileDialogTest.cc \
    src/qgcunittest/MockLink.cc \
    src/qgcunittest/MockLinkMissionItemHandler.cc \
	src/qgcunittest/MockUASManager.cc \
	src/qgcunittest/MockUAS.cc \
	src/qgcunittest/MockQGCUASParamManager.cc \
	src/qgcunittest/MockMavlinkFileServer.cc \
	src/qgcunittest/MultiSignalSpy.cc \
	src/qgcunittest/FlightGearTest.cc \
	src/qgcunittest/TCPLinkTest.cc \
	src/qgcunittest/TCPLoopBackServer.cc \
	src/qgcunittest/QGCUASFileManagerTest.cc \
    src/qgcunittest/PX4RCCalibrationTest.cc \
    src/qgcunittest/LinkManagerTest.cc \
    src/qgcunittest/MainWindowTest.cc \
    src/qgcunittest/MavlinkLogTest.cc \
    src/FactSystem/FactSystemTestBase.cc \
    src/FactSystem/FactSystemTestPX4.cc \
    src/FactSystem/FactSystemTestGeneric.cc \
    src/QmlControls/QmlTestWidget.cc \
    src/VehicleSetup/SetupViewTest.cc \

}

#
# AutoPilot Plugin Support
#

INCLUDEPATH += \
    src/VehicleSetup

FORMS += \
    src/VehicleSetup/ParameterEditor.ui \
    src/VehicleSetup/SetupView.ui \

HEADERS+= \
    src/VehicleSetup/SetupView.h \
    src/VehicleSetup/ParameterEditor.h \
    src/VehicleSetup/VehicleComponent.h \
    src/VehicleSetup/FirmwareUpgradeController.h \
    src/VehicleSetup/PX4Bootloader.h \
    src/VehicleSetup/PX4FirmwareUpgradeThread.h \
    src/AutoPilotPlugins/AutoPilotPluginManager.h \
    src/AutoPilotPlugins/AutoPilotPlugin.h \
    src/AutoPilotPlugins/Generic/GenericAutoPilotPlugin.h \
    src/AutoPilotPlugins/Generic/GenericParameterFacts.h \
    src/AutoPilotPlugins/PX4/PX4AutoPilotPlugin.h \
    src/AutoPilotPlugins/PX4/PX4Component.h \
    src/AutoPilotPlugins/PX4/RadioComponent.h \
    src/AutoPilotPlugins/PX4/FlightModesComponent.h \
    src/AutoPilotPlugins/PX4/FlightModesComponentController.h \
    src/AutoPilotPlugins/PX4/AirframeComponent.h \
    src/AutoPilotPlugins/PX4/AirframeComponentAirframes.h \
    src/AutoPilotPlugins/PX4/AirframeComponentController.h \
    src/AutoPilotPlugins/PX4/SensorsComponent.h \
    src/AutoPilotPlugins/PX4/SensorsComponentController.h \
    src/AutoPilotPlugins/PX4/SafetyComponent.h \
    src/AutoPilotPlugins/PX4/PowerComponent.h \
    src/AutoPilotPlugins/PX4/PX4ParameterFacts.h \

SOURCES += \
    src/VehicleSetup/SetupView.cc \
    src/VehicleSetup/ParameterEditor.cc \
    src/VehicleSetup/VehicleComponent.cc \
    src/VehicleSetup/FirmwareUpgradeController.cc \
    src/VehicleSetup/PX4Bootloader.cc \
    src/VehicleSetup/PX4FirmwareUpgradeThread.cc \
    src/AutoPilotPlugins/AutoPilotPluginManager.cc \
    src/AutoPilotPlugins/AutoPilotPlugin.cc \
    src/AutoPilotPlugins/Generic/GenericAutoPilotPlugin.cc \
    src/AutoPilotPlugins/Generic/GenericParameterFacts.cc \
    src/AutoPilotPlugins/PX4/PX4AutoPilotPlugin.cc \
    src/AutoPilotPlugins/PX4/PX4Component.cc \
    src/AutoPilotPlugins/PX4/RadioComponent.cc \
    src/AutoPilotPlugins/PX4/FlightModesComponent.cc \
    src/AutoPilotPlugins/PX4/FlightModesComponentController.cc \
    src/AutoPilotPlugins/PX4/AirframeComponent.cc \
    src/AutoPilotPlugins/PX4/AirframeComponentAirframes.cc \
    src/AutoPilotPlugins/PX4/AirframeComponentController.cc \
    src/AutoPilotPlugins/PX4/SensorsComponent.cc \
    src/AutoPilotPlugins/PX4/SensorsComponentController.cc \
    src/AutoPilotPlugins/PX4/SafetyComponent.cc \
    src/AutoPilotPlugins/PX4/PowerComponent.cc \
    src/AutoPilotPlugins/PX4/PX4ParameterFacts.cc \

# Fact System code

INCLUDEPATH += \
    src/FactSystem

HEADERS += \
    src/FactSystem/FactSystem.h \
    src/FactSystem/Fact.h \
    src/FactSystem/FactBinder.h \
    src/FactSystem/FactMetaData.h \
    src/FactSystem/FactValidator.h \
    src/FactSystem/ParameterLoader.h \

SOURCES += \
    src/FactSystem/FactSystem.cc \
    src/FactSystem/Fact.cc \
    src/FactSystem/FactBinder.cc \
    src/FactSystem/FactMetaData.cc \
    src/FactSystem/FactValidator.cc \
    src/FactSystem/ParameterLoader.cc \

CONFIG += c++11


