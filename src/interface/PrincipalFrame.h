///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PrincipalFrame__
#define __PrincipalFrame__

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include "GLCanvas.h"
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PrincipalFrame
///////////////////////////////////////////////////////////////////////////////
class PrincipalFrame : public wxFrame 
{
	DECLARE_EVENT_TABLE()
	private:
		
		// Private event handlers
		void _wxFB_newModel( wxCommandEvent& event ){ newModel( event ); }
		void _wxFB_openModel( wxCommandEvent& event ){ openModel( event ); }
		void _wxFB_saveModel( wxCommandEvent& event ){ saveModel( event ); }
		void _wxFB_quit( wxCommandEvent& event ){ quit( event ); }
		void _wxFB_setGraham( wxCommandEvent& event ){ setGraham( event ); }
		void _wxFB_setDelaunay( wxCommandEvent& event ){ setDelaunay( event ); }
		void _wxFB_setMergeHull3D( wxCommandEvent& event ){ setMergeHull3D( event ); }
		void _wxFB_setDelauny3D( wxCommandEvent& event ){ setDelauny3D( event ); }
		void _wxFB_setVoronoi( wxCommandEvent& event ){ setVoronoi( event ); }
		void _wxFB_about( wxCommandEvent& event ){ about( event ); }
		void _wxFB_fitCam( wxCommandEvent& event ){ fitCam( event ); }
		void _wxFB_setPage( wxNotebookEvent& event ){ setPage( event ); }
		void _wxFB_setCentroid( wxCommandEvent& event ){ setCentroid( event ); }
		void _wxFB_setPoints( wxCommandEvent& event ){ setPoints( event ); }
		void _wxFB_setConvexPoints( wxCommandEvent& event ){ setConvexPoints( event ); }
		void _wxFB_setStarEdges( wxCommandEvent& event ){ setStarEdges( event ); }
		void _wxFB_setStarPoligon( wxCommandEvent& event ){ setStarPoligon( event ); }
		void _wxFB_setConvexHull( wxCommandEvent& event ){ setConvexHull( event ); }
		void _wxFB_clearGraham( wxCommandEvent& event ){ clearGraham( event ); }
		void _wxFB_executeGraham( wxCommandEvent& event ){ executeGraham( event ); }
		void _wxFB_setPointsDelaunay( wxCommandEvent& event ){ setPointsDelaunay( event ); }
		void _wxFB_setTriangles( wxCommandEvent& event ){ setTriangles( event ); }
		void _wxFB_setCircumference( wxCommandEvent& event ){ setCircumference( event ); }
		void _wxFB_clearDelaunay( wxCommandEvent& event ){ clearDelaunay( event ); }
		void _wxFB_executeDelaunay( wxCommandEvent& event ){ executeDelaunay( event ); }
		void _wxFB_setPointsMergeHull3d( wxCommandEvent& event ){ setPointsMergeHull3d( event ); }
		void _wxFB_setFacesMergeHull3d( wxCommandEvent& event ){ setFacesMergeHull3d( event ); }
		void _wxFB_setEdgesMergeHull3d( wxCommandEvent& event ){ setEdgesMergeHull3d( event ); }
		void _wxFB_clearMergeHull3D( wxCommandEvent& event ){ clearMergeHull3D( event ); }
		void _wxFB_executeMergeHull3D( wxCommandEvent& event ){ executeMergeHull3D( event ); }
		void _wxFB_setPointsDelaunay3D( wxCommandEvent& event ){ setPointsDelaunay3D( event ); }
		void _wxFB_setEdgesDelaunay3D( wxCommandEvent& event ){ setEdgesDelaunay3D( event ); }
		void _wxFB_setTrianglesDelaunay3D( wxCommandEvent& event ){ setTrianglesDelaunay3D( event ); }
		void _wxFB_clearDelaunay3D( wxCommandEvent& event ){ clearDelaunay3D( event ); }
		void _wxFB_executeDelaunay3D( wxCommandEvent& event ){ executeDelaunay3D( event ); }
		void _wxFB_setPointsVoronoi( wxCommandEvent& event ){ setPointsVoronoi( event ); }
		void _wxFB_setEdgesVoronoi( wxCommandEvent& event ){ setEdgesVoronoi( event ); }
		void _wxFB_setTrianglesVoronoi( wxCommandEvent& event ){ setTrianglesVoronoi( event ); }
		void _wxFB_clearVoronoi( wxCommandEvent& event ){ clearVoronoi( event ); }
		void _wxFB_executeVoronoi( wxCommandEvent& event ){ executeVoronoi( event ); }
		
	
	protected:
		enum
		{
			ID_NEW_MODEL = 1000,
			ID_OPEN_MODEL,
			ID_SAVE_MODEL,
			ID_QUIT,
			wxID_GRAHAM,
			wxID_DELAUNAY,
			wxID_MERGEHULL3D,
			wxID_DELAUNAY3D,
			wxID_VORONOI,
			ID_ABOUT,
			wxID_FITCAM,
			wxID_NOTEBOOK,
			wxID_CENTROIDGRAHAM,
			wxID_POINTSGRAHAM,
			wxID_CONVEXPOINTSGRAHAM,
			wxID_STAREDGESGRAHAM,
			wxID_STARPOLIGONGRAHAM,
			wxID_CONVEXHULLGRAHAM,
			wxID_GRAHAMCLEAN,
			wxID_GRAHAMEXECUTE,
			wxID_POINTSDELAUNAY,
			wxID_TRIANGLESDELAUNAY,
			wxID_CIRCUMFERENCEDELAUNAY,
			wxID_DELAUNAYCLEAN,
			wxID_DELAUNAYEXECUTE,
			wxID_POINTSMERGEHULL3D,
			wxID_TRIANGLESMERGEHULL3D,
			wxID_EDGESMERGEHULL3D,
			wxID_MERGEHULL3DCLEAN,
			wxID_MERGEHULL3DEXECUTE,
			wxID_POINTSDELAUNAY3D,
			wxID_EDGESDELAUNAY3D,
			wxID_TRIANGLESDELAUNAY3D,
			wxID_DELAUNAY3DCLEAN,
			wxID_DELAUNAY3DEXECUTE,
			wxID_POINTSVORONOI,
			wxID_EDGESVORONIO,
			wxID_TRIANGLESVORONIO,
			wxID_VORONOICLEAN,
			wxID_VORONOIEXECUTE,
		};
		
