#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

//System
class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);

    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates; // Luu flag Scancode cua? phim' vua` bam',
        static Input* s_Instance;

};

#endif // INPUT_H
