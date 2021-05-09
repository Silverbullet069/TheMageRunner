#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "Animation.h"
#include "SDL.h"

//La` Component, khong^ phai? System
class SpriteAnimation : public Animation
{
    public:
    //Khong^ truyen` Props trong constructor vi` cac' Entity khi su dung. Animation, se~ thay? doi? Animation lien^ tuc.
    //vi` the^' phai? tao. 1 ham` SetProps rieng^
        SpriteAnimation(bool repeat = true);

        virtual void Update();
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animateSpeed);
        void DrawAnime(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:

        int m_AnimateSpeed; //Thoi gian ve~ animation giua 2 frame trong 1 action
        int m_SpriteRow; //So^' hang` trong 1 sprites, set default = 0 (tuc' 1 hang`)
        int m_FrameCount; //Tong? so frame/1 action cua? nhan^ vat^.
        std::string m_TextureID; //ID dinh. danh ten^ cua? loai. hanh` dong^ cua? Entity
};

#endif // SPRITEANIMATION_H
