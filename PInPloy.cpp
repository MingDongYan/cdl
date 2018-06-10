#include"PInPloy.h"
#include<QtDebug>

PInPloy::PInPloy()
{

}
// 计算叉乘 |P0P1| × |P0P2|
double PInPloy::Multiply(QPointF p1, QPointF p2, QPointF p0)
{
    return ( (p1.x() - p0.x()) * (p2.y() - p0.y()) - (p2.x() - p0.x()) * (p1.y() - p0.y()) );
}

// 判断线段是否包含点point
bool PInPloy::IsOnline(QPointF point, LineSegment line)
{
    return( ( fabs(Multiply(line.pt1, line.pt2, point)) < ESP ) &&
    ( ( point.x() - line.pt1.x() ) * ( point.x() - line.pt2.x() ) <= 0 ) &&
    ( ( point.y() - line.pt1.y() ) * ( point.y() - line.pt2.y() ) <= 0 ) );
}

bool PInPloy::IsOnline(QPointF point, QPointF st_p,QPointF to_p)
{
    return( ( fabs(Multiply(st_p, to_p , point)) < ESP ) &&
    ( ( point.x() - st_p.x() ) * ( point.x() - to_p.x() ) <= 0 ) &&
    ( ( point.y() - st_p.y() ) * ( point.y() - to_p.y() ) <= 0 ) );
}

// 判断线段相交
bool PInPloy::Intersect(LineSegment L1, LineSegment L2)
{
    return( (max(L1.pt1.x(), L1.pt2.x()) >= min(L2.pt1.x(), L2.pt2.x())) &&
    (max(L2.pt1.x(), L2.pt2.x()) >= min(L1.pt1.x(), L1.pt2.x())) &&
    (max(L1.pt1.y(), L1.pt2.y()) >= min(L2.pt1.y(), L2.pt2.y())) &&
    (max(L2.pt1.y(), L2.pt2.y()) >= min(L1.pt1.y(), L1.pt2.y())) &&
    (Multiply(L2.pt1, L1.pt2, L1.pt1) * Multiply(L1.pt2, L2.pt2, L1.pt1) >= 0) &&
    (Multiply(L1.pt1, L2.pt2, L2.pt1) * Multiply(L2.pt2, L1.pt2, L2.pt1) >= 0)
    );
}

// 判断点在多边形内
bool PInPloy::isInPolygon(const QVector<QPointF>& polygon,const  QPointF& point)
{
    int n = polygon.size();
    int count = 0;
    LineSegment line;
    line.pt1 = point;
    line.pt2.setX(point.x());
    line.pt2.setY(- INFINITY);

    for( int i = 0; i < n; i++ ) {
        // 得到多边形的一条边
        LineSegment side;
        side.pt1 = polygon[i];
        side.pt2 = polygon[(i + 1) % n];
     //判断已知点是否在边上
    if( IsOnline(point, side) ) {
    return 1 ;
    }

    // 如果side平行y轴则不作考虑
    if( fabs(side.pt1.x() - side.pt2.x()) < ESP ) {
    continue;
    }

    if( IsOnline(side.pt1, line) )
    {
    if( side.pt1.x() > side.pt2.x() ) count++;
    }
    else if( IsOnline(side.pt2, line) )
    {
    if( side.pt2.x()> side.pt1.x() ) count++;
    }
    else if( Intersect(line, side) )
    {
    count++;
    }
    }

     if ( count % 2 == 1 ) { return true; }
    else { return false; }

}

PInPloy* PInPloy::m_pInstance = new PInPloy();

PInPloy * PInPloy::getInstance()
{
    return m_pInstance;
}
