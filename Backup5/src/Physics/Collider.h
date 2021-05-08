#ifndef COLLIDER_H
#define COLLIDER_H

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
