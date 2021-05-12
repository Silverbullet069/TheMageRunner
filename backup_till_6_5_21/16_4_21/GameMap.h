
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "Common_Function.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMat : public BaseObject
{
public:
   TileMat();
   ~TileMat();
};

class GameMap
{
public:
   GameMap();
   ~GameMap();

   void LoadMap(const std::string file_name);
   void LoadTiles(SDL_Renderer* des);
   void DrawMap(SDL_Renderer* des);

private:
   Map game_map_;
   TileMat tile_mat_[MAX_TILES];

};

#endif // GAME_MAP_H_H
