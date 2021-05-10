#ifndef IMGLAYER_H
#define IMGLAYER_H

#include <iostream>
#include <string>
#include "Layer.h"
#include "SDL.h"
#include "SDL_image.h"

class ImgLayer : public Layer
{
    public:
        //Constructor, nhan^ properties parameter vao`
        ImgLayer(std::string texID, int x, int y, int w, int h,
                 float scrollRatio = 1.0f, float scaleX = 1.0f, float scaleY = 1.0f);
        void SetScrollRatio(float scrollRatio) { m_ScrollRatio = scrollRatio; }
        void SetOffset(int x, int y) { m_OffsetX = x; m_OffsetY = y;}
        void SetRepeated(bool repeated) { m_Repeated = repeated; }

        virtual void Update();
        virtual void Render();

    private:
        bool m_Repeated;
        float m_ScrollRatio;
        std::string m_TextureID;
        float m_ScaleX;
        float m_ScaleY;
        int m_OffsetX;
        int m_OffsetY;
        int m_ImgWidth;
        int m_ImgHeight;
        SDL_RendererFlip m_Flip;
};

#endif // IMGLAYER_H
