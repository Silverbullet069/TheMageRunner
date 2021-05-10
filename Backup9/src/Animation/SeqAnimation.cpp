
#include <iostream>
#include "SeqAnimation.h"
#include "TextureManager.h"
#include "tinyxml.h"

SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat){}

void SeqAnimation::DrawAnime(float x, float y, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->Draw(m_CurrentSeq.TextureIDs[m_CurrentFrame],
                                        x, y, m_CurrentSeq.Width, m_CurrentSeq.Height, flip);
    /** LUU Y : Draw, chu' k phai? DrawFrame, ta k phai? la` in tung` frame trong 1 sprite, ma` la`
    in cai' frame co' index = m_CurrentFrame, cung~ chinh' la` ID cua? frame do' trong chuoi~ ID duoc^. lay' tu`
    file XML, duoc. quan? ly' boi? vector string TextureIDs trong Sequence **/
}

void SeqAnimation::Update()
{
    //SDL_Log("%d\n", m_CurrentFrame);
    //Nv chay.^ lien^ tuc. animation va` animation do' chua? ket^' thuc'
    if(m_Repeat == true || m_IsEnded == false)
    {
        m_IsEnded = false; //Van^~ cho animation do' chua? ket^' thuc'
        m_CurrentFrame = (SDL_GetTicks()/m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
    }
    //Vay^. thi` neu' frame hien^. tai. cua? nv = frame cuoi' cung` (-1 vi`theo zero-based indexing)
    //Dong^` thoi` nv co' flag animation k con` chay. lien^ tuc. nua~
    if(m_Repeat == false && m_CurrentFrame == (m_CurrentSeq.FrameCount - 1))
    {
        m_IsEnded = true; //Flag animation do' ket^' thuc' = true
        m_CurrentFrame = (m_CurrentSeq.FrameCount - 1); //Cho frame hien^. tai. = frame cuoi' cung` cua? no'
    }
}

void SeqAnimation::SetCurrentSeq(std::string seqID)
{
    //Kiem? tra trong m_SeqMap co' ton` tai. Seq co' seqID tuong ung' ma` ta dang can^` dung`
    if(m_SeqMap.count(seqID) > 0)
    {
        m_CurrentSeq = m_SeqMap[seqID]; //Set m_CurrentSeq theo seq co' seqID tuong ung'
    }
    else
    {
        std::cout << "The given sequence animation is not matching: " << seqID << std::endl;
    }
}

void SeqAnimation::Parse(std::string source)
{
    //Load file XML chua' toan` bo^. thong^ so' cua? 1 Sequence
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        std::cout << "Failed to load animation xml file : " << source << std::endl;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement() ; e != nullptr ; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("sequence"))
        {
            Sequence seq;
            std::string seqID = e->Attribute("id"); //lay^' id cua? Sequence
            e->Attribute("speed", &seq.Speed); //lay' speed, hay thoi` gian giua~ 2 frame trong 1 Sequence
            e->Attribute("width", &seq.Width); //lay' chieu` dai` frame
            e->Attribute("height", &seq.Height); //lay' chieu` cao frame
            e->Attribute("frameCount", &seq.FrameCount); //Lay' tong? so^' frame trong 1 Sequence (zero-based indexing)
            for(TiXmlElement* frame = e->FirstChildElement(); frame != nullptr ; frame=frame->NextSiblingElement())
            {
                seq.TextureIDs.push_back(frame->Attribute("textureID"));
                m_SeqMap[seqID] = seq;
            }
        }
    }
}

