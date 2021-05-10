#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "TileMap.h"
#include "Engine.h"

class CollisionHandler
{
    public:
        inline static CollisionHandler* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler();
        }

        bool MapCollision(SDL_Rect a); //Check va cham. giua~ 1 Entity voi' 1 Map
        bool CheckCollision(SDL_Rect a, SDL_Rect b); //Check va cham. giua~ 2 Entity
        void SetCollisionMap(TileMatrix tilematrix, int tilesize); //Set cac' thong^ so^' check va cham. 1 TileMap cu. the^?

    private:
        CollisionHandler();
        static CollisionHandler* s_Instance;

        int m_MapTileSize;
        int m_MapHeight;
        int m_MapWidth;

        TileMatrix m_CollisionTileMatrix; //1 vector 2 chieu` luu cac' tileID cua? TileLayer tren^ cung`
        TileLayer* m_CollisionLayer; //Kiem? tra tat' ca? cac' TileLayer trong 1 Map roi` lay' TileLayer* tren^ cung`

};

#endif // COLLISIONHANDLER_H
