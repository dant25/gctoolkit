#include "GLCanvas.h"


BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_SIZE( GLCanvas::onSize )
    EVT_PAINT( GLCanvas::onPaint )
    EVT_ERASE_BACKGROUND( GLCanvas::onEraseBackground )
    EVT_ENTER_WINDOW( GLCanvas::onEnterWindow )
    EVT_LEFT_DOWN( GLCanvas::onMouseLeftDown )
    EVT_LEFT_UP( GLCanvas::onMouseLeftUp )
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
    //float ratio = (float) w/(float) h;
    GetClientSize(&w, &h);
    glViewport(0, 0, (GLint) w , (GLint) h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-100, 100, -100, 100, 0, 1);
    //gluOrtho2D(-200,200,-200,200);
    gluOrtho2D(0,1,0,1);  //JONAS
}

void GLCanvas::resizeOrtho(float xMin, float xMax, float yMin, float yMax)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xMin, xMax, yMin, yMax);
}

void GLCanvas::fitCam()
{
    float fatorX = (manager.getBoxXmax() - manager.getBoxXmin())*0.05;
    float fatorY = (manager.getBoxYmax() - manager.getBoxYmin())*0.05;

    xMin = manager.getBoxXmin()-fatorX;
    xMax = manager.getBoxXmax()+fatorX;
    yMin = manager.getBoxYmin()-fatorY;
    yMax = manager.getBoxYmax()+fatorY;

    this->resizeOrtho(xMin, xMax, yMin, yMax);
}

void GLCanvas::render()
{
    SetCurrent(*glContext);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //renderBackground();


    manager.render();

/*
glPointSize(7);
glColor3f(1, 0, 0);
glBegin(GL_POINTS);
    glVertex2f(-1, 0);
    glVertex2f(0, -1);
    glVertex2f(-1, -1);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
    glVertex2f(1, 0);
    glVertex2f(1, 1);
    glVertex2f(10, 10);
glEnd();
std::cout << "asdasdasdasdas" << std::endl;
*/
/*
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, texID);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
    glEnd();
*/
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    //FIXME passando na ordem inversa, funcionou então
    //não foi modificado
    //renderer.setImgSize(h, w);
    // Redraw window
    Refresh();
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
/*
std::cout << "UP" << std::endl;
    wxPoint mouse;
    event.GetPosition( &mouse.x, &mouse.y );

    wxPoint windowSize;
    GetClientSize( &windowSize.x, &windowSize.y );
    static wxString msg;

        //temp = manipulator->update( mouse.x, mouse.y, windowSize.x, windowSize.y );

        wxPoint currPos;
        currPos.x = ( this->lastPos.x - ( ( 2.0 * mouse.x - windowSize.x ) / windowSize.x ) );
        currPos.y = ( this->lastPos.y - ( ( windowSize.y - 2.0 * mouse.y ) / windowSize.y ) );


        xMin += currPos.x;
        xMax += currPos.x;
        yMin += currPos.y;
        yMax += currPos.y;

        this->resizeOrtho(xMin, xMax, yMin, yMax);

        Refresh();
//Vector3 offset = lastPos - currPos;
//Vector3 distance =  SPEED * ( lastPos - currPos );
//mesh->move( distance );
*/
}

void GLCanvas::onMouseWheel(wxMouseEvent& event)
{
    int wheel = event.GetWheelRotation();
    if ( wheel > 0 )
    {
        xMin = xMin*0.9;
        xMax = xMax*0.9;
        yMin = yMin*0.9;
        yMax = yMax*0.9;
    }
    else
    {
        xMin = xMin*1.2;
        xMax = xMax*1.2;
        yMin = yMin*1.2;
        yMax = yMax*1.2;
    }

    this->resizeOrtho(xMin, xMax, yMin, yMax);

    Refresh();
}
