#include "Delaunay.h"

#include <fstream>
#include <GL/gl.h>


Delaunay::Delaunay(std::list<Point*> pointList)
{
    renderPointList = false;
    renderTrianglesList = false;
    renderCircumference = false;

    this->pointList = pointList;
}

Delaunay::~Delaunay()
{

}

bool Delaunay::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);

    arquivo << std::endl << "METODO Delaunay" << std::endl  << std::endl;
    arquivo << "PONTOS DOS TRIANGULOS" << std::endl;

    arquivo << triangleList.size() << std::endl;

    for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
    {
        arquivo << (*it)->getP1()-> getCoord(0) << "\t" << (*it)->getP1()->getCoord(1) << "\t" << (*it)->getP1()->getCoord(2) << "\t";
        arquivo << (*it)->getP2()-> getCoord(0) << "\t" << (*it)->getP2()->getCoord(1) << "\t" << (*it)->getP2()->getCoord(2) << "\t";
        arquivo << (*it)->getP3()-> getCoord(0) << "\t" << (*it)->getP3()->getCoord(1) << "\t" << (*it)->getP3()->getCoord(2) << std::endl;

    }

    return true;
}

void Delaunay::triangulate()
{
    edgeList.clear();
    free_edgeList.clear();

    Triangle* auxTriangle;
    Edge* auxEdge;
    Point* auxPoint;

    Edge* edge;
    edge = initialEdge();       //ARESTA INICIAL

    edgeList.push_back(edge);
    free_edgeList.push_back(edge);


int passos = 0;
    while( free_edgeList.size() > 0 )
    {
        passos++;
        auxEdge = free_edgeList.front();
        free_edgeList.pop_front();

        auxPoint = bestPoint(auxEdge);
        if(auxPoint==NULL)
            continue;

        auxTriangle= new Triangle2D( (Point2D*)auxEdge->getP1(), (Point2D*)auxEdge->getP2(), (Point2D*)auxPoint );

        triangleList.push_back(auxTriangle);

        ((Edge2D*)auxEdge)->addAdjTriangle(auxTriangle);
        insertEdge( auxEdge->getP1(), auxPoint, auxTriangle );
        insertEdge( auxPoint , auxEdge->getP2(), auxTriangle );
    }
std::cout << "Fim do algoritmo!!!" << std::endl;

}

Edge* Delaunay::initialEdge()
{
    Point* initialPoint;
    Point *secondPoint;
    double Xmax = -9999.99;
    double angleMin = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if((*it)->getCoord(0) > Xmax)
        {
            initialPoint = (*it);
            Xmax = (*it)->getCoord(0);
        }
    }

    Point *point = new Point2D( ((Point2D*)initialPoint)->getX() + 20, ((Point2D*)initialPoint)->getY(), 0);
    Edge *aux_edge = new Edge2D((Point2D*)initialPoint, (Point2D*)point, 0);

    double angle = 0.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        angle = ((Edge2D*)aux_edge)->angle( (Point2D*)initialPoint, (Point2D*)(*it) );

        if( ((Edge2D*)aux_edge)->right( (Point2D*)(*it) )==true )
            angle = 2.0*M_PI - angle;

        if( angle < angleMin)
        {
            secondPoint = (*it);
            angleMin = angle;
        }
    }

    delete aux_edge;
    delete point;

    return ( new Edge2D((Point2D*)initialPoint, (Point2D*)secondPoint, 0) );
}

Point* Delaunay::bestPoint(Edge* e)
{
    Point *point = NULL;
    double maxAngle = 0.0;
    double angle;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( ((Edge2D*)e)->right( (Point2D*)(*it) ) == true )
            continue;

        angle = e->angle((Point2D*)(*it));

        angle = angle*(360.0/(2.0*M_PI));

        if( angle > maxAngle )
        {
            maxAngle = angle ;
            point = (*it);
        }
    }

    return point;
}

bool Delaunay::insertEdge(Point* p1, Point* p2, Triangle* triangle)
{
    for (std::list<Edge*>::iterator it=free_edgeList.begin(); it!=free_edgeList.end(); it++)
    {
        if( ( ( (*it)->getP1() ==  p1) && ( (*it)->getP2() ==  p2) )
         || ( ( (*it)->getP1() ==  p2) && ( (*it)->getP2() ==  p1) ) )
        {
            free_edgeList.erase(it);
            ((Edge2D*)(*it))->addAdjTriangle(triangle);
            return false;
        }
    }

    Edge* edge = new Edge2D( (Point2D*)p1, (Point2D*)p2 );
    edgeList.push_back( edge );
    free_edgeList.push_back( edge );
    ((Edge2D*)edge)->addAdjTriangle(triangle);

    return true;
}

void Delaunay::setPoint()
{
       renderPointList = !renderPointList;
}

void Delaunay::setTriangles()
{
       renderTrianglesList = !renderTrianglesList;
}

void Delaunay::setCircumference()
{
       renderCircumference = !renderCircumference;
}

void Delaunay::clear()
{
    pointList.clear();
    triangleList.clear();
    edgeList.clear();
    free_edgeList.clear();
    circumferenceList.clear();
    circumferencePointList.clear();
}

void Delaunay::execute()
{
    std::cout << "DELAUNAY...." << std::endl;
    triangulate();

    Point center;
    double radius;
    Point *p1;
    Point *p2;

    for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
    {
        center = ( (Triangle2D*)(*it) )->circumcenter();

        radius = center.distance( (*it)->getP1() );

        circumferencePointList.push_back( new Point2D(center.getCoord(0), center.getCoord(1)) );

        for(double i = 0.0; i < 2.0*M_PI; )
        {
            p1 =  new Point2D( radius*cos(i) + center.getCoord(0), radius*sin(i) + center.getCoord(1));

            i += M_PI/30;

            p2 =  new Point2D( radius*cos(i) + center.getCoord(0), radius*sin(i) + center.getCoord(1));

            circumferenceList.push_back( new Edge2D((Point2D*)p1, (Point2D*)p2) );
        }
    }
}

void Delaunay::draw()
{
    if(renderPointList == true)
    {
        for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
            (*it)->draw();
    }

    if(renderTrianglesList == true)
    {
        for (std::list<Triangle*>::iterator it = triangleList.begin(); it != triangleList.end(); it++)
        {
            (*it)->setColorB(1.0);
            (*it)->draw(0);
        }
    }

    if( renderCircumference == true)
    {
        for (std::list<Point*>::iterator it=circumferencePointList.begin(); it!=circumferencePointList.end(); it++)
        {
            (*it)->setColorG(1.0);
            (*it)->draw();
        }
        for (std::list<Edge*>::iterator it=circumferenceList.begin(); it!=circumferenceList.end(); it++)
        {
            (*it)->setColorG(1.0);
            (*it)->setColorR(1.0);
            (*it)->draw(1);
        }
    }

    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        (*it)->setColorR(1.0);
        (*it)->draw(1);
    }
}
