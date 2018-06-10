
#include "pdetect.h"
#include "PInPloy.h"

namespace pt_detect {

    //判断点是否在线段内( 精确判断)
    bool isOnline_Accurate(QPointF point, QPointF st_p,QPointF to_p)
    {
        PInPloy pin;
        return pin.IsOnline( point , st_p , to_p );
    }

    //只是判断点是否再两点之间(用于检测切点再哪对主通道节点间)
    bool isOnline_Area(QPointF point, QPointF st_p,QPointF to_p)
    {
        double x = point.x();
        double y = point.y();
        double x1 = st_p.x();
        double y1 = st_p.y();
        double x2 = to_p.x();
        double y2 = to_p.y();

        if( fabs(x - x1) == 0 && fabs(y - y1) == 0)
        {
            return true;
        }
        if(fabs(x - x2) == 0 && fabs( y - y2) == 0)
        {
            return true;
        }

        double ac_x = x - x1;
        double ac_y = y - y1;
        double mod_ac = distance( point , st_p );

        double bc_x = x - x2;
        double bc_y = y - y2;
        double mod_bc = distance( point , to_p );

        double ab_x = x2 - x1;
        double ab_y = y2 -y1;
        double mod_ab = distance( st_p , to_p );

        if(acos( VecDotVec( ac_x , ac_y , ab_x , ab_y ) / ( mod_ac * mod_ab ) ) > M_PI/2 ||
                acos ( VecDotVec( bc_x , bc_y , (-ab_x) , (-ab_y) ) / ( mod_bc * mod_ab ) ) > M_PI/2 )
          {
            return false;
        }
        else
        {
            return true;
        }
    }

    // 判断点在多边形内
    bool isInPolygon(const QVector<QPointF>& polygon,const QPointF& point)
    {
        PInPloy pin;
        return pin.isInPolygon( polygon , point );
    }

    double distance(QPointF p1, QPointF p2)
    {
        return sqrt( pow( p2.x() - p1.x() , 2 ) + pow( p2.y() - p1.y() , 2 ) );
    }

    double VecDotVec(double x1, double y1, double x2, double y2)
    {
        return x1*x2 + y1*y2;
    }

}
