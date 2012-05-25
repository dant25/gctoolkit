#ifndef _GRAHAM_H_
#define _GRAHAM_H_

#include<list>
#include <map>
#include <stack>
#include <cmath>
#include "Point2D.h"
#include "Edge2D.h"

class Graham2D
{
    public:
        Graham2D(std::list<Point*> pointList);
        ~Graham2D();

        void draw();

        bool save(std::string fileName);

        void setCentroid();
        void setPoint();
        void setConvexPoint();
        void setStarEdge();
        void setStarPoligon();
        void setConvexHull();


        void clear();
        void execute();

    protected:
        void findCentroid();
        void starPolygon();
        void coincidentPoint();
        void findConvexPolygon();

        void sortPoints();
        static bool compareAngle(Point* first, Point* second);

    private:

        bool renderPointList;
        bool renderConvexPointList;
        bool renderStarEdgeList;
        bool renderStarPoligonList;
        bool renderConvexHull;
        bool renderCentroid;

        std::list<Point*> pointList;
        std::list<Point*> convexPointList;
        std::list<Edge*> starEdgeList;
        std::list<Edge*> starPoligonList;
        std::list<Edge*> convexHullList;

        Point* centroid;

        static std::map<Point*,double> pointMap;
};



#endif //#ifndef _GRAHAM_H_
