#include "MergeHull3D.h"

#include <fstream>
#include <GL/gl.h>

MergeHull3D::MergeHull3D(std::list<Point*> pointList)
{
    //ctor
}

MergeHull3D::~MergeHull3D()
{
    //dtor
}

void MergeHull3D::draw()
{
    //dtor
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

void MergeHull3D::clear()
{
    //dtor
}

void MergeHull3D::execute()
{
    //dtor
}
