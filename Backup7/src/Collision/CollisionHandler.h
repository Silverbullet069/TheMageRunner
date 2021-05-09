#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"

class CollisionHandler
{
    public:
        inline static CollisionHandler* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler();
        }

        bool CheckCollision(SDL_Rect a, SDL_Rect b); //Check va cham. giua~ 2 Entity
        bool MapCollision(SDL_Rect a); //Check va cham. giua~ 1 Entity voi' 1 Map

    private:
        CollisionHandler();
        static CollisionHandler* s_Instance;

        TileMap m_CollisionTileMap; //1 vector 2 chieu` luu cac' tileID cua? TileLayer tren^ cung`
        TileLayer* m_CollisionLayer; //Kiem? tra tat' ca? cac' TileLayer trong 1 Map roi` lay' TileLayer* tren^ cung`

};

#endif // COLLISIONHANDLER_H
