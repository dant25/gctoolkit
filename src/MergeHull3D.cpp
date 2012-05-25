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
}

bool MergeHull3D::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);// | ios::in);

    arquivo << std::endl << "METODO MERGE HULL 3D" << std::endl  << std::endl;
    arquivo << "PONTOS" << std::endl;
    arquivo << pointList.size()-1 << std::endl;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=--pointList.end(); it++)
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
    //dtor
}

void MergeHull3D::execute()
{
    //dtor
}

Polygon* MergeHull3D::initialFace(std::list<Point*> pointList)
{
    pointList.sort(compareY);
}

bool MergeHull3D::compareY(Point* first, Point* second)
{
    if(first->getCoord(1) <= second->getCoord(1))
        return true;
    else
        return false;
}
