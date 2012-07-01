#ifndef _DELAUNAY_H_
#define _DELAUNAY_H_

#include<list>
#include <map>
#include <stack>
#include <cmath>
#include "Point2D.h"
#include "Edge2D.h"
#include "Triangle2D.h"

class Delaunay
{
    public:
        Delaunay(std::list<Point*> pointList);
        ~Delaunay();

        void draw();

        bool save(std::string fileName);

        void setPoint();
        void setTriangles();
        void setCircumference();

        void clear();
        void execute();

        std::list<Triangle*> getTriangulation() { return triangleList; };
        std::list<Edge*> getEdges()  { return edgeList; };

    protected:
        void triangulate();
        Edge* initialEdge();
        Point* bestPoint(Edge* e);
        bool insertEdge(Point* p1, Point* p2, Triangle* triangle);

    private:

        bool renderPointList;
        bool renderTrianglesList;
        bool renderCircumference;

        std::list<Point*> pointList;
        std::list<Edge*> edgeList;
        std::list<Edge*> free_edgeList;
        std::list<Triangle*> triangleList;

        std::list<Point*> circumferencePointList;
        std::list<Edge*> circumferenceList;
};



#endif //#ifndef _DELAUNAY_H_
