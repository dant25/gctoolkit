#ifndef VORONOI_H
#define VORONOI_H

#include<list>
#include <cmath>
#include "Point2D.h"
#include "Edge2D.h"

class Voronoi
{
    public:
        Voronoi(std::list<Point*> list);
        virtual ~Voronoi();

        void clear();
        void execute();

        void draw();

    protected:
    private:
};

#endif // VORONOI_H
