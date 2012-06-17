#include "Delaunay3D.h"

#include <fstream>

Delaunay3D::Delaunay3D(std::list<Point*> list)
{
    renderPointList = true;
    renderEdgesList = true;
    renderTetrahedronsList = true;

    pointList = list;
}

Delaunay3D::~Delaunay3D()
{
    //dtor
}

void Delaunay3D::draw()
{
   if(renderPointList == true)
    {
        for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
            (*it)->draw();
    }
/*
    if(renderTetrahedronsList == true)
    {
        for (std::list<Polygon*>::iterator it=polygonList.begin(); it!=polygonList.end(); it++)
            (*it)->draw(true);
    }
*/
    if(renderEdgesList == true)
    {
        for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
            (*it)->draw(true);
    }

    for (std::list<Triangle*>::iterator it=triangleList.begin(); it!=triangleList.end(); it++)
        (*it)->draw(true);

}

bool Delaunay3D::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);// | ios::in);

    arquivo << std::endl << "METODO DELAUNAY 3D" << std::endl  << std::endl;
    arquivo << std::endl;

    arquivo << "PONTOS" << std::endl;
    arquivo << pointList.size() << std::endl;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
            arquivo << (*it)->getId()  << "\t";
            arquivo << (*it)->getCoord(0) << "\t" << (*it)->getCoord(1) << "\t" << (*it)->getCoord(2) << "\t";
            arquivo << std::endl;
    }

    arquivo << std::endl;
    arquivo << "PONTOS DAS FACES" << std::endl;
    arquivo << polygonList.size() << std::endl;

    int id=1;

    for (std::list<Polygon*>::iterator it=polygonList.begin(); it!=polygonList.end(); it++)
    {
        arquivo << id << "\t";
        id++;
        for(unsigned int i = 0; i < (*it)->numPoints(); i++)
        {
            arquivo << (*it)->getPoint(i)->getId() << "\t";
        }
            arquivo << std::endl;
    }

    return true;
}

void Delaunay3D::clear()
{
        pointList.clear();
        edgeList.clear();
        triangleList.clear();
        free_triangleList.clear();
        polygonList.clear();
}

void Delaunay3D::execute()
{
    initialTriangle();
    initialPolygon();

    while(free_triangleList.size() > 0)
    {
std::cout << "FREE:   " << free_triangleList.size() << std::endl;
        nextPolygon();
    }




    std::cout << "FACES: " << triangleList.size() << std::endl;
    std::cout << "Tetraedros: " << polygonList.size() << std::endl;
}

bool Delaunay3D::interceptTriangle(Triangle* t)
{
    for (std::list<Triangle*>::iterator it=triangleList.begin(); it!=triangleList.end(); it++)
    {
        if( t->equal((*it)) ||
           ( t->have( (*it)->getP1() ) && t->have( (*it)->getP2() ) ) ||
           ( t->have( (*it)->getP1() ) && t->have( (*it)->getP3() ) ) ||
           ( t->have( (*it)->getP2() ) && t->have( (*it)->getP3() ) ) )
        {
            continue;
        }


        if( ((Triangle3D*)t)->intercept( (Triangle3D*)(*it)) )
        {
std::cout << "TOCOU" << std::endl;
            return true;
        }

    }

    return false;
}

bool Delaunay3D::addTriangle(Triangle* t)
{
    for (std::list<Triangle*>::iterator it=triangleList.begin(); it!=triangleList.end(); it++)
    {
        if( t->equal((*it)) )
        {
            t = (Triangle*)(*it);
                free_triangleList.remove( (*it) );

            return false;
        }
    }

    triangleList.push_back(t);
    free_triangleList.push_back(t);

    return true;
}

void Delaunay3D::initialTriangle()
{
    pointList.sort(compareY);

    Point *p0 = pointList.front();
    Point *p0_1 = new Point3D( p0->getCoord(0) + 1.0, p0->getCoord(1), p0->getCoord(2) );
    Point *p0_2 = new Point3D( p0->getCoord(0), p0->getCoord(1), p0->getCoord(2) - 1.0 );

    Vector3D n1 = Vector3D( p0, p0_1 ).cross( Vector3D(p0, p0_2) );

    n1.normalize();

    double ang = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( (*it)->getId() == p0->getId() )
            continue;

        Vector3D n2 = Vector3D( (*it) , p0 ).cross( Vector3D((*it), p0_2) );

        n2.normalize();

        double ang_temp = n2.angle(n1);

        if(ang >= ang_temp)
        {
            ang = ang_temp;
            p0_1 = (*it);
        }
    }

    n1 = Vector3D( p0, p0_1 ).cross( Vector3D(p0, p0_2) );

    n1.normalize();

    ang = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( (*it)->getId() == p0->getId() || (*it)->getId() == p0_1->getId() )
            continue;

        Vector3D n2 = Vector3D( (*it) , p0 ).cross( Vector3D((*it), p0_1) );

        n2.normalize();

        double ang_temp = n2.angle(n1);

        if(ang >= ang_temp)
        {
            ang = ang_temp;
            p0_2 = (*it);
        }

    }

    p0->setColorRGB(1.0, 0.0, 0.0);
    p0_1->setColorRGB(0.0, 1.0, 0.0);
    p0_2->setColorRGB(0.0, 0.0, 1.0);

    Edge *e0 = new Edge3D((Point3D*)p0_1, (Point3D*)p0, edgeList.size()+1);
    Edge *e1 = new Edge3D((Point3D*)p0, (Point3D*)p0_2, edgeList.size()+1);
    Edge *e2 = new Edge3D((Point3D*)p0_2, (Point3D*)p0_1, edgeList.size()+1);

    edgeList.push_back( (Edge3D*)e0 );
    edgeList.push_back( (Edge3D*)e1 );
    edgeList.push_back( (Edge3D*)e2 );

    Triangle *triangle_aux = new Triangle3D( (Point3D*)p0_2, (Point3D*)p0_1, (Point3D*)p0 );

    ((Triangle*)triangle_aux)->setColorRGB(0.5, 0.5, 0.5);

    free_triangleList.push_back( triangle_aux );
    triangleList.push_back( triangle_aux );
}

