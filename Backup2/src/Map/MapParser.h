#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

//Tao. system MapParser de? doc. cac' GameMap
class MapParser
{
    public:
        inline static MapParser* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();
        }

        bool Load();
        void Clean();
        inline GameMap* GetMaps();

    private:
        bool Parse(std::string id, std::string source);
        TileSet ParseTileSet(TiXmlElement* xmlTileSet);
        TileLayer ParseTileLayer(TiXmlElement* xmlTileLayer, TileSetsList,
                                 int tileSize, int rowCount, int colCount)


    private:
        MapParser();
        static MapParser* s_Instance;
        std::map<std::string, GameMap*> m_MapDict;
        //map nay` gom` ten^ va` GameMap ung' voi' ten^ do'
        //Trong 1 GameMap co' cac' TileLayer
        //Trong 1 TileLayer co' ID cua? cac' tile khac' nhau trong 1 TileSet. (vector 2 chieu`)
        //Dong` thoi`, trong 1 TileLayer cung~ co' cac' TileSet khac' nhau.
        //Trong 1 TileSet co' cac' du~ lieu^. can` thiet' de? truyen` vao TileLayer.
        //Cuoi' cung` implement cac' method cua GameMap.
        //Cac' method cua? GameMap lai. implement cac' abstruct method cua Layer.
        //Cac' abstruct method cua Layer lai...
};

#endif // MAPPARSER_H
