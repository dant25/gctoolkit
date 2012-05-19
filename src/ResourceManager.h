#ifndef __ResourceManager__
#define __ResourceManager__

#include <string>
#include <list>
#include <fstream>

#include "Point.h"
#include "Point2D.h"

#include "Graham2D.h"
#include "Delaunay.h"
#include "MergeHull3D.h"


enum enumType { GRAHAM2D, DELAUNAY, MERGEHULL3D};


class ResourceManager
{
    public:
        bool loadFromFile( std::string fileName);
        bool saveToFile( std::string fileName);

        void setType(int type);

        void render();

        ResourceManager();
        ~ResourceManager();

        Graham2D *graham;
        Delaunay *delaunay;
        MergeHull3D * mergehull3d;

        float getBoxXmin() { return boxXmin; };
        float getBoxXmax() { return boxXmax; };

        float getBoxYmin() { return boxYmin; };
        float getBoxYmax() { return boxYmax; };

        float getBoxZmin() { return boxZmin; };
        float getBoxZmax() { return boxZmax; };


    private:
        enumType type;

        float boxXmin;
        float boxXmax;
        float boxYmin;
        float boxYmax;
        float boxZmin;
        float boxZmax;
        long int numPoint;
        std::list<Point*> pointList;

};

#endif // __ResourceManager__
