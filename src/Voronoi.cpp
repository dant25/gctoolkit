#include "Voronoi.h"
#include "Delaunay.h"

#include <fstream>

Voronoi::Voronoi(std::list<Point*> list)
{
    renderPointList = true;
    renderTriangleList = true;
    renderVoronoi = true;

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
    voronoi_edgeList.clear();
}

bool Voronoi::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);

    arquivo << std::endl << "METODO Voronoi" << std::endl  << std::endl;
    arquivo << "PONTOS" << std::endl;

    arquivo << voronoi_pointList.size() << std::endl;

        for (std::list<Point*>::iterator it=voronoi_pointList.begin(); it!=voronoi_pointList.end(); it++)
    {
        arquivo << (*it)->getId() << "\t" << (*it)->getCoord(0) << "\t" << (*it)->getCoord(1) << "\t" << (*it)->getCoord(2) << std::endl;

    }

    arquivo << std::endl;
    arquivo << "Arestas Voronoi" << std::endl;

    arquivo << voronoi_edgeList.size() << std::endl;

    for (std::list<Edge*>::iterator it=voronoi_edgeList.begin(); it!=voronoi_edgeList.end(); it++)
    {
        arquivo << (*it)->getP1()->getId() << "\t" << (*it)->getP2()->getId() << std::endl;
    }

    return true;
}

void Voronoi::makeVoronoi()
{
    long int id = 1;

    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        if( ((Edge2D*)(*it))->getAdjTriangleList().size() == 2 )
        {
/*
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
*/
            Point *p1 = new Point2D( ( (Triangle2D*)(((Edge2D*)(*it))->getAdjTriangleList().front()) )->circumcenter() );
            p1->setId(id);
            id++;
            Point *p2 = new Point2D( ( (Triangle2D*)(((Edge2D*)(*it))->getAdjTriangleList().back()) )->circumcenter() );
            p2->setId(id);
            id++;


            bool insert1 = true;
            bool insert2 = true;
            for (std::list<Point*>::iterator it=voronoi_pointList.begin(); it!=voronoi_pointList.end(); it++)
            {
                if( (*it)->match(p1) )
                {
                    p1 = (*it);
                    insert1 = false;
                }

                if( (*it)->match(p2) )
                {
                    p2 = (*it);
                    insert2 = false;
                }
            }

            if(insert1 == true)
            {
                voronoi_pointList.push_back( p1 );
            }
            if(insert2 == true)
            {
                voronoi_pointList.push_back( p2 );
            }

            Edge* edge = new Edge2D( (Point2D*)p1, (Point2D*)p2 );

            voronoi_edgeList.push_back(edge);
        }
        else    //ARESTAS AO INFINITO TO DO!!!!!!
        {
            Point *p1 = new Point2D( ( (Triangle2D*)(((Edge2D*)(*it))->getAdjTriangleList().front()) )->circumcenter() );
            p1->setId(id);
            id++;

            bool insert = true;
            for (std::list<Point*>::iterator it=voronoi_pointList.begin(); it!=voronoi_pointList.end(); it++)
            {
                if( (*it)->match(p1) )
                {
                    p1 = (*it);
                    insert = false;
                    id--;
                    break;
                }
            }

            if(insert == true)
            {
                voronoi_pointList.push_back( p1 );
            }
            /*
            double x1 = ( ((Edge2D*)(*it))->getAdjTriangleList().front()->getP1()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP2()->getCoord(0) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP3()->getCoord(0) ) / 3.0;

            double y1 = ( ((Edge2D*)(*it))->getAdjTriangleList().front()->getP1()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP2()->getCoord(1) +
                        ((Edge2D*)(*it))->getAdjTriangleList().front()->getP3()->getCoord(1) ) / 3.0;

            double x2 = ( (*it)->getP1()->getCoord(0) + (*it)->getP2()->getCoord(0) ) / 2.0;
            double y2 = ( (*it)->getP1()->getCoord(1) + (*it)->getP2()->getCoord(1) ) / 2.0;

            voronoi_edgeList.push_back(new Edge2D( new Point2D(x1, y1), new Point2D(x2, y2) ));
            */
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

    if(renderPointList)
    {
        for (std::list<Point*>::iterator it=voronoi_pointList.begin(); it!=voronoi_pointList.end(); it++)
        {
            (*it)->draw();
        }
    }

    if(renderTriangleList)
    {
        for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
        {
            (*it)->setColorB(1.0);
            (*it)->draw(0);
        }

        for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
            (*it)->draw();

        for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
        {
            (*it)->setColorR(1.0);
            (*it)->draw(1);
        }
    }

    if(renderVoronoi)
    {
        for (std::list<Edge*>::iterator it=voronoi_edgeList.begin(); it!=voronoi_edgeList.end(); it++)
        {
            (*it)->setColorG(1.0);
            (*it)->draw(1);
        }
    }

}

