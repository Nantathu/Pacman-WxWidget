/***************************************************************
 * Name:      PacmanMain.h
 * Purpose:   Defines Application Frame
 * Author:    Jakub Sobieraj (jakub.sobieraj2137@gmail.com)
 * Created:   2021-02-28
 * Copyright: Jakub Sobieraj ()
 * License:
 **************************************************************/

#ifndef PACMANMAIN_H
#define PACMANMAIN_H

//(*Headers(PacmanFrame)
#include <wx/frame.h>
#include <wx/statbmp.h>
//*)

class PacmanFrame: public wxFrame
{
    public:

        PacmanFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PacmanFrame();

    private:

        //(*Handlers(PacmanFrame)
        void OnKeyDown(wxKeyEvent& event);
        void MapRender();
        void saveMapFile(char* FileName);
        void loadMapFile(char* FileName);
        //*)

        //(*Identifiers(PacmanFrame)
        static const long ID_STATICBITMAP1;
        //*)

        //(*Declarations(PacmanFrame)
        wxStaticBitmap* PacmanEntity;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PACMANMAIN_H
