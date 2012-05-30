#ifndef _glcanvase_
#define _glcanvas_

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "../Camera.h"

#include "../ResourceManager.h"


class GLCanvas : public wxGLCanvas
{
    friend class LohnerFrame;
public:
	GLCanvas(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style=0, const wxString& name=_T("GLCanvas"), int* attribList = 0);
    ~GLCanvas();

    void init();
    void render();
    void renderBackground();
    void fitCam();

    void clear();

    int select1, select2;

private:
    void onPaint(wxPaintEvent& event);
    void onSize(wxSizeEvent& event);
    void onEraseBackground(wxEraseEvent& event);
    void onEnterWindow(wxMouseEvent& event);

    void resizeOrtho(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);

    void onMouseLeftDown(wxMouseEvent& event);
    void onMouseLeftUp(wxMouseEvent& event);
    void onMouseWheel(wxMouseEvent& event);

    void onMouseMove(wxMouseEvent& event);


    DECLARE_EVENT_TABLE()


private:
    wxGLContext *glContext;
    ResourceManager manager;

    Camera camera;

    double xMin, xMax, yMin, yMax, zMin, zMax;
    wxPoint lastPos;

    //Textura usada para desenhar a cena
    unsigned int texID;

};

#endif
