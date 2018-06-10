#include "polygonsdis.h"
namespace polygons_dis {

    // 向量AB 与 AC 的叉积 如果叉积大于0，那么C在向量AB的逆时针方向，叉积小于0则在AB的顺时针方向。如果叉积等于0，则ABC共线。
    inline double cross(QPointF A, QPointF B, QPointF C)
    {
        return ( B.x() - A.x() ) * ( C.y() - A.y() ) - ( B.y() - A.y() ) * ( C.x() - A.x() );
    }

    // 向量AB 与 AC 的点积 如果点积的结果为0，那么这两个向量互相垂直
    inline double multi(QPointF A, QPointF B, QPointF C)
    {
        return ( B.x() - A.x() ) * ( C.x() - A.x() ) + ( B.y() - A.y() ) * ( C.y() - A.y() );
    }

    // 两点距离
    double dist(QPointF A, QPointF B)
    {
        return sqrt( ( A.x() - B.x() ) * ( A.x() - B.x() ) + ( A.y() - B.y() ) * ( A.y() - B.y() ) );
    }

    // 逆时针排序
    QVector< QPointF > anticlockwise_sort(QVector< QPointF > ps )
    {
        QVector< QPointF > rt_pts;
        int N = ps.size();
        for (int i = 0; i < N - 2; ++i)
        {
            double tmp = cross( ps[ i ], ps[ i + 1 ], ps[ i + 2 ]);
            if (tmp > EPS) return ps;
            else if (tmp < -EPS)
            {
                //翻转向量
                while( !ps.isEmpty() )
                {
                    rt_pts.push_front( ps.first() );  //每次插到vector头部，这样不用反转
                    ps.pop_front();
                }
                return rt_pts;
            }
        }
    }

    //计算C点到线段AB的最短距离
    inline double point_to_line(QPointF A, QPointF B, QPointF C)
    {
        if (dist(A, B) < EPS) return dist(B, C);
        if (multi(A, B, C) < -EPS) return dist(A, C);
        if (multi(B, A, C) < -EPS) return dist(B, C);
        return fabs(cross(A, B, C) / dist(A, B));
    }

    //求一条线段的两端点到另外一条线段的距离，反过来一样，共4种情况
    inline double line_to_line(QPointF A, QPointF B, QPointF C, QPointF D ,
                               QPointF& rt_p , QPointF& rt_st_p , QPointF& rt_to_p )//间距最小的点和边
    {
        QPointF p_to_l[ 4 ][ 3 ] = {{ A , B , C },
                                   { A , B , D },
                                   { C , D , A },
                                   { C , D , B }};

        double min_dis = fabs( std::numeric_limits< double >::max() );
        for( int  i = 0 ; i < 4 ; i++ )
        {
            double c_dis = point_to_line( p_to_l[ i ][ 0 ] , p_to_l[ i ][ 1 ] , p_to_l[ i ][ 2 ]) ;
            if( c_dis < min_dis )
            {
                min_dis = c_dis;
                rt_p = p_to_l[ i ][ 2 ] ;
                rt_st_p = p_to_l[ i ][ 0 ] ;
                rt_to_p = p_to_l[ i ][ 1 ];
            }

        }
        return min_dis;
    }
    //求两凸多边形的最小间距
    double polygons_dis( QVector< QPointF >& P, QVector< QPointF >& Q ,
                         QPointF& rt_p , QPointF& rt_st_p , QPointF& rt_to_p )//多边形间距最小的点和边
    {
        int yminP = 0, ymaxQ = 0;
        int n = P.size() - 1;
        int m = Q.size() - 1;
        for (int i = 0; i < n; ++i) if ( P[ i ].y() < P[ yminP ].y() ) yminP = i;	// P上y坐标最小的顶点
        for (int i = 0; i < m; ++i) if ( Q[ i ].y() > Q[ ymaxQ ].y() ) ymaxQ = i; // Q上y坐标最大的顶点
        P[n] = P[0];	// 为了方便，避免求余
        Q[m] = Q[0];
        double arg, ans = INF;
        for (int i = 0; i < n; ++i)
        {
            while (arg = cross(P[yminP + 1], Q[ymaxQ + 1], P[yminP]) - cross(P[yminP + 1], Q[ymaxQ], P[yminP]) > EPS)
                ymaxQ = (ymaxQ + 1) % m;
            QPointF tmp_p , tmp_st_p ,  tmp_to_p;
            double tmp_dis = line_to_line(P[yminP], P[yminP + 1], Q[ymaxQ], Q[ymaxQ + 1] , tmp_p , tmp_st_p , tmp_to_p );
            if( ans > tmp_dis )
            {
                ans = tmp_dis;
                rt_p = tmp_p;
                rt_st_p = tmp_st_p;
                rt_to_p = tmp_to_p;
            }
            yminP = (yminP + 1) % n;
        }
        return ans;
    }
}
