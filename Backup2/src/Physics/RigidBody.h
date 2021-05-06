#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNIT_MASS 1.0f
#define GRAVITY_ACCEL 9.8f

#define FORWARD 1
#define BACKWARD -1

#define UPWARD -1
#define DOWNWARD 1

//Component
class RigidBody
{
    public:
        RigidBody()
        {
            m_Mass = UNIT_MASS;
            m_GravityAccel = GRAVITY_ACCEL;
        }

        //Setter khoi^' luong. va` gia toc^' trong. truong`
        inline void SetMass(float mass) { m_Mass = mass; }
        inline void SetGravityAccel(float gravityAccel) { m_GravityAccel = gravityAccel; }

        //Setter luc. co? ban?
        inline void ApplyForce(Vector2D F) { m_Force = F; }
        inline void ApplyForceXAxis(float Fx) { m_Force.X = Fx; }
        inline void ApplyForceYAxis(float Fy) { m_Force.Y = Fy; }
        inline void UnsetForce() { m_Force = Vector2D(0,0); }

        //Setter luc. ma sat'
        inline void ApplyFriction(Vector2D Fr) { m_Friction = Fr; }
        inline void UnsetFriction() { m_Friction = Vector2D(0,0); }

        //Getter khoi^' luong., vi. tri', van^. toc^' va` gia toc^'
        inline float GetMass() const { return m_Mass; }
        inline Vector2D GetPosition() const { return m_Position; }
        inline Vector2D GetVelocity() const { return m_Velocity; }
        inline Vector2D GetAccel() const { return m_Accel; }


        //Update gia toc^' theo phuong X va` phuong Y
        //Theo Dinh. luat^. 2 Newton : (F + Fr)*(1/m) = a;
        void Update(float dt)
        {
            m_Accel.X = (m_Force.X + m_Friction.X)/m_Mass;
            m_Accel.Y = (m_GravityAccel) + m_Force.Y/m_Mass;
            //Giai thich' : Cong^ thuc' goc^' la (<Trong. luc. cua? nv> + m_Force.Y)/m_Mass
            //Ma` <Trong. luc. cua? nv> = m_GravityAccel*m_Mass;

            m_Velocity = m_Accel*dt;
            //Giai thich' : Theo dong^. luc?. hoc. chat^' diem?, doi voi chuyen? dong. thuong`
            //=> gia toc la vi phan cua van^ toc^' tren 1 dv tg. (a = dv/dt)
            //O? day^, coi nhu chuyen dong cua nhan vat^. trong game la chuyen? dong. deu^`
            //=> gia toc = van toc / thoi gian
            //=> Ta co the tinh van toc = gia toc^' * tg.

            m_Position = m_Velocity*dt;
        }
        /** LUU Y :
        Neu' m_Friction.X = 0.0f, m_Mass = 1.0f
        => m_Accel.X ~ m_Force.X
        Ma` m_Velocity = m_Accel*dt => m_Velocity ~ m_Accel.X ~ m_Force.X
        Ma` m_Position = m_Velocity*dt = m_Accel*(dt^2)
        => m_Position ~ m_Velocity ~ m_Accel.X ~ m_Force.X
        Va` m_Position ~ (dt)^2

        =>Tang do^. dich. pixel tang 100 lan` neu' m_Force.X tang 100 lan`
        =>Giam do^. dich. pixel xuong 100 lan` neu' dt giam 10 lan`

        **/



    private:
        float m_GravityAccel;
        Vector2D m_Force;
        Vector2D m_Friction;

        float m_Mass;
        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Accel;

};

#endif // RIGIDBODY_H
