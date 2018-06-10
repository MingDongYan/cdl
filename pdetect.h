#ifndef PDETECT_H
#define PDETECT_H
#define _USE_MATH_DEFINES
#include <QPointF>
#include <QVector>
namespace pt_detect {

    //判断点是否在线段内( 精确判断)
    bool isOnline_Accurate(QPointF point, QPointF st_p,QPointF to_p);

    //只是判断点是否再两点之间(用于检测切点再哪对主通道节点间)
    bool isOnline_Area(QPointF point, QPointF st_p,QPointF to_p);

    // 判断点在多边形内
    bool isInPolygon(const QVector<QPointF>& polygon,const QPointF& point);

    //两点距离
    double distance( QPointF p1, QPointF p2 );

    //向量点乘
    double VecDotVec(double x1, double y1, double x2, double y2);

}

#endif // PDETECT_H
