#include "Warrior.h"
#include "Config.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"

static Registrar<Warrior> registrar("PLAYER");

Warrior::Warrior(Properties* props) : Character(props)
{
    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking1 = false;
    m_IsAttacking2 = false;
    m_IsCrouching = false;

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime1 = ATTACK_TIME;
    m_AttackTime2 = ATTACK_TIME;

    //Buffer la` phan` margins xung quanh Box ngan cach' phan` hinh` anh? cua? Entity va` Box

    m_Collider = new Collider();
    m_Collider->SetBuffer(PLAYER_BUFFER_X_POS,
                          PLAYER_BUFFER_Y_POS,
                          PLAYER_BUFFER_W_POS,
                          PLAYER_BUFFER_H_POS);

    /** Set lai. GravityAccel thap' hon? voi' GravityAccel default
    Co' the? tang them^ luc. tac' dung. theo phuong? Y, hoac. la` tang them^ thoi` gian nhay? **/

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravityAccel(PLAYER_RIGID_BODY_GRAVITY_ACCEL);


    /**lan` luot. la` so^' row, so^' frame trong 1 row, tg 2 frame cach' nhau
    m_TextureID trong GameObject, da duoc. khoi? tao. trong Engine::Init()
    Set Props de? khoi? tao. truoc' chu' khong^ de^? lam` gi` ca?, Props that^. duoc. su? dung. trong AnimationState() **/

    m_Animation = new SpriteAnimation(true); //Thay the^' Animation
    m_Animation->SetProps(m_TextureID, PLAYER_SPRITE_COMMON_ROW,
                                       PLAYER_SPRITE_COMMON_FRAME,
                                       PLAYER_ANIME_IDLE_SPEED);

}

void Warrior::Draw()
{
    m_Animation->DrawAnime(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip); //SpriteAnimation
    //Lan` luot. la` toa. do^. cua? Entity sau khi update va` kich' thuoc' cua? Entity va` flag flip cua? GameObject
    m_Collider->Draw();
}

void Warrior::AnimationState()
{
    //idling
    m_Animation->SetProps("player_idle", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_COMMON_FRAME, PLAYER_ANIME_IDLE_SPEED);

    //running
    if(m_IsRunning == true)
    {
        m_Animation->SetProps("player_run", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_COMMON_FRAME, PLAYER_ANIME_RUN_SPEED);
    }

    //crouching
    if(m_IsCrouching == true)
    {
        m_Animation->SetProps("player_crouch", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_COMMON_FRAME, PLAYER_ANIME_CROUCH_SPEED);
    }

    //jumping
    if(m_IsJumping == true)
    {
        m_Animation->SetProps("player_jump", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_JUMP_FRAME, PLAYER_ANIME_JUMP_SPEED);
    }

    //falling
    if(m_IsFalling == true)
    {
        m_Animation->SetProps("player_fall", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_FALL_FRAME, PLAYER_ANIME_FALL_SPEED);
    }

    //attacking 1
    if(m_IsAttacking1 == true)
    {
        m_Animation->SetProps("player_attack1", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_COMMON_FRAME, PLAYER_ANIME_ATTACK_SPEED);
    }

    //attacking 2
    if(m_IsAttacking2 == true)
    {
        m_Animation->SetProps("player_attack2", PLAYER_SPRITE_COMMON_ROW, PLAYER_SPRITE_COMMON_FRAME, PLAYER_ANIME_ATTACK_SPEED);
    }

    //taking hit, die, ....
}


