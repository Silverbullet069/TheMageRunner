#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 20.0f

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

        bool m_IsJumping; //Flag kiem? tra nv dang nhay?
        bool m_IsGrounded; //Flag kiem? tra nv duoi' mat. dat^'

        float m_JumpTime; //Thoi gian nv NHAY? LEN^
        float m_JumpForce; //Luc. tac' dung. vao` nv de? nv NHAY? LEN^

        Collider* m_Collider; //Collider quan? ly' cac' vung` Box va` Buffer de? su? dung. cho CollisionHandler
        Animation* m_Animation; //Animation quan? ly' viec^. ve~ va` in nv
        RigidBody* m_RigidBody; //Rigid quan? ly' yeu^' to^' vat^. ly', quan? ly' vi. tri' xy trong m_Transform.
        Vector2D m_LastSafePosition;
        //Luu lai. vi. tri' cua? nv truoc' khi nv collide vao` 1 Entity hay Map, moi~ khi collider xay? ra thi` phai?
        //su? dung. lai. vi. tri' cu~, neu' su? dung. vi. tri' moi' de^? chay. tiep^' nv thi` nv se~ bi. ket., trong^
        //rat^' bugging
};

#endif // WARRIOR_H
