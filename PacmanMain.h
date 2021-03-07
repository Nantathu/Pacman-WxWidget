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
#include <wx/stattext.h>
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
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICBITMAP2;
        static const long ID_STATICBITMAP3;
        static const long ID_STATICBITMAP4;
        //*)

        //(*Declarations(PacmanFrame)
        wxStaticBitmap* PacmanEntity;
        wxStaticBitmap* PlayerHealth1;
        wxStaticBitmap* PlayerHealth2;
        wxStaticBitmap* PlayerHealth3;
        wxStaticText* HighscoreText;
        wxStaticText* StaticText1;
        wxStaticText* TimeText;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PACMANMAIN_H
