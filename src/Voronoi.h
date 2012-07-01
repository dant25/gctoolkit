#ifndef VORONOI_H
#define VORONOI_H

#include<list>
#include <map>
#include <stack>
#include <cmath>
#include "Point2D.h"
#include "Edge2D.h"
#include "Triangle2D.h"

class Voronoi
{
    public:
        Voronoi(std::list<Point*> list);
        virtual ~Voronoi();

        void clear();
        void execute();

        void makeVoronoi();

        void draw();

    protected:

    private:
        bool renderPointList;
        bool renderTriangleList;
        bool renderEdgeList;

        std::list<Point*> pointList;
        std::list<Point*> voronoi_pointList;
        std::list<Edge*> edgeList;
        std::list<Edge*> voronoi_edgeList;
        std::list<Triangle*> triangleList;
};

#endif // VORONOI_H
