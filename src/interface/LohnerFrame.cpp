#include <wx/filedlg.h>
#include <wx/msgdlg.h>

#include "LohnerFrame.h"

#include "../ResourceManager.h"


LohnerFrame::LohnerFrame( wxWindow* parent )
:
PrincipalFrame( parent )
{

}

void LohnerFrame::init()
{
    canvas->init();
}

void LohnerFrame::newModel( wxCommandEvent& event )
{
	// TODO: Implement newModel
}

void LohnerFrame::openModel( wxCommandEvent& event )
{

    // TODO: Implement openModel
    static const wxChar *FILETYPES  = _("TXT files (*.txt)|*.txt|"
                                        "All files (*.*)|*.*");

    wxFileDialog openFileDialog(this, _("Select a file"), _(""), _(""), FILETYPES, wxFD_CHANGE_DIR );
    if(openFileDialog.ShowModal() == wxID_OK)
    {
        wxString fileName = openFileDialog.GetPath();
        if(!fileName)
        {
            // TODO:
            // Choose more informative message. This is just a placeholder.
            wxMessageBox( _("Could not open file"), _("File error"), wxOK | wxICON_ERROR );
            return;
        }

        bool success = canvas->manager.loadFromFile( std::string( fileName.ToAscii() ) );

        if ( !success )
        {
            wxMessageBox( _("Could not open file: Invalid format."),_("File error"), wxOK | wxICON_ERROR );
            return;
        }

//canvas->manager.loadFromFile( std::string( "" ) );

        switch(options_notebook->GetSelection())
        {
            case 0:
                centroidGraham_checkBox->SetValue(false);
                pointsGraham_checkBox->SetValue(false);
                convexPointsGraham_checkBox->SetValue(false);
                starEdgesGraham_checkBox->SetValue(false);
                starPoligonGraham_checkBox->SetValue(false);
                convexEdgesGraham_checkBox->SetValue(false);
            break;
            case 1:
                pointsDelaunay_checkBox->SetValue(false);
                trianglesDelaunay_checkBox->SetValue(false);
                circumferenceDelaunay_checkBox->SetValue(false);
            break;
            case 2:
                pointsMergeHull3D_checkBox1->SetValue(true);
                facesMergeHull3D_checkBox->SetValue(true);
                edgesMergeHull3D_checkBox->SetValue(true);
            break;
        }

        canvas->fitCam();

        Refresh();
    }
}

void LohnerFrame::saveModel( wxCommandEvent& event )
{
    static const wxChar *FILETYPES  = _("TXT files (*.txt)|*.txt|"
                                    "All files (*.*)|*.*");

    wxFileDialog saveSceneDialog(this, _("Save Scene"), _(""), _(""), FILETYPES, wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR );
    if(saveSceneDialog.ShowModal() == wxID_OK )
    {
        wxString fileName = saveSceneDialog.GetPath();

        canvas->manager.saveToFile( std::string( fileName.ToAscii() ) );
    }
}

void LohnerFrame::fitCam( wxCommandEvent& event )
{
    canvas->fitCam();
    Refresh();
}

void LohnerFrame::quit( wxCommandEvent& event )
{
	Destroy();
}

void LohnerFrame::setGraham( wxCommandEvent& event )
{
    canvas->manager.setType(0);

    options_notebook->SetSelection( 0 );

    Refresh();
}

void LohnerFrame::about( wxCommandEvent& event )
{
    wxString text = _("");
    text << _("GC Toolkit\n\n")
        << _("By Daniel N Teixeira\n\n");

	wxMessageDialog dialog(this, text, _("About"));
    dialog.ShowModal();
}

void LohnerFrame::setPage( wxNotebookEvent& event )
{
    options_notebook->SetSelection( options_notebook->GetSelection() );

    switch(options_notebook->GetSelection())
    {
        case 0:
            canvas->manager.setType(0);
            operations_menu->FindItemByPosition(0)->Check( true );
        break;
        case 1:
            canvas->manager.setType(1);
            operations_menu->FindItemByPosition(1)->Check( true );
        break;
        case 2:
            canvas->manager.setType(2);
            operations_menu->FindItemByPosition(2)->Check( true );
        break;
    }

    Refresh();

}

