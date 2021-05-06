#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input()
{
    //Khoi tao. m_KeyStates o? day^ vi` co' the ham` GetKeyDown duoc. goi. khi m_KeyStates chua ton` tai.
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    //m_KeyStates co gia' tri = 1 chuoi~ array gom cac flag cua phim' duoc quy dinh = scancode, chuoi~ nay` co 255 phan` tu
    //Khi SDL_PollEvent ghi nhan co' phim' duoc nhan', scancode cua phim' do' duoc ghi nhan^., flag cua phim' do duoc gan' = 1
    //Neu' nha? ra, scancode cua? phim' do' duoc. ghi nhan^., flag cua phim' do duoc gan' = 0.
    //Truy cap^. vao` flag cua 1 phim', ta chi? can` goi. m_KeyStates[SDL_SCANCODE phim' do'].
}

void Input::Listen()
{
    SDL_Event events;

    while(SDL_PollEvent(&events))
    {
        switch(events.type)
        {
        case SDL_QUIT :
            Engine::GetInstance()->Quit();
            break;

        case SDL_KEYUP :
            KeyUp();
            break;

        case SDL_KEYDOWN :
            KeyDown();
            break;

        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    //Check key truyen` vao` co flag = 1 khong?
    if (m_KeyStates[key] == 1)
    {
        return true;
    }
    return false;
}

void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    // SDL_PollEvent ghi nhan^. Scancode cua phim' vua` nha?
    //Va flag tuong ung' cua? phim' vua` nha? se~ duoc. gan' bang 0 trong array
}

void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    // SDL_PollEvent ghi nhan^. Scancode cua phim' vua` nha?
    //Va flag tuong ung' cua? phim' vua` nhan' se~ duoc. gan' bang 1 trong array
    //m_KeyStates duoc gan' bang array~ SDL co' 255 ptu, 254 ptu = 0, 1 ptu = 1 va` do' la` phim' vua` nhan'
}
