///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PrincipalFrame.h"

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( PrincipalFrame, wxFrame )
	EVT_MENU( ID_NEW_MODEL, PrincipalFrame::_wxFB_newModel )
	EVT_MENU( ID_OPEN_MODEL, PrincipalFrame::_wxFB_openModel )
	EVT_MENU( ID_SAVE_MODEL, PrincipalFrame::_wxFB_saveModel )
	EVT_MENU( ID_QUIT, PrincipalFrame::_wxFB_quit )
	EVT_MENU( wxID_GRAHAM, PrincipalFrame::_wxFB_setGraham )
	EVT_MENU( wxID_DELAUNAY, PrincipalFrame::_wxFB_setDelaunay )
	EVT_MENU( wxID_MERGEHULL3D, PrincipalFrame::_wxFB_setMergeHull3D )
	EVT_MENU( ID_ABOUT, PrincipalFrame::_wxFB_about )
	EVT_TOOL( ID_NEW_MODEL, PrincipalFrame::_wxFB_newModel )
	EVT_TOOL( ID_OPEN_MODEL, PrincipalFrame::_wxFB_openModel )
	EVT_TOOL( ID_SAVE_MODEL, PrincipalFrame::_wxFB_saveModel )
	EVT_TOOL( wxID_FITCAM, PrincipalFrame::_wxFB_fitCam )
	EVT_NOTEBOOK_PAGE_CHANGED( wxID_NOTEBOOK, PrincipalFrame::_wxFB_setPage )
	EVT_CHECKBOX( wxID_CENTROIDGRAHAM, PrincipalFrame::_wxFB_setCentroid )
	EVT_CHECKBOX( wxID_POINTSGRAHAM, PrincipalFrame::_wxFB_setPoints )
	EVT_CHECKBOX( wxID_CONVEXPOINTSGRAHAM, PrincipalFrame::_wxFB_setConvexPoints )
	EVT_CHECKBOX( wxID_STAREDGESGRAHAM, PrincipalFrame::_wxFB_setStarEdges )
	EVT_CHECKBOX( wxID_STARPOLIGONGRAHAM, PrincipalFrame::_wxFB_setStarPoligon )
	EVT_CHECKBOX( wxID_CONVEXHULLGRAHAM, PrincipalFrame::_wxFB_setConvexHull )
	EVT_TOGGLEBUTTON( wxID_GRAHAMCLEAN, PrincipalFrame::_wxFB_clearGraham )
	EVT_TOGGLEBUTTON( wxID_GRAHAMEXECUTE, PrincipalFrame::_wxFB_executeGraham )
	EVT_CHECKBOX( wxID_POINTSDELAUNAY, PrincipalFrame::_wxFB_setPointsDelaunay )
	EVT_CHECKBOX( wxID_TRIANGLESDELAUNAY, PrincipalFrame::_wxFB_setTriangles )
	EVT_CHECKBOX( wxID_CIRCUMFERENCEDELAUNAY, PrincipalFrame::_wxFB_setCircumference )
	EVT_TOGGLEBUTTON( wxID_DELAUNAYCLEAN, PrincipalFrame::_wxFB_clearDelaunay )
	EVT_TOGGLEBUTTON( wxID_DELAUNAYEXECUTE, PrincipalFrame::_wxFB_executeDelaunay )
	EVT_CHECKBOX( wxID_POINTSMERGEHULL3D, PrincipalFrame::_wxFB_setPointsMergeHull3d )
	EVT_CHECKBOX( wxID_TRIANGLESMERGEHULL3D, PrincipalFrame::_wxFB_setFacesMergeHull3d )
	EVT_TOGGLEBUTTON( wxID_MERGEHULL3DCLEAN, PrincipalFrame::_wxFB_clearMergeHull3D )
	EVT_TOGGLEBUTTON( wxID_MERGEHULL3DEXECUTE, PrincipalFrame::_wxFB_executeMergeHull3D )
END_EVENT_TABLE()

