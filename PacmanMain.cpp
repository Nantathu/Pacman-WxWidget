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

constexpr int W = 32;
constexpr int M = 178;
constexpr int P1 = 46;
constexpr int P2 = 175;

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
const long PacmanFrame::ID_STATICTEXT1 = wxNewId();
const long PacmanFrame::ID_STATICTEXT2 = wxNewId();
const long PacmanFrame::ID_STATICTEXT3 = wxNewId();
const long PacmanFrame::ID_STATICBITMAP2 = wxNewId();
const long PacmanFrame::ID_STATICBITMAP3 = wxNewId();
const long PacmanFrame::ID_STATICBITMAP4 = wxNewId();
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
    SetClientSize(wxSize(320,352));
    PacmanEntity = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("C:\\Users\\jakub\\Documents\\GitHub\\Pacman-WxWidget\\images\\pacman_open.png"))), wxPoint(32,32), wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
    HighscoreText = new wxStaticText(this, ID_STATICTEXT1, _("Highscore:"), wxPoint(200,320), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    TimeText = new wxStaticText(this, ID_STATICTEXT2, _("Time:"), wxPoint(200,336), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT3, _("Lifes:"), wxPoint(104,320), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    PlayerHealth1 = new wxStaticBitmap(this, ID_STATICBITMAP2, wxBitmap(wxImage(_T("C:\\Users\\jakub\\Documents\\GitHub\\Pacman-WxWidget\\images\\pacman_open.png"))), wxPoint(135,320), wxDefaultSize, 0, _T("ID_STATICBITMAP2"));
    PlayerHealth2 = new wxStaticBitmap(this, ID_STATICBITMAP3, wxBitmap(wxImage(_T("C:\\Users\\jakub\\Documents\\GitHub\\Pacman-WxWidget\\images\\pacman_open.png"))), wxPoint(155,320), wxDefaultSize, 0, _T("ID_STATICBITMAP3"));
    PlayerHealth3 = new wxStaticBitmap(this, ID_STATICBITMAP4, wxBitmap(wxImage(_T("C:\\Users\\jakub\\Documents\\GitHub\\Pacman-WxWidget\\images\\pacman_open.png"))), wxPoint(175,320), wxDefaultSize, 0, _T("ID_STATICBITMAP4"));
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
const int MAP_SIZE_Y = 20;

int iMapSizeX = 20;
int iMapSizeY = 20;
int iMapFromFile[MAX_MAP_SIZE][MAX_MAP_SIZE];

std::vector<std::vector<int>> mainMap
{
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
    {
        pointCordinate.x -= 16;
        Sleep(10);
        std::cout << "Lewo" << std::endl;
    }
    if (myString == "316")
    {
        pointCordinate.x += 16;
        Sleep(10);
       std::cout << "Prawo" << std::endl;
    }
    if (myString == "315")
    {
        pointCordinate.y -= 16;
        Sleep(10);
        std::cout << "Gora" << std::endl;
    }
    if (myString == "317")
    {
        pointCordinate.y += 16;
        Sleep(10);
        std::cout << "Dol" << std::endl;
    }

    if (myString == "32")
    {
        wxWindowID ID_STATICBITMAP1;
        wxString name = "ID_STATICBITMAP";
        wxString tempName = "";

        int num = 0;

        name << num;
        wxStaticBitmap* mainMap[20][20];

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                tempName = name;
                tempName << i << j;
                mainMap[i][j] = new wxStaticBitmap(
                                                       this,
                                                       wxID_ANY,
                                                       wxBitmap(wxImage(_T("images/wall.png")).Rescale(wxSize(16, 16).GetWidth(), wxSize(16, 16).GetHeight())),
                                                       wxPoint(i * 16, j * 16),
                                                       wxSize(16, 16),
                                                       0
                                                   );
                }
        }

    }

    PacmanEntity->SetPosition(pointCordinate);
    PacmanEntity->Refresh();
}

void PacmanFrame::MapRender()
{
    for (int i = 0; i <= MAP_SIZE_Y; i++)
        {
            for (int j = 0; j <= MAP_SIZE_X; j++)
            {
                iMapFromFile[i][j] = mainMap[i][j];
            }// end for j <= MAP_SIZE_X
        }// endfor i <= MAP_SIZE_Y
}
