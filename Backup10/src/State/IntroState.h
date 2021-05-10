#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <iostream>
#include "SDL.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"

class IntroState : public GameState
{
    public:
        IntroState(){};

        virtual bool IsInit();
        virtual bool IsExit();

        virtual void Update();
        virtual void Render();
        virtual void Events();

        virtual inline std::string GetStateID() const {return m_IntroID;}

    private:

        static const std::string m_IntroID;

};

#endif // INTROSTATE_H
