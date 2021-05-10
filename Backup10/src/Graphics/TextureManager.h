#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SDL.h"
#include "SDL_ttf.h"
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

        bool Load(std::string id, std::string file_name); //Khoi tao. texture cua Entity duoc. quan? ly' boi? m_TextureMap
        bool Parse(std::string source); //Load cac' texture anh? cua cac' Entity vao` m_TextureMap
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

        bool LoadFont(std::string source); //Load cac' TTF_Font* vao` m_FontMap
        //Khoi? tao. texture dang. chu~ duoc. quan? ly' boi? m_TextureMap
        bool LoadTxt(std::string id, TTF_Font* font, std::string content, SDL_Color color);
        bool ParseConvo(std::string source); //Load cac' texture chu~ vao` m_TextureMap

    private:
        TextureManager(){};
        static TextureManager* s_Instance; //Doi' tuong. cua TextureManager
        std::map<std::string, TTF_Font*> m_FontMap; //Cac' font cua? texture dang. chu~
        std::map<std::string, SDL_Texture*> m_TextureMap; //Cac hinh` anh? cua object duoc quan? ly' bang m_TextureID
};

#endif // TEXTUREMANAGER_H
