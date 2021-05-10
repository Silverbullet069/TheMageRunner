
#include "SpriteAnimation.h"
#include "TextureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat){}

void SpriteAnimation::Update()
{
    m_CurrentFrame = (SDL_GetTicks()/m_AnimateSpeed)%m_FrameCount; //m_CurrentFrame cua? Animation
}

void SpriteAnimation::DrawAnime(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight,
                                             m_SpriteRow, m_CurrentFrame, flip); //m_CurrentFrame cua? Animation
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int animateSpeed)
{
    m_AnimateSpeed = animateSpeed;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
}
