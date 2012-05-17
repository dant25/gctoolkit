#ifndef __LohnerFrame__
#define __LohnerFrame__

/**
@file
Subclass of PrincipalFrame, which is generated by wxFormBuilder.
*/

#include <string>
#include <fstream>

#include "PrincipalFrame.h"


/** Implementing PrincipalFrame */
class LohnerFrame : public PrincipalFrame
{
protected:
	// Handlers for PrincipalFrame events.
    void newModel( wxCommandEvent& event );
    void openModel( wxCommandEvent& event );
    void saveModel( wxCommandEvent& event );
    void fitCam( wxCommandEvent& event );
    void quit( wxCommandEvent& event );
    void setGraham( wxCommandEvent& event );
    void about( wxCommandEvent& event );
    void setPage( wxNotebookEvent& event );
    void setCentroid( wxCommandEvent& event );
    void setPoints( wxCommandEvent& event );
    void setConvexPoints( wxCommandEvent& event );
    void setStarEdges( wxCommandEvent& event );
    void setStarPoligon( wxCommandEvent& event );
    void setConvexHull( wxCommandEvent& event );
    void clearGraham( wxCommandEvent& event );
    void executeGraham( wxCommandEvent& event );

    void setDelaunay( wxCommandEvent& event );
    void setPointsDelaunay( wxCommandEvent& event );
    void setTriangles( wxCommandEvent& event );
    void setCircumference( wxCommandEvent& event );
    void clearDelaunay( wxCommandEvent& event );
    void executeDelaunay( wxCommandEvent& event );

    void setMergeHull3D( wxCommandEvent& event );
    void setPointsMergeHull3d( wxCommandEvent& event );
    void setFacesMergeHull3d( wxCommandEvent& event );
    void clearMergeHull3D( wxCommandEvent& event );
    void executeMergeHull3D( wxCommandEvent& event );

public:

	void init();

	/** Constructor */
	LohnerFrame( wxWindow* parent );
};

#endif // __LohnerFrame__