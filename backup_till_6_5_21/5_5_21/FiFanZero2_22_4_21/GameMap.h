
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

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
   Map GetMap() const {return game_map_;}
   void SetMap(const Map& map_data) {game_map_ = map_data;}

private:
   Map game_map_;
   TileMat tile_mat_[MAX_TILES];

};

#endif // GAME_MAP_H_H
