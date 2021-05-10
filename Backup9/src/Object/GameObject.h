#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include "Point.h"

struct Properties
{
public:
    //Construct Properties, thuong` duoc goi khi khoi tao class non-abstruct ke^' thua` GameObject nhu Warrior, Mage
    Properties(std::string textureID, float x, float y, int width, int height, float deltaTime, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        TextureID = textureID;
        X = x;
        Y = y;
        Width = width;
        Height = height;
        DeltaTime = deltaTime;
        Flip = flip;
    }
public :
    std::string TextureID; //Ten^ hoac. ma~ so^'
    float X; //Toa. do^. X cua? goc' tren^ trai' cua? tung` frame trong Sprite
    float Y; //Toa. do^. Y cua? goc' tren^ trai' cua? tung` frame trong Sprite
    int Width; //Chieu` dai` 1 frame
    int Height; //Chieu` rong. 1 frame
    float DeltaTime; //Thoi` gian cho cac' component Physics
    SDL_RendererFlip Flip; //Flag xoay
};

//Truoc khi tao. GameObject, tao. Properties truoc'
class GameObject : public IObject
{
    //Tat ca cac class non-abstruct ke' thua` class nay` chay. contructor tu ham` nay`
    public:
        GameObject(Properties* props) :
            m_Width(props->Width),
            m_Height(props->Height),
            m_TextureID(props->TextureID),
            m_DeltaTime(props->DeltaTime),
            m_Flip(props->Flip)
        {
            //Dat. m_Transform trong nay` vi Properties khong^ quan? ly' bien' nay`
            //Nhung toa. do. X, Y thi lai duoc Properties quan? ly'
            //Bien' nay` co' the? hieu? la` 1 point
            m_Transform = new Transform(props->X, props->Y);

            float px = props->X + (props->Width)/2;
            float py = props->Y + (props->Height)/2;
            m_Origin = new Point(px, py);

        }

       //Khai bao' lai. cac phuong thuc' abstruct
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void Clean() = 0;

        inline Point* GetOrigin() {return m_Origin;}

    protected:

        int m_Width; //Chieu` dai` cua? Entity
        int m_Height; //Chieu rong^. cua? Entity
        std::string m_TextureID; //ID (ten^ hoac. ma~ so^') cua Entity, dung` de dinh. danh tren m_TextureMap
        float m_DeltaTime; //Thoi` gian cho cac' component Physics
        SDL_RendererFlip m_Flip; //Trang. thai' xoay cua Entity, set default = SDL_FLIP_NONE

        Transform* m_Transform; //1 point, quan? ly' toa do X, Y cua GOC TREN^ TRAI' cua? Entity, phuc. vu. Physics, hay Rigidbody
        Point* m_Origin; //1 point, quan? ly' toa. do^. X, Y cua? TAM^ cua? Entity, phuc. vu. cho Camera


};

#endif // GAMEOBJECT_H
