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

//Tao. kieu? du~ lieu (vector int 2 chieu`) ten^ la` TileMap
using TileMap = std::vector<std::vector<int> >; //Luu y: phai co' dau' cach' o day^

//Tao. kieu? du~ lieu TileLayer, ke' thua` tu Layer
//=>Chi dung` de tru~ TileLayer, khac' voi ImageLayer, ObjectLayer...
class TileLayer : public Layer
{
    public:
        TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetsList tileSets);

        //Bat' dau` implement cac' abstruct method
        virtual void Render();
        virtual void Update();

        //Get danh sach' ID trong 1 TileSet
        inline TileMap GetTileMap() const {return m_Tilemap; }


    private:
        // 1 TileLayer gom` co' cac' du~ lieu sau day^
        int m_TileSize; //Kich' thuoc' cua? 1 o^ tile
        int m_RowCount; //Tong? so' hang` trong 1 TileLayer
        int m_ColCount; //Tong? so' cot^. trong 1 TileLayer
        TileMap m_Tilemap;
        /** 1 vector 2 chieu` luu ID cua cac' tile khac' nhau.tuong ung' voi' Layer do'**/

        TileSetsList m_Tilesets;
        /** 1 vector 1 chieu` luu cac' TileSet khac' nhau duoc' sap' xep'
        theo thu' tu. chong` len^ nhau trong 1 TileLayer **/

};

#endif // TILELAYER_H
