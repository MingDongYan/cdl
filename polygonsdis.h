#ifndef POLYGONSDIS_H
#define POLYGONSDIS_H

#define EPS 1E-10
#define INF 0x3F3F3F3F

#include <vector>
#include <algorithm>

#include <QPointF>

#include <QVector>

using namespace std;

namespace polygons_dis {

    // 向量AB 与 AC 的叉积 如果叉积大于0，那么C在向量AB的逆时针方向，叉积小于0则在AB的顺时针方向。如果叉积等于0，则ABC共线。
    extern inline double cross(QPointF A, QPointF B, QPointF C);

    // 向量AB 与 AC 的点积 如果点积的结果为0，那么这两个向量互相垂直
    extern inline double multi(QPointF A, QPointF B, QPointF C);

    // 两点距离
    extern double dist(QPointF A, QPointF B);

    // 逆时针排序
    extern QVector< QPointF > anticlockwise_sort(QVector< QPointF > ps );

    //计算C点到线段AB的最短距离
    extern inline double point_to_line(QPointF A, QPointF B, QPointF C);

    //求一条线段的两端点到另外一条线段的距离，反过来一样，共4种情况
    extern inline double line_to_line(QPointF A, QPointF B, QPointF C, QPointF D, QPointF &rt_p, QPointF &rt_st_p, QPointF &rt_to_p);

    //求两凸多边形的最小间距 ， 并返回确定最小间距的点与边
    extern double polygons_dis(QVector< QPointF >& P, QVector< QPointF >& Q ,
                        QPointF &rt_p, QPointF &rt_st_p, QPointF &rt_to_p);

}

#endif // POLYGONSDIS_H
