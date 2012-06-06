#ifndef DELAUNAY3D_H
#define DELAUNAY3D_H

#include<list>
#include <cmath>
#include "Point3D.h"
#include "Edge3D.h"
#include "Triangle3D.h"


class Delaunay3D
{
    public:
        Delaunay3D(std::list<Point*> list);
        virtual ~Delaunay3D();

        void clear();
        void execute();

        void draw();

        void initialFace(std::list<Point*> pointList);

        void addEdge(Edge3D* e);

        static bool compareX(Point* first, Point* second);
        static bool compareY(Point* first, Point* second);
        static bool compareZ(Point* first, Point* second);

    private:
        bool renderPointList;
        bool renderEdgesList;
        bool renderTetrahedronsList;

        std::list<Point*> pointList;
        std::list<Edge*> edgeList;
        std::list<Edge*> free_edgeList;
        std::list<Polygon*> facesList;
        std::list<Triangle3D*> trianglesList;
};

#endif // DELAUNAY3D_H
