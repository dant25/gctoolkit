#include "MergeHull3D.h"

#include <fstream>
#include <GL/gl.h>

MergeHull3D::MergeHull3D(std::list< std::list<Point*> > list)
{
    renderPointList = true;
    renderFacesList = true;
    renderEdgesList = true;

    this->listObj = list;
}

MergeHull3D::~MergeHull3D()
{
    //dtor
}

void MergeHull3D::draw()
{
   if(renderPointList == true)
    {
        for (std::list< std::list<Point*> >::iterator iter=listObj.begin(); iter!=listObj.end(); iter++)
            for (std::list<Point*>::iterator it=(*iter).begin(); it!=(*iter).end(); it++)
                (*it)->draw();
    }

    if(renderFacesList == true)
    {
        for (std::list<Polygon*>::iterator it=facesList.begin(); it!=facesList.end(); it++)
            (*it)->draw(true);
    }

    if(renderEdgesList == true)
    {
        for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
            (*it)->draw(true);
    }

}

bool MergeHull3D::save(std::string fileName)
{
    std::fstream arquivo;
    arquivo.open( fileName.c_str() , std::ios::trunc | std::ios::out);// | ios::in);

    arquivo << std::endl << "METODO MERGE HULL 3D" << std::endl  << std::endl;
    arquivo << "PONTOS DAS FACES" << std::endl;
    arquivo << facesList.size()-1 << std::endl;

    for (std::list<Polygon*>::iterator it=facesList.begin(); it!=facesList.end(); it++)
    {
        for(unsigned int i = 0; i < (*it)->numPoints(); i++)
        {
            arquivo << (*it)->getPoint(i)->getCoord(0) << "\t" << (*it)->getPoint(i)->getCoord(1) << "\t" << (*it)->getPoint(i)->getCoord(2) << "\t";
        }
            arquivo << std::endl;
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

void MergeHull3D::setEdge()
{
    renderEdgesList = !renderEdgesList;
}

void MergeHull3D::clear()
{
    listObj.clear();
    pointList.clear();
    edgeList.clear();
    free_edgeList.clear();
    facesList.clear();
}

void MergeHull3D::execute()
{
    for (std::list< std::list<Point*> >::iterator iter=listObj.begin(); iter!=listObj.end(); iter++)
    {
        pointList = (*iter);

        initialFace(pointList);

        while( free_edgeList.size() > 0)
            nextFaces();
        /*
        std::cout << "Num faces: " << facesList.size() << std::endl;
        std::cout << "Num edge: " << edgeList.size() << std::endl;
        std::cout << "Num edge FREE: " << free_edgeList.size() << std::endl;
        */
        pointList.clear();
    }
}

bool MergeHull3D::existEdge(Edge3D e)
{
    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        if( e.equal((*it)) )
        {
            if( ((Edge3D*)*it)->getAdjFaceList().size() > 1)
                return true;
        }
    }
   return false;
}

void MergeHull3D::addEdge(Edge3D* e)
{
    for (std::list<Edge*>::iterator it=edgeList.begin(); it!=edgeList.end(); it++)
    {
        if( e->equal((*it)) )
        {
            e = (Edge3D*)(*it);
            //if( ((Edge3D*)*it)->getAdjFaceList().size() > 1)
                free_edgeList.remove( (*it) );

            return;
        }
    }
    edgeList.push_back(e);
    free_edgeList.push_back(e);
}

void MergeHull3D::initialFace(std::list<Point*> pointList)
{
    pointList.sort(compareY);

    Point *p0 = pointList.front();
    Point *p0_1 = new Point3D( p0->getCoord(0) + 1.0, p0->getCoord(1), p0->getCoord(2) );
    Point *p0_2 = new Point3D( p0->getCoord(0), p0->getCoord(1), p0->getCoord(2) - 1.0 );


    Vector3 n1 = Vector3(p0_1->getCoord(0) - p0->getCoord(0), p0_1->getCoord(1) - p0->getCoord(1), p0_1->getCoord(2) - p0->getCoord(2))
                ^Vector3(p0_2->getCoord(0) - p0->getCoord(0), p0_2->getCoord(1) - p0->getCoord(1), p0_2->getCoord(2) - p0->getCoord(2));

    n1.normalize();

    double ang = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( (*it)->getId() == p0->getId() )
            continue;

        Vector3 n2 = Vector3( p0->getCoord(0) - (*it)->getCoord(0), p0->getCoord(1) - (*it)->getCoord(1), p0->getCoord(2) - (*it)->getCoord(2))
                    ^Vector3(p0_2->getCoord(0) - (*it)->getCoord(0), p0_2->getCoord(1) - (*it)->getCoord(1), p0_2->getCoord(2) - (*it)->getCoord(2));

        n2.normalize();

        double ang_temp = n2.angle(n1);

        if(ang >= ang_temp)
        {
            ang = ang_temp;
            p0_1 = (*it);
        }
    }


    n1 = Vector3(p0_1->getCoord(0) - p0->getCoord(0), p0_1->getCoord(1) - p0->getCoord(1), p0_1->getCoord(2) - p0->getCoord(2))
        ^Vector3(p0_2->getCoord(0) - p0->getCoord(0), p0_2->getCoord(1) - p0->getCoord(1), p0_2->getCoord(2) - p0->getCoord(2));

    n1.normalize();

    ang = 360.0;

    for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
    {
        if( (*it)->getId() == p0->getId() || (*it)->getId() == p0_1->getId() )
            continue;

        Vector3 n2 = Vector3( p0->getCoord(0) - (*it)->getCoord(0), p0->getCoord(1) - (*it)->getCoord(1), p0->getCoord(2) - (*it)->getCoord(2))
                    ^Vector3(p0_1->getCoord(0) - (*it)->getCoord(0), p0_1->getCoord(1) - (*it)->getCoord(1), p0_1->getCoord(2) - (*it)->getCoord(2));

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

void MergeHull3D::nextFaces()
{
    Edge *edge_aux = free_edgeList.front();

    if( ((Edge3D*)edge_aux)->getAdjFaceList().size() == 1 )
    {
        Polygon* face = ((Edge3D*)edge_aux)->getAdjFaceList().front();

        Vector3 n1 = Vector3( face->getPoint(1)->getCoord(0) - face->getPoint(0)->getCoord(0), face->getPoint(1)->getCoord(1) - face->getPoint(0)->getCoord(1), face->getPoint(1)->getCoord(2) - face->getPoint(0)->getCoord(2))
                    ^Vector3( face->getPoint(2)->getCoord(0) - face->getPoint(0)->getCoord(0), face->getPoint(2)->getCoord(1) - face->getPoint(0)->getCoord(1), face->getPoint(2)->getCoord(2) - face->getPoint(0)->getCoord(2));

        n1.normalize();

        double ang = 360.0;

        Point *p = NULL;

        for (std::list<Point*>::iterator it=pointList.begin(); it!=pointList.end(); it++)
        {
/*
            if( ((Edge3D*)edge_aux)->getAdjFaceList().front()->getPoint(0)->getId() == (*it)->getId()
               || ((Edge3D*)edge_aux)->getAdjFaceList().front()->getPoint(1)->getId() == (*it)->getId()
               || ((Edge3D*)edge_aux)->getAdjFaceList().front()->getPoint(2)->getId() == (*it)->getId() )
                continue;

            if( existEdge( Edge3D( (Point3D*)(*it), (Point3D*)edge_aux->getP1()) )
                && existEdge( Edge3D( (Point3D*)(*it), (Point3D*)edge_aux->getP2()) ) )
                continue;
*/
            Vector3 n2 = Vector3( edge_aux->getP2()->getCoord(0) - (*it)->getCoord(0), edge_aux->getP2()->getCoord(1) - (*it)->getCoord(1), edge_aux->getP2()->getCoord(2) - (*it)->getCoord(2))
                        ^Vector3( edge_aux->getP1()->getCoord(0) - (*it)->getCoord(0), edge_aux->getP1()->getCoord(1) - (*it)->getCoord(1), edge_aux->getP1()->getCoord(2) - (*it)->getCoord(2));

            n2.normalize();

            double ang_temp = n1.angle(n2);

            if(ang >= ang_temp)
            {
                ang = ang_temp;
                p = (*it);
            }
        }
        if(p == NULL) return;


        Edge *e0 = new Edge3D( (Point3D*)edge_aux->getP2(), (Point3D*)edge_aux->getP1(), edgeList.size()+1);;
        Edge *e1 = new Edge3D( (Point3D*)edge_aux->getP1(), (Point3D*)p, edgeList.size()+1);
        Edge *e2 = new Edge3D( (Point3D*)p, (Point3D*)edge_aux->getP2(), edgeList.size()+1);

        addEdge( (Edge3D*)e0 );
        addEdge( (Edge3D*)e1 );
        addEdge( (Edge3D*)e2 );

        GeometricShape *face_aux = new Polygon(3);

        face_aux->setPoint(0, edge_aux->getP1());
        face_aux->setPoint(1, p);
        face_aux->setPoint(2, edge_aux->getP2());

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

        //REMOVE A ARESTA QUE ERA FREE DA LISTA POIS FOI ENCONTRADA SUA NOVA FACE
        ((Edge3D*)edge_aux)->addAdjFace( (Polygon*)face_aux );
        free_edgeList.remove(edge_aux);
    }
}

bool compareZ(Point* first, Point* second)
{
    if(first->getCoord(2) < second->getCoord(2))
        return true;
    else
        return false;
}

bool compareX(Point* first, Point* second)
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

bool MergeHull3D::compareY(Point* first, Point* second)
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
