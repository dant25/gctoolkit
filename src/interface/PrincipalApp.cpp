#include "PrincipalApp.h"


#include "PrincipalFrame.h"
#include "LohnerFrame.h"
#include <wx/image.h>



IMPLEMENT_APP(PrincipalApp);

bool PrincipalApp::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	LohnerFrame* Frame = new LohnerFrame(0);
    	Frame->Show();
        Frame->init();
    	SetTopWindow(Frame);
    }

    return wxsOK;

}
