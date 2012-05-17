#include "Graham2D.h"

#include <fstream>
#include <GL/gl.h>

std::map<Point*,float> Graham2D::pointMap;

Graham2D::Graham2D(std::list<Point*> pointList)
{

    renderCentroid = false;
    renderPointList = false;
    renderConvexPointList = false;
    renderStarEdgeList = false;
    renderStarPoligonList = false;
    renderConvexHull = false;

    centroid = NULL;

    this->pointList = pointList;

}

Graham2D::~Graham2D()
{
    delete centroid;
}

bool Graham2D::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);// | ios::in);

    arquivo << std::endl << "METODO GRAHAM" << std::endl  << std::endl;
    arquivo << "PONTOS" << std::endl;
    arquivo << convexPointList.size()-1 << std::endl;

    for (std::list<Point*>::iterator it=convexPointList.begin(); it!=--convexPointList.end(); it++)
    {
        arquivo << (*it)->getCoord(0) << "\t" << (*it)->getCoord(1) << "\t" << (*it)->getCoord(2) << std::endl;
    }

    return true;
}

void Graham2D::findCentroid()
{
    float Ox = 0.0;
    float Oy = 0.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        Ox += ((Point2D *)(*it))->getX();
        Oy += ((Point2D *)(*it))->getY();
    }

    Ox = Ox/pointList.size();
    Oy = Oy/pointList.size();

    if(centroid != NULL)
        delete centroid;

    centroid = new Point2D(Ox, Oy, 0);
    centroid->setColorR(1.0);
}

void Graham2D::starPolygon()
{
    starPoligonList.clear();

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        Edge *edge = new Edge2D((Point2D*)centroid, (Point2D*)(*it), 0);
        edge->setColorR(1.0);
        edge->setColorG(1.0);

        starPoligonList.push_front(edge);
    }

    starEdgeList.clear();

    int idEdge = 1;
    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        Edge *edge;
        if( (++it) == pointList.end())
        {
            --it;
            edge = new Edge2D((Point2D*)(*it), (Point2D*)(*pointList.begin()), idEdge);
            edge->setColorB(1.0);
            starEdgeList.push_back(edge);
        }
        else
        {
            --it;
            edge = new Edge2D((Point2D*)(*it), (Point2D*)(*(++it)), idEdge);
            --it;
            edge->setColorB(1.0);
            starEdgeList.push_back(edge);
        }

        idEdge++;
    }

}

void Graham2D::coincidentPoint()
{
    std::list<Point*>::iterator it;
    std::list<Point*>::iterator it2;
    std::map<Point*, float>::iterator map_it;

    float Ox = centroid->getCoord(0);
    float Oy = centroid->getCoord(1);

    for (it=pointList.begin() ; it != --pointList.end();  )
    {
        it2 = ++it;
        it--;

        if( fabs( pointMap[(*it)] - pointMap[(*it2)] ) <= 0.001 )
        {
            float dist1 = sqrt( pow((*it)->getCoord(0)-Ox, 2.0) + pow((*it)->getCoord(1)-Oy, 2.0) );

            float dist2 = sqrt( pow((*it2)->getCoord(0)-Ox, 2.0) + pow((*it2)->getCoord(1)-Oy, 2.0) );

            if(dist1 <= dist2)
            {
                map_it = pointMap.find((*it));
                pointMap.erase(map_it);

                it = pointList.erase(it);
            }
            else
            {
                map_it = pointMap.find((*it2));
                pointMap.erase(map_it);

                it = pointList.erase(it2);
            }
        }
        else
        {
            it++;
        }
    }
}

void Graham2D::findConvexPolygon()
{
    std::stack<Point*> pointStack;
    std::list<Edge*>::iterator it2;
    std::list<Point*>::iterator iter = pointList.begin();

    Edge *edge;
    Point *p1, *p2;

    pointStack.push((*iter));
    iter++;
    pointStack.push((*iter));
    iter++;

    //SELECIONANDO OS PONTOS DO FECHO
    for (; iter!=pointList.end(); iter++)
    {
        p2 = pointStack.top();
        pointStack.pop();
        p1 = pointStack.top();

        pointStack.push(p2);
        edge = new Edge2D( (Point2D*)p1, (Point2D*)p2 );

        if( ((Edge2D*)edge)->right( (Point2D*)(*iter) ) == false  )
            pointStack.push((*iter));
        else
        {
            pointStack.pop();

            if(pointStack.size() == 1)
                pointStack.push((*iter));
            else
                iter--;
        }
        delete edge;
    }


    //TRATA O CASO DOS 2 ULTIMOS PONTOS COM O PRIMEIRO PONTO
    bool ok = false;
    while(ok == false)
    {
        p2 = pointStack.top();
        pointStack.pop();
        p1 = pointStack.top();

        pointStack.push(p2);
        edge = new Edge2D( (Point2D*)p1, (Point2D*)p2 );

        if( ((Edge2D*)edge)->right( (Point2D*)(*pointList.begin()) ) == false  )
        {
            pointStack.push(((*pointList.begin())));
            ok = true;
        }
        else
        {
            pointStack.pop();

            if(pointStack.size() == 1)
            {
                pointStack.push(((*pointList.begin())));
                ok = true;
            }
            else
                ok = false;
        }
        delete edge;
    };

    convexPointList.clear();

    //RETIRA DA PILHA E COLOCA NUMA LISTA
    while(pointStack.size() != 0)
    {
        convexPointList.push_front( pointStack.top() );
        pointStack.pop();
    };

    convexHullList.clear();

    //CRIA AS ARESTAS DO FECHO CONVEXO
    for (std::list<Point*>::iterator it=convexPointList.begin(); it!=convexPointList.end(); it++)
    {
        Edge *edge;
        if( (++it) == convexPointList.end())
        {
            --it;
            edge = new Edge2D((Point2D*)(*it), (Point2D*)(*convexPointList.begin()), 0);
            edge->setColorR(1.0);
            convexHullList.push_back(edge);
        }
        else
        {
            --it;
            edge = new Edge2D((Point2D*)(*it), (Point2D*)(*(++it)), 0);
            --it;
            edge->setColorR(1.0);
            convexHullList.push_back(edge);
        }
    }

}

