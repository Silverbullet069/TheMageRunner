#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "Animation.h"

//Kieu? du~ lieu^. luu toan` bo^. thong^ so' ve^` 1 kieu^? hanh` dong^. cua? Entity
struct Sequence
{
    int Speed; //Thoi gian giua~ 2 frame trong 1 Sequance
    int FrameCount; //Tong? so' frame trong 1 Sequance
    int Width; //Chieu` dai` cua? 1 frame
    int Height; //Chieu` rong^. cua? 1 frame
    std::vector<std::string> TextureIDs;
    //Cac' frame trong 1 Sequence duoc. quan? ly' bang` chuoi~ ID
};

//SeqAnimation la` tao. Animation tu` CAC' ANH? DOC^. LAP^. ghep' voi' nhau thanh` 1 chuoi~ cac' hinh` anh?
//lien^ tiep', du~ lieu^. duoc. quan? ly' ben^ trong 2 file XML,
//1 file quan? ly' texture, luu duong` dan~ den^' tung` frame doc^. lap^. va` id tuong' ung' voi' tung` frame do'
//1 file quan? ly' cac' thong^ so^' cua? cac' kieu? hanh` dong^. cua? Entity, duoc. luu vao` trong bien' Sequence
class SeqAnimation : public Animation
{
    public:
        SeqAnimation(bool repeat = true);

        virtual void Update();
        void Parse(std::string source);
        /** Khac' biet^. voi' SpriteAnimation o? ham` nay` - truyen^` tat^' ca? cac' du~ lieu^ ve^`
        Animation cua? Entity trong 1 file XML vao` **/
        void SetCurrentSeq(std::string SeqID); //Thay doi Seq hien^. tai. cua? entity theo Seq co' ID trong m_SeqMap
        void SetRepeat(bool repeat) {m_Repeat = repeat;} //Set lai. flag loop sequence
        void DrawAnime(float x, float y, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        Sequence m_CurrentSeq; //Sequence ma` entity dang xet'
        std::map<std::string, Sequence> m_SeqMap; //Map quan? ly' tat^' ca? cac' Sequence cua? 1 entity
};

#endif // SEQANIMATION_H
