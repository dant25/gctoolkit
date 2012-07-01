#include "Voronoi.h"
#include "Delaunay.h"

Voronoi::Voronoi(std::list<Point*> list)
{
    renderPointList = true;
    renderTriangleList = false;
    renderEdgeList = true;

    this->pointList = list;
}

Voronoi::~Voronoi()
{
    //dtor
}

void Voronoi::clear()
{
    pointList.clear();
    edgeList.clear();
    triangleList.clear();
    voronoi_pointList.clear();
}

void Voronoi::makeVoronoi()
{
    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        if( ((Edge2D*)(*it))->getAdjTriangleList().size() == 2 )
        {
            double x1 = ( ((Edge2D*)(*it))->getAdjTriangleList().front()->getP1()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP2()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP3()->getCoord(0) ) / 3.0;

            double y1 = ( ((Edge2D*)(*it))->getAdjTriangleList().front()->getP1()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP2()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP3()->getCoord(1) ) / 3.0;

            double x2 = ( ((Edge2D*)(*it))->getAdjTriangleList().back()->getP1()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().back()->getP2()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().back()->getP3()->getCoord(0) ) / 3.0;

            double y2 = ( ((Edge2D*)(*it))->getAdjTriangleList().back()->getP1()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().back()->getP2()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().back()->getP3()->getCoord(1) ) / 3.0;

            Point *p1 = new Point2D(x1, y1);
            Point *p2 = new Point2D(x2, y2);

            bool insert = true;
            for (std::list<Point*>::iterator it=voronoi_pointList.begin(); it!=voronoi_pointList.end(); it++)
            {
                if( (*it)->match(Point2D(x1, y1)) )
                {
                    p1 = (*it);
                    insert = false;
                }

                if( (*it)->match(Point2D(x2, y2)) )
                {
                    p2 = (*it);
                }
            }

            if(insert == true)
                voronoi_pointList.push_back( new Point2D(x1, y1) );

            Edge* edge = new Edge2D( (Point2D*)p1, (Point2D*)p2 );

            voronoi_edgeList.push_back(edge);
        }
        else
        {
            double x1 = ( ((Edge2D*)(*it))->getAdjTriangleList().front()->getP1()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP2()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP3()->getCoord(0) ) / 3.0;

            double y1 = ( ((Edge2D*)(*it))->getAdjTriangleList().front()->getP1()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP2()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP3()->getCoord(1) ) / 3.0;

            double x2 = ( (*it)->getP1()->getCoord(0) + (*it)->getP2()->getCoord(0) ) / 2.0;
            double y2 = ( (*it)->getP1()->getCoord(1) + (*it)->getP2()->getCoord(1) ) / 2.0;

            voronoi_edgeList.push_back(new Edge2D( new Point2D(x1, y1), new Point2D(x2, y2) ));
        }

    }
std::cout << voronoi_pointList.size() << std::endl;
std::cout << voronoi_edgeList.size() << std::endl;
}

void Voronoi::execute()
{
    Delaunay *d = new Delaunay(pointList);
    d->execute();
    triangleList = d->getTriangulation();
    edgeList = d->getEdges();

    makeVoronoi();
}

void Voronoi::draw()
{
    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
        (*it)->draw();

    for (std::list<Point*>::iterator it=voronoi_pointList.begin(); it!=voronoi_pointList.end(); it++)
        (*it)->draw();

    for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
    {
        (*it)->setColorB(1.0);
        (*it)->draw(0);
    }

    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        (*it)->setColorR(1.0);
        (*it)->draw(1);
    }

    for (std::list<Edge*>::iterator it=voronoi_edgeList.begin(); it!=voronoi_edgeList.end(); it++)
    {
        (*it)->setColorG(1.0);
        (*it)->draw(1);
    }
}
