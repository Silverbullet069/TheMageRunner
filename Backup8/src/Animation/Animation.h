#ifndef ANIMATION_H
#define ANIMATION_H

//Abstruct class
class Animation
{
    public:
        Animation(bool repeat = true) : m_Repeat(repeat), m_CurrentFrame(0) { m_IsEnded = false; }
        virtual void Update() = 0;
        inline bool IsEnded() {return m_IsEnded;}

    protected:
        bool m_Repeat; //Flag kiem? tra animation cua? entity se~ loop lien^ tuc.
        bool m_IsEnded; //Flag kiem? tra da~ chay. het^' 1 vong` animation chua?
        int m_CurrentFrame; //Frame index hien^. tai. cua? nhan^ vat^. quan? ly' boi? ham` Update
};

#endif // ANIMATION_H
