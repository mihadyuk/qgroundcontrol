#include "waypointroundlineitem.h"

namespace mapcontrol
{
WaypointRoundLineItem::WaypointRoundLineItem(WayPointItem* wp1, WayPointItem* wp2, WayPointItem* wp3, int radius, QColor color, mapcontrol::MapGraphicItem* map) :
        //QGraphicsLineItem(map),
    QGraphicsPathItem(map),
    wp1(wp1),
    wp2(wp2),
    wp3(wp3),
    radius(radius),
    map(map)
{
    // Make sure this stick to the map
    //this->setFlag(QGraphicsItem::Item,true);
    setParentItem(map);
    painter = new QPainter();


    // Set up the pen for this icon with the UAV color
    QPen pen(Qt::green);
    pen.setWidth(2);
    setPen(pen);

    point1 = wp1->Coord();
    point2 = wp2->Coord();
    point3 = wp3->Coord();

    // Pixel coordinates of the local points
    core::Point localPoint1 = map->FromLatLngToLocal(point1);
    core::Point localPoint2 = map->FromLatLngToLocal(point2);
    core::Point localPoint3 = map->FromLatLngToLocal(point3);

//    core::Point localPoint1 = map->FromLatLngToLocal(wp1->Coord());
//    core::Point localPoint2 = map->FromLatLngToLocal(wp2->Coord());
//    core::Point localPoint3 = map->FromLatLngToLocal(wp3->Coord());

    // Draw line
    //setLine(localPoint1.X(), localPoint1.Y(), localPoint2.X(), localPoint2.Y());
//    drawPath(localPoint1, localPoint2, localPoint3, radius);
    drawPolygonAngle(&localPoint1, &localPoint2, &localPoint3, radius);

    // Connect updates
    // Update line from both waypoints
    connect(wp1, SIGNAL(WPValuesChanged(WayPointItem*)), this, SLOT(updateWPValues(WayPointItem*)));
    connect(wp2, SIGNAL(WPValuesChanged(WayPointItem*)), this, SLOT(updateWPValues(WayPointItem*)));
    connect(wp3, SIGNAL(WPValuesChanged(WayPointItem*)), this, SLOT(updateWPValues(WayPointItem*)));
    // Delete line if one of the waypoints get deleted
    connect(wp1, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    connect(wp2, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    connect(wp3, SIGNAL(destroyed()), this, SLOT(deleteLater()));

    // Map Zoom and move
    connect(map, SIGNAL(mapChanged()), this, SLOT(updateWPValues()));
}

void WaypointRoundLineItem::RefreshPos()
{
    // Delete if either waypoint got deleted
    if (!wp1 || !wp2 || !wp3)
    {
        this->deleteLater();
    }
    else
    {
        // Set new pixel coordinates based on new global coordinates
        //QTimer::singleShot(0, this, SLOT(updateWPValues()));
        core::Point localPoint1 = map->FromLatLngToLocal(wp1->Coord());
        core::Point localPoint2 = map->FromLatLngToLocal(wp2->Coord());
        core::Point localPoint3 = map->FromLatLngToLocal(wp3->Coord());
        if (!localPoint1.IsEmpty() && !localPoint2.IsEmpty() && !localPoint3.IsEmpty())
        {
            //setLine(localPoint1.X(), localPoint1.Y(), localPoint2.X(), localPoint2.Y());
            drawPolygonAngle(&localPoint1, &localPoint2, &localPoint3, radius);
        }
    }
}

//void WaypointRoundLineItem::drawPath(Point point1, Point point2, Point point3, int radius){

//    Point t1, t2;

//    int l1n, l2n;

//    t1.SetX(point1.X() - point2.X());
//    t1.SetY(point1.Y() - point2.Y());

//    t2.SetX(point3.X() - point2.X());
//    t2.SetY(point3.Y() - point2.Y());

//    l1n = sqrt((t1.X())*(t1.X()) + (t1.Y())*(t1.Y()));
//    l2n = sqrt((t2.X())*(t2.X()) + (t2.Y())*(t2.Y()));




//}


void WaypointRoundLineItem::drawPolygonAngle(Point *start, Point *center, Point *end, int radius)
{

    //Q_UNUSED(center);
    //Q_UNUSED(radius);
    //Q_UNUSED(angle);

    QPainterPath path;
    Point* tmpPoint = new Point;

    int deltaX = center->X();
    int deltaY = center->Y();


    Point* p0 = new Point;//point start in new coord system
    Point* p1 = new Point;//center
    Point* p2 = new Point;//point end in new coord system


    p0->SetX(start->X() - deltaX);
    p0->SetY(-(start->Y() - deltaY));//transform from screen to north-east coords

    p1->SetX(0);
    p1->SetY(0);

    p2->SetX(end->X() - deltaX);
    p2->SetY(-(end->Y() - deltaY));//transform from screen to north-east coords

//    p2->SetX(end->X() - deltaX);
//    p2->SetY(end->Y() - deltaY);//transform from screen to north-east coords

    Point* Px1 = new Point;
    Point* Px2 = new Point;
    Point* Pc_r = new Point;
    double* paintAngle = new double;

    //getCurveAndCenterPointsTest(new Point((329 - 657), -(233 - 195)), new Point(0,0), new Point((741 - 657), -(488 - 195)), Px1, Px2, Pc_r, 80, paintAngle);
    getCurveAndCenterPoints(p0, p1, p2, Px1, Px2, Pc_r, radius, paintAngle);

    ////todo: draw angle points in NE coords, NOT in screen coords

    Point startVector;//zero-angle vector from Pc_r
    Point endVector;//vector between zero angle and beginning of startAngle


    /*//translate from temporary to view coords
    Px1->SetX(Px1->X() + deltaX);
    Px1->SetY(-(Px1->Y()) + deltaY);

    Px2->SetX(Px2->X() + deltaX);
    Px2->SetY(-(Px2->Y()) + deltaY);

    Pc_r->SetX(Pc_r->X() + deltaX);
    Pc_r->SetY(-(Pc_r->Y()) + deltaY);*/

    //screen coords of Px1 and Px2
    Point scrPx1, scrPx2;
    Point scrPc_r;

    scrPx1.SetX(Px1->X() + deltaX);
    scrPx1.SetY(-(Px1->Y()) + deltaY);

    scrPx2.SetX(Px2->X() + deltaX);
    scrPx2.SetY(-(Px2->Y()) + deltaY);

    scrPc_r.SetX(Pc_r->X() + deltaX);
    scrPc_r.SetY(-(Pc_r->Y()) + deltaY);

    path.moveTo(start->X(), start->Y());
    //path.lineTo(scrPx1.X(), scrPx1.Y());

    double dist1 = sqrt((Px1->X()/*-center->X()*/)*(Px1->X()/*-center->X()*/) +
                        (Px1->Y()/*-center->Y()*/)*(Px1->Y()/*-center->Y()*/));

    double dist2 = sqrt((Px2->X()/*-center->X()*/)*(Px2->X()/*-center->X()*/) +
                        (Px2->Y()/*-center->Y()*/)*(Px2->Y()/*-center->Y()*/));

    if(true/*(dist1 > radius)&&(dist2 > radius)*/){


    path.lineTo(scrPx1.X(), scrPx1.Y());///!!

    //coords of vectors in NE coords
//    startVector.SetX(-(Pc_r->X()));
//    startVector.SetY(Pc_r->Y() + radius);

    endVector.SetX(Px1->X() - Pc_r->X());
    endVector.SetY(Px1->Y() - Pc_r->Y());


    /*endVector.SetX(scrPx1.X() - scrPc_r.X());
    endVector.SetY(scrPx1.Y() - scrPc_r.Y());*/


//    startVector.SetX(scrPc_r.X());
//    startVector.SetY(scrPc_r.Y() + radius);

//    endVector.SetX(-(scrPx1.X() - scrPc_r.X()));
//    endVector.SetY(scrPx1.Y() - scrPc_r.Y());


    /*startVector.SetX(Pc_r->X() - radius);
    startVector.SetY(Pc_r->Y());

    endVector.SetX(Px1->X() - Pc_r->X());
    endVector.SetY(Px1->Y() - Pc_r->Y());*/

//    double scalMul = startVector.X()*endVector.X() + startVector.Y()*endVector.Y();
//    double modStart = sqrt(startVector.X()*startVector.X()+startVector.Y()*startVector.Y());
//    double modEnd = sqrt(endVector.X()*endVector.X()+endVector.Y()*endVector.Y());

    //double startAngle = acos(scalMul/(modStart*modEnd))*180.0/M_PI;//startAngle in degrees
    //TODO: use ATAN2 instead ACOS!!!!!
    //double startAngle = 0.0;

    //double startAngle = atan2(endVector.Y(), endVector.X())*180.0/M_PI;
    double startAngle = atan2(endVector.Y(), endVector.X())*180.0/M_PI;

    qDebug()<<"Start Angle:"<<startAngle;
    qDebug()<<"Paint Angle:"<<*paintAngle;

//    startAngle = fmod(startAngle,360);
//    if (startAngle < 0)
//        startAngle += 360;

    //startAngle = 270.0 - startAngle;
    double endAngle = startAngle + *paintAngle;
    qDebug()<<"End Angle:"<<endAngle;

//    endAngle = fmod(endAngle,360);
//    if (endAngle < 0)
//        endAngle += 360;

//    double d_phi = M_PI/180;

    qDebug()<<"scrPx1.X:"<<scrPx1.X();
    qDebug()<<"scrPx1.Y:"<<scrPx1.Y();


    for (int i = /*startAngle*/0.0; i < *paintAngle/*endAngle*/; i+=30.0)//draw angle arc
    //for (int i = endAngle; i > startAngle; i-=30.0)//draw angle arc
    {
//        tmpPoint.SetX(Pc_r->X() - radius*cos(startAngle + i*d_phi));

//        tmpPoint.SetY(Pc_r->Y() - radius*sin(startAngle + i*d_phi));
        getCurvePoint(tmpPoint, i, Pc_r, /*startAngle*/0);

//        tmpPoint->SetX(tmpPoint->X() + deltaX);
//        tmpPoint->SetY(-(tmpPoint->Y()) + deltaY);

        tmpPoint->SetX(tmpPoint->X() + deltaX);
        tmpPoint->SetY(-(tmpPoint->Y()) + deltaY);

        path.lineTo(tmpPoint->X(), tmpPoint->Y());
        qDebug()<<"X:"<<tmpPoint->X();
        qDebug()<<"Y:"<<tmpPoint->Y();
    }

    /*double d_phi = M_PI/180;
    for (int i = startAngle; i < endAngle; i+=30)//draw angle arc
    {
        tmpPoint->SetX(scrPc_r.X() + radius*cos(i*d_phi));

        tmpPoint->SetY(scrPc_r.Y() + radius*sin(i*d_phi));
        //getCurvePoint(tmpPoint, i,  new Point(80,80), 0.0);

//        tmpPoint->SetX(tmpPoint->X());
//        tmpPoint->SetY(tmpPoint->Y());

        path.lineTo(tmpPoint->X(), tmpPoint->Y());
        qDebug()<<"X:"<<tmpPoint->X();
        qDebug()<<"Y:"<<tmpPoint->Y();
    }*/

    qDebug()<<"scrPx2.X:"<<scrPx2.X();
    qDebug()<<"scrPx2.Y:"<<scrPx2.Y();

    //path.lineTo(Px2->X(), Px2->Y());
    path.lineTo(scrPx2.X(), scrPx2.Y());
    }
    else
    {
        path.lineTo(center->X(), center->Y());
    }
    //path.lineTo(scrPx2.X(), scrPx2.Y());


//    path.lineTo(Pc_r->X(), Pc_r->Y());
//    path.lineTo(Px1->X(), Px1->Y());

    path.lineTo(end->X(), end->Y());
    //debug lines
//    path.lineTo(Pc_r->X(), Pc_r->Y());

    path.lineTo(scrPc_r.X(), scrPc_r.Y());

    //path.lineTo(startVector.X() + deltaX, -(startVector.Y())+deltaY);
//    path.lineTo(Px1->X(), Px1->Y());
    path.lineTo(endVector.X() + deltaX, -(endVector.Y())+deltaY);


    this->setPath(path);

    delete p0;
    delete p1;
    delete p2;
    delete Px1;
    delete Px2;
    delete Pc_r;
    delete paintAngle;

    delete tmpPoint;
}

void WaypointRoundLineItem::getCurvePoint(Point* tmpPoint, int iter, Point* Pc_r, double startAngle)
{
    double d_phi = M_PI/180;

    tmpPoint->SetX(Pc_r->X() + radius*cos((startAngle + iter)*d_phi));

    //tmpPoint->SetY(Pc_r->Y() - radius*sin((startAngle + iter)*d_phi));
    tmpPoint->SetY(Pc_r->Y() + radius*sin((startAngle + iter)*d_phi));

}


//    Point tmpPoint;

//    int x = end->X() - start->X();
//    int y = end->Y() - start->Y();

//    //setLine(start->X(), start->Y(), end->X(), end->Y());
//    //int len = sqrt(x^2 + y^2);
//    int len = sqrt(x*x + y*y);
//    qDebug()<<"X&&"<<x<<"Y&&"<<y;

//    //QPolygon polygon;
//    //polygon << QPoint(start->X(), start->Y());

//    Point debugCenter;
//    Point mainCenter;
//    double debugRadius = len/2;
//    double mainRadius = 2*len;
//    double debugAngle = 180.0;
//    int n_segments = 180;

//    //double startAngle = qAcos((double)x/(double)len)*180.0/M_PI;
//    double angleBeta = 60*M_PI/180;
//    double startAngle = atan2(y,x);
////    if(startAngle > 0)
////        startAngle *=-1;
//    double curAngle = startAngle + angleBeta;

//    double circleLen = M_PI*debugRadius;

//    QPainterPath path;

//    debugCenter.SetX((end->X() + start->X())/2);
//    debugCenter.SetY((end->Y() + start->Y())/2);

//    path.moveTo(start->X(), start->Y());

//    qDebug()<<"START:";
//    qDebug()<<"x:"<<start->X()<<"y:"<<start->Y();

//    qDebug()<<"END:";
//    qDebug()<<"x:"<<end->X()<<"y:"<<end->Y();
//    qDebug()<<"startAngle"<<startAngle*180.0/M_PI;
//    qDebug()<<"debugRadius"<<debugRadius;

////    tmpPoint.SetX(start->X() + 200);
////    tmpPoint.SetY(start->Y());
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    tmpPoint.SetY(tmpPoint.Y()+200);
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    tmpPoint.SetX(start->X());
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    tmpPoint.SetY(start->Y());
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    this->setPath(path);
//    double d_phi = M_PI/180;

//    //for (int i = 0; i < 180; i++){
//    for (int i = angleBeta*180/M_PI; i < 180 - angleBeta*180/M_PI ; i++){//left and right angles

//        tmpPoint.SetX(debugCenter.X() - debugRadius*cos(startAngle + i*d_phi));

//        tmpPoint.SetY(debugCenter.Y() - debugRadius*sin(startAngle + i*d_phi));

////        curAngle = curAngle + 30.0;

//        path.lineTo(tmpPoint.X(), tmpPoint.Y());

//        /*qDebug()<<"Iteration:"<<i;
//        qDebug()<<"debugRadius*cos(curAngle)"<<debugRadius*qCos(curAngle*M_PI/180.0);
//        qDebug()<<"debugRadius*sin(curAngle)"<<debugRadius*qSin(curAngle*M_PI/180.0);
//        qDebug()<<"curAngle"<<curAngle;
//        qDebug()<<"cos(curAngle)"<<qCos(curAngle*M_PI/180.0);
//        qDebug()<<"sin(curAngle)"<<qSin(curAngle*M_PI/180.0);
//        qDebug()<<"X"<<tmpPoint.X();
//        qDebug()<<"Y"<<tmpPoint.Y();*/
//    }

//    path.lineTo(end->X(), end->Y());
//    path.lineTo(debugCenter.X(), debugCenter.Y());
//    this->setPath(path);
////    path.lineTo(end->X(), end->Y());
////    this->setPath(path);
//}

void WaypointRoundLineItem::getCurveAndCenterPoints(Point* p0, Point* p1, Point* p2, Point* Px1, Point* Px2, Point* Pc_r, int radius, double* paintAngle)
{

    Point t1;//vector p0 to p1
    Point t2;//vector p0 to p2

    double t1x, t1y, t2x, t2y;

    double l1n, l2n;//modules of t1 and t2 vectors

    double head_l1, head_l2, d_yaw, gamma;//angles

    t1.SetX(p0->X() - p1->X());
    t1.SetY(p0->Y() - p1->Y());

    t2.SetX(p2->X() - p1->X());
    t2.SetY(p2->Y() - p1->Y());

    l1n = sqrt((t1.X())*(t1.X()) + (t1.Y())*(t1.Y()));
    l2n = sqrt((t2.X())*(t2.X()) + (t2.Y())*(t2.Y()));

//    head_l1 = atan2(t1.Y(), t1.X())*180/M_PI;//in degrees
//    head_l2 = atan2(t2.Y(), t2.X())*180/M_PI;//in degrees

    //NE <=> YX in this function
    head_l1 = atan2(t1.X(), t1.Y())*180/M_PI;//in degrees
    head_l2 = atan2(t2.X(), t2.Y())*180/M_PI;//in degrees

    //wrap180 d_yaw
    d_yaw = head_l2 - head_l1;//in degrees
    while(d_yaw <= -180)
        d_yaw += 360;
    while(d_yaw > 180)
        d_yaw -= 360;

//    d_yaw = fmod(head_l2 - head_l1 + 180, 360);//in degrees
//    if(d_yaw < 0)
//        d_yaw += 360;
//    d_yaw -= 180;

    if(d_yaw >= 0)
        radius *= -1;

    //normalize t1
    if (l1n != 0)
    {
        t1x = (double)t1.X()/l1n;
        t1y = (double)t1.Y()/l1n;
//        t1.SetX(t1.X()/l1n);
//        t1.SetY(t1.Y()/l1n);
    }
    else
    {
        t1x = 0;
        t1y = 0;
//        t1.SetX(0);
//        t1.SetY(0);
    }

    //normalize t2
    if (l2n != 0)
    {
        t2x = (double)t2.X()/l2n;
        t2y = (double)t2.Y()/l2n;
//        t2.SetX(t2.X()/l2n);
//        t2.SetY(t2.Y()/l2n);
    }
    else
    {
        t2x = 0;
        t2y = 0;
//        t2.SetX(0);
//        t2.SetY(0);
    }

    gamma = d_yaw/2;//in degrees

    double sing = sin(gamma*M_PI/180.0);//in radians
    double cosg = cos(gamma*M_PI/180.0);//in radians

    //QMatrix C(cosg, -sing, sing, cosg);

    double C[2][2];

//    C[0][0] = cosg;
//    C[0][1] = sing;
//    C[1][0] = -sing;
//    C[1][1] = cosg;

    C[0][0] = cosg;
    C[0][1] = -sing;
    C[1][0] = sing;
    C[1][1] = cosg;

    double Rx = -(double)radius/sing;
    //Point Tx;
    double Txx, Txy;


    Txy = C[0][0]*t1y + C[0][1]*t1x;
    Txx = C[1][0]*t1y + C[1][1]*t1x;

//    Txx = C[0][0]*t1y + C[0][1]*t1x;
//    Txy = C[1][0]*t1y + C[1][1]*t1x;


//    Txx = C[0][0]*t1x + C[0][1]*t2y;
//    Txy = C[1][0]*t1x + C[1][1]*t2y;


    //Point Pc_r;

//    Pc_r->SetX(Tx.X()*Rx);
//    Pc_r->SetY(Tx.Y()*Rx);
    Pc_r->SetX(Txx*Rx);
    Pc_r->SetY(Txy*Rx);

    double delta_ln = -(double)radius/tan(gamma*M_PI/180.0);

    //coords of tangent points Px1, Px2
    //Point Px1, Px2;

    Px1->SetX(t1x*delta_ln);
    Px1->SetY(t1y*delta_ln);

    Px2->SetX(t2x*delta_ln);
    Px2->SetY(t2y*delta_ln);

//    Px1->SetX(t1.X()*delta_ln);
//    Px1->SetY(t1.Y()*delta_ln);

//    Px2->SetX(t2.X()*delta_ln);
//    Px2->SetY(t2.Y()*delta_ln);

    double angle_b = atan2(-t1y, -t1x)*180/M_PI;
    //double angle_b = atan2(-t1x, -t1y)*180/M_PI;//!!!!!CHANGE COORDS!!!!!
//    double angle_b = atan2(-t1.Y(), -t1.X())*180/M_PI;
    if(angle_b < 0)
        angle_b *=-1;
    //wrap360 angle_b    
    angle_b = fmod(angle_b,360);
    if (angle_b < 0)
        angle_b += 360;


    double angle_e = 2*(90 - abs(gamma));
    //wrap360 angle_e
    angle_e = fmod(angle_e,360);
    if (angle_e < 0)
        angle_e += 360;

    *paintAngle = 180.0 - fabs(d_yaw);
    //wrap180 paintAngle
//    while(*paintAngle <= -180)
//        *paintAngle += 360;
//    while(*paintAngle > 180)
//        *paintAngle -= 360;

}

void WaypointRoundLineItem::getCurveAndCenterPointsTest(Point* p0, Point* p1, Point* p2, Point* Px1, Point* Px2, Point* Pc_r, int radius, double* paintAngle)
{

    Point t1;//vector p0 to p1
    Point t2;//vector p0 to p2

    double t1x, t1y, t2x, t2y;

    double l1n, l2n;//modules of t1 and t2 vectors

    double head_l1, head_l2, d_yaw, gamma;//angles

    t1.SetX(p0->X() - p1->X());
    t1.SetY(p0->Y() - p1->Y());

    t2.SetX(p2->X() - p1->X());
    t2.SetY(p2->Y() - p1->Y());

//    t1.SetX(p0->Y() - p1->Y());
//    t1.SetY(p0->X() - p1->X());

//    t2.SetX(p2->Y() - p1->Y());
//    t2.SetY(p2->X() - p1->X());

    l1n = sqrt((t1.X())*(t1.X()) + (t1.Y())*(t1.Y()));
    l2n = sqrt((t2.X())*(t2.X()) + (t2.Y())*(t2.Y()));

//    head_l1 = atan2(t1.Y(), t1.X())*180/M_PI;//in degrees
//    head_l2 = atan2(t2.Y(), t2.X())*180/M_PI;//in degrees

    //NE <=> YX in this function
    head_l1 = atan2(t1.X(), t1.Y())*180/M_PI;//in degrees
    head_l2 = atan2(t2.X(), t2.Y())*180/M_PI;//in degrees

    qDebug()<<"t1.x"<<t1.X();
    qDebug()<<"t1.y"<<t1.Y();

    qDebug()<<"t2.x"<<t2.X();
    qDebug()<<"t2.y"<<t2.Y();

    qDebug()<<"l1n"<<l1n;
    qDebug()<<"l2n"<<l2n;

    qDebug()<<"head_l1"<<head_l1;
    qDebug()<<"head_l2"<<head_l2;



    //wrap180 d_yaw
    d_yaw = head_l2 - head_l1;//in degrees
    while(d_yaw <= -180)
        d_yaw += 360;
    while(d_yaw > 180)
        d_yaw -= 360;

    qDebug()<<"d_yaw"<<d_yaw;

//    d_yaw = fmod(head_l2 - head_l1 + 180, 360);//in degrees
//    if(d_yaw < 0)
//        d_yaw += 360;
//    d_yaw -= 180;

    if(d_yaw >= 0)
        radius *= -1;

    //normalize t1
    if (l1n != 0)
    {
        t1x = (double)t1.X()/l1n;
        t1y = (double)t1.Y()/l1n;
//        t1.SetX(t1.X()/l1n);
//        t1.SetY(t1.Y()/l1n);
    }
    else
    {
        t1x = 0;
        t1y = 0;
//        t1.SetX(0);
//        t1.SetY(0);
    }

    //normalize t2
    if (l2n != 0)
    {
        t2x = (double)t2.X()/l2n;
        t2y = (double)t2.Y()/l2n;
//        t2.SetX(t2.X()/l2n);
//        t2.SetY(t2.Y()/l2n);
    }
    else
    {
        t2x = 0;
        t2y = 0;
//        t2.SetX(0);
//        t2.SetY(0);
    }

    gamma = d_yaw/2;//in degrees

    qDebug()<<"gamma"<<gamma;

    double sing = sin(gamma*M_PI/180.0);//in radians
    double cosg = cos(gamma*M_PI/180.0);//in radians

    //QMatrix C(cosg, -sing, sing, cosg);

    double C[2][2];

//    C[0][0] = cosg;
//    C[0][1] = sing;
//    C[1][0] = -sing;
//    C[1][1] = cosg;

    C[0][0] = cosg;
    C[0][1] = -sing;
    C[1][0] = sing;
    C[1][1] = cosg;

    double Rx = -(double)radius/sing;
    //Point Tx;
    double Txx, Txy;

//    Tx.SetX(C[0][0]*t1x + C[0][1]*t2y);
//    Tx.SetY(C[1][0]*t1x + C[1][1]*t2y);

//    Tx.SetX(C[0][0]*t1.X() + C[0][1]*t2.Y());
//    Tx.SetY(C[1][0]*t1.X() + C[1][1]*t2.Y());

    Txx = C[0][0]*t1y + C[0][1]*t1x;
    Txy = C[1][0]*t1y + C[1][1]*t1x;

//    Txx = C[0][0]*t1x + C[0][1]*t2y;
//    Txy = C[1][0]*t1x + C[1][1]*t2y;

    qDebug()<<"Rx"<<Rx;
    qDebug()<<"Txx"<<Txx;
    qDebug()<<"Txy"<<Txy;

    //Point Pc_r;

//    Pc_r->SetX(Tx.X()*Rx);
//    Pc_r->SetY(Tx.Y()*Rx);
    Pc_r->SetX(Txx*Rx);
    Pc_r->SetY(Txy*Rx);

    qDebug()<<"Pc_r.x"<<Pc_r->X();
    qDebug()<<"Pc_r.y"<<Pc_r->Y();

    double delta_ln = -(double)radius/tan(gamma*M_PI/180.0);

    //coords of tangent points Px1, Px2
    //Point Px1, Px2;

    Px1->SetX(t1x*delta_ln);
    Px1->SetY(t1y*delta_ln);

    Px2->SetX(t2x*delta_ln);
    Px2->SetY(t2y*delta_ln);

    qDebug()<<"delta_ln"<<delta_ln;

    qDebug()<<"Px1.x"<<Px1->X();
    qDebug()<<"Px1.y"<<Px1->Y();

    qDebug()<<"Px2.x"<<Px2->X();
    qDebug()<<"Px2.y"<<Px2->Y();

//    Px1->SetX(t1.X()*delta_ln);
//    Px1->SetY(t1.Y()*delta_ln);

//    Px2->SetX(t2.X()*delta_ln);
//    Px2->SetY(t2.Y()*delta_ln);

    double angle_b = atan2(-t1x, -t1y)*180/M_PI;
    //double angle_b = atan2(-t1x, -t1y)*180/M_PI;//!!!!!CHANGE COORDS!!!!!
//    double angle_b = atan2(-t1.Y(), -t1.X())*180/M_PI;
    if(angle_b < 0)
        angle_b *=-1;
    //wrap360 angle_b
    angle_b = fmod(angle_b,360);
    if (angle_b < 0)
        angle_b += 360;


    double angle_e = 2*(90 - abs(gamma));
    //wrap360 angle_e
    angle_e = fmod(angle_e,360);
    if (angle_e < 0)
        angle_e += 360;

    qDebug()<<"angle_b"<<angle_b;
    qDebug()<<"angle_e"<<angle_e;

    *paintAngle = 180.0 - fabs(d_yaw);
    //wrap180 paintAngle
//    while(*paintAngle <= -180)
//        *paintAngle += 360;
//    while(*paintAngle > 180)
//        *paintAngle -= 360;

}


//void WaypointRoundLineItem::drawPolygonAngle(Point *start, Point *end, Point *center, int radius)
//{

//    Q_UNUSED(center);
//    Q_UNUSED(radius);
////    Q_UNUSED(angle);

//    Point tmpPoint;

//    int x = end->X() - start->X();
//    int y = end->Y() - start->Y();

//    //setLine(start->X(), start->Y(), end->X(), end->Y());
//    //int len = sqrt(x^2 + y^2);
//    int len = sqrt(x*x + y*y);
//    qDebug()<<"X&&"<<x<<"Y&&"<<y;

//    //QPolygon polygon;
//    //polygon << QPoint(start->X(), start->Y());

//    Point debugCenter;
//    Point mainCenter;
//    double debugRadius = len/2;
//    double mainRadius = 2*len;
//    double debugAngle = 180.0;
//    int n_segments = 180;

//    //double startAngle = qAcos((double)x/(double)len)*180.0/M_PI;
//    double angleBeta = 60*M_PI/180;
//    double startAngle = atan2(y,x);
////    if(startAngle > 0)
////        startAngle *=-1;
////    double curAngle = startAngle + angleBeta;

////    double circleLen = M_PI*debugRadius;

//    QPainterPath path;

//    debugCenter.SetX((end->X() + start->X())/2);
//    debugCenter.SetY((end->Y() + start->Y())/2);

//    path.moveTo(start->X(), start->Y());

//    qDebug()<<"START:";
//    qDebug()<<"x:"<<start->X()<<"y:"<<start->Y();

//    qDebug()<<"END:";
//    qDebug()<<"x:"<<end->X()<<"y:"<<end->Y();
//    qDebug()<<"startAngle"<<startAngle*180.0/M_PI;
//    qDebug()<<"debugRadius"<<debugRadius;

////    tmpPoint.SetX(start->X() + 200);
////    tmpPoint.SetY(start->Y());
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    tmpPoint.SetY(tmpPoint.Y()+200);
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    tmpPoint.SetX(start->X());
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    tmpPoint.SetY(start->Y());
////    path.lineTo(tmpPoint.X(), tmpPoint.Y());
////    this->setPath(path);
//    double d_phi = M_PI/180;

//    //for (int i = 0; i < 180; i++){
//    for (int i = angleBeta*180/M_PI; i < 180 - angleBeta*180/M_PI ; i++){//left and right angles

//        tmpPoint.SetX(debugCenter.X() - debugRadius*cos(startAngle + i*d_phi));

//        tmpPoint.SetY(debugCenter.Y() - debugRadius*sin(startAngle + i*d_phi));

////        curAngle = curAngle + 30.0;

//        path.lineTo(tmpPoint.X(), tmpPoint.Y());

//        /*qDebug()<<"Iteration:"<<i;
//        qDebug()<<"debugRadius*cos(curAngle)"<<debugRadius*qCos(curAngle*M_PI/180.0);
//        qDebug()<<"debugRadius*sin(curAngle)"<<debugRadius*qSin(curAngle*M_PI/180.0);
//        qDebug()<<"curAngle"<<curAngle;
//        qDebug()<<"cos(curAngle)"<<qCos(curAngle*M_PI/180.0);
//        qDebug()<<"sin(curAngle)"<<qSin(curAngle*M_PI/180.0);
//        qDebug()<<"X"<<tmpPoint.X();
//        qDebug()<<"Y"<<tmpPoint.Y();*/
//    }

//    path.lineTo(end->X(), end->Y());
//    path.lineTo(debugCenter.X(), debugCenter.Y());
//    this->setPath(path);
////    path.lineTo(end->X(), end->Y());
////    this->setPath(path);
//}

void WaypointRoundLineItem::updateWPValues(WayPointItem* waypoint)
{
    Q_UNUSED(waypoint);
    // Delete if either waypoint got deleted
    if (!wp1 || !wp2 || !wp3)
    {
        this->deleteLater();
    }
    else
    {
        // Set new pixel coordinates based on new global coordinates
        point1 = wp1->Coord();
        point2 = wp2->Coord();
        point3 = wp3->Coord();
        core::Point localPoint1 = map->FromLatLngToLocal(point1);
        core::Point localPoint2 = map->FromLatLngToLocal(point2);
        core::Point localPoint3 = map->FromLatLngToLocal(point3);


        //setLine(localPoint1.X(), localPoint1.Y(), localPoint2.X(), localPoint2.Y());
        drawPolygonAngle(&localPoint1, &localPoint2, &localPoint3, radius);

    }
}

void WaypointRoundLineItem::updateWPValues()
{
    updateWPValues(NULL);
}

int WaypointRoundLineItem::type()const
{
    return Type;
}

}
