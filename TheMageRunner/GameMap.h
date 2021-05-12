
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

//Khai bao kieu du lieu Map
struct Map
{
   int start_x_; //Luu vi tri mep tren ben trai ban do phuong x
   int start_y_; //Luu vi tri mep tren ben trai ban do phuong y
   int max_x_; //So luong o toi da theo phuong x
   int max_y_; //So luong o toi da theo phuong y
   int tile[MAX_MAP_Y][MAX_MAP_X]; //Gia tri cua tung o tile theo toa do[y][x]
   std::string file_name_; //Ten cua file .txt tile map
};

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

   void set_is_size_screen(const bool& flag) { is_size_screen_ = flag; }
   bool get_is_size_screen() const { return is_size_screen_; }

private:
   Map game_map_;
   TileMat tile_mat_[MAX_TILES];
   bool is_size_screen_;

};

#endif // GAME_MAP_H_H
