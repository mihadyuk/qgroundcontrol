#ifndef WAYPOINTROUNDLINEITEM_H
#define WAYPOINTROUNDLINEITEM_H

//#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "../../opmapcontrol.h"

namespace mapcontrol {
//class WaypointRoundLineItem : public QObject,public QGraphicsLineItem
class WaypointRoundLineItem : public QObject,public QGraphicsPathItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Type = UserType + 7 };
    WaypointRoundLineItem(WayPointItem* wp1, WayPointItem* wp2, WayPointItem* wp3, int radius, QColor color=QColor(Qt::green), MapGraphicItem* parent=0);
    int type() const;

public slots:
    /**
    * @brief Update waypoint values
    *
    * @param waypoint The waypoint object that just changed
    */
    void updateWPValues(WayPointItem* waypoint);
    /**
    * @brief Update waypoint values
    */
    void updateWPValues();
    /**
    * @brief Update waypoint values
    *
    */
    void RefreshPos();

    //void drawPath(core::Point point1, core::Point point2, core::Point point3, int radius);

    //void drawPolygonAngle(Point* start, Point* end, Point* center, int radius);
    void drawPolygonAngle(Point* start, Point* center, Point* end, int radius);

    void getCurveAndCenterPoints(Point* p0, Point* p1, Point* p2, Point* Px1, Point* Px2, Point* Pc_r, int radius, double* paintAngle);
    void getCurveAndCenterPointsTest(Point* p0, Point* p1, Point* p2, Point* Px1, Point* Px2, Point* Pc_r, int radius, double* paintAngle);

    void getCurvePoint(Point* tmpPoint, int iter, Point* Pc_r, double startAngle);
protected:
    internals::PointLatLng point1;
    internals::PointLatLng point2;
    internals::PointLatLng point3;
    WayPointItem* wp1;
    WayPointItem* wp2;
    WayPointItem* wp3;
    int radius;
    MapGraphicItem* map;              ///< The map this item is parent of


    QPainter* painter;
};
}

#endif // WAYPOINTROUNDLINEITEM_H
