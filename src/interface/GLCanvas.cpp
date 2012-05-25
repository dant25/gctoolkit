#include "GLCanvas.h"


BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_SIZE( GLCanvas::onSize )
    EVT_PAINT( GLCanvas::onPaint )
    EVT_ERASE_BACKGROUND( GLCanvas::onEraseBackground )
    EVT_ENTER_WINDOW( GLCanvas::onEnterWindow )
    EVT_LEFT_DOWN( GLCanvas::onMouseLeftDown )
    EVT_LEFT_UP( GLCanvas::onMouseLeftUp )
    EVT_MOTION( GLCanvas::onMouseMove )
    EVT_MOUSEWHEEL( GLCanvas::onMouseWheel )
END_EVENT_TABLE()


GLCanvas::GLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name, int* attribList) :
wxGLCanvas(parent, id, pos, size, style, name,  attribList)
{
   glContext = new wxGLContext(this);
}

GLCanvas::~GLCanvas()
{
    delete glContext;
    glContext = NULL;
}

void GLCanvas::init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable( GL_DEPTH_TEST );
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable( GL_LINE_SMOOTH );
    glLineWidth( 2.0 );
    glEnable( GL_POLYGON_SMOOTH );
    glEnable(GL_POLYGON_OFFSET_FILL);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

glClear(GL_COLOR_BUFFER_BIT);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_POINT_SMOOTH);
glEnable(GL_LINE_SMOOTH);

    //Inicialização da luz
    GLfloat lambient_model[4] = { 0.4, 0.4, 0.4, 1.0};
    GLfloat a[4] = { 0.5, 0.5, 0.5, 1.0};
    GLfloat d[4] = { 0.8, 0.8, 0.8, 0.80};
    GLfloat s[4] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat p[4] = { 100.0, 100.0, 120.0, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    glLightfv(GL_LIGHT0, GL_SPECULAR, s);
    glLightfv(GL_LIGHT0, GL_POSITION, p);
    glEnable(GL_LIGHT0);


    glEnable(GL_LIGHT_MODEL_AMBIENT);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lambient_model);



    //Inicialização do viewport
    int w, h;
    //double ratio = (double) w/(double) h;
    GetClientSize(&w, &h);
    glViewport(0, 0, (GLint) w , (GLint) h );

    //gluOrtho2D(-200,200,-200,200);
    //gluOrtho2D(0,1,0,1);  //JONAS
    camera.fit(manager.getBoundingBox());
}

