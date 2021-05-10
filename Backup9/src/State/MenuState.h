#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <iostream>
#include "SDL.h"
#include "GameState.h"

class MenuState : public GameState
{
    public:
        MenuState(){};

        virtual bool IsInit();
        virtual bool IsExit();

        virtual void Update();
        virtual void Render();

        virtual void Events();

        virtual inline std::string GetStateID() const {return m_MenuID;}

    private:

        static const std::string m_MenuID;

        //Cac' UI trong 1 MENU
        static void StartGame();
        static void Settings();
        static void Editor();
        static void Quit();
};

#endif // MENUSTATE_H
