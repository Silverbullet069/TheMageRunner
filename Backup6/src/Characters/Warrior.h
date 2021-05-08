#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_FORCE 20.0f
#define JUMP_TIME 15.0f

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

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
        void AnimationState();

    private:
        bool m_IsRunning; //Flag kiem? tra nv dang chay.
        bool m_IsJumping; //Flag kiem? tra nv dang nhay?
        bool m_IsFalling; //Flag kiem? tra nv dang roi?
        bool m_IsGrounded; //Flag kiem? tra nv dang dung' tren^ mat. dat^'
        bool m_IsAttacking1; //Flag kiem? tra nv dang tan^' cong^ loai. 1
        bool m_IsAttacking2; //Flag kiem? tra nv dang tan^' cong^ loai. 2
        bool m_IsCrouching; //Flag kiem? tra nv dang cui'

        float m_JumpTime; //Thoi gian nv NHAY? LEN^
        float m_JumpForce; //Luc. tac' dung. vao` nv de? nv NHAY? LEN^
        float m_AttackTime1; //Thoi gian dung` de? chay. Animation tan^' cong^ loai. 1 cua? nv
        float m_AttackTime2; //Thoi gian dung` de? chay. Animation tan^' cong^ loai. 2 cua? nv

        Collider* m_Collider; //Collider quan? ly' cac' vung` Box va` Buffer de? su? dung. cho CollisionHandler
        Animation* m_Animation; //Animation quan? ly' viec^. ve~ va` in nv
        RigidBody* m_RigidBody; //Rigid quan? ly' yeu^' to^' vat^. ly', quan? ly' vi. tri' xy trong m_Transform.
        Vector2D m_LastSafePosition;
        //Luu lai. vi. tri' cua? nv truoc' khi nv collide vao` 1 Entity hay Map, moi~ khi collider xay? ra thi` phai?
        //su? dung. lai. vi. tri' cu~, neu' su? dung. vi. tri' moi' de^? chay. tiep^' nv thi` nv se~ bi. ket., trong^
        //rat^' bugging
};

#endif // WARRIOR_H
