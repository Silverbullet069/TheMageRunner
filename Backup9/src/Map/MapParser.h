#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "TileMap.h"
#include "TileLayer.h"
//Ham` nay` sau se~ tu. viet' lai.
#include "TxtReader.h"
//Su dung. thu vien^. mo rong^. de doc. file XML
#include "tinyxml.h"

//Tao. system MapParser de? doc. cac' GameMap
class MapParser
{
    public:
        inline static MapParser* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();
        }

        bool Parse(std::string id, std::string source);
        void Clean();
        inline TileMap* GetMap(std::string id) { return m_MapDict[id]; }

    private:

    /** TiXmlElement* dong' vai tro` nhu? la` 1 Node,
    luu du~ lieu^. cua? Element dang duoc. tro? toi'
    va` ca? con tro? de? tro? toi' Element tiep' theo **/

        TileSet ParseTileSet(TiXmlElement* xmlTileSet);
        TileLayer* ParseTileLayer(TiXmlElement* xmlTileLayer, TileSetsList tileSets,
                                 int tileSize, int rowCount, int colCount);


    private:
        MapParser(){};
        static MapParser* s_Instance;
        std::map<std::string, TileMap*> m_MapDict;
        //map nay` gom` ten^ va` GameMap ung' voi' ten^ do'
        //Trong 1 TileMap co' cac' TileLayer
        //Trong 1 TileLayer co' ID cua? cac' tile khac' nhau trong cac' TileSet khac' nhau.
        //TileLayer cung~ co' 1 bien' TileSetsList quan? ly' cac' TileSet khac' nhau do'.
        //Cuoi' cung` implement cac' method cua GameMap.
        //Cac' method cua? GameMap lai. implement cac' abstruct method cua Layer.
        //Cac' abstruct method cua Layer lai implement cua? TileLayer, ImageLayer, vv ...
};

#endif // MAPPARSER_H
