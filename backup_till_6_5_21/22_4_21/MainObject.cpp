
#include "MainObject.h"

MainObject::MainObject()
{
   frame_ = 0;
   x_pos_ = 0;
   y_pos_ = PLAYER_START_FALL_Y_POS;
   x_val_ = 0;
   y_val_ = 0;
   width_frame_ = 0;
   height_frame_ = 0;
   status_ = WALK_NONE_RIGHT;
   input_type_.idle_ = 1; //Khoi tao ban dau
   input_type_.left_ = 0;
   input_type_.right_ = 0;
   input_type_.up_ = 0;
   input_type_.down_ = 0;
   input_type_.jump_ = 0;
   on_ground_ = false;
   map_x_ = 0;
   map_y_ = 0;
   come_back_time_ = 0;
   toggle_bullet_ = 0;
   money_count_ = 0;

   txt_player_idle_left_ = NULL;
   txt_player_idle_right_ = NULL;
   txt_player_walk_left_ = NULL;
   txt_player_walk_right_ = NULL;
}

MainObject::~MainObject()
{
   if(txt_player_idle_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_idle_left_);
      txt_player_idle_left_ = NULL;
   }
   if(txt_player_idle_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_idle_right_);
      txt_player_idle_right_ = NULL;
   }
   if(txt_player_walk_left_ != NULL)
   {
      SDL_DestroyTexture(txt_player_walk_left_);
      txt_player_walk_left_ = NULL;
   }
   if(txt_player_walk_right_ != NULL)
   {
      SDL_DestroyTexture(txt_player_walk_right_);
      txt_player_walk_right_ = NULL;
   }
}

void MainObject::LoadAllPlayerAction(SDL_Renderer* des)
{
   txt_player_idle_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_idle_left, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_player_idle_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_idle_right, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_player_walk_left_ = SDLCommonFunction::LoadTexture(g_name_main_obj_move_left, des,
                                                          rect_, SDL_FALSE, WHITE);
   txt_player_walk_right_ = SDLCommonFunction::LoadTexture(g_name_main_obj_move_right, des,
                                                           rect_, SDL_FALSE, WHITE);
   //rect_ chung cho tat ca action
   width_frame_ = rect_.w/PLAYER_FRAME_NUM;
   height_frame_ = rect_.h;
}

/**

         0,0     mxtl     mxtr    width_frame_
            ************************
            *                      *
            *                      *
        mytl*       ********       *
            *       *      *       *
            *       *      *       *
            *       *      *       *
        mytr*       ********       *
            *                      *
            *                      *
            ************************
            height_frame_

**/

//Cach cu~
bool MainObject::LoadImg(const std::string file_path, SDL_Renderer* des)
{
   bool ret = BaseObject::LoadImg(file_path, des, SDL_TRUE, DEMO);
   if(!ret) { printf("Unable to load main object!"); }
   else
   {
      width_frame_ = rect_.w/PLAYER_FRAME_NUM;
      height_frame_ = rect_.h;
   }
   return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
   SDL_Rect rect_tmp = {0, 0, 0, 0};
   rect_tmp.x = rect_.x;
   rect_tmp.y = rect_.y;
   rect_tmp.w = width_frame_;
   rect_tmp.h = height_frame_;
   return rect_tmp;
}

void MainObject::set_clips()
{
   if(width_frame_ > 0 && height_frame_ > 0)
   {
      for(int i = 0 ; i < PLAYER_FRAME_NUM ; ++i)
      {
         frame_clip_[i].x = i*width_frame_;
         frame_clip_[i].y = 0;
         frame_clip_[i].w = width_frame_;
         frame_clip_[i].h = height_frame_;
      }
   }
}

