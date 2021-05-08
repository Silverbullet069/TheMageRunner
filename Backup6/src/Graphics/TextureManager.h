#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SDL.h"
#include "tinyxml.h"
#include <string>
#include <map>

class TextureManager //System
{
    //Ham` quan? ly' doi' tuong?. cua? TextureManager(Khoi tao va lay' ra su dung.)
    public:
        static TextureManager* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();
        }

        //Khoi tao. texture cua Entity duoc. quan? ly' boi? m_TextureMap va` m_TextureID
        bool Load(std::string id, std::string file_name);

        bool ParseTextures(std::string source);
        //Khong can^` dung` toi' texture cua object nao` thi` xoa' di va free bo^. nho'
        void Drop(std::string id);
        //Xoa' het' tat' ca? cac texture con` lai. trong m_TextureMap
        void Clean();

        //Ve~ anh? tinh~
        void Draw(std::string id, int x, int y, int width, int height, float speedRatio, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //Ve~ anh? dong^. (animation)
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //Ve~ tile trong 1 TileSet
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        TextureManager(){};

        std::map<std::string, SDL_Texture*> m_TextureMap; //Cac hinh` anh? cua object duoc quan? ly' bang m_TextureID
        static TextureManager* s_Instance; //Doi' tuong. cua TextureManager
};

#endif // TEXTUREMANAGER_H
