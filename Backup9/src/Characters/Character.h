#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>

class Character : public GameObject
{
    public:
        //Constructtor cua Character cung~ dung` Properties vi` duoc. ke^' thua` tu GameObject
        Character(Properties* props): GameObject(props) {}

        //Khai bao' lai. cac phuong thuc' abstruct
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void Clean() = 0;

    protected:
        //O? day^ them` 1 truong` ke^' thua` nua~ la` ten^ (khac' voi' m_TextureID)
        std::string m_Name;
};

#endif // CHARACTER_H
