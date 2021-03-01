/***************************************************************
 * Name:      PacmanApp.h
 * Purpose:   Defines Application Class
 * Author:    Jakub Sobieraj (jakub.sobieraj2137@gmail.com)
 * Created:   2021-02-28
 * Copyright: Jakub Sobieraj ()
 * License:
 **************************************************************/

#ifndef PACMANAPP_H
#define PACMANAPP_H

#include <wx/app.h>

class PacmanApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // PACMANAPP_H
