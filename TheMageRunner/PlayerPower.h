
#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_

#include "BaseObject.h"
#include "TextObject.h"
#include "ScreenEffect.h"

class PlayerLive : public BaseObject
{
public:
   PlayerLive();
   ~PlayerLive();
   void Init(SDL_Renderer* des);
   void Show(SDL_Renderer* des);
   int GetNumLive() const { return number_live_; }
   void SetNumLive(const int& num) {number_live_ = num;}

private:
   int number_live_;
   std::vector<int> pos_list_;
};

class PlayerSkill : public BaseObject
{
public:
    PlayerSkill();
    ~PlayerSkill();
    void SetNumSkill(const int& num) {number_skill_ = num;}
    void Init(SDL_Renderer* des);
    void Show(SDL_Renderer* des);

private:
    int number_skill_;
};

class PlayerBuff : public BaseObject
{
public:
    enum BUFF
    {
        HASTE = 0,
        POWER_UP = 1,
        INVIN = 2,
        TOTAL_BUFF = 3,
    };

    PlayerBuff();
    ~PlayerBuff();
    void Init(SDL_Renderer* des);
    void Show(SDL_Renderer* des);
    void ImpBuffType(const int& buff_type, const int& time_left);

private:
    bool buff_status_[TOTAL_BUFF];
};

class PlayerScore
{
public:

    PlayerScore();
    ~PlayerScore();

    void Init(SDL_Renderer* des);
    void Show(SDL_Renderer* des);
    void SetNumScore(const int& num) { score_count_ = num; }

private:
    int score_count_;
    std::string score_cvrt_;
    TextObject score_game_;
};

class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();

    void Init(SDL_Renderer* des);
    void Show(SDL_Renderer* des);
    void SetNumMoney(const int& num) { money_count_ = num; }

private:
    int money_count_;
    std::string money_cvrt_;
    TextObject money_game_;

};

class PlayerTime : public BaseObject
{
public:
    PlayerTime();
    ~PlayerTime();

    void Init(SDL_Renderer* des);
    void Show(SDL_Renderer* des);
    void SetTimeCount(const int& time_c) {time_count_ = time_c; }

private:
    int time_count_;
    std::string time_cvrt_;
    TextObject time_game_;
};


#endif // PLAYER_POWER_H_
