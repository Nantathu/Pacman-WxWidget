/***************************************************************
 * Name:      PacmanMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Jakub Sobieraj (jakub.sobieraj2137@gmail.com)
 * Created:   2021-02-28
 * Copyright: Jakub Sobieraj ()
 * License:
 **************************************************************/

#include "PacmanMain.h"
#include <wx/msgdlg.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>

#define W 32
#define M 178
#define PLAYER 153
#define G 148
#define P1 46
#define P2 175

//(*InternalHeaders(PacmanFrame)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(PacmanFrame)
const long PacmanFrame::ID_STATICBITMAP1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PacmanFrame,wxFrame)
    //(*EventTable(PacmanFrame)
    EVT_KEY_DOWN(PacmanFrame::OnKeyDown)
    //*)
END_EVENT_TABLE()

PacmanFrame::PacmanFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(PacmanFrame)
    Create(parent, wxID_ANY, _("Pacman by Jakub Sobieraj"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(224,184));
    PacmanEntity = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("C:\\Users\\jakub\\Documents\\CodeBlocksProjects\\Pacman\\images\\pacman_open.png"))), wxPoint(0,-8), wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
    //*)

    this->SetFocus();
}

PacmanFrame::~PacmanFrame()
{
    //(*Destroy(PacmanFrame)
    //*)
}

const int MAX_MAP_SIZE = 20;
const int MAP_SIZE_X = 20;
const int MAP_SIZE_Y = 19;

int iMapSizeX = 20;
int iMapSizeY = 20;
int iMapFromFile[MAX_MAP_SIZE][MAX_MAP_SIZE];

int iMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = {
    {M,M,M,M,M,M,M,M,M,W,M,M,M,M,M,M,M,M,M,M},                              //LINE 1
    {M,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P2,M},            //LINE 2
    {M,P1,M,M,M,M,P1,M,M,M,P1,M,M,P1,M,M,M,M,P1,M},                         //LINE 3
    {M,P1,M,M,M,M,P1,M,M,M,P1,M,M,P1,M,M,M,M,P1,M},                         //LINE 4
    {M,P1,M,P1,P1,P1,P1,P1,M,M,P1,M,P1,P1,P1,P1,P1,M,P1,M},                 //LINE 5
    {M,P1,M,P1,M,M,M,P1,M,M,P1,M,P1,M,M,M,P1,M,P1,M},                       //LINE 6
    {M,P1,M,P1,M,M,M,P1,M,M,P1,M,P1,M,M,M,P1,M,P1,M},                       //LINE 7
    {M,P1,M,P1,M,M,P1,P1,P1,P1,P1,P1,P1,P1,M,M,P1,M,P1,M},                  //LINE 8
    {M,P1,M,P1,M,M,P1,M,M,W,M,M,M,P1,M,M,P1,M,P1,M},                        //LINE 9
    {W,P1,P1,P1,P1,P1,P1,M,W,W,W,W,M,P1,P1,P1,P1,P1,P1,W},                  //LINE 10
    {M,P1,M,P1,M,M,P1,M,M,M,M,M,M,P1,M,M,P1,M,P1,M},                        //LINE 11
    {M,P1,M,P1,M,M,P1,P1,P1,P1,P1,P1,P1,P1,M,M,P1,M,P1,M},                  //LINE 12
    {M,P1,M,P1,M,M,M,P1,M,P1,M,M,P1,M,M,M,P1,M,P1,M},                       //LINE 13
    {M,P1,M,P1,M,M,M,P1,M,P1,M,M,P1,M,M,M,P1,M,P1,M},                       //LINE 14
    {M,P1,M,P1,P1,P1,P1,P1,M,P1,M,M,P1,P1,P1,P1,P1,M,P1,M},                 //LINE 15
    {M,P1,M,M,M,M,P1,M,M,P1,M,M,M,P1,M,M,M,M,P1,M},                         //LINE 16
    {M,P1,M,M,M,M,P1,M,M,P1,M,M,M,P1,M,M,M,M,P1,M},                         //LINE 17
    {M,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,P1,M},            //LINE 18
    {M,M,M,M,M,M,M,M,M,M,M,W,M,M,M,M,M,M,M,M}                               //LINE 19
};

void PacmanFrame::OnKeyDown(wxKeyEvent& event)
{
    wxString myString = wxString::Format(wxT("%i"),event.GetKeyCode());
    wxPoint pointCordinate = PacmanEntity->GetPosition();

    if (myString == "314")
        pointCordinate.x -= 5;
    if (myString == "316")
        pointCordinate.x += 5;
    if (myString == "315")
        pointCordinate.y -= 5;
    if (myString == "317")
        pointCordinate.y += 5;

    PacmanEntity->SetPosition(pointCordinate);
}

void PacmanFrame::MapRender()
{
    for (int i = 0; i <= MAP_SIZE_Y - 1; i++)
        {
            for (int j = 0; j <= MAP_SIZE_X - 1; j++)
            {
                iMapFromFile[i][j] = iMap[i][j];
            }// end for j <= MAP_SIZE_X
        }// endfor i <= MAP_SIZE_Y
}

void PacmanFrame::saveMapFile(char* FileName)
{
    fstream file;
    file.open(FileName, ios::out);

    if (file.good() == true)
    {
        file << MAP_SIZE_X << " " << '\n';
        file << MAP_SIZE_Y << " " << '\n';
        for (int i = 0; i < MAP_SIZE_Y; i++)
        {
            for (int j = 0; j < MAP_SIZE_X; j++)
            {
                file << iMap[i][j] << " ";
            }// endfor j < MAP_SIZE_X
            file << '\n';
        }// endfor j < MAP_SIZE_Y
        file.close();
    }
    else {
        cout << "File missing";
    }// endif file.good() == true
}

void PacmanFrame::loadMapFile(char* FileName)
{
    fstream file;
    file.open(FileName, ios::in);

    if (file.good() == false)
    {
        cout << "File doesn't exist" << '\n';
        exit(0);
    }
    else
    {
        file >> iMapSizeX;
        file >> iMapSizeY;
        for (int i = 0; i < iMapSizeY; i++)
        {
            for (int j = 0; j < iMapSizeX; j++)
            {
                file >> iMapFromFile[i][j];
            }// endfor j < iMapSizeX
        }// endfor i < iMapSizeY
    }// endif file.good() == false
}
