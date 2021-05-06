#include "TextureManager.h"
#include "Engine.h"

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

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect desRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*row, width, height};
    SDL_Rect desRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
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



