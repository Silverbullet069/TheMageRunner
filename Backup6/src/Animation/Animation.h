#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL.h"
#include <string>

//La` Component, khong^ phai? System, vi` Animation chi? quan? ly' viec^. ve~ va` in cua? nhan^ vat.
class Animation
{
    public:

    //Khong^ truyen` Props vi` cac' Entity khi su dung. Animation da~ duoc. truyen` = Props truoc' do'
    //Sau do, cac Entity truyen` lai. props vao` Animation theo tung` gia' tri. mot^.
        Animation(){}

        void Update();
        void DrawAnime(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animateSpeed);

    private:

        int m_SpriteRow; //So^' hang` trong 1 sprites, set default = 0 (tuc' 1 hang`)
        int m_SpriteCurrentFrame; //Frame index cua? nhan^ vat^. quan? ly' boi? ham` Update
        int m_AnimateSpeed; //Thoi gian ve~ animation giua 2 frame trong 1 action
        int m_FrameCount; //Tong? so frame/1 action cua? nhan^ vat^.
        std::string m_TextureID; //ID dinh. danh ten^ cua? loai. hanh` dong^ cua? Entity
};

#endif // ANIMATION_H
