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
        inline int GetSceneWidth() {return m_SceneWidth; }
        inline int GetSceneHeight() { return m_SceneHeight; }

        inline SDL_Rect GetViewBox() { return m_ViewBox; }
        inline Vector2D GetPosition() { return m_Position; }

        inline void MoveX (float x) {m_Position.X = x;}
        inline void MoveY (float y) {m_Position.Y = y;}

        inline void SetTarget(Point* target) { m_Target = target; }
        inline void SetSceneLimit(int w, int h) { m_SceneWidth = w; m_SceneHeight = h; }

    private:
        Camera();
        static Camera* s_Instance;

        //Phan` Rect ma` man` hinh` hien? thi., trung gian XY cho m_Position
        //Luu. vi. tri' cua? Entity dang xet' toi'
        //Su? dung. pointer vi` phai? lien^ tuc. theo doi~ no', giam? ganh' nang. bo^. nho'
        Point* m_Target;

        //Trung gian cua? m_Position, xu? ly' du~ lieu^. cua? m_Target
        SDL_Rect m_ViewBox;

        //Luu vi. tri' cua? Camera, su? dung. toa. do^. X Y cua? m_ViewBox
        Vector2D m_Position;

        //Kich' thuoc' cua? 1 Map (theo TileLayer, kp SCREEN_WIDTH)
        int m_SceneWidth;
        int m_SceneHeight;
};

#endif // CAMERA_H
