#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "GameObject.h"

/**
    Sau nay`, ObjectFactory se~ su? dung. de? quan' ly' tat^' ca? cac' GameObject
    trong 1 Level duoc. thiet^' ke^' ben^ trong 1 file XML

    ObjectFactory hay o? cho^~ :
    1. Ta k the? new va` init lung tung cac' GameObject* o ben^ trong Engine, ma` ta da~ "cap^' quyen^`"
    quan? ly' cac' GameObject* , chi? co' ObjectFactory moi' co' the? new va init cac' GameObject

    2. Ta lam` rat^' nhieu^` level, moi^~ level duoc. thiet^' ke^' bang cac' file XML, bao gom^` map cua?
    level do' va` du~ lieu^. ve^` tat^' ca? cac' GameObject* ma` trong level do' co'
**/

class ObjectFactory
{
    public:
        static ObjectFactory* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new ObjectFactory();
        }

        //Tao. 1 Object (Entity), dat^. ten^ va` nhap^. thong^ so^' cho no'
        GameObject* CreateObject(std::string type, Properties* props);

        //std::function la` kieu^ du~ lieu^. thay the^' con tro? ham`, ca? doan. cau^ lenh^. ve^' 2nd nghia~ la`,
        //no' nhan^. 1 kieu? du~ lieu^. bat^' ky`, co' kha? nang tra? ve^` GameObject* va` nhan^. props
        //(co' kieu? du~ lieu^. la` Properties) de^? Construct
        //Tuc ngan' gon. la`, ve^' 2nd` co' the^? nhan^. GameObject va` ke' thua` cua? GameObject vao` day^
        //Nhung ma` cach' ta dung` cai' nay`, khong^ truyen^` ve^' 2nd tu` ben^ ngoai`, chi? co' ve^' 1st thoi^
        //ve^' 2nd duoc. new va` construct cung` luc' voi' khi ta truyen^` ve^' 1st vao`
        //Ta khong new va` construct ve^' 2nd o? day^, ma` bang` Constructor trong ham` Registrar

        void RegisterType(std::string className, std::function<GameObject*(Properties* props)> type);

    private:
        ObjectFactory(){}
        static ObjectFactory* s_Instance;
        //Map bao gom^` ten^ cua? class Object, va` con tro? cua? class GameObject, duoc. construct = props.
        std::map<std::string, std::function<GameObject*(Properties* props)>> m_TypeRegistryMap;
};

//Tao. 1 kieu^? du~ lieu^. chung ten^ la` Type
//(thuc. ra sau nay` cai' Type chinh' la` Warrior, Mage, Enemy,... goi. chung la` ke^' thua` cua? GameObject)
//Lop' tong^? quat' la` Registrar, su? dung. kieu^? du~ lieu^. chung la` Type do'
template<class Type>
class Registrar
{
public:
    //Constructor
    Registrar(std::string className)
    {
ObjectFactory::GetInstance()->RegisterType( className, [](Properties* props)->GameObject* {return new Type(props); }   );
    }

};

/** CAI' TEMPLATE NAY` CHINH' XAC' THI` NO' LAM` CAI' GI?

Cai' class Registrar nay`, co' Constructor nhan^. className lam` du~ lieu^. dinh. danh cho m_TypeRegistryMap,

Trong Constructor nay`, goi. toi' doi^' tuong. cua? ObjectFactory (goi. toi' System doc^. nhat^ vo^ nhi.)

Doi^' tuong. nay` goi. toi' ham` RegisterType, truyen^` className vao` va` NHAN^. 1 CON TRO? KIEU^ DU~ LIEU^. TYPE,
DUOC GENERATE (new va` construct = props) theo KIEU^ DU~ LIEU^. TYPE (su? dung. suc' manh. cua? template)

Neu' khong^ dung` template, neu' ta muon^' generate 10 cai' object thi` phai? lam` 10 cai' class Registar
tuong' ung' voi' 10 cai' class ke^' thua` tu` GameObject thi` moi' du?

Ham` nhan^ 2 truong` du~ lieu^., 1 ben^ la` className truyen^` tu` ngoai`, 1 ben^ la` CON TRO? KIEU^ DU~ LIEU^. TYPE

O day^ rat' hop. ly', vi` ta khai' bao' ham` RegisterType nhan^. 1 kieu^? du~ lieu^. tra? ve^` GameObject va`
ke' thua` cua? no' (Type chinh' la` bao gom^` tat^' ca? cha lan~ con)

SO DO^` TAO. 1 GAME OBJECT :

Goi. constructor cua? class Registrar su? dung. kieu^? du~ lieu^. la` Type,
-> Goi. RegisterType truyen^` class Name, tao. 1 con tro? Type va` nhan^. con tro? Type do' vao` ham`
-> add object (con tro? Type) vao` m_TypeRegistryMap theo className

**/


#endif // OBJECTFACTORY_H
