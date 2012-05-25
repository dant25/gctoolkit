#ifndef __ResourceManager__
#define __ResourceManager__

#include <string>
#include <list>
#include <fstream>

#include "Point.h"
#include "Point2D.h"
#include "Point3D.h"
#include "BoundingBox.h"

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

        double getBoxXmin() { return boxXmin; };
        double getBoxXmax() { return boxXmax; };

        double getBoxYmin() { return boxYmin; };
        double getBoxYmax() { return boxYmax; };

        double getBoxZmin() { return boxZmin; };
        double getBoxZmax() { return boxZmax; };

        BoundingBox getBoundingBox() { return bBox; };


    private:
        enumType type;
        BoundingBox bBox;

        double boxXmin;
        double boxXmax;
        double boxYmin;
        double boxYmax;
        double boxZmin;
        double boxZmax;
        long int numPoint;
        std::list<Point*> pointList;

};

#endif // __ResourceManager__
