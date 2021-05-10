
#include "Engine.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "Config.h"
#include "ObjectFactory.h"
#include "MenuState.h"
#include "PlayState.h"

//Vi` s_Instance la` bien' static nen^ phai? duoc. khoi? tao. truoc' khi lam` gi` do'
Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if( SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Texture filtering chuyen? thanh` duong` thang?
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    if(!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG))
    {
        SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    if(TTF_Init() == -1)
    {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("TheMageRunner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

/**
    //Init map
    if(!MapParser::GetInstance()->Parse("level1", "resource/maps/map01.tmx"))
    {
        SDL_Log("Failed to load and parse map!");
        return false;
    }

    //Load map
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    //Load textures, bao gom^` ca? player, enemy, background
    TextureManager::GetInstance()->Parse("resource/textures.tml");

    //Khong^ su? dung. : Init k su? dung. ObjectFactory
    //Init player
    //Warrior* player = new Warrior(new Properties("player_idle", 100, 200, 500, 500, 0.8));

    //Init co' su? dung. ObjectFactory
    Properties* props = new Properties("player_idle", 100, 200, 500, 500, 0.8);
    GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);

    //Init enemy
    Enemy* enemy = new Enemy(new Properties("slime_jump", 1000, 200, 250, 250, 0.3));

    //Init vector GameObject*
    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);

    //Set camera nhan^. player lam` center Entity
    Camera::GetInstance()->SetTarget(player->GetOrigin());
**/

    GameStateManager::GetInstance()->PushState(new MenuState());

    return m_IsRunning = true; //if not false, return true and set m_IsRunning = true
}

void Engine::Update()
{
    for(auto gamestate : GameStateManager::GetInstance()->GetGameStates())
        gamestate->Update();
}

void Engine::Render()
{
    for(auto gamestate : GameStateManager::GetInstance()->GetGameStates())
        gamestate->Render();
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
    for(auto gamestate : GameStateManager::GetInstance()->GetGameStates())
        gamestate->Events();
}

bool Engine::Clean()
{
    for(auto gamestate : GameStateManager::GetInstance()->GetGameStates())
        gamestate->IsExit();

    MapParser::GetInstance()->Clean();
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
