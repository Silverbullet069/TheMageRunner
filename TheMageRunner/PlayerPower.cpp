
#include "PlayerPower.h"

/*************************************PLAYER_LIVE***************************************/

PlayerLive::PlayerLive()
{
   number_live_ = 0;
}

PlayerLive::~PlayerLive()
{
    //
}

void PlayerLive::Init(SDL_Renderer* des)
{
   bool ret = LoadImg(g_name_icon_live, des, SDL_FALSE, WHITE);
   if(!ret) { printf("Unable to load player live!"); }
   else
   {
        if(!pos_list_.empty())
        {
            pos_list_.clear();
        }

        //Khoi? tao. so^' luong^. mang. mac. dinh. va` toa. do^. cua? tung` mang.
        number_live_ = 3;
        for(int i = 0 ; i < number_live_ ; ++i)
        {
            pos_list_.push_back(10 + i*rect_.w);
        }
   }
}

void PlayerLive::Show(SDL_Renderer* des)
{
    //In tung` mang. tuong? ung' voi' tung` toa. do^. x trong pos_list_
    for(int i = 0 ; i < number_live_ ; ++i)
    {
        SetRect(pos_list_[i], (2*TILE_SIZE-rect_.h)/2);
        Render(des);
    }
}

/*************************************PLAYER_SKILL***************************************/

PlayerSkill::PlayerSkill()
{
    number_skill_ = 0;
}

PlayerSkill::~PlayerSkill()
{
    //
}

void PlayerSkill::Init(SDL_Renderer* des)
{
    bool ret = LoadImg(g_name_icon_skill, des, SDL_FALSE, WHITE);
    if(!ret) { printf("Unable to load player skill!"); }
    else
    {
        number_skill_ = 1;
        SetRect(4*TILE_SIZE, (2*TILE_SIZE-rect_.h)/2);
    }
}

void PlayerSkill::Show(SDL_Renderer* des)
{
    SDL_Rect current_clip = {0, 0, TILE_SIZE*number_skill_, TILE_SIZE};
    SDL_Rect renderQuad = {rect_.x, rect_.y, TILE_SIZE*number_skill_, TILE_SIZE};
    SDL_RenderCopy(des, p_object_, &current_clip, &renderQuad);
}

/***************************************PLAYER_BUFF***************************************/

PlayerBuff::PlayerBuff()
{
    //
}

PlayerBuff::~PlayerBuff()
{
    //
}

void PlayerBuff::Init(SDL_Renderer* des)
{
    bool ret = LoadImg(g_name_icon_buff, des, SDL_FALSE, WHITE);
    if(!ret) { printf("Unable to load player buff!"); }
    else
    {
        SetRect(7*TILE_SIZE, (2*TILE_SIZE-rect_.h)/2);
    }
}

void PlayerBuff::ImpBuffType(const int& buff_type, const int& time_left)
{
    if(time_left > 0)
    {
        buff_status_[buff_type] = true;
    }
    else
    {
        buff_status_[buff_type] = false;
    }
}

void PlayerBuff::Show(SDL_Renderer* des)
{
    Render(des);

    for(int i = 0 ; i < TOTAL_BUFF ; ++i)
    {
        if(buff_status_[i] == false)
        {
            SDL_Rect hide = {rect_.x + i*128, rect_.y, 128, 128};
            ScreenEffect::RenderRectangle(des, hide, DEMO); //Ham` nay` k co' SDL_RenderPresent
        }
    }
}

/************************************PLAYER_SCORE**************************************/

PlayerScore::PlayerScore()
{
    score_count_ = 0;
    score_cvrt_  = "";
}

PlayerScore::~PlayerScore()
{
   //
}

void PlayerScore::Init(SDL_Renderer* des)
{
    score_cvrt_ = "Score : ";
}

void PlayerScore::Show(SDL_Renderer* des)
{
    Init(des);
    std::string str_tmp = std::to_string(score_count_);
    score_cvrt_ += str_tmp;
    score_game_.SetPosXY(SCREEN_WIDTH/2 + 0.8*TILE_SIZE, 110);
    score_game_.SetTextType(score_cvrt_);
    score_game_.LoadTextureTextType(g_font_text_2, des);
    score_game_.RenderText(des);
}

/****************************************PLAYER_MONEY******************************************/

PlayerMoney::PlayerMoney()
{
    money_count_ = 0;
    money_cvrt_  = "";
}

PlayerMoney::~PlayerMoney()
{
   //
}

void PlayerMoney::Init(SDL_Renderer* des)
{
   bool ret = LoadImg(g_name_icon_coin, des, SDL_FALSE, WHITE);
   if(!ret) {printf("Unable to load player money!");}
   else
   {
      BaseObject::SetRect(SCREEN_WIDTH/2 + 4.2*TILE_SIZE, (2*TILE_SIZE-rect_.h)/2);
   }
}

void PlayerMoney::Show(SDL_Renderer* des)
{
    Render(des);

    money_cvrt_ = ": " + std::to_string(money_count_);
    money_game_.SetPosXY(SCREEN_WIDTH - 4.7*TILE_SIZE, 110);
    money_game_.SetTextType(money_cvrt_);
    money_game_.LoadTextureTextType(g_font_text_2, des);
    money_game_.RenderText(des);
}

/***************************************PLAYER_TIME*********************************************/

PlayerTime::PlayerTime()
{
    time_count_ = 0;
    time_cvrt_ = "";
}

PlayerTime::~PlayerTime()
{
    //
}

void PlayerTime::Init(SDL_Renderer* des)
{
    bool ret = LoadImg(g_name_icon_hour_glass, des, SDL_FALSE, WHITE);
    if(!ret) {printf("Unable to load player time!");}
    else
    {
        BaseObject::SetRect(SCREEN_WIDTH/2 + 7*TILE_SIZE, (2*TILE_SIZE-rect_.h)/2);
    }
}

void PlayerTime::Show(SDL_Renderer* des)
{
    Render(des);

    time_cvrt_ = ": " + std::to_string(time_count_);
    time_game_.SetPosXY(SCREEN_WIDTH - 2*TILE_SIZE, 110);
    time_game_.SetTextType(time_cvrt_);
    time_game_.LoadTextureTextType(g_font_text_2, des);
    time_game_.RenderText(des);
}
