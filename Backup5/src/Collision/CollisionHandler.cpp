#include "CollisionHandler.h"
#include "Engine.h"
#include "Config.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().front();
    m_CollisionTileMap = m_CollisionLayer->GetTileMap();


    /** GIAI THICH : VE^` CU' PHAP' CONTRUCT m_CollisionLayer
    Ta dang muon^' gan' TileLayer TREN^ CUNG` cua? 1 GameMap vao` m_CollisionLayer, co' 2 cong^ viec^. :

    1. Lay' cac' TileLayer* ra khoi? cac' Layer*
    trong GameMap, dinh. dang. kieu^? du~ lieu^ la` 1 vector gom^` cac' LAYER, bao gom^` TileLayer, ImageLayer, ...vv
    neu' khong^' co' dau' (), he^. thong' se~ co' the^? nhan^. Layer lung tung, co' the? nhan^. nham` TileImage,
    kha' la` nguy hiem^? nen^ phai? chu' y' vi` o? day^ ta chi? xet' toi' cac TileLayer

    2. Sau khi lay^' cac' TileLayer*, ta phai? lay^' TileLayer* TREN^ CUNG`, dung` .back() **/
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlays = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlays = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlays && y_overlays);
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int TileSize = TILE_SIZE;
    int RowCount = TILE_MAP_ROW_COUNT;
    int ColCount = TILE_MAP_COL_COUNT;

    int left_tile = a.x/TileSize;
    int right_tile = (a.x + a.w)/TileSize;

    int top_tile = a.y/TileSize;
    int bottom_tile = (a.y + a.h)/TileSize;

    if(left_tile < 0) left_tile = 0;
    if(right_tile > ColCount) right_tile = ColCount;

    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > RowCount) bottom_tile = RowCount;

    for(int i = left_tile; i <= right_tile; ++i)
    {
        for(int j = top_tile ; j <= bottom_tile ; ++j)
        {
            if(m_CollisionTileMap[j][i] > 0)
                return true;
        }
    }

    return false;
}

