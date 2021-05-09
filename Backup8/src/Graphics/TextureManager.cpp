#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"

TextureManager* TextureManager::s_Instance = nullptr; //

bool TextureManager::Load(std::string id, std::string file_name)
{
    SDL_Surface* loaded_surface = IMG_Load(file_name.c_str());
    if(loaded_surface == nullptr)
    {
        SDL_Log("Failed to load surface: %s, %s", file_name.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), loaded_surface);
    if(new_texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = new_texture;

    return true;
}

bool TextureManager::ParseTextures(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        std::cerr<< "Failed to load: " << source << std::endl;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id, src);
        }
    }
    std::cout<< "Texture parse success!" << std::endl;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float speedRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};

    Vector2D cam = Camera::GetInstance()->GetPosition()*speedRatio;
    //gioi' han. RATIO_SPEED_BKG < 1 de? bkg luon^ scroll cham. hon? entity dang duoc center
    SDL_Rect desRect = {x - cam.X, y - cam.Y, width, height};
    //SDL_Rect desRect = {x, y, width, height};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*row, width, height};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect desRect = {x - cam.X, y - cam.Y, width, height}; /** GIAI THICH = GIAO' CU. TRUC. QUAN **/
    //SDL_Rect desRect = {x, y, width, height};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int col, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize*col, tileSize*row, tileSize, tileSize};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect desRect = {x - cam.X, y - cam.Y, tileSize, tileSize}; /** GIAI THICH = GIAO' CU. TRUC. QUAN **/
    //SDL_Rect desRect = {x, y, tileSize, tileSize};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    //Map can't use int index
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin() ; it != m_TextureMap.end() ; ++it)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();

    SDL_Log("Texture map clean!");
}