void GLCanvas::resizeOrtho(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
{
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(xMin, xMax, yMin, yMax);
    //glFrustum(xMin, xMax, yMin, yMax, zMin, zMax);
    camera.fit(manager.getBoundingBox());
}

void GLCanvas::fitCam()
{
    double fatorX = (manager.getBoxXmax() - manager.getBoxXmin())*0.05;
    double fatorY = (manager.getBoxYmax() - manager.getBoxYmin())*0.05;
    double fatorZ = (manager.getBoxZmax() - manager.getBoxZmin())*0.05;

    xMin = manager.getBoxXmin()-fatorX;
    xMax = manager.getBoxXmax()+fatorX;
    yMin = manager.getBoxYmin()-fatorY;
    yMax = manager.getBoxYmax()+fatorY;
    zMin = manager.getBoxZmin()-fatorZ;
    zMax = manager.getBoxZmax()+fatorZ;

    //this->resizeOrtho(xMin, xMax, yMin, yMax, zMin, zMax);
    camera.fit(manager.getBoundingBox());
}

void GLCanvas::render()
{
    SetCurrent(*glContext);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(xMin, xMax, yMin, yMax, zMin, zMax);
    //renderBackground();

    camera.render();

    BoundingBox octBBox = manager.getBoundingBox();
    Vector3 center((octBBox.pMin.x + octBBox.pMax.x)*0.5,
                   (octBBox.pMin.y + octBBox.pMax.y)*0.5,
                   (octBBox.pMin.z + octBBox.pMax.z)*0.5);


    glPushAttrib( GL_TRANSFORM_BIT );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

    glTranslatef(-center.x, -center.y, -center.z);

    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEdgeFlag(GL_FALSE);

    manager.render();

    //glFlush();
    SwapBuffers();
    //Refresh();
}

void GLCanvas::renderBackground()
{
    // Save color, shading, fill mode, culling, matrixe mode, so it can be restored later
    glPushAttrib( GL_CURRENT_BIT | GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_TRANSFORM_BIT | GL_DEPTH_BUFFER_BIT );

    // To guarantee we can fill a polygon
    glPolygonMode( GL_FRONT, GL_FILL );
    glDisable( GL_LIGHTING );
    glDisable( GL_CULL_FACE );

    // To guarantee we can do gradient color
    glShadeModel( GL_SMOOTH );

    // Make it be rendered always below objects
    glDisable( GL_DEPTH_TEST );

    // Save modelview matrix and reset current to identity
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Save projection matrix and reset current to identity
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();

    // Draw the gradient background ( degradê )
    glBegin(GL_QUADS);
        glColor3f(0.6431,0.5843,0.8705);
        glVertex2f(-1.0,-1.0);
        glVertex2f(1.0,-1.0);
        glColor3f(0.0862,0.0,0.4039);
        glVertex2f(1.0,1.0);
        glVertex2f(-1.0,1.0);
    glEnd();

    // Restore projection matrix
    glPopMatrix();

    // Restore modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    // Restore states changed
    glPopAttrib();
}

void GLCanvas::clear() {
    //scene.clear();
    Refresh();
}

#include <iostream>

void GLCanvas::onEnterWindow(wxMouseEvent& event)
{
    SetFocus();
}

void GLCanvas::onPaint( wxPaintEvent& event )
{
    wxPaintDC dc(this);
    render();
}

void GLCanvas::onSize(wxSizeEvent& event)
{
    // Necessary to update the context in some plataforms
    wxGLCanvas::OnSize(event);

    // Reset the viewport
    int w, h;
    GetClientSize(&w, &h);

	glViewport(0, 0, (GLint) w , (GLint) h );

    // Redraw window
    Refresh();
/*
    // Necessary to update the context in some plataforms
    wxGLCanvas::OnSize(event);

    // Reset the viewport
    int w, h;
    GetClientSize(&w, &h);

    glViewport(0, 0, (GLint) w , (GLint) h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    //FIXME passando na ordem inversa, funcionou então
    //não foi modificado
    //renderer.setImgSize(h, w);
    // Redraw window
    Refresh();
    */
}

void GLCanvas::onEraseBackground(wxEraseEvent& event)
{
  // Just to get rid of flickering.
}

void GLCanvas::onMouseLeftDown(wxMouseEvent& event)
{
/*
std::cout << "DOWN" << std::endl;

    wxPoint mouse;
    event.GetPosition( &lastPos.x, &lastPos.y );
*/
}

void GLCanvas::onMouseLeftUp(wxMouseEvent& event)
{
    camera.reset();
}

void GLCanvas::onMouseWheel(wxMouseEvent& event)
{
    if ( event.ControlDown() )
    {
        int wheel = event.GetWheelRotation();
        if ( wheel > 0 )
            camera.zoom( 0.8 );
        else
            camera.zoom( 1.2 );
    }
    /*
    int wheel = event.GetWheelRotation();
    if ( wheel > 0 )
    {
        xMin = xMin*0.9;
        xMax = xMax*0.9;
        yMin = yMin*0.9;
        yMax = yMax*0.9;
        zMin = zMin*0.9;
        zMax = zMax*0.9;
    }
    else
    {
        xMin = xMin*1.2;
        xMax = xMax*1.2;
        yMin = yMin*1.2;
        yMax = yMax*1.2;
        zMin = zMin*1.2;
        zMax = zMax*1.2;
    }

    this->resizeOrtho(xMin, xMax, yMin, yMax, zMin, zMax);
*/
    Refresh();
}


void GLCanvas::onMouseMove(wxMouseEvent &event)
{
    wxPoint mouse;
    event.GetPosition( &mouse.x, &mouse.y );

    wxPoint windowSize;
    GetClientSize( &windowSize.x, &windowSize.y );
    //static wxString msg;

    if ( event.Dragging() )
    {
        camera.updateRotatation(mouse.x,mouse.y, windowSize.x, windowSize.y);
        //static std::string temp;
        //temp = manipulator->update( mouse.x, mouse.y, windowSize.x, windowSize.y );
        //msg = wxString::FromAscii( temp.c_str() );
        //parent->SetStatusText( msg, 1 );
    }
    //else
    //{
    //    msg.Printf(_("Mouse Position: ( %d, %d )"), mouse.x, mouse.y );
    //    parent->SetStatusText( msg, 1 );
    //}

    Refresh();
    event.Skip();
}

