
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

//Vi` s_Instance la` bien' static nen^ phai? duoc. khoi? tao. truoc' khi lam` gi` do'
Engine* Engine::s_Instance = nullptr;

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

    if(!MapParser::GetInstance()->Load())
    {
        SDL_Log("Failed to load map!");
        return false;
    }

    //Load map
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    //Load textures, bao gom^` ca? player, enemy, background
    TextureManager::GetInstance()->ParseTextures("resource/textures.tml");

/**
    //Init k su? dung. ObjectFactory
    //Init player
    Warrior* player = new Warrior(new Properties("player_idle", 100, 200, 500, 500, 0.8));
**/

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
    return m_IsRunning = true; //if not false, return true and set m_IsRunning = true
}

void Engine::Update()
{
    //Update game map
    m_LevelMap->Update();

    //Update camera
    Camera::GetInstance()->Update();

    //Update tung` GameObject*
    for(unsigned int i = 0 ; i < m_GameObjects.size(); ++i)
    {
        m_GameObjects[i]->Update();
    }
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    //Render background
    TextureManager::GetInstance()->Draw("bkg3", BKG_MAP_START_X_POS,
                                                BKG_MAP_START_Y_POS,
                                                BKG_MAP_WIDTH,
                                                BKG_MAP_HEIGHT,
                                                BKG_LAYER_LAST_SPEED);

    TextureManager::GetInstance()->Draw("bkg2", BKG_MAP_START_X_POS,
                                                BKG_MAP_START_Y_POS,
                                                BKG_MAP_WIDTH,
                                                BKG_MAP_HEIGHT,
                                                BKG_LAYER_MID_SPEED);

    TextureManager::GetInstance()->Draw("bkg1", BKG_MAP_START_X_POS,
                                                BKG_MAP_START_Y_POS,
                                                BKG_MAP_WIDTH,
                                                BKG_MAP_HEIGHT,
                                                BKG_LAYER_FIRST_SPEED);
    /** LUU Y : THU' TU RENDER CUA? TUNG` BACKGROUND **/

    //Render game map
    m_LevelMap->Render();

    //Render tung` GameObject
    for(unsigned int i = 0 ; i < m_GameObjects.size(); ++i)
    {
        m_GameObjects[i]->Draw();
    }

    //In toan` bo^. moi. thu' ra man` hinh`
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{
    //Clean tung` GameObject*
    for(unsigned int i = 0 ; i < m_GameObjects.size(); ++i)
    {
        m_GameObjects[i]->Clean();
    }

    TextureManager::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}
