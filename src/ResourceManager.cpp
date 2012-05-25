#include "ResourceManager.h"
#include <float.h>


ResourceManager::ResourceManager()
{
    boxXmin = -1.0;
    boxXmax = 1.0;
    boxYmin = -1.0;
    boxYmax = 1.0;
    boxZmin = -1.0;
    boxZmax = 1.0;
    graham = NULL;
    delaunay = NULL;
    mergehull3d = NULL;
    type = MERGEHULL3D;

    this->bBox = BoundingBox(Vector3(-50, -50, -300), Vector3(50, 50, 400));

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::loadFromFile(std::string fileName)
{
    //std::cout << fileName.c_str() << std::endl;

    //std::ifstream file( fileName.c_str(), std::ifstream::in);
    std::ifstream file( "crab 3.txt", std::ifstream::in);

    if( !file )
        return false;

    pointList.clear();

    file >> numPoint;
    float x, y, z;

    boxXmin = DBL_MAX;
    boxXmax = -DBL_MAX;
    boxYmin = DBL_MAX;
    boxYmax = -DBL_MAX;
    boxZmin = DBL_MAX;
    boxZmax = -DBL_MAX;

    for(int i=0; i<numPoint; i++)
    {
        file >> x;
        file >> y;
        file >> z;

        if(boxXmin > x)
            boxXmin = x;

        if(boxXmax < x)
            boxXmax = x;

        if(boxYmin > y)
            boxYmin = y;

        if(boxYmax < y)
            boxYmax = y;

        if(boxZmin > z)
            boxZmin = z;

        if(boxZmax < z)
            boxZmax = z;

        Point *point = new Point2D(x, y, i+1);
        pointList.push_back(point);
    }

    switch(this->type)
    {
        case GRAHAM2D:
            graham = new Graham2D(pointList);
        break;
        case DELAUNAY:
            delaunay = new Delaunay(pointList);
        break;
        case MERGEHULL3D:
            mergehull3d = new MergeHull3D(pointList);
        break;
    }


    return true;
}

bool ResourceManager::saveToFile(std::string fileName)
{
    switch(this->type)
    {
        case GRAHAM2D:
            return graham->save(fileName);
        break;
        case DELAUNAY:
            return delaunay->save(fileName);
        break;
        case MERGEHULL3D:
            return delaunay->save(fileName);
        break;
    }
    return false;
}

void ResourceManager::setType(int type)
{
    switch(this->type)          //DELETA O TIPO ANTIGO
    {
        case GRAHAM2D:
            delete graham;
            graham = NULL;
        break;
        case DELAUNAY:
            delete delaunay;
            delaunay = NULL;
        break;
        case MERGEHULL3D:
            delete mergehull3d;
            mergehull3d = NULL;
        break;
    }

    switch(type)          //SET NO NOVO TIPO
    {
        case 0:
            this->type = GRAHAM2D;
        break;
        case 1:
            this->type = DELAUNAY;
        break;
        case 2:
            this->type = MERGEHULL3D;
        break;
    }
}

void ResourceManager::render()
{
    switch(this->type)
    {
        case 0:
            if(graham != NULL)
                graham->draw();
        break;
        case 1:
            if(delaunay != NULL)
                delaunay->draw();
        break;
        case 2:
            if(mergehull3d != NULL)
                mergehull3d->draw();
        break;
    }
}