void MainObject::Show(SDL_Renderer* des)
{
   //Thay doi status nhan vat
   UpdateImagePlayer(des);

   //Xu ly trang thai ghi nhan
   //Nhan vat dang di chuyen sang trai, phai, hoac dung yen
   if(input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.idle_ == 1)
   {
      frame_ ++; //Tang frame
   }
   else
   {
      frame_ = 0;
   }

   if(frame_ >= PLAYER_FRAME_NUM)
   {
      frame_ = 0;
   }

   //Giam duoc cong viec xu ly khi dang delay time de hoi sinh nhan vat
   if(come_back_time_ == 0)
   {
      //x_pos_ la vi tri cua nhan vat tren toan bo map
      //map_x la vi tri mep khung hinh tren toan bo map
      //rect_.x la vi tri cua nhan vat tren khung hinh
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_ - map_y_;

      //Lay rect cua frame hien tai
      SDL_Rect* current_clip = &frame_clip_[frame_];

      SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

      SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
   }
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* des)
{
   //Ban phim
   if(events.type == SDL_KEYDOWN)
   {
      switch(events.key.keysym.sym)
      {
      case SDLK_a :
         {
            status_ = WALK_LEFT;
            input_type_.left_ = 1;
            input_type_.idle_ = 0;  //Huy trang thai dung yen
            input_type_.right_ = 0; //Tranh TH bam 2 nut cung luc
         }
         break;
      case SDLK_d :
         {
            status_ = WALK_RIGHT;
            input_type_.right_ = 1;
            input_type_.idle_ = 0; //Huy trang thai dung yen
            input_type_.left_ = 0; //Tranh TH bam 2 nut cung luc
         }
         break;
      case SDLK_SPACE :
         {
            input_type_.jump_ = 1;
         }
         break;
      case SDLK_1 :
         {
            if(toggle_bullet_ != BulletObject::FIRE_BALL)
            {
               toggle_bullet_ = BulletObject::FIRE_BALL;
            }
         }
         break;
      case SDLK_2 :
         {
            if(toggle_bullet_ != BulletObject::ICE_SHARD)
            {
               toggle_bullet_ = BulletObject::ICE_SHARD;
            }
         }
         break;
      }
   }
   else if (events.type == SDL_KEYUP)
   {
      switch(events.key.keysym.sym)
      {
         case SDLK_a :
         {
            input_type_.left_ = 0;
            status_ = WALK_NONE_LEFT;
            input_type_.idle_ = 1;
         }
         break;
         case SDLK_d :
         {
            input_type_.right_ = 0;
            status_ = WALK_NONE_RIGHT;
            input_type_.idle_ = 1;
         }
         break;
      }
   }

   //Bam chuot
   if(events.type == SDL_MOUSEBUTTONDOWN)
   {
      if(events.button.button == SDL_BUTTON_LEFT)
      {
         BulletObject* p_bullet = new BulletObject();

      //Set loai dan
         if(toggle_bullet_ == BulletObject::FIRE_BALL) //fire ball
         {
            p_bullet->set_bullet_type(BulletObject::FIRE_BALL);
         }
         else if (toggle_bullet_ == BulletObject::ICE_SHARD) //ice shard
         {
            p_bullet->set_bullet_type(BulletObject::ICE_SHARD);
         }

      //Load img cua loai dan tuong ung
         p_bullet->LoadImgBullet(des);

         if(status_ == WALK_LEFT || status_ == WALK_NONE_LEFT)
         {
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(this->rect_.x + width_frame_ - BULLET_MARGINS_X_VAL, this->rect_.y);
         }
         else if(status_ == WALK_RIGHT || status_ == WALK_NONE_RIGHT)
         {
            p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
            p_bullet->SetRect(this->rect_.x + width_frame_ - BULLET_MARGINS_X_VAL, this->rect_.y);
         }

      //Set van toc cua vien dan
      //Van toc <0 hay >0 phu thuoc vao huong' dan
         p_bullet->set_x_val(BULLET_VELOCITY_X_VAL);
         p_bullet->set_y_val(BULLET_VELOCITY_Y_VAL);

      //Set vi tri cua vien dan tren tile map
         p_bullet->set_x_pos(this->get_x_pos() + this->get_width_frame());
         p_bullet->set_y_pos(this->get_y_pos());

      //Set flag di chuyen cua vien dan
         p_bullet->set_is_move(true);

         p_bullet_list_.push_back(p_bullet);
      }
   }
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
   if(on_ground_ == true)
   {
      /** Phan biet giua status va input.
      Su dung input co the lay duoc trang thai, nhung khi nha phim/chuot ra, input se mat.
      Status luu trang thai, cho du co nha phim/chuot, status van giu nguyen **/
      if(status_ == WALK_LEFT)
      {
         BaseObject::SetObject(txt_player_walk_left_);
      }
      else if (status_ == WALK_RIGHT)
      {
         BaseObject::SetObject(txt_player_walk_right_);
      }
      else if (status_ == WALK_NONE_LEFT)
      {
         BaseObject::SetObject(txt_player_idle_left_);
      }
      else if(status_ = WALK_NONE_RIGHT)
      {
         BaseObject::SetObject(txt_player_idle_right_);
      }
   }
   else // dang nhay hoac dang roi tu do
   {
      if(status_ == WALK_NONE_LEFT)
      {
         BaseObject::SetObject(txt_player_idle_left_);
      }
      else if (status_ == WALK_NONE_RIGHT)
      {
         BaseObject::SetObject(txt_player_idle_right_);
      }
   }
}

