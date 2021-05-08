#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"
#include "Config.h"

#define MAP_FRACTION 1.5 /** LUU Y : THAY DOI TI LE NAY` TRONG TRUONG HOP THAY DOI? CHIEU` DAI/RONG CUA? MAP **/

class Camera
{
    public:

        inline static Camera* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
        }
        void Update();
        inline SDL_Rect GetViewBox() { return m_ViewBox; }
        inline Vector2D GetPosition() { return m_Position; }
        inline void SetTarget(Point* target) {m_Target = target;}


    private:
        Camera()
        {
            m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        }

        SDL_Rect m_ViewBox; //Phan` Rect ma` man` hinh` hien? thi., trung gian XY cho m_Position
        Point* m_Target;
        //Luu. vi. tri' cua? Entity dang xet' toi'
        //Su? dung. pointer vi` phai? lien^ tuc. theo doi~ no', giam? ganh' nang. bo^. nho'
        Vector2D m_Position; //Luu vi. tri' cua? Camera, su? dung. toa. do^. X Y cua? m_ViewBox

        static Camera* s_Instance;
};

#endif // CAMERA_H
