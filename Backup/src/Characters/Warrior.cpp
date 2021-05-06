#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    /**
    m_Row = 0; //Set sprite chi? co 1 row
    m_FrameCount = 8; //trong 1 row co' 8 frame
    m_AnimateSpeed = 50; //tg 2 frame cach' nhau
    **/
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 8, 100);
    //m_TextureID trong GameObject, da duoc. khoi? tao. trong Engine::Init()

    m_RigidBody = new RigidBody();
}

void Warrior::Draw()
{
    /**
    TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
    //m_TextureID, m_Transform trong GameObject
    //m_Width, mHeight duoc. khoi? tao. trong constructor nhap. = Properties
    //m_Row trong class nay`, da~ duoc khoi? tao truoc'
    //m_Frame trong class nay`, moi~ khi ham` Update chay. thi` m_frame tang them 1.
    **/
    m_Animation->DrawAnime(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{

    m_Animation->SetProps("player_idle", 0, 8, 100);
    m_RigidBody->UnsetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) == true)
    {
        m_RigidBody->ApplyForceXAxis(10*BACKWARD);
        m_Animation->SetProps("player_run", 0, 8, 100, SDL_FLIP_HORIZONTAL);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) == true)
    {
        m_RigidBody->ApplyForceXAxis(10*FORWARD);
        m_Animation->SetProps("player_run", 0, 8, 100);
    }

    m_RigidBody->Update(dt); //tgian

    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    //m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