void MainObject::DoPlayer(Map& map_data)
{
   if(come_back_time_ == 0)
   {
      x_val_ = 0;
      //Xu ly nhan vat roi tu tu xuong
      y_val_ += PLAYER_GRAVITY_VELOCITY; //Toc do roi

      //Gioi han van toc roi
      if(y_val_ >= PLAYER_MAX_FALL_SPEED)
      {
         y_val_ = PLAYER_MAX_FALL_SPEED;
      }

      if(input_type_.jump_ == 1) //nv nhay len
      {
         if(on_ground_ == true) //neu nv dang nam duoi mat dat
         {
            y_val_ = -PLAYER_JUMP_VAL; //Khong dung -= vi muon nhay nhanh
         }
         on_ground_ = false; //Set nv hien tai dang khong nam duoi dat
         input_type_.jump_ = 0; //Ngay tu luc nhay len, set truoc flag dap xuong mat dat
         //Neu khong, ngay sau khi dap xuong, nv tiep tuc nhay len vi flag van bang 1
      }
      //Neu flag ghi nhan, nhan vat dang di chuyen sang trai
      else if(input_type_.left_ == 1)
      {
         x_val_ -= PLAYER_VELOCITY; //Tang toc do di chuyen len trai
      }
      else if(input_type_.right_ == 1) // nv di chuyen sang phai
      {
         x_val_ += PLAYER_VELOCITY; //Tang toc do di chuyen len phai
      }
      else if(input_type_.idle_ == 1)
      {
         //
      }
      //Ham kiem tra va cham voi tilemap
      CheckToMap(map_data, 0, EPSILON_Y);
      //Ham lam tile map chay theo nhan vat
      CenterEntityOnMap(map_data);
   }

   //Xu ly delay time giua 2 mang
   if(come_back_time_ > 0)
   {
      come_back_time_ --;
      if(come_back_time_ == 0) //RESET lai nhan vat, roi tu tren cao xuong
      {
         InitPlayer();
      }
   }
}

void MainObject::InitPlayer()
{
   on_ground_ = false;
   //Neu vi tri nhan vat theo phuong x vuot qua 4 o tile
   if(x_pos_ >= 4*TILE_SIZE)
   {
      x_pos_ -= 4*TILE_SIZE;
   }
   else //x_pos < 4*TILE_SIZE (Nv dang o vi tri xuat phat)
   {
      x_pos_ = 0;
   }
   y_pos_ = PLAYER_START_FALL_Y_POS;
   x_val_ = 0;
   y_val_ = 0;
}

