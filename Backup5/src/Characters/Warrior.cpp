#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Config.h"

Warrior::Warrior(Properties* props) : Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(PLAYER_BUFFER_X_POS,
                          PLAYER_BUFFER_Y_POS,
                          PLAYER_BUFFER_W_POS,
                          PLAYER_BUFFER_H_POS);

    //Buffer la` phan` margins xung quanh Box
    //ngan cach' phan` hinh` anh? cua? Entity va` Box

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravityAccel(PLAYER_RIGID_BODY_GRAVITY_ACCEL);
    //Set lai. GravityAccel thap' hon? voi' GravityAccel default
    /** Co' the? tang them^ luc. tac' dung. theo phuong? Y, hoac. la` tang them^ thoi` gian nhay? **/

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, PLAYER_SPRITE_ROW,
                                       PLAYER_SPRITE_FRAME,
                                       PLAYER_ANIMATION_SPEED);
    //lan` luot. la` so^' row, so^' frame trong 1 row, tg 2 frame cach' nhau
    //m_TextureID trong GameObject, da duoc. khoi? tao. trong Engine::Init()
}

void Warrior::Draw()
{
    m_Animation->DrawAnime(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    //Lan` luot. la` toa. do^. cua? Entity sau khi update va` kich' thuoc' cua? Entity


    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->GetBox();
    /** GIAI THICH :
    BOX ve~ theo he^ quy chieu^' cua? Entity, ma` Entity duoc. ve~ theo he^. quy chieu' cua? Camera,
    luc' dau` Box theo he^. quy chieu^' rieng^ cua? no', nv cang` di, Box se~ cang` di chuyen? lech^ khoi?
    nv neu' nhu? khong^ tinh' toan' lai. Box theo  theo he^. quy chieu^' cua? Camera **/
    box.x -= cam.X;
    box.y -= cam.Y;
    //Ve~ BoxCollider bao quanh nhan^ vat^.
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update()
{
    float dt = m_DeltaTime; //Thoi gian default su? dung. de? xet' movement cua? nv

    m_Animation->SetProps("player_idle", PLAYER_SPRITE_ROW,
                                         PLAYER_SPRITE_FRAME,
                                         PLAYER_ANIMATION_SPEED); //ID, rows, frames/row, speed anime
    m_RigidBody->UnsetForce(); //Ngung` ap' dung. luc. khi khong^ bam' nut'

    //Move left
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) == true)
    {
        m_RigidBody->ApplyForceXAxis(PLAYER_RUN_FORCE*BACKWARD); //Tac' dung. 1 luc. theo huong' ve` phia' sau (-)
        m_Animation->SetProps("player_run", PLAYER_SPRITE_ROW,
                                            PLAYER_SPRITE_FRAME,
                                            PLAYER_ANIMATION_SPEED,
                                            SDL_FLIP_HORIZONTAL); //ID, rows, frames/row, speed anime, flag lat^. hinh`
    }

    //Move right
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) == true)
    {
        m_RigidBody->ApplyForceXAxis(PLAYER_RUN_FORCE*FORWARD); //Tac' dung. 1 luc. theo huong' ve` phia' truoc' (+)
        m_Animation->SetProps("player_run", PLAYER_SPRITE_ROW,
                                            PLAYER_SPRITE_FRAME,
                                            PLAYER_ANIMATION_SPEED); //ID, rows, frames/row, speed anime, k set flag
    }

    //Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded == true)
    {
        m_IsJumping = true; //Set flag jump = true
        m_IsGrounded = false; //Set flag ground = false
        m_RigidBody->ApplyForceYAxis(UPWARD*m_JumpForce);
    }
    //LY DO co' them^ 1 if-else o? duoi', vi` sau khi m_IsGrounded = false, lan` toi' Update se~ khong^ chay. vao`
    //lenh^. if o? tren^ nua~, keo' theo ngung?` ApplyForceYAxis va` nv se~ khong^ jump tiep duoc. len^
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping == true && m_JumpTime > 0)
    {
        //Nv dang co' flag jump == true va` flag thoi` gian de? nhay? LEN^ van~ con`
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceYAxis(UPWARD*m_JumpForce);
        m_Animation->SetProps("player_jump", PLAYER_SPRITE_ROW,
                                             PLAYER_SPRITE_JUMP_FALL_ROW,
                                             PLAYER_ANIMATION_SPEED); //ID, rows, frames/row, speed anime, k set flag

        //Moi~ lan` update, giam? dan` thoi` gian de? jump, trong luc' nay` van~ ApplyForceYAxis
        //khi no' < 0, nv se~ khong^ the? jump cao hon duoc. nua~ vi` flag m_JumpTime > 0 sai,
        //thoat' khoi? lenh^. if, keo' thao ngung` ApplyForceYAxis

        //Luu y : ke? ca? jump time van~ chua <0 ma` tha? nut' SPACE ra, nhan^ vat^. van~ se~ fall ngay sau do'
    }
    else
    {
        m_IsJumping = false; //Set lai. flag jump = false, luc' nay` nv vua` k jump va` k ground => Falling
        m_JumpTime = JUMP_TIME; //Set lai. jump time (vi` jump time hien^ gio dang < 0, lan` toi nv se~ k jump)
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

    //Update animation cua? Entity
    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
