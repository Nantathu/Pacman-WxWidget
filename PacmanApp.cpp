/***************************************************************
 * Name:      PacmanApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Jakub Sobieraj (jakub.sobieraj2137@gmail.com)
 * Created:   2021-02-28
 * Copyright: Jakub Sobieraj ()
 * License:
 **************************************************************/

#include "PacmanApp.h"

//(*AppHeaders
#include "PacmanMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PacmanApp);

bool PacmanApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PacmanFrame* Frame = new PacmanFrame(0);
    	Frame->Show();
    	Frame->SetIcon(wxICON(aaaa));
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
