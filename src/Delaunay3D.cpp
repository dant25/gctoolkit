#include "Delaunay3D.h"

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

    if(renderTetrahedronsList == true)
    {
        for (std::list<Triangle3D*>::iterator it=trianglesList.begin(); it!=trianglesList.end(); it++)
            (*it)->draw(true);
    }

    if(renderEdgesList == true)
    {
        for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
            (*it)->draw(true);
    }
}


void Delaunay3D::clear()
{

}

void Delaunay3D::execute()
{
    initialFace(pointList);
}

void Delaunay3D::addEdge(Edge3D* e)
{
    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        if( e->equal((*it)) )
        {
            e = (Edge3D*)(*it);
            //if( ((Edge3D*)*it)->getAdjFaceList().size() > 1)
                free_edgeList.remove( (*    it) );

            return;
        }
    }
    edgeList.push_back(e);
    free_edgeList.push_back(e);
}

void Delaunay3D::initialFace(std::list<Point*> pointList)
{
    pointList.sort(Delaunay3D::compareY);

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


    p0->setColorR(1);
    p0_1->setColorG(1);
    p0_2->setColorB(1);

    Edge *e0 = new Edge3D((Point3D*)p0_1, (Point3D*)p0, edgeList.size()+1);
    Edge *e1 = new Edge3D((Point3D*)p0, (Point3D*)p0_2, edgeList.size()+1);
    Edge *e2 = new Edge3D((Point3D*)p0_2, (Point3D*)p0_1, edgeList.size()+1);

    addEdge( (Edge3D*)e0 );
    addEdge( (Edge3D*)e1 );
    addEdge( (Edge3D*)e2 );

    GeometricShape *face_aux = new Polygon(3);

    face_aux->setPoint(0, p0_1);
    face_aux->setPoint(1, p0);
    face_aux->setPoint(2, p0_2);

    face_aux->setEdge(0, e0);
    face_aux->setEdge(1, e1);
    face_aux->setEdge(2, e2);

    ((Edge3D*)e0)->addAdjFace( ((Polygon*)face_aux) );
    ((Edge3D*)e1)->addAdjFace( ((Polygon*)face_aux) );
    ((Edge3D*)e2)->addAdjFace( ((Polygon*)face_aux) );

    ((Polygon*)face_aux)->setColorR(0.5);
    ((Polygon*)face_aux)->setColorG(0.5);
    ((Polygon*)face_aux)->setColorB(0.5);

    facesList.push_back( (Polygon*)face_aux );
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
