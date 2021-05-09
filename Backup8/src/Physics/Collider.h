#ifndef COLLIDER_H
#define COLLIDER_H

#include "Camera.h"

class Collider
{
    public:
        void Set(int x, int y, int w, int h)
        {
            m_Box = {x - m_Buffer.x,
                     y - m_Buffer.y,
                     w - m_Buffer.w,
                     h - m_Buffer.h};
        }

        void Draw() //Ve~ va` cap^. nhat^. Box
        {
            Vector2D cam = Camera::GetInstance()->GetPosition();
    /** GIAI THICH :
    BOX ve~ theo hqc' cua? Entity, ma` Entity duoc. ve~ theo hqc' cua? Camera,
    luc' dau` Box theo hqc' rieng^ cua? no' (hqc giong' TileLayer), nv cang` di,
    Box se~ cang` di chuyen? lech^ khoi? nv neu' nhu? khong^ tinh' toan' lai. Box
    theo  theo hqc' cua? Camera **/

            //Update box
            m_Box.x -= cam.X;
            m_Box.y -= cam.Y;
            SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &m_Box);
        }
        inline SDL_Rect GetBox() const { return m_Box; } //Getter Box
        inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = {x, y, w, h}; } //Setter Buffer


    private:
        SDL_Rect m_Box;
        SDL_Rect m_Buffer;

    /**
    BOX la` gi` ?
    Box la` toa, do^. va` kich' thuoc' cua? 1 khung bao quanh 1 Entity

    BUFFER la` gi`?
    Cac' Entity trong 1 frame thuong` khong^ the? chiem' tron. ca? khung hinh`, ma` se~ co' mang? transparent
    bao xung quanh Entity ay^', Buffer la` margins de? thu nho? phan` dien^. tich' ma` ta se~ check va cham.
    VD : Gia? su? Entity da~ kha' be' roi? lai. co' mang? transparent bao quanh day` thi` phai? thiet' lap^. margins
    cho cai' Box no' thu nho? lai. sao cho khop' voi' hinh` anh? cua Entity

    Doi' voi' nhung buc' anh? ma` Entity nam` gon. trong do' thi` khong^ can^` SetBuffer (de mac dinh. la` 0 0 0 0) **/
};

#endif // COLLIDER_H