void Warrior::Update()
{
    float dt = m_DeltaTime; //Thoi gian default su? dung. de? xet' movement cua? nv

    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnsetForce(); //Ngung` ap' dung. luc. khi khong^ bam' nut'

    //Run forward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && (m_IsAttacking1 == false || m_IsAttacking2 == false) )
    {
        m_RigidBody->ApplyForceXAxis(PLAYER_RUN_FORCE*FORWARD);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    //Run backward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && (m_IsAttacking1 == false || m_IsAttacking2 == false) )
    {
        m_RigidBody->ApplyForceXAxis(PLAYER_RUN_FORCE*BACKWARD);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    //Crouching
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        m_RigidBody->UnsetForce();
        m_IsCrouching = true;
    }

    //Attack 1 and 2
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J))
    {
        m_RigidBody->UnsetForce();
        m_IsAttacking1 = true;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K))
    {
        m_RigidBody->UnsetForce();
        m_IsAttacking2 = true;
    }

    //Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded == true)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceYAxis(UPWARD*m_JumpForce);
    }
    //LY DO co' them^ 1 if-else o? duoi', vi` sau khi m_IsGrounded = false, lan` toi' Update se~ khong^ chay. vao`
    //lenh^. if o? tren^ nua~, keo' theo ngung?` ApplyForceYAxis va` nv se~ khong^ jump tiep duoc. len^
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping == true && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceYAxis(UPWARD*m_JumpForce);

        //Moi~ lan` update, giam? dan` thoi` gian de? jump, trong luc' nay` van~ ApplyForceYAxis
        //khi no' < 0, nv se~ khong^ the? jump cao hon duoc. nua~ vi` flag m_JumpTime > 0 sai,
        //thoat' khoi? lenh^. if, keo' thao ngung` ApplyForceYAxis
        //Luu y : ke? ca? jump time van~ chua <0 ma` tha? nut' SPACE ra, nhan^ vat^. van~ se~ fall ngay sau do'
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME; //Set lai. jump time
    }

    //Fall
    if(m_RigidBody->GetVelocity().Y > 0 && m_IsGrounded == false)
    {
        m_IsFalling = true;
    }
    else
    {
        m_IsFalling = false;
    }

    //Attack timer 1
    if(m_IsAttacking1 == true && m_AttackTime1 > 0)
    {
        m_AttackTime1 -= dt;
        //Tuong. tu. khi xu? ly' Jump
    }
    else
    {
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) == false)
            /** CHUA~ BUG GIUA~ NUT' DE? TAN^' CONG^ LIEN^ TUC. THI` BI. NHAP^' NHAY' 1 FRAME TU IDLE **/
        {
            m_IsAttacking1 = false;
        }
        m_AttackTime1 = ATTACK_TIME; //Set lai. attack time
    }

    //Attack timer 2
    if(m_IsAttacking2 == true && m_AttackTime2 > 0)
    {
        m_AttackTime2 -= dt;
        //Tuong. tu. khi xu? ly' Jump
    }
    else
    {
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) == false)
            /** CHUA~ BUG GIUA~ NUT' DE? TAN^' CONG^ LIEN^ TUC. THI` BI. NHAP^' NHAY' 1 FRAME TU IDLE **/
        {
            m_IsAttacking2 = false;
        }
        m_AttackTime2 = ATTACK_TIME; //Set lai. attack time
    }

    /** XU LY' DI CHUYEN THEO PHUONG X **/

    //Sau khi update, m_Position.X trong RigidBody bien' dong^.
        m_RigidBody->Update(dt);

    //Set vi. tri' cu~ theo phuong x truoc' khi check va cham.
        m_LastSafePosition.X = m_Transform->X;

    //Cal vi. tri' moi' sau khoang? tg dt = vi. tri' cu~ + posX
    //== m_Transform->TranslateX(m_RigidBody->GetPosition().X);
        m_Transform->X += m_RigidBody->GetPosition().X;

    //Set BoxCollider theo vi. tri' moi' theo phuong x (LUU Y: VI. TRI' MOI', chu' K PHAI? VI. TRI' CU~)
        m_Collider->Set(m_Transform->X, m_Transform->Y, PLAYER_WIDTH_FRAME, PLAYER_HEIGHT_FRAME);

    //Check entity va. cham. voi' Map theo phuong x
        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox()))
        {
            m_Transform->X = m_LastSafePosition.X; //Set lai. vi. tri' cua? entity ve` vi. tri' cu~
        }

                                                                    /** NGUNG XU LY' DI CHUYEN THEO PHUONG X **/

    /** XU LY' DI CHUYEN THEO PHUONG Y **/

    //Sau khi update, m_Position.Y trong RigidBody bien' dong^.
        m_RigidBody->Update(dt);

    //Set vi. tri' cu~ theo phuong y truoc' khi check va cham.
        m_LastSafePosition.Y = m_Transform->Y;

    //Cal vi. tri' moi' sau khoang? tg dt = vi. tri' cu~ + posY
    //== m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
        m_Transform->Y += m_RigidBody->GetPosition().Y;

    //Set BoxCollider theo vi. tri' moi' theo phuong y (LUU Y: VI. TRI' MOI', chu' K PHAI? VI. TRI' CU~)
        m_Collider->Set(m_Transform->X, m_Transform->Y, PLAYER_WIDTH_FRAME, PLAYER_HEIGHT_FRAME);

    //Check entity va. cham. voi' Map theo phuong y
        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox()))
        {
            m_IsGrounded = true; //Set flag ground = true, de? nv co' the? jump
            m_Transform->Y = m_LastSafePosition.Y; //Set lai. vi. tri' cua? entity ve` vi. tri' cu~
        }
        else
        {
            m_IsGrounded = false;
        }
                                                                    /** NGUNG XU LY' DI CHUYEN THEO PHUONG Y **/

    //Cal toa. do^. TAM^ de? cal toa. do^. cua? Camera
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    //SDL_Log("%f\n", m_Origin->X);
    //SDL_Log("%f\n", m_Origin->Y);

    AnimationState();

    //Update animation cua? Entity
    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Erase(m_TextureID);
}
