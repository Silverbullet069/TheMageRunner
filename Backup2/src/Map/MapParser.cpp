#include "MapParser.h"

bool MapParser::Load()
{
    return Parse("level1", "resource/maps/map01.tmx"));
}

void MapParser::Clean()
{

}

GameMap* MapParser::GetMaps()
{

}

bool MapParser::Parse(std::string id, std::string source)
{

}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{

}

TileLayer MapParser::ParseTileLayer(TiXmlElement* xmlTileLayer, TileSetsList, int tileSize, int rowCount, int colCount)
{

}

MapParser::MapParser()
{

}
