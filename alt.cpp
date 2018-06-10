#include "alt.h"

#include "CollisionDetection.hpp"

namespace alt {
cdl::Polygon getPolygonFromVec(const QVector<QPointF> &vec)
{
    std::vector<cdl::Vec2> t_p_corners;

    for(int i=0;i<vec.size();i++)
      {
          double p_x = vec[i].x();
          double p_y = vec[i].y();

          t_p_corners.push_back(cdl::Vec2(p_x,p_y));
      }

      return cdl::Polygon( t_p_corners );
}

QVector<QPointF> getRotatePts(const QVector<QPointF>& jzj_ps, const QPair<QPointF, double> &pos_pair)
{
    QVector<QPointF> ret_vec;
    for(int i=0;i < jzj_ps.size();i++)
      {
          //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
          double p_x = jzj_ps[i].x();
          double p_y = jzj_ps[i].y();
          double d = sqrt( p_x * p_x + p_y * p_y );
          double p_angle = GetAngle(QPointF(p_x,p_y),QPointF(0,0),d);
//          qDebug()<<"r_x:"<<p_x<<"r_y:"<<p_y;
          p_x=pos_pair.first.x()+d*cos( p_angle + pos_pair.second);
          p_y=pos_pair.first.y()+d*sin( p_angle + pos_pair.second);
          ret_vec.push_back(QPointF(p_x,p_y));
      }
    return ret_vec;
}



/*cdl::Polygon getScalePolygon(cdl::Polygon polygon, double w_l, double l_l)
{
    std::vector<cdl::Vec2> t_p_corners;

    std::vector<cdl::Vec2> bs_pologon = polygon.corners;

    for( cdl::Vec2 p : bs_pologon)
      {
          //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
          double p_x = p.x * w_l;
          double p_y = p.y * l_l;

          t_p_corners.push_back(cdl::Vec2(p_x,p_y));

      }

    cdl::Polygon t_p(t_p_corners);
    return t_p;
}*/

#define pi (3.141592654)
    cdl::Polygon GetRotatePolygon(cdl::Polygon t_polygon, QPointF c_point, double angle)
    {

        std::vector<cdl::Vec2> t_p_corners;
          for(int i=0;i<t_polygon.corners.size();i++)
          {
              //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
              double p_x=t_polygon.corners[i].x;
              double p_y=t_polygon.corners[i].y;
              double d=sqrt(p_x*p_x+p_y*p_y);
              double p_angle=GetAngle(QPointF(p_x,p_y),QPointF(0,0),d);
              p_x=c_point.x()+d*cos(p_angle+angle);
              p_y=c_point.y()+d*sin(p_angle+angle);
              t_p_corners.push_back(cdl::Vec2(p_x,p_y));
          }
          cdl::Polygon t_p(t_p_corners);
          return t_p;
    }
    double GetAngle(QPointF p, QPointF o,double MinR)//返回在圆上点的圆心角（弧度）
    {

            double delt_x=p.x()-o.x();
            double delt_y=p.y()-o.y();
            double alf;
            if(delt_y>0)
            {
                alf=acos((p.x()-o.x())/MinR);

            }
            else if(delt_x<0&&delt_y<0)
            {
                alf=2*pi-acos((p.x()-o.x())/MinR);

            }
            else
            {
                alf=2*pi-acos((p.x()-o.x())/MinR);

            }
            return alf;
    }

    cdl::Polygon GetRotatePolygon(QVector<QPointF> jzj_ps, const QPair<QPointF, double>& pos_pair)
    {
        std::vector<cdl::Vec2> t_p_corners;

        for(int i=0;i < jzj_ps.size();i++)
          {
              //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
              double p_x = jzj_ps[i].x();
              double p_y = jzj_ps[i].y();
              double d = sqrt(p_x*p_x+p_y*p_y);
              double p_angle = GetAngle( QPointF(p_x,p_y) , QPointF(0,0) , d );

              p_x=pos_pair.first.x()+d*cos(p_angle+pos_pair.second);
              p_y=pos_pair.first.y()+d*sin(p_angle+pos_pair.second);
              t_p_corners.push_back(cdl::Vec2(p_x,p_y));
          }

          cdl::Polygon t_p(t_p_corners);
          return t_p;
    }

    void qDebugPolygon(cdl::Polygon polygon)
    {
        std::vector<cdl::Vec2>::iterator iter = polygon.corners.begin();
        for(iter ; iter != polygon.corners.end();iter++)
        {
            qDebug()<<"Polygon"<<(*iter).x<<","<<(*iter).y;
        }
    }

    cdl::Polygon getScalePolygon(const QVector<QPointF> &pts, double o_w ,
                                 double o_l , double safe_w, double safe_l)
    {
        std::vector<cdl::Vec2> t_p_corners;

        for( QPointF p : pts)
          {
              //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
              double p_x = p.x() * ( o_l + safe_l ) / o_l;
              double p_y = p.y() * ( o_w + safe_w ) / o_w ;

              t_p_corners.push_back(cdl::Vec2(p_x,p_y));

          }

        cdl::Polygon t_p(t_p_corners);
        return t_p;
    }

    QVector<QPointF> getScalePts(const QVector<QPointF> &pts, double safe_w, double safe_l, double head_l)
    {
        QVector<QPointF> result;

        for( QPointF p : pts)
          {
//              //根据角度旋转并平移包围盒   水平向右为0度基准，逆时针旋转
//              result.push_back( QPointF( p.x() * ( o_l + safe_l ) / o_l ,
//                                         p.y() * ( o_w + safe_w ) / o_w ));
            double x , y;
            // 纵向
            if( fabs( p.x() ) > 1.0  )//1.0误差 坐标轴上的只进行延轴平移
                p.x() < 0 ? x = p.x() - safe_l + head_l : x = p.x()  + head_l ;
            else x = p.x();
            // 横向
            if( fabs( p.y() ) > 1.0  )
                p.y() < 0 ? y = p.y() - safe_w/2 : y = p.y()  + safe_w/2 ;
            else y = p.y();

            result.push_back( QPointF( x  , y ) );

          }

        return result;
    }

    QVector<QPointF> getRealCurPts(const QVector<QPointF>& pts, const QPair<QPointF,double>& pos_pair ,
                                   double safe_w, double safe_l, double head_l)
    {
        //先缩放 , 再旋转
        return getRotatePts( getScalePts( pts , safe_w , safe_l , head_l ) , pos_pair );
    }

}