void Delaunay3D::initialPolygon()
{
    Triangle* t0 = free_triangleList.front();

    double max_ang = 0.0;
    Point *p;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( t0->have((*it)) )
            continue;

        double ang = ((Triangle3D*)t0)->solidAngle( (Point3D*)(*it) );

//std::cout << ang << std::endl;

        if( max_ang <= ang )
        {
            max_ang = ang;
            p = (*it);
        }
    }
//std::cout << max_ang << std::endl;

    Edge *e0 = new Edge3D((Point3D*)p, (Point3D*)t0->getP1());
    Edge *e1 = new Edge3D((Point3D*)p, (Point3D*)t0->getP2());
    Edge *e2 = new Edge3D((Point3D*)p, (Point3D*)t0->getP3());

    edgeList.push_back( (Edge3D*)e0 );
    edgeList.push_back( (Edge3D*)e1 );
    edgeList.push_back( (Edge3D*)e2 );

    Triangle *t0_1 = new Triangle3D( (Point3D*)t0->getP3(), (Point3D*)p, (Point3D*)t0->getP1() );
    Triangle *t0_2 = new Triangle3D( (Point3D*)t0->getP2(), (Point3D*)t0->getP1(), (Point3D*)p );
    Triangle *t0_3 = new Triangle3D( (Point3D*)t0->getP3(), (Point3D*)t0->getP2(), (Point3D*)p );

    t0_1->setColorRGB(1.0, 0.0, 0.0);
    t0_2->setColorRGB(0.0, 1.0, 0.0);
    t0_3->setColorRGB(0.0, 0.0, 1.0);

    addTriangle(t0_1);
    addTriangle(t0_2);
    addTriangle(t0_3);

    free_triangleList.remove(t0);

    GeometricShape *polygon = new Polygon(4);

    polygon->setPoint(0, t0->getP1());
    polygon->setPoint(1, t0->getP2());
    polygon->setPoint(2, t0->getP3());
    polygon->setPoint(3, p);

    polygonList.push_back((Polygon*)polygon);
}

void Delaunay3D::nextPolygon()
{
    Triangle* t0 = free_triangleList.front();

    double max_ang = 0.0;
    Point *p = NULL;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( t0->have((*it)) )
            continue;

        double ang = ((Triangle3D*)t0)->orientedSolidAngle( (Point3D*)(*it) );
//std::cout << ang << std::endl;
        if( max_ang > ang )
        {
            max_ang = ang;
            p = (*it);
        }
    }

    if(p == NULL)
    {
//std::cout << "VAZOU......................................." << std::endl;
        free_triangleList.remove(t0);
        return;
    }


//std::cout << max_ang << " " << p->getCoord(0) << " " << p->getCoord(1) << " " << p->getCoord(2) << std::endl;

    Edge *e0 = new Edge3D((Point3D*)p, (Point3D*)t0->getP1());
    Edge *e1 = new Edge3D((Point3D*)p, (Point3D*)t0->getP2());
    Edge *e2 = new Edge3D((Point3D*)p, (Point3D*)t0->getP3());

    edgeList.push_back( (Edge3D*)e0 );
    edgeList.push_back( (Edge3D*)e1 );
    edgeList.push_back( (Edge3D*)e2 );

    Triangle *t0_1 = new Triangle3D( (Point3D*)t0->getP1(), (Point3D*)p, (Point3D*)t0->getP3() );
    Triangle *t0_2 = new Triangle3D( (Point3D*)t0->getP1(), (Point3D*)t0->getP2(), (Point3D*)p );
    Triangle *t0_3 = new Triangle3D( (Point3D*)t0->getP2(), (Point3D*)t0->getP3(), (Point3D*)p );

    t0_1->setColorRGB(0.0, 0.5, 0.5);
    t0_2->setColorRGB(0.5, 0.0, 0.5);
    t0_3->setColorRGB(0.5, 0.5, 0.0);


    if( !interceptTriangle(t0_1) && !interceptTriangle(t0_2) && !interceptTriangle(t0_3) )
    {
        addTriangle(t0_1);
        addTriangle(t0_2);
        addTriangle(t0_3);


        GeometricShape *polygon = new Polygon(4);

        polygon->setPoint(0, t0->getP1());
        polygon->setPoint(1, t0->getP2());
        polygon->setPoint(2, t0->getP3());
        polygon->setPoint(3, p);

        polygonList.push_back((Polygon*)polygon);

    }

    free_triangleList.remove(t0);
}

bool Delaunay3D::compareZ(Point* first, Point* second)
{
    if(first->getCoord(2) < second->getCoord(2))
        return true;
    else
        return false;
}

bool Delaunay3D::compareX(Point* first, Point* second)
{
    if(first->getCoord(0) < second->getCoord(0))
        return true;
    else
    {
        if(first->getCoord(0) == second->getCoord(0))
            return compareZ(first, second);
        else
            return false;
    }
}

bool Delaunay3D::compareY(Point* first, Point* second)
{
    if(first->getCoord(1) < second->getCoord(1))
        return true;
    else
    {
        if(first->getCoord(1) == second->getCoord(1))
            return compareX(first, second);
        else
            return false;
    }
}
