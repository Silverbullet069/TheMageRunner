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
   is_size_screen_ = false;
}

GameMap::~GameMap()
{
   //
}

void GameMap::LoadMap(const std::string file_name)
{
   //Tinh theo pixel
   game_map_.start_x_ = 0;
   game_map_.start_y_ = 0;

   //Khoi tao so luong o toi da theo phuong x va y
   game_map_.max_x_ = 0;
   game_map_.max_y_ = 0;

   if(is_size_screen_ == true)
   {
      game_map_.max_x_ = MAX_MAP_X_SCREEN; // 20
      game_map_.max_y_ = MAX_MAP_Y_SCREEN; // 12
   }
   else //scroll map
   {
      game_map_.max_x_ = MAX_MAP_X; // 100
      game_map_.max_y_ = MAX_MAP_Y; // 12
   }

   //convert tu` so' o^ tiles sang pixel
   game_map_.max_x_ *= TILE_SIZE;
   game_map_.max_y_ *= TILE_SIZE;

   //Luu lai name cua file map de sau nay dung
   game_map_.file_name_ = file_name;

   std::ifstream file_in;
   file_in.open(file_name.c_str(), std::ios::in);

   if(file_in.is_open())
   {
      //Bat dau chay toan bo file
      //Theo phuong y
      for(int i = 0 ; i < MAX_MAP_Y && !file_in.eof() ; ++i)
      {
         //Theo phuong x
         for(int j = 0 ; j < MAX_MAP_X && !file_in.eof() ; ++j)
         {
            if(is_size_screen_ == true)
            {
               if(j >= MAX_MAP_X_SCREEN)
               {
                  break;
               }
            }

            file_in >> game_map_.tile[i][j];
         }
      }
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
   std::string file_img = g_name_tile_directory;

   //Duyet tat ca cac tiles
   for(int i = 0 ; i < MAX_TILES ; ++i)
   {
      //Gan ten file cua tile (ex : 1.png, 2.png)
      file_img += std::to_string(i) + ".png";
      //Load anh tile
      bool ret = tile_mat_[i].LoadImg(file_img.c_str(), des, SDL_FALSE, WHITE);
      if(!ret) { printf("Unable to load tile image number %d", i);}
      //Set lai ten file mac dinh
      file_img = g_name_tile_directory;
   }
   file_img.clear();
}

//Fill img vua load duoc vao cac o
void GameMap::DrawMap(SDL_Renderer* des)
{
   //Khoi tao border de fill anh, TINH THEO PIXEL
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

   //LUU Y: Vong` lap. chi? tile map TRONG 1 KHUNG HINH, chu khong phai la` IN TOAN BO TILE MAP
   for(int i = y1 ; i < y2 ; i += TILE_SIZE)
   {
      //Set lai vi tri theo phuong x bat dau render, lay PHAN NGUYEN
      //Khong can set lai theo phuong y, vi game di chuyen theo phuong x
      map_x = game_map_.start_x_/TILE_SIZE;

      for(int j = x1 ; j < x2 ; j += TILE_SIZE)
      {
         //Vi tri o thu bao nhieu
         int val = game_map_.tile[map_y][map_x];

         //Khong phai tile rong~
         if(val != BLANK_TILE)
         {
            //Thiet lap vi tri cua tung o theo i va j
            tile_mat_[val].SetRect(j, i);
            //Render tung o tuong ung voi val ra man hinh
            tile_mat_[val].Render(des);

            //Xu ly' animation cua? SPELL_BOOK
            if(SPELL_BOOK <= val && val <= SPELL_BOOK + SPELL_BOOK_FRAME - 1) //25 => 28
            {
                static int count_fr = 0;
                if(count_fr < SPELL_BOOK_FRAME)
                {
                    count_fr++;
                }
                else
                {
                    game_map_.tile[map_y][map_x]++;
                    count_fr = 0;
                }

                if(game_map_.tile[map_y][map_x] == SPELL_BOOK + SPELL_BOOK_FRAME) //29
                {
                    game_map_.tile[map_y][map_x] = SPELL_BOOK; //=> 25
                }
            }

            //Xu ly' animation cua? COIN
            if(GOLD_COIN <= val && val <= GOLD_COIN + GOLD_COIN_FRAME - 1) //55 => 58
            {
                static int count_fr = 0;
                if(count_fr < GOLD_COIN_FRAME)
                {
                    count_fr++;
                }
                else
                {
                    game_map_.tile[map_y][map_x]++;
                    count_fr = 0;
                }

                if(game_map_.tile[map_y][map_x] == GOLD_COIN + GOLD_COIN_FRAME) //59
                {
                    game_map_.tile[map_y][map_x] = GOLD_COIN; //=> 25
                }
            }

         }
         //Sau 1 moi vong, tang them 1 o chi so (sang cot tiep theo)
         map_x++;
      }
      //Tang them 1 o theo phuong y (xuong dong tiep theo)
      map_y++;
   }
}