void MainObject::CheckToMap(Map& map_data, const int& epsilon_x, const int& epsilon_y)
{
   //Cach kiem tra nay chi chuan xac, neu tat ca cac tile deu la 64x64

   //x1x2y1y2 tinh theo o tiles, KHONG PHAI PIXEL
   //Gioi han kiem tra tu a => b theo phuong x
   int x1 = 0;
   int x2 = 0;

   //Gioi han kiem tra tu a => b theo phuong y
   int y1 = 0;
   int y2 = 0;

   //Kiem tra theo phuong ngang
   int height_min = (height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE);

   //Tim` xem nhan^ vat. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_ + x_val_) / TILE_SIZE;
   //De ma duong` bien cua nhan vat co the trung voi bien cua TILE_MAP
   //Ta tru di 1 luong EPSILON la sai so de check chuan xac hon
   x2 = (x_pos_ + x_val_ + width_frame_ - EPSILON) / TILE_SIZE;

   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong y
   y1 = (y_pos_) / TILE_SIZE; //Khong cong them y_val_
   y2 = (y_pos_ + height_min - EPSILON - epsilon_y) / TILE_SIZE; /** LUU Y : EPSILON_Y FIX TEXTURE NON 64x64 */

   /**

           x1,y1 ********* x2,y1 * *
           *               *
           *               *
           *               *
           *               *
           *               *
           x1,y2 ********* x2,y2 * *
           *               *
           *               *

   **/

   //Nam trong vung ban do tile map
   if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
   {
      if(x_val_ > 0) //Move right
      {
         //Check collision with coins
         int val1 = map_data.tile[y1][x2];
         int val2 = map_data.tile[y2][x2];

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            //Set gia tri cua no = 0 => Lan render tiep theo se ra o tile blank
            map_data.tile[y1][x2] = 0;
            map_data.tile[y2][x2] = 0;
            IncreaseMoney();
         }
         else
         {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE )
            //Check o ben phai, va o ben duoi cua no
            {
               x_pos_ = x2*TILE_SIZE;
               x_pos_ -= (width_frame_ + EPSILON);
               x_val_ = 0;
            }
         }
      }
      else if(x_val_ < 0) //Move left
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y2][x1];

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            map_data.tile[y1][x1] = 0;
            map_data.tile[y2][x1] = 0;
            IncreaseMoney();
         }
         else
         {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            //Check o ben trai, va o ben duoi cua no
            {
               x_pos_ = (x1 + EPSILON)*TILE_SIZE;
               x_val_ = 0;
            }
         }
      }
   }

   /**

           x1,y1 ********* x2,y1 ***
           *               *
           *               *
           *               *
           *               *
           *               *
           x1,y2 ********* x2,y2 ***
           *               *
           *               *

   **/


   //Check theo phuong thang dung
   int width_min = (width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE);

   //Tim` xem nhan^ vat. dang dat. tai. o^ thu' bn den o^ thu' bn
   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong x
   x1 = (x_pos_)/TILE_SIZE;
   x2 = (x_pos_ + width_min)/TILE_SIZE;

   //Vi. tri' cua nhan^ vat^ la o^ thu' bao nhieu^ sau khi di chuyen? theo phuong y
   y1 = (y_pos_ + y_val_)/TILE_SIZE;
   y2 = (y_pos_ + y_val_ + height_frame_ - EPSILON) / TILE_SIZE;

   //Nam ben trong tile map
   if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
   {
      if(y_val_ > 0) //Idle
      {
         int val1 = map_data.tile[y2][x1];
         int val2 = map_data.tile[y2][x2];

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            map_data.tile[y2][x1] = 0;
            map_data.tile[y2][x2] = 0;
            IncreaseMoney();
         }
         else
         {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
               y_pos_ = y2*TILE_SIZE;
               y_pos_ -= (height_frame_ + EPSILON);
               y_val_ = 0;
               on_ground_ = true;
            }
         }
      }
      else if(y_val_ < 0) //Jump
      {
         int val1 = map_data.tile[y1][x1];
         int val2 = map_data.tile[y1][x2];

         if(val1 == STATE_MONEY || val2 == STATE_MONEY)
         {
            map_data.tile[y1][x1] = 0;
            map_data.tile[y1][x2] = 0;
            IncreaseMoney();
         }
         else
         {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
               y_pos_ = (y1 + EPSILON)*TILE_SIZE;
               y_val_ = 0;
            }
         }
      }
   }

   //printf("%d\n", &on_ground_);

   //Neu khong phai TH dac biet, di chuyen nhan vat theo x_val_ va y_val_
   x_pos_ += x_val_;
   y_pos_ += y_val_;

   //Nhan vat di chuyen cham toi bien trai'
   if(x_pos_ < 0)
   {
      x_pos_ = 0;
   }
   else if(x_pos_ + width_frame_ > map_data.max_x_) //Nhan vat di chuyen cham toi bien phai?
   {
      x_pos_ = map_data.max_x_ - width_frame_ - EPSILON;
   }
   //Nhan vat di chuyen cham toi bien duoi (roi xuong vuc)
   if(y_pos_ > map_data.max_y_)
   {
      come_back_time_ = 60; //theo delay time giua 2 mang la (60 frame)
   }
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
   map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
   //Kiem tra luc o goc tile map ma nv xuat hien, chua di chuyen qua' 1/2 man hinh
   //thi chua cho tile map chay theo nv
   if(map_data.start_x_ < 0)
   {
      map_data.start_x_ = 0;
   }
   //Nhu tren, trg hop nay la goc tile map cuoi cung, con dung 1 goc tile map = man hinh
   //thi cung khong cho tile map chay theo nv nua
   else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) //max_x_ theo pixel
   {
      map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
   }

   //Kiem tra theo phuong y (danh cho Game di chuyen theo phuong thang dung)
   map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);

   if(map_data.start_y_ < 0)
   {
      map_data.start_y_ = 0;
   }
   else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) //max_y_ theo pixel
   {
      map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
   }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
   for(int i = 0 ; i < p_bullet_list_.size() ; ++i)
   {
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if(p_bullet != NULL)
      {
         if(p_bullet->get_is_move() == true)
         {
            p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_bullet->Render(des);
         }
         else
         {
            p_bullet_list_.erase(p_bullet_list_.begin() + i);
            if(p_bullet != NULL)
            {
               delete p_bullet;
               p_bullet = NULL;
            }
         }
      }
   }
}