void LohnerFrame::setCentroid( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->setCentroid();
        Refresh();
    }
}

void LohnerFrame::setPoints( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->setPoint();
        Refresh();
    }
}

void LohnerFrame::setConvexPoints( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->setConvexPoint();
        Refresh();
    }
}

void LohnerFrame::LohnerFrame::setStarEdges( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->setStarEdge();
        Refresh();
    }
}

void LohnerFrame::setStarPoligon( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->setStarPoligon();
        Refresh();
    }
}

void LohnerFrame::setConvexHull( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->setConvexHull();
        Refresh();
    }
}

void LohnerFrame::clearGraham( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->clear();
        delete canvas->manager.graham;
        canvas->manager.graham = NULL;
        Refresh();
    }
}

void LohnerFrame::executeGraham( wxCommandEvent& event )
{
    if(canvas->manager.graham != NULL)
    {
        canvas->manager.graham->execute();
        Refresh();
    }
    else
    {
        this->openModel(event);
        this->executeGraham(event);
    }
}

void LohnerFrame::setDelaunay( wxCommandEvent& event )
{
    canvas->manager.setType(1);

    options_notebook->SetSelection( 1 );

    Refresh();
}

void LohnerFrame::setPointsDelaunay( wxCommandEvent& event )
{
    if(canvas->manager.delaunay != NULL)
    {
        canvas->manager.delaunay->setPoint();
        Refresh();
    }

}

void LohnerFrame::setTriangles( wxCommandEvent& event )
{
    if(canvas->manager.delaunay != NULL)
    {
        canvas->manager.delaunay->setTriangles();
        Refresh();
    }
}

void LohnerFrame::setCircumference( wxCommandEvent& event )
{
    if(canvas->manager.delaunay != NULL)
    {
        canvas->manager.delaunay->setCircumference();
        Refresh();
    }
}

void LohnerFrame::clearDelaunay( wxCommandEvent& event )
{
    if(canvas->manager.delaunay != NULL)
    {
        canvas->manager.delaunay->clear();
        delete canvas->manager.delaunay;
        canvas->manager.delaunay = NULL;
        Refresh();
    }
}

void LohnerFrame::executeDelaunay( wxCommandEvent& event )
{
    if(canvas->manager.delaunay != NULL)
    {
        canvas->manager.delaunay->execute();
        Refresh();
    }
    else
    {
        this->openModel(event);
        this->executeDelaunay(event);
    }
}

void LohnerFrame::setMergeHull3D( wxCommandEvent& event )
{
    canvas->manager.setType(2);

    options_notebook->SetSelection( 2 );

    Refresh();
}

void LohnerFrame::setPointsMergeHull3d( wxCommandEvent& event )
{
    if(canvas->manager.mergehull3d != NULL)
    {
        canvas->manager.mergehull3d->setPoint();
        Refresh();
    }
}

void LohnerFrame::setFacesMergeHull3d( wxCommandEvent& event )
{
    if(canvas->manager.mergehull3d != NULL)
    {
        canvas->manager.mergehull3d->setFace();
        Refresh();
    }
}

void LohnerFrame::setEdgesMergeHull3d( wxCommandEvent& event )
{
    if(canvas->manager.mergehull3d != NULL)
    {
        canvas->manager.mergehull3d->setEdge();
        Refresh();
    }
}

void LohnerFrame::clearMergeHull3D( wxCommandEvent& event )
{
    if(canvas->manager.mergehull3d != NULL)
    {
        canvas->manager.mergehull3d->clear();
        delete canvas->manager.mergehull3d;
        canvas->manager.mergehull3d = NULL;

        Refresh();
    }
}

void LohnerFrame::executeMergeHull3D( wxCommandEvent& event )
{
    if(canvas->manager.mergehull3d != NULL)
    {
        canvas->manager.mergehull3d->execute();
        Refresh();
    }
}
