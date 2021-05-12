#include "GameMap.h"

void GameMap::LoadMap(const std::string file_name)
{
   game_map_.max_x_ = 0;
   game_map_.max_y_ = 0;

   ifstream file_in;
   file_in.open(file_name.c_str(), ios::in);

   if(file_in.is_open()) //Kiem tra mo thanh cong
   {
      //Chay toan bo file (0 => 10)
      for(int i = 0 ; i < MAX_MAP_Y && !file_in.eof() ; ++i)
      {
         //(0 => 400)
         for(int j = 0 ; j < MAX_MAP_X && !file_in.eof() ; ++j)
         {
            file_in >> game_map_.tile[i][j];

            int val = game_map_.tile[i][j];
            if(val > 0) // 1 2 3 ...
            {
               if(j > game_map_.max_x_) //
               {
                  game_map_.max_x_ = j;
               }

               if(i > game_map_.max_y_)
               {
                  game_map_.max_y_ = i;
               }
            }
         }
      }

      game_map_.max_x_ = (game_map_.max_x_ + 1)*TILE_SIZE;
      game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;

      game_map_.start_x_ = 0;
      game_map_.start_y_ = 0;

      game_map_.file_name_ = file_name;
   }
   else
   {
      printf("Can't open file!");
   }
   file_in.close();
}

//Load img cho tung tam anh tuong ung
void GameMap::LoadTiles(SDL_Renderer* des)
{
   std::string file_img = "";

   for(int i = 0 ; i < MAX_TILES ; ++i)
   {
      //Gan ten file cua tile
      file_img += to_string(i) + ".png";
      //Load anh
      bool ret = tile_mat[i].LoadImg(file_img.c_str(), des);
      if(!ret) { printf("Unable to load %s", &file_img.c_str());}
      //Set lai ten file mac dinh
      file_img = "";
   }
   file_img.clear();
}

//Fill img vua load duoc vao cac o
void GameMap::DrawMap(SDL_Renderer* des)
{
   //Fill anh
   int x1 = 0;
   int x2 = 0;

   int y1 = 0;
   int y2 = 0;

   //Chi so cua o trong tile map
   int map_x = 0;
   int map_y = 0;

   map_x = game_map_.start_x_/TILE_SIZE;
   x1 = (game_map_.start_x_%TILE_SIZE)*-1;
   x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

   map_y = game_map_.start_y_/TILE_SIZE;
   y1 = (game_map_.start_y_%TILE_SIZE)*-1;
   y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

   for(int i = y1 ; i < y2 ; i += TILE_SIZE)
   {
      map_x = game_map_.start_x_/TILE_SIZE;
      for(int j = x1 ; j < x2 ; j += TILE_SIZE)
      {
         //Vi tri o thu bao nhieu
         int val = game_map_.tile[map_y][map_x];
         if(val > 0)
         {
            tile_mat[val].SetRect(j, i);
            tile_mat[val].Render(des);
         }
         //Sau 1 moi vong, tang them 1 o chi so
         map_x_++;
      }
      map_y_++;
   }
}
