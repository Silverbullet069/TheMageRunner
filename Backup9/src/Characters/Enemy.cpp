#include "Enemy.h"
#include "Config.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"

static Registrar<Enemy> registrar("SLIME");

Enemy::Enemy(Properties* props) : Character(props)
{
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravityAccel(ENEMY_RIGID_BODY_GRAVITY_ACCEL);

    m_Collider = new Collider();

    m_Animation = new SeqAnimation(false); //Set flag m_Repeat = false
    m_Animation->Parse("resource/slime.tml");
    m_Animation->SetCurrentSeq("slime_jump");
}

void Enemy::Draw()
{
    m_Animation->DrawAnime(m_Transform->X, m_Transform->Y, m_Flip);
}

void Enemy::Update()
{
    float dt = m_DeltaTime;

    /** XU LY' DI CHUYEN THEO PHUONG X **/

    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->GetPosition().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 250, 250);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }

    /** XU LY' DI CHUYEN THEO PHUONG Y **/

    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->GetPosition().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 250, 250);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox()))
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }

    //Update animation
    m_Animation->Update();

    if(m_Animation->IsEnded() == true)
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentSeq("slime_idle");
    }


}

void Enemy::Clean()
{
    //
}
