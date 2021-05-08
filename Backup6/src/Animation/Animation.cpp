#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
    m_SpriteCurrentFrame = (SDL_GetTicks()/m_AnimateSpeed)%m_FrameCount;
}

void Animation::DrawAnime(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight,
                                             m_SpriteRow, m_SpriteCurrentFrame, flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animateSpeed)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimateSpeed = animateSpeed;
}