		wxStatusBar* statusBar;
		wxMenuBar* menubar;
		wxMenu* file_menu;
		wxMenu* operations_menu;
		wxMenu* help_menu;
		wxToolBar* toolBar;
		wxNotebook* options_notebook;
		wxPanel* graham_panel;
		wxStaticText* show_staticText;
		wxStaticLine* m_staticline1;
		wxCheckBox* centroidGraham_checkBox;
		wxCheckBox* pointsGraham_checkBox;
		wxCheckBox* convexPointsGraham_checkBox;
		wxCheckBox* starEdgesGraham_checkBox;
		wxCheckBox* starPoligonGraham_checkBox;
		wxCheckBox* convexEdgesGraham_checkBox;
		wxStaticLine* m_staticline2;
		wxToggleButton* grahamClean_toggleBtn;
		wxToggleButton* grahamExecute_toggleBtn;
		wxPanel* delaunay_painel;
		wxStaticText* show_staticText2;
		wxStaticLine* m_staticline11;
		wxCheckBox* pointsDelaunay_checkBox;
		wxCheckBox* trianglesDelaunay_checkBox;
		wxCheckBox* circumferenceDelaunay_checkBox;
		wxStaticLine* m_staticline21;
		wxToggleButton* delaunayClean_toggleBtn;
		wxToggleButton* delaunayExecute_toggleBtn;
		wxPanel* mergehull3d_panel;
		wxStaticText* show_staticText21;
		wxStaticLine* m_staticline111;
		wxCheckBox* pointsMergeHull3D_checkBox1;
		wxCheckBox* facesMergeHull3D_checkBox;
		wxCheckBox* edgesMergeHull3D_checkBox;
		wxStaticLine* m_staticline211;
		wxToggleButton* mergehull3dClean_toggleBtn;
		wxToggleButton* mergehull3dExecute_toggleBtn;
		wxPanel* delaunay3d_painel;
		wxStaticText* show_staticText22;
		wxStaticLine* m_staticline112;
		wxCheckBox* pointsDelaunay3D_checkBox;
		wxCheckBox* edgesDelaunay3D_checkBox;
		wxCheckBox* trianglesDelaunay3D_checkBox;
		wxStaticLine* m_staticline212;
		wxToggleButton* delaunay3DClean_toggleBtn;
		wxToggleButton* delaunay3DExecute_toggleBtn;
		wxPanel* voronoi_painel;
		wxStaticText* show_staticText23;
		wxStaticLine* m_staticline113;
		wxCheckBox* pointsVoronoi_checkBox;
		wxCheckBox* edgesVoronoi_checkBox;
		wxCheckBox* trianglesVoronoi_checkBox;
		wxStaticLine* m_staticline213;
		wxToggleButton* voronioClean_toggleBtn;
		wxToggleButton* voronoiExecute_toggleBtn;
		GLCanvas *canvas;
		
