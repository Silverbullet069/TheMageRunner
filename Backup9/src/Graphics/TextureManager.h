#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SDL.h"
#include "tinyxml.h"
#include <string>
#include <map>

class TextureManager
{
    public:
        static TextureManager* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();
        }

        bool Load(std::string id, std::string file_name); //Khoi tao. texture cua Entity duoc. quan? ly' boi? m_TextureMap va` m_TextureID
        bool Parse(std::string source); //Load toan` bo^. texture cua Entity duoc. dinh. danh' boi? m_TextureMap va` m_TextureID trong 1 file XML
        void Erase(std::string id); //Khong can^` dung` toi' texture cua object nao` thi` xoa' di va free bo^. nho'
        void Clean(); //Xoa' het' tat' ca? cac texture con` lai. trong m_TextureMap

        void Draw(std::string id, int x, int y, int w, int h,
                  SDL_RendererFlip flip = SDL_FLIP_NONE,    //Ve~ anh? tinh~
                  float speedRatio = 1.0f, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f);


        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame,
                       SDL_RendererFlip flip = SDL_FLIP_NONE, //Ve~ anh? dong^. (animation)
                       float speedRatio = 1.0f, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f);


        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame,
                      float speedRatio = 1.0f); //Ve~ tile trong 1 TileSet

    private:
        TextureManager(){};
        static TextureManager* s_Instance; //Doi' tuong. cua TextureManager

        std::map<std::string, SDL_Texture*> m_TextureMap; //Cac hinh` anh? cua object duoc quan? ly' bang m_TextureID
};

#endif // TEXTUREMANAGER_H