PrincipalFrame::PrincipalFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 900,650 ), wxDefaultSize );

	statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	menubar = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	wxMenuItem* new_menuItem;
	new_menuItem = new wxMenuItem( file_menu, ID_NEW_MODEL, wxString( wxT("New") ) + wxT('\t') + wxT("Ctrl+N"), wxT("New Model"), wxITEM_NORMAL );
	file_menu->Append( new_menuItem );

	wxMenuItem* open_menuItem;
	open_menuItem = new wxMenuItem( file_menu, ID_OPEN_MODEL, wxString( wxT("Open") ) + wxT('\t') + wxT("Ctrl+O"), wxT("Open saved file"), wxITEM_NORMAL );
	file_menu->Append( open_menuItem );

	wxMenuItem* save_menuItem;
	save_menuItem = new wxMenuItem( file_menu, ID_SAVE_MODEL, wxString( wxT("Save") ) + wxT('\t') + wxT("Ctrl+S"), wxT("Save current model"), wxITEM_NORMAL );
	file_menu->Append( save_menuItem );

	wxMenuItem* quit_menuItem;
	quit_menuItem = new wxMenuItem( file_menu, ID_QUIT, wxString( wxT("Quit") ) + wxT('\t') + wxT("Ctrl+Q"), wxT("Quit program"), wxITEM_NORMAL );
	file_menu->Append( quit_menuItem );

	menubar->Append( file_menu, wxT("File") );

	operations_menu = new wxMenu();
	wxMenuItem* graham_menuItem;
	graham_menuItem = new wxMenuItem( operations_menu, wxID_GRAHAM, wxString( wxT("Graham") ) , wxEmptyString, wxITEM_RADIO );
	operations_menu->Append( graham_menuItem );
	graham_menuItem->Check( true );

	wxMenuItem* delaunay_menuItem;
	delaunay_menuItem = new wxMenuItem( operations_menu, wxID_DELAUNAY, wxString( wxT("Delaunay") ) , wxEmptyString, wxITEM_RADIO );
	operations_menu->Append( delaunay_menuItem );
	delaunay_menuItem->Check( true );

	wxMenuItem* mergehull3d_menuItem;
	mergehull3d_menuItem = new wxMenuItem( operations_menu, wxID_MERGEHULL3D, wxString( wxT("Merge Hull 3D") ) , wxEmptyString, wxITEM_RADIO );
	operations_menu->Append( mergehull3d_menuItem );
	mergehull3d_menuItem->Check( true );

	menubar->Append( operations_menu, wxT("Operations") );

	help_menu = new wxMenu();
	wxMenuItem* about_menuItem;
	about_menuItem = new wxMenuItem( help_menu, ID_ABOUT, wxString( wxT("About") ) + wxT('\t') + wxT("F1"), wxT("Show about dialog"), wxITEM_NORMAL );
	help_menu->Append( about_menuItem );

	menubar->Append( help_menu, wxT("Help") );

	this->SetMenuBar( menubar );

	toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	toolBar->AddTool( ID_NEW_MODEL, wxT("New Model"), wxBitmap( wxT("data/icons/new.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("New Model") );
	toolBar->AddTool( ID_OPEN_MODEL, wxT("Open Model"), wxBitmap( wxT("data/icons/open.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Open Model") );
	toolBar->AddTool( ID_SAVE_MODEL, wxT("Save Model"), wxBitmap( wxT("data/icons/save.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Save model") );
	toolBar->AddSeparator();
	toolBar->AddTool( wxID_FITCAM, wxT("Fit Cam"), wxBitmap( wxT("data/icons/zoom.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Fit Cam") );
	toolBar->Realize();

	wxBoxSizer* bSizer_Global;
	bSizer_Global = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer_Options;
	bSizer_Options = new wxBoxSizer( wxHORIZONTAL );

	options_notebook = new wxNotebook( this, wxID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0 );
	graham_panel = new wxPanel( options_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	show_staticText = new wxStaticText( graham_panel, wxID_ANY, wxT("Show"), wxDefaultPosition, wxDefaultSize, 0 );
	show_staticText->Wrap( -1 );
	bSizer6->Add( show_staticText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline1 = new wxStaticLine( graham_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	centroidGraham_checkBox = new wxCheckBox( graham_panel, wxID_CENTROIDGRAHAM, wxT("Centroid"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( centroidGraham_checkBox, 0, wxALL, 5 );

	pointsGraham_checkBox = new wxCheckBox( graham_panel, wxID_POINTSGRAHAM, wxT("Points"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( pointsGraham_checkBox, 0, wxALL, 5 );

	convexPointsGraham_checkBox = new wxCheckBox( graham_panel, wxID_CONVEXPOINTSGRAHAM, wxT("Convex Hull Points"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( convexPointsGraham_checkBox, 0, wxALL, 5 );

	starEdgesGraham_checkBox = new wxCheckBox( graham_panel, wxID_STAREDGESGRAHAM, wxT("Star Poligon Edges"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( starEdgesGraham_checkBox, 0, wxALL, 5 );

	starPoligonGraham_checkBox = new wxCheckBox( graham_panel, wxID_STARPOLIGONGRAHAM, wxT("Star Poligon"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( starPoligonGraham_checkBox, 0, wxALL, 5 );

	convexEdgesGraham_checkBox = new wxCheckBox( graham_panel, wxID_CONVEXHULLGRAHAM, wxT("Convex Hull"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( convexEdgesGraham_checkBox, 0, wxALL, 5 );

	m_staticline2 = new wxStaticLine( graham_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	grahamClean_toggleBtn = new wxToggleButton( graham_panel, wxID_GRAHAMCLEAN, wxT("Clean"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( grahamClean_toggleBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	grahamExecute_toggleBtn = new wxToggleButton( graham_panel, wxID_GRAHAMEXECUTE, wxT("Execute"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( grahamExecute_toggleBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	graham_panel->SetSizer( bSizer6 );
	graham_panel->Layout();
	bSizer6->Fit( graham_panel );
	options_notebook->AddPage( graham_panel, wxT("Graham"), false );
	delaynay_painel = new wxPanel( options_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxVERTICAL );

	show_staticText2 = new wxStaticText( delaynay_painel, wxID_ANY, wxT("Show"), wxDefaultPosition, wxDefaultSize, 0 );
	show_staticText2->Wrap( -1 );
	bSizer61->Add( show_staticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline11 = new wxStaticLine( delaynay_painel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer61->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );

	pointsDelaunay_checkBox = new wxCheckBox( delaynay_painel, wxID_POINTSDELAUNAY, wxT("Points"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( pointsDelaunay_checkBox, 0, wxALL, 5 );

	trianglesDelaunay_checkBox = new wxCheckBox( delaynay_painel, wxID_TRIANGLESDELAUNAY, wxT("Triangles"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( trianglesDelaunay_checkBox, 0, wxALL, 5 );

	circumferenceDelaunay_checkBox = new wxCheckBox( delaynay_painel, wxID_CIRCUMFERENCEDELAUNAY, wxT("Circumference"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( circumferenceDelaunay_checkBox, 0, wxALL, 5 );

	m_staticline21 = new wxStaticLine( delaynay_painel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer61->Add( m_staticline21, 0, wxEXPAND | wxALL, 5 );

	delaunayClean_toggleBtn = new wxToggleButton( delaynay_painel, wxID_DELAUNAYCLEAN, wxT("Clean"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( delaunayClean_toggleBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	delaunayExecute_toggleBtn = new wxToggleButton( delaynay_painel, wxID_DELAUNAYEXECUTE, wxT("Execute"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( delaunayExecute_toggleBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	delaynay_painel->SetSizer( bSizer61 );
	delaynay_painel->Layout();
	bSizer61->Fit( delaynay_painel );
	options_notebook->AddPage( delaynay_painel, wxT("Delaunay"), false );
	mergehull3d_panel = new wxPanel( options_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer611;
	bSizer611 = new wxBoxSizer( wxVERTICAL );

	show_staticText21 = new wxStaticText( mergehull3d_panel, wxID_ANY, wxT("Show"), wxDefaultPosition, wxDefaultSize, 0 );
	show_staticText21->Wrap( -1 );
	bSizer611->Add( show_staticText21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline111 = new wxStaticLine( mergehull3d_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer611->Add( m_staticline111, 0, wxEXPAND | wxALL, 5 );

	pointsMergeHull3D_checkBox1 = new wxCheckBox( mergehull3d_panel, wxID_POINTSMERGEHULL3D, wxT("Points"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( pointsMergeHull3D_checkBox1, 0, wxALL, 5 );

	facesMergeHull3D_checkBox = new wxCheckBox( mergehull3d_panel, wxID_TRIANGLESMERGEHULL3D, wxT("Faces"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( facesMergeHull3D_checkBox, 0, wxALL, 5 );

	m_staticline211 = new wxStaticLine( mergehull3d_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer611->Add( m_staticline211, 0, wxEXPAND | wxALL, 5 );

	mergehull3dClean_toggleBtn = new wxToggleButton( mergehull3d_panel, wxID_MERGEHULL3DCLEAN, wxT("Clean"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( mergehull3dClean_toggleBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	mergehull3dExecute_toggleBtn = new wxToggleButton( mergehull3d_panel, wxID_MERGEHULL3DEXECUTE, wxT("Execute"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer611->Add( mergehull3dExecute_toggleBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	mergehull3d_panel->SetSizer( bSizer611 );
	mergehull3d_panel->Layout();
	bSizer611->Fit( mergehull3d_panel );
	options_notebook->AddPage( mergehull3d_panel, wxT("Merge Hull 3D"), true );

	bSizer_Options->Add( options_notebook, 1, wxALL|wxEXPAND, 5 );

	bSizer_Global->Add( bSizer_Options, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer_Canvas;
	bSizer_Canvas = new wxBoxSizer( wxVERTICAL );

	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

	canvas = new GLCanvas(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE | wxSUNKEN_BORDER,_T("ID_CUSTOM1"), args);
	bSizer_Canvas->Add( canvas, 1, wxALL|wxEXPAND, 5 );

	bSizer_Global->Add( bSizer_Canvas, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer_Global );
	this->Layout();

	this->Centre( wxBOTH );
}

PrincipalFrame::~PrincipalFrame()
{
}
