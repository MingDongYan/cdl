#define _USE_MATH_DEFINES
#undef __STRICT_ANSI__
#include <math.h>
#include <QVector>
#include <QPointF>
using namespace std;

const double ESP = 1e-5; 
const int MAX_N = 1000; 
//定义点
struct LineSegment
{
    QPointF pt1, pt2;
};
class PInPloy
{
public:

    PInPloy();
    // 计算叉乘 |P0P1| × |P0P2|
    double Multiply(QPointF p1, QPointF p2, QPointF p0);
    // 判断线段是否包含点point
    bool IsOnline(QPointF point, LineSegment line);

    bool IsOnline(QPointF point, QPointF st_p,QPointF to_p);

    // 判断线段相交
    bool Intersect(LineSegment L1, LineSegment L2) ;
    // 判断点在多边形内
    bool isInPolygon(const QVector<QPointF>& polygon,const QPointF& point);


    /****************/
    /*   单例类      */
    /****************/
public:
    static PInPloy *getInstance();
private:
    static PInPloy* m_pInstance;
    class CGarbo   //它的唯一工作就是在析构函数中删除CSingleton的实例
        {
        public:
            ~CGarbo()
            {
                if(PInPloy::m_pInstance)
                    delete PInPloy::m_pInstance;
            }
        };
    static CGarbo Garbo;  //定义一个静态成员变量，程序结束时，
protected:

};
 
