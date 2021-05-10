#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

Camera::Camera()
{
    m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Camera::Update()
{
    if(m_Target != nullptr)
    {
        //Chi? bat' dau` chay. Camera theo Entity khi ma` Entity da~ di qua' 1/2 man` hinh` dau` tien^
        m_ViewBox.x = m_Target->X - SCREEN_WIDTH/2;
        m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT/2;

        //Entity van~ dang nam` trong 1/2 man` hinh` dau^` tien^
        if(m_ViewBox.x < 0) m_ViewBox.x = 0;

        if(m_ViewBox.y < 0) m_ViewBox.y = 0;

        //Entity da~ di toi' goc' man` hinh` cuoi' cung`, luc' do' Camera khong^ chay. nua~
        if(m_ViewBox.x > (m_SceneWidth - m_ViewBox.w))   m_ViewBox.x = (m_SceneWidth - m_ViewBox.w);

        if(m_ViewBox.y > (m_SceneHeight - m_ViewBox.h))     m_ViewBox.y = (m_SceneHeight - m_ViewBox.h);

        //Luu vi. tri' cua? Camera duoi' dang. 1 Vector 2 chieu`
        m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    }
}
