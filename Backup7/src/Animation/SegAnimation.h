#ifndef SEGANIMATION_H
#define SEGANIMATION_H

#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "Animation.h"

//Kieu? du~ lieu^. luu toan` bo^. data ve^` 1 kieu^? action cua? Entity
//Run, Idle, Move, Attack,... la` cac' Sequence
struct Sequence
{
    int Speed; //Thoi gian giua~ 2 frame trong 1 Sequance
    int FrameCount; //Tong? so' frame trong 1 Sequance
    int Width; //Chieu` dai` cua? 1 frame
    int Height; //Chieu` rong^. cua? 1 frame
    std::vector<std::string> TextureIDs;
    //Cac' frame trong 1 Sequence duoc. quan? ly' bang` chuoi~ ID
};

class SegAnimation : public Animation
{
    public:
        SegAnimation(bool repeat = true);

        virtual void Update();
        void Parse(std::string source);
        /** Khac' biet^. voi' SpriteAnimation o? ham` nay` - truyen^` tat^' ca? cac' du~ lieu^ ve^`
        Animation cua? Entity trong 1 file XML vao` **/
        void SetCurrentSeg(std::string segID); //Thay doi Seq hien^. tai. cua? entity theo Seq co' ID trong m_SeqMap
        void SetRepeat(bool repeat) {m_Repeat = repeat;}
        void DrawAnime(float x, float y, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence m_CurrentSeq; //Sequence ma` entity dang xet'
        std::map<std::string, Sequence> m_SeqMap; //Map quan? ly' tat^' ca? cac' Sequence cua? 1 entity
};

#endif // SEGANIMATION_H
