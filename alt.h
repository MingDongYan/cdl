#ifndef ALT_H
#define ALT_H

#include <vector>
#include "Polygon.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include <QPair>

namespace alt {

    //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
    cdl::Polygon GetRotatePolygon(cdl::Polygon t_polygon,QPointF c_point, double angle);

    cdl::Polygon GetRotatePolygon(QVector<QPointF> jzj_ps,const QPair<QPointF,double>& pos_pair);

    QVector<QPointF> getRotatePts(const QVector<QPointF> &jzj_ps, const QPair<QPointF,double>& pos_pair);

    /*! 旧的缩放函数，以缩放倍数进行缩放
    //分别对横向和纵向以不同倍数对碰撞轮廓放大缩小
    cdl::Polygon getScalePolygon(cdl::Polygon polygon, double weight_scale, double heigth_scale);

    cdl::Polygon getScalePolygon(const QVector<QPointF>& pts, double weight_scale, double heigth_scale);
    */
    //分别对横向和纵向 根据横向和纵向安全间距 进行缩放(jzj摆放方向朝右，则横向为y轴，纵向为x轴
//    cdl::Polygon getScalePolygon(cdl::Polygon polygon, double w_l, double l_l );

    cdl::Polygon getScalePolygon(const QVector<QPointF> &pts, double o_w ,
                                 double o_l , double safe_w, double safe_l );

    // 实际包围盒 >> 横向安全间距 >> 纵向安全间距(机首到机尾) >> 机首安全间距
    // 纵向安全间距区分 滑行 还是 牵引 状态 ，如果是滑行态，需要先减去尾喷长度
    QVector<QPointF> getScalePts(const QVector<QPointF> &pts, double safe_w, double safe_l , double head_l );

    //旋转并缩放包围和 获取当前真实轮廓点
    QVector<QPointF> getRealCurPts( const QVector<QPointF>& pts,const QPair<QPointF,double>& pos_pair ,
                                     double safe_w, double safe_l , double head_l );

    cdl::Polygon getPolygonFromVec(const QVector<QPointF>& vec);

    double GetAngle(QPointF p, QPointF o,double MinR);//返回在圆上点的圆心角（弧度）

    void qDebugPolygon(cdl::Polygon polygon);
}
#endif // ALT_H
