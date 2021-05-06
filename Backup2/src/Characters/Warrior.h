#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Warrior : public Character
{
    public:
        //Constructtor cua Character cung~ dung` Properties vi` duoc. ke^' thua` tu Character
        //Bat' dau` tu class nay` tien' hanh`
        Warrior(Properties* props);

        //Bat' dau` Implement cac phuong thuc' abstract tu IObject
        virtual void Draw();
        virtual void Update();
        virtual void Clean();

    private:

        /**
        int m_Row; //So^' hang` trong 1 sprites, set default = 0 (tuc' 1 hang`)
        int m_Frame; //Frame index cua? nhan^ vat^. quan? ly' boi? ham` Update
        int m_FrameCount; //Tong? so frame/1 action cua? nhan^ vat^.
        int m_AnimateSpeed; //Thoi gian ve~ animation giua 2 frame trong 1 action
        **/

        //Animation quan? ly' viec^. ve~ va` in nv
        Animation* m_Animation;
        //Rigid quan? ly' yeu^' to^' vat^. ly', dan toi' quan? ly' vi. tri' xy trong m_Transform.
        RigidBody* m_RigidBody;
};

#endif // WARRIOR_H
