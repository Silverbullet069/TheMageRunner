#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetsList tileSets)
{
    m_TileSize = tileSize;
    m_RowCount = rowCount;
    m_ColCount = colCount;
    m_Tilemap = tileMap;
    m_Tilesets = tileSets;
}

void TileLayer::Render()
{

}

void TileLayer::Update()
{

}
