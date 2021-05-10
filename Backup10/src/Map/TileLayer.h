#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>

//Tao. kieu? du~ lieu TileSet
struct TileSet
{
    int FirstID;
    int LastID;
    int RowCount;
    int ColCount;
    int TileCount;
    int TileSize;
    std::string Name;
    std::string Source; //Ten^ cua? file CSV | XML
};

//Tao. kieu? du~ lieu (vector cac' TileSet) ten^ la` TileSetLists
using TileSetsList = std::vector<TileSet> ;

//Tao. kieu? du~ lieu (vector int 2 chieu`) ten^ la` TileMatrix
using TileMatrix = std::vector<std::vector<int> >; //Luu y: phai co' dau' cach' o day^

//Tao. kieu? du~ lieu TileLayer, ke' thua` tu Layer
//=>Chi dung` de tru~ TileLayer, khac' voi ImageLayer, ObjectLayer...
class TileLayer : public Layer
{
    public:
        TileLayer(int tileSize, int rowCount, int colCount, TileMatrix tileMatrix, TileSetsList tileSets);

        //Bat' dau` implement cac' abstruct method
        virtual void Render();
        virtual void Update();

        inline int GetTileSize() {return m_TileSize;}
        inline int GetWidth() {return m_ColCount;}
        inline int GetHeight() {return m_RowCount;}

        //Get vector 2 chieu` danh sach' ID trong 1 TileSet
        inline TileMatrix GetTileMatrix() const {return m_Tilematrix; }

    private:
        // 1 TileLayer gom` co' cac' du~ lieu sau day^
        int m_TileSize; //Kich' thuoc' cua? 1 o^ tile
        int m_RowCount; //Tong? so' hang` trong 1 TileLayer (LUU Y : la` cua? TILE LAYER, chu' cua? KHONG PHAI SCREEN WIDTH)
        int m_ColCount; //Tong? so' cot^. trong 1 TileLayer (LUU Y : cung~ la` cua? TILE LAYER, chu' cua? KHONG PHAI SCREEN WIDTH)
        TileMatrix m_Tilematrix;
        /** 1 vector 2 chieu` luu ID cua cac' tile khac' nhau.tuong ung' voi' Layer do'**/

        TileSetsList m_Tilesets;
        /** 1 vector 1 chieu` luu cac' TileSet khac' nhau duoc' sap' xep'
        theo thu' tu. chong` len^ nhau trong 1 TileLayer **/

};

#endif // TILELAYER_H