void MainObject::RemoveBullet(const int& idx)
{
   int size_ = p_bullet_list_.size();
   if(size_ > 0 && idx < size_)
   {
      BulletObject* p_bullet = p_bullet_list_.at(idx);
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);

      if(p_bullet != NULL)
      {
         delete p_bullet;
         p_bullet = NULL;
      }
   }
}

void MainObject::InitExplosion(const int& objType, const int& obj_x_pos, const int& obj_y_pos, SDL_Renderer* des)
{
   ExpObject* exp_obj = new ExpObject();
   exp_obj->set_exp_type(ExpObject::EXP_THREAT);
   exp_obj->LoadImgExp(g_renderer);
   exp_obj->set_clips();

   int exp_x_pos = obj_x_pos - exp_obj->get_frame_width()*0.5;
   int exp_y_pos = obj_y_pos - exp_obj->get_frame_height()*0.5;
   exp_obj->SetRect(exp_x_pos, exp_y_pos);
   exp_obj->set_is_exp(true);

   p_exp_list_.push_back(exp_obj);
}

void MainObject::HandleExplosion(SDL_Renderer* des)
{
   //Check tung vu no trong chuoi~ vu no
   for(int i = 0 ; i < p_exp_list_.size() ; ++i)
   {
      //Lay tung vu no ra
      ExpObject* p_exp = p_exp_list_.at(i);
      if(p_exp != NULL)
      {
         if(p_exp->get_is_exp() == true)
         {
            p_exp->Show(des);
         }
         else //get_is_exp() == false // frame_ > EXP_NUM_FRAME
         {
            p_exp_list_.erase(p_exp_list_.begin() + i);
            if(p_exp != NULL)
            {
               delete p_exp;
               p_exp = NULL;
            }
         }
      }
   }
}

//Chua dung den
void MainObject::RemoveExplosion(const int& idx)
{
   int size_ = p_exp_list_.size();
   if(size_ > 0 && idx < size_)
   {
      ExpObject* p_exp = p_exp_list_.at(idx);
      p_exp_list_.erase(p_exp_list_.begin() + idx);

      if(p_exp != NULL)
      {
         delete p_exp;
         p_exp = NULL;
      }
   }
}

void MainObject::IncreaseMoney()
{
   money_count_++;
}
