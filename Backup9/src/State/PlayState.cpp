#include "PlayState.h"
#include "MenuState.h"

const std::string PlayState::m_PlayID = "PLAY";

bool PlayState::IsInit()
{
    m_Context = Engine::GetInstance()->GetRenderer();

    //Init map
    if(!MapParser::GetInstance()->Parse("level1", "resource/maps/map01.tmx"))
    {
        SDL_Log("Failed to load and parse map!");
        return false;
    }

    //Load map by using MapParser
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    //Load textures, bao gom^` ca? player, enemy, background,...
    TextureManager::GetInstance()->Parse("resource/textures.tml");

    //Load TileLayer dung` de^? check va. cham`, lay^' 3 thong^ so^' va` set check va cham. voi' TileMatrix trong TileLayer
    TileLayer* collisionlayer = (TileLayer*)m_LevelMap->GetLayers().front();
    int tilesize = collisionlayer->GetTileSize();
    int width = collisionlayer->GetWidth()*tilesize;
    int height = collisionlayer->GetHeight()*tilesize;
    CollisionHandler::GetInstance()->SetCollisionMap(collisionlayer->GetTileMatrix(), tilesize);

    //Init background
    m_ParallexBkg.push_back(new ImgLayer("bkg3", 0, 0, 3840, 1536, 0.6));
    m_ParallexBkg.push_back(new ImgLayer("bkg2", 0, 0, 3840, 1536, 0.7));
    m_ParallexBkg.push_back(new ImgLayer("bkg1", 0, 0, 3840, 1536, 0.8));

    //Init player co' su? dung. ObjectFactory
    Properties* props = new Properties("player_idle", 100, 200, 500, 500, 0.8);
    GameObject* player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);

    //Init enemy
    Enemy* enemy = new Enemy(new Properties("slime_jump", 1000, 200, 250, 250, 0.3));

    //Push cac' object vua` init vao` vector GameObject*
    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);

    //Set camera nhan^. player lam` center Entity
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    Camera::GetInstance()->SetSceneLimit(3840, 1536);

    SDL_Log("Play initialize!\n");
    return true;
}

void PlayState::Render()
{
    SDL_SetRenderDrawColor(m_Context, 48, 96, 128, 255);
    SDL_RenderClear(m_Context);

    for(auto imglayer : m_ParallexBkg)
        imglayer->Render();

    m_LevelMap->Render();

    for (auto gameobj : m_GameObjects)
        gameobj->Draw();

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();
    SDL_RenderCopy(m_Context, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Context);
}

void PlayState::Update()
{
    //Update game map
    m_LevelMap->Update();

    //Update camera
    Camera::GetInstance()->Update();

    //Update tung` GameObject*
    for(auto gameobj : m_GameObjects)
        gameobj->Update();
}

void PlayState::Events()
{
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
    {
        GameStateManager::GetInstance()->ChangeState(new MenuState());
    }
}

bool PlayState::IsExit()
{
    m_LevelMap->Clean();
    delete m_LevelMap;

    for(auto gameobj : m_GameObjects)
    {
        gameobj->Clean();
        delete gameobj;
    }
    m_GameObjects.clear();

    for(auto imgobj : m_ParallexBkg)
    {
        delete imgobj;
    }
    m_ParallexBkg.clear();

    SDL_Log("Play exit!\n");

    return true;
}

void PlayState::OpenMenu()
{
    //Engine::GetInstance()->ChangeState(new Menu());
}

void PlayState::PauseGame()
{
    //
}


