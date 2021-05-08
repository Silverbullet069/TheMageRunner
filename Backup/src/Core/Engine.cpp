
#include "Engine.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

//Vi` s_Instance la` bien' static nen^ phai? duoc. khoi? tao. truoc' khi lam` gi` do'
Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init()
{
    if( SDL_Init(SDL_INIT_VIDEO) < 0  ||  !(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) )
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
                                , SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(m_Window == nullptr)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError);
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: &s", SDL_GetError);
        return false;
    }

    //Load player
    TextureManager::GetInstance()->Load("player_idle","resource/Idle.png");
    TextureManager::GetInstance()->Load("player_run","resource/Move.png");

    //Load background
    TextureManager::GetInstance()->Load("bkg3", "resource/Maps/bkg3.png");
    TextureManager::GetInstance()->Load("bkg2", "resource/Maps/bkg2.png");
    TextureManager::GetInstance()->Load("bkg1", "resource/Maps/bkg1.png");

    //Load map
    if(!MapParser::GetInstance()->Load())
    {
        SDL_Log("Failed to load map!");
        return false;
    }
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    //Init player
    player = new Warrior(new Properties("player_run", 100, 200, 150, 150, 0.8));
    //Properties chi? co' 1 lan` duoc truyen` vao` nen dong` nhan' width_ va height_ cua? cac nhan vat

    //Set camera nhan^. player lam` center Entity
    Camera::GetInstance()->SetTarget(player->GetOrigin());

    return m_IsRunning = true; //if not false, return true and set m_IsRunning = true
}

void Engine::Update()
{
    player->Update();
    m_LevelMap->Update();
    Camera::GetInstance()->Update();
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 125, 127, 180, 255);
    SDL_RenderClear(m_Renderer);

    /** LUU Y : THU' TU RENDER CUA? TUNG` ENTITY **/
    TextureManager::GetInstance()->Draw("bkg3", 0, 0, 3840, 1536, 0.8);
    TextureManager::GetInstance()->Draw("bkg2", 0, 0, 3840, 1536, 1);
    TextureManager::GetInstance()->Draw("bkg1", 0, 0, 3840, 1536, 1);
    m_LevelMap->Render();
    player->Draw();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}
