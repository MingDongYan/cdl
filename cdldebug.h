#ifndef CDLDEBUG_H
#define CDLDEBUG_H

#include "Polygon.hpp"
#include <QtDebug>

namespace cdlDebug {

    void cdl_qDebug( cdl::Polygon ps )
    {
        std::vector<cdl::Vec2> vec = ps.corners;
        for( cdl::Vec2 p : vec )
        {
            qDebug()<<"x:"<<p.x<<"y:"<<p.y;
        }
    }

    void cdl_qDebug( QVector<QPointF> ps )
    {
        for( QPointF p : ps )
        {
            qDebug()<<"x:"<<p.x()<<"y:"<<p.y();
        }
    }
}

#endif // CDLDEBUG_H
