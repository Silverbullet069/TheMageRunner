#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL.h"
#include <string>

//La` Component, khong^ phai? System, vi` Animation chi? quan? ly' viec^. ve~ va` in cua? nhan^ vat.
class Animation
{
    public:

    //Khong^ truyen` Props vi` cac' Entity khi su dung. Animation da~ duoc. truyen` = Props truoc' do'
    //Sau do, cac Entity truyen` lai. props vao` Animation theo tung` gia' tri. 1.
        Animation(){}

        void Update();
        void DrawAnime(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animateSpeed,
                      SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:

        int m_SpriteRow;
        int m_SpriteCurrentFrame;
        int m_AnimateSpeed;
        int m_FrameCount;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
