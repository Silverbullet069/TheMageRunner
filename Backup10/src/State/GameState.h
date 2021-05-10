#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SDL.h"
#include <string>

//Interface
class GameState
{
    public:
        virtual bool IsInit() = 0; //Init tat' ca? cac' component ben^ trong 1 state
        virtual bool IsExit() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;

        virtual void Events() = 0;

        virtual inline std::string GetStateID() const = 0;

    protected:
        SDL_Renderer* m_Context;
};

#endif // GAMESTATE_H
