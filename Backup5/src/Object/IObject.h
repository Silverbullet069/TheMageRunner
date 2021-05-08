#ifndef IOBJECT_H
#define IOBJECT_H
//Interface

class IObject
{
    //Cac phuong thuc' abstruct
    public:
        virtual void Draw() = 0; //Component drawable
        virtual void Update() = 0; //Component updateable
        virtual void Clean() = 0; //Component cleanable
};

#endif // IOBJECT_H