void Graham2D::sortPoints()
{
    Point *point = new Point2D(((Point2D*)centroid)->getX()+10, ((Point2D*)centroid)->getY(), 0);
    Edge *edge = new Edge2D((Point2D*)centroid, (Point2D*)point, 0);

    float angle;

    float xMax = -999.9;
    float yMin = 999.9;
    Point *pMaxMin = NULL;

    pointMap.clear();

    //GERA O ANGULO DA ARESTA (CENTROIDE, CENTROIDE+1) COM OS OUTROS PONTOS
    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( ((*it)->getCoord(1) < yMin) ||
            (((*it)->getCoord(1) == yMin) && ((*it)->getCoord(0) > xMax)))
        {
            yMin = (*it)->getCoord(1);
            xMax = (*it)->getCoord(0);

            pMaxMin = (*it);
        }

        angle = ((Edge2D*)edge)->angle((Point2D*)centroid, ((Point2D*)(*it)));

        if( ((Edge2D*)edge)->right( (Point2D*)(*it) )==true )
            angle = 2.0*M_PI - angle;

        pointMap[(*it)] = angle*(360.0/(2.0*M_PI));      //EM º
    }

    //ORDENA LISTA
    pointList.sort(compareAngle);

    //FAZ O PONTO DE MENOR Y E MAIOR X ESTAR NO INICIO DA LISTA
    while ((pMaxMin) && (pointList.front() != pMaxMin))
    {
        pointList.push_back(pointList.front());
        pointList.pop_front();
    }

    delete point;
    delete edge;
}

bool Graham2D::compareAngle(Point* first, Point* second)
{
    if(pointMap[first] <= pointMap[second])
        return true;
    else
        return false;
}

void Graham2D::setCentroid()
{
       renderCentroid = !renderCentroid;
}

void Graham2D::setPoint()
{
       renderPointList = !renderPointList;
}

void Graham2D::setConvexPoint()
{
       renderConvexPointList = !renderConvexPointList;
}

void Graham2D::setStarEdge()
{
       renderStarEdgeList = !renderStarEdgeList;
}

void Graham2D::setStarPoligon()
{
    renderStarPoligonList = !renderStarPoligonList;
}

void Graham2D::setConvexHull()
{
    renderConvexHull = !renderConvexHull;
}

void Graham2D::clear()
{
    starEdgeList.clear();
    starPoligonList.clear();
    pointList.clear();
    convexPointList.clear();
    convexHullList.clear();
    delete centroid;
    centroid = NULL;
}

void Graham2D::execute()
{
    this->findCentroid();

    this->sortPoints();

    this->coincidentPoint();

    this->findConvexPolygon();

    this->starPolygon();
}

void Graham2D::draw()
{
    if(renderStarEdgeList == true)
    {
        for (std::list<Edge*>::iterator it=starEdgeList.begin(); it!=starEdgeList.end(); it++)
            (*it)->draw(1);
    }

    if(renderStarPoligonList == true)
    {
        for (std::list<Edge*>::iterator it=starPoligonList.begin(); it!=starPoligonList.end(); it++)
            (*it)->draw(1);
    }

    if(renderConvexHull == true)
    {
        for (std::list<Edge*>::iterator it=convexHullList.begin(); it!=convexHullList.end(); it++)
            (*it)->draw(1);
    }

    if(renderPointList == true)
    {
        for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
            (*it)->draw();
    }

    if(renderConvexPointList == true)
    {
        for (std::list<Point*>::iterator it=convexPointList.begin(); it!=convexPointList.end(); it++)
            (*it)->draw();
    }

    if(renderCentroid== true)
    {
        if(centroid != NULL)
            centroid->draw();
    }
}
