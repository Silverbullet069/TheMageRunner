#include "ImgLayer.h"
#include "TextureManager.h"
#include "Config.h"

ImgLayer::ImgLayer(std::string texID, int x, int y, int w, int h,
                   float scrollRatio, float scaleX, float scaleY) :
m_TextureID(texID), m_OffsetX(x), m_OffsetY(y), m_ImgWidth(w), m_ImgHeight(h), m_ScrollRatio(scrollRatio), m_ScaleX(scaleX), m_ScaleY(scaleY)

{
    m_Repeated = true;
}

void ImgLayer::Render()
{
    TextureManager::GetInstance()->Draw(m_TextureID, m_OffsetX, m_OffsetY, m_ImgWidth, m_ImgHeight,
                                        m_Flip, m_ScrollRatio, m_ScaleX, m_ScaleY);

}

void ImgLayer::Update()
{
    //
}
