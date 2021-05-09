
#include "ObjectFactory.h"
#include "Warrior.h"
#include "Enemy.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

GameObject* ObjectFactory::CreateObject(std::string type, Properties* props)
{
    //Duyet^. toan` bo^. m_TypeRegistryMap

    GameObject* object = nullptr;
    auto it = m_TypeRegistryMap.find(type);

    if(it != m_TypeRegistryMap.end())
        object = it->second(props);
    else
    {
        //
    }

    return object;
}


void ObjectFactory::RegisterType(std::string className, std::function<GameObject*(Properties* props)> type)
{
    //Gan' con tro? kieu? du~ lieu^. Type do' tuong' ung' voi ID la` className
    m_TypeRegistryMap[className] = type;
}
