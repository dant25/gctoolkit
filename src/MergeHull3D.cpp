#include "MergeHull3D.h"

#include <fstream>
#include <GL/gl.h>

MergeHull3D::MergeHull3D(std::list<Point*> pointList)
{
    renderPointList = true;
    renderFacesList = false;

    this->pointList = pointList;
}

MergeHull3D::~MergeHull3D()
{
    //dtor
}

void MergeHull3D::draw()
{
   if(renderPointList == true)
    {
        for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
            (*it)->draw();
    }

    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
        (*it)->draw(true);

    for (std::list<Polygon*>::iterator it=facesList.begin(); it!=facesList.end(); it++)
        (*it)->draw();
}

bool MergeHull3D::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);// | ios::in);

    arquivo << std::endl << "METODO MERGE HULL 3D" << std::endl  << std::endl;
    arquivo << "PONTOS" << std::endl;
    arquivo << pointList.size()-1 << std::endl;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        arquivo << (*it)->getCoord(0) << "\t" << (*it)->getCoord(1) << "\t" << (*it)->getCoord(2) << std::endl;
    }

    return true;
}

void MergeHull3D::setPoint()
{
       renderPointList = !renderPointList;
}

void MergeHull3D::setFace()
{
       renderFacesList = !renderFacesList;
}

void MergeHull3D::clear()
{
    pointList.clear();
    edgeList.clear();
    facesList.clear();
}

void MergeHull3D::execute()
{
    facesList.push_back( initialFace(pointList) );



}

Polygon* MergeHull3D::initialFace(std::list<Point*> pointList)
{
    pointList.sort(compareY);

    Point *p0 = pointList.front();

    std::cout << p0->getCoord(0) << std::endl;
    std::cout << p0->getCoord(1) << std::endl;
    std::cout << p0->getCoord(2) << std::endl;

    GeometricShape *face_aux = new Polygon(3);

    Point *p0_1 = new Point3D( p0->getCoord(0) + 1.0, p0->getCoord(1), p0->getCoord(2) );
    Point *p0_2 = new Point3D( p0->getCoord(0), p0->getCoord(1), p0->getCoord(2) - 1.0 );


    Vector3 n1 = Vector3(p0_1->getCoord(0) - p0->getCoord(0), p0_1->getCoord(1) - p0->getCoord(1), p0_1->getCoord(2) - p0->getCoord(2))
                ^Vector3(p0_2->getCoord(0) - p0->getCoord(0), p0_2->getCoord(1) - p0->getCoord(1), p0_2->getCoord(2) - p0->getCoord(2));

    std::cout << "VEja : " << n1.x << " " << n1.y << " " << n1.z << std::endl;

    double ang = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( (*it)->getId() == p0->getId() )
            continue;

        Vector3 n2 = Vector3( p0->getCoord(0) - (*it)->getCoord(0), p0->getCoord(1) - (*it)->getCoord(1), p0->getCoord(2) - (*it)->getCoord(2))
                    ^Vector3(p0_2->getCoord(0) - (*it)->getCoord(0), p0_2->getCoord(1) - (*it)->getCoord(1), p0_2->getCoord(2) - (*it)->getCoord(2));

        double ang_temp = n2.angle(n1);
        while(ang_temp >= 360.0)
            ang_temp-=360.0;

        if(ang >= ang_temp)
        {
            ang = ang_temp;
            p0_1 = (*it);
        }
    }
std::cout << ang << std::endl;

    n1 = Vector3(p0_1->getCoord(0) - p0->getCoord(0), p0_1->getCoord(1) - p0->getCoord(1), p0_1->getCoord(2) - p0->getCoord(2))
        ^Vector3(p0_2->getCoord(0) - p0->getCoord(0), p0_2->getCoord(1) - p0->getCoord(1), p0_2->getCoord(2) - p0->getCoord(2));

    ang = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( (*it)->getId() == p0->getId() || (*it)->getId() == p0_1->getId() )
            continue;

        Vector3 n2 = Vector3( p0->getCoord(0) - (*it)->getCoord(0), p0->getCoord(1) - (*it)->getCoord(1), p0->getCoord(2) - (*it)->getCoord(2))
                    ^Vector3(p0_1->getCoord(0) - (*it)->getCoord(0), p0_1->getCoord(1) - (*it)->getCoord(1), p0_1->getCoord(2) - (*it)->getCoord(2));

        double ang_temp = n2.angle(n1);

        while(ang_temp >= 360.0)
            ang_temp-=360.0;

        if(ang >= ang_temp)
        {
            ang = ang_temp;
            p0_2 = (*it);
        }

    }
std::cout << ang << std::endl;

std::cout << p0->getId() << " " << p0_1->getId() << " " << p0_2->getId()  << std::endl;

p0->setColorR(1);
p0_1->setColorG(1);
p0_2->setColorB(1);

    std::cout << p0_1->getCoord(0) << std::endl;
    std::cout << p0_1->getCoord(1) << std::endl;
    std::cout << p0_1->getCoord(2) << std::endl;

    std::cout << p0_2->getCoord(0) << std::endl;
    std::cout << p0_2->getCoord(1) << std::endl;
    std::cout << p0_2->getCoord(2) << std::endl;

    face_aux->setPoint(0, p0);
    face_aux->setPoint(1, p0_1);
    face_aux->setPoint(2, p0_2);

    edgeList.push_back( new Edge3D((Point3D*)p0, (Point3D*)p0_1, edgeList.size()+1) );
    edgeList.push_back( new Edge3D((Point3D*)p0_1, (Point3D*)p0_2, edgeList.size()+1) );
    edgeList.push_back( new Edge3D((Point3D*)p0_2, (Point3D*)p0, edgeList.size()+1) );

    return (Polygon*)face_aux;
}

bool MergeHull3D::compareY(Point* first, Point* second)
{
    if(first->getCoord(1) <= second->getCoord(1))
        return true;
    else
        return false;
}
