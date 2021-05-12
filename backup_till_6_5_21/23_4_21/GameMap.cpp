#include "GameMap.h"

TileMat::TileMat()
{
   //
}

TileMat::~TileMat()
{
   //
}


GameMap::GameMap()
{
   //
}

GameMap::~GameMap()
{
   //
}

void GameMap::LoadMap(const std::string file_name)
{
   //Khoi tao so luong o toi da theo phuong x va y
   game_map_.max_x_ = 0;
   game_map_.max_y_ = 0;

   std::ifstream file_in;
   file_in.open(file_name.c_str(), std::ios::in);

   if(file_in.is_open()) //Kiem tra mo thanh cong
   {
      //Bat dau chay toan bo file
      //Theo phuong y : 0 => 10
      for(int i = 0 ; i < MAX_MAP_Y && !file_in.eof() ; ++i)
      {
         //Theo phuong x : 0 => 400
         for(int j = 0 ; j < MAX_MAP_X && !file_in.eof() ; ++j)
         {
            file_in >> game_map_.tile[i][j];

            int val = game_map_.tile[i][j]; // 0 1 2 3 ...
            if(val > 0)
            {
               if(j > game_map_.max_x_)
               {
                  //Gioi han so luong o toi da theo phuong x TRONG 1 KHUNG HINH
                  game_map_.max_x_ = j;
               }

               if(i > game_map_.max_y_) //
               {
                  //Gioi han so luong o toi da theo phuong y TRONG 1 KHUNG HINH
                  game_map_.max_y_ = i;
               }
            }
         }
      }

      //+1 la vi max_x_ va max_y_ theo zero-based
      //convert tu so o => pixel
      game_map_.max_x_ = (game_map_.max_x_ + 1)*TILE_SIZE;// 400*64 = 25600
      game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;// 10*64 = 640

      //Khoi tao vi tri bat dau render (thuong la nam ngoai bien trai 1 o)
      //Tinh theo pixel
      game_map_.start_x_ = 0;
      game_map_.start_y_ = 0;

      //Luu lai name cua file map de sau nay dung
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
   //Khoi tao ten cua tung file tiles
   std::string file_img = "";

   //Duyet tat ca cac tiles
   for(int i = 0 ; i < MAX_TILES ; ++i)
   {
      //Gan ten file cua tile
      file_img += std::to_string(i) + ".png";
      //Load anh tile
      bool ret = tile_mat_[i].LoadImg(file_img.c_str(), des);
      if(!ret) { printf("Unable to load tile image number %d", &i);}
      //Set lai ten file mac dinh
      file_img = "";
   }
   file_img.clear();
}

//Fill img vua load duoc vao cac o
void GameMap::DrawMap(SDL_Renderer* des)
{
   //Khoi tao border de fill anh, tinh theo pixel, KHONG PHAI SO O TILES
   int x1 = 0;
   int x2 = 0;

   int y1 = 0;
   int y2 = 0;

   //Khoi tao chi so cua o trong tile map
   int map_x = 0;
   int map_y = 0;

   //Vi tri theo phuong x o tile bat dau render, tinh theo o, KHONG PHAI PIXEL
   map_x = game_map_.start_x_/TILE_SIZE;
   x1 = (game_map_.start_x_%TILE_SIZE)*-1; //start_x_ la bien dong vi bkgn di chuyen
   x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

   //Vi tri theo phuong y o tile bat dau render, tinh theo o, KHONG PHAI PIXEL
   map_y = game_map_.start_y_/TILE_SIZE;
   y1 = (game_map_.start_y_%TILE_SIZE)*-1; //start_y_ la bien dong vi bkgn di chuyen
   y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

   for(int i = y1 ; i < y2 ; i += TILE_SIZE)
   {
      //Set lai vi tri theo phuong x bat dau render, lay PHAN NGUYEN
      //Khong can set lai theo phuong y, vi game di chuyen theo phuong x
      map_x = game_map_.start_x_/TILE_SIZE;

      for(int j = x1 ; j < x2 ; j += TILE_SIZE)
      {
         //Vi tri o thu bao nhieu
         int val = game_map_.tile[map_y][map_x];
         if(val > 0)
         {
            //Thiet lap vi tri cua tung o theo i va j
            tile_mat_[val].SetRect(j, i);
            //Render tung o tuong ung voi val ra man hinh
            tile_mat_[val].Render(des);
         }
         //Sau 1 moi vong, tang them 1 o chi so (sang cot tiep theo)
         map_x++;
      }
      //Tang them 1 o theo phuong y (xuong dong tiep theo)
      map_y++;
   }
}
