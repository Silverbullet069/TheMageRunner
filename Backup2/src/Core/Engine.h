
#ifndef ENGINE_H_
#define ENGINE_H_

#include "SDL.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1536

class Engine //System
{
public:
    //Ham` quan? ly' doi' tuong?. cua? Engine(Khoi tao va lay' ra su dung.)
    inline static Engine* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
    }

    bool Init(); //Khoi tao. tat^' ca? cac' cong^ cu. trong Engine, bao gom^` TextureManager
    bool Clean(); //Giai? phong' bo^ nho' tat^' ca? cac' cong^ cu. trong Engine
    void Quit();  //Set lai. flag m_IsRunning = false

    void Update(); //Update tat^' ca? cac' gia' tri. dynamic (vd nhu? frame cua nv, hinh` anh? background,...)
    void Render(); //In hinh` anh? tuong ung' voi cac' gia' tri. dynamic
    void Events(); //Ham` nhan. input tu` chuot va` ban` phim'

    inline bool IsRunning() {return m_IsRunning;} //Set flag Engine dang su? dung.

    inline SDL_Renderer* GetRenderer() { return m_Renderer; }
    //Lay' Renderer trong Engine
    //NOTE : TRONG 1 GAME CHI? SU? DUNG. 1 RENDERER LA` CUA? ENGINE.

private:
    Engine(){}; //Constructor

    bool m_IsRunning; //Flag Engine hoat. dong^.
    SDL_Window* m_Window; //Window
    SDL_Renderer* m_Renderer; //Renderer

    //Doi' tuong. trong class Engine
    //khai bao' static de^? su? dung. truc. tiep', khong^ can` phai? tao. object
    static Engine* s_Instance;
};

#endif // ENGINE_H_