		// Virtual event handlers, overide them in your derived class
		virtual void newModel( wxCommandEvent& event ) { event.Skip(); }
		virtual void openModel( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveModel( wxCommandEvent& event ) { event.Skip(); }
		virtual void quit( wxCommandEvent& event ) { event.Skip(); }
		virtual void setGraham( wxCommandEvent& event ) { event.Skip(); }
		virtual void setDelaunay( wxCommandEvent& event ) { event.Skip(); }
		virtual void setMergeHull3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void setDelauny3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void setVoronoi( wxCommandEvent& event ) { event.Skip(); }
		virtual void about( wxCommandEvent& event ) { event.Skip(); }
		virtual void fitCam( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPage( wxNotebookEvent& event ) { event.Skip(); }
		virtual void setCentroid( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPoints( wxCommandEvent& event ) { event.Skip(); }
		virtual void setConvexPoints( wxCommandEvent& event ) { event.Skip(); }
		virtual void setStarEdges( wxCommandEvent& event ) { event.Skip(); }
		virtual void setStarPoligon( wxCommandEvent& event ) { event.Skip(); }
		virtual void setConvexHull( wxCommandEvent& event ) { event.Skip(); }
		virtual void clearGraham( wxCommandEvent& event ) { event.Skip(); }
		virtual void executeGraham( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPointsDelaunay( wxCommandEvent& event ) { event.Skip(); }
		virtual void setTriangles( wxCommandEvent& event ) { event.Skip(); }
		virtual void setCircumference( wxCommandEvent& event ) { event.Skip(); }
		virtual void clearDelaunay( wxCommandEvent& event ) { event.Skip(); }
		virtual void executeDelaunay( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPointsMergeHull3d( wxCommandEvent& event ) { event.Skip(); }
		virtual void setFacesMergeHull3d( wxCommandEvent& event ) { event.Skip(); }
		virtual void setEdgesMergeHull3d( wxCommandEvent& event ) { event.Skip(); }
		virtual void clearMergeHull3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void executeMergeHull3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPointsDelaunay3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void setEdgesDelaunay3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void setTrianglesDelaunay3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void clearDelaunay3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void executeDelaunay3D( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPointsVoronoi( wxCommandEvent& event ) { event.Skip(); }
		virtual void setEdgesVoronoi( wxCommandEvent& event ) { event.Skip(); }
		virtual void setTrianglesVoronoi( wxCommandEvent& event ) { event.Skip(); }
		virtual void clearVoronoi( wxCommandEvent& event ) { event.Skip(); }
		virtual void executeVoronoi( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PrincipalFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GC Toolkit"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,688 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~PrincipalFrame();
	
};

#endif //__PrincipalFrame__
