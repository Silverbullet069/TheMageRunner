#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Layer.h"

//Tao. kieu? du~ lieu. GameMap
class TileMap
{
    public:
        TileMap(){}

        void Render()
        {
            //Render tung` Layer mot^. tu` duoi' cung` len^ tren^ cung`
            for(auto layer : m_MapLayers)
                layer->Render();
        }

        void Update()
        {
            //Update tung` Layer mot^.
            for(auto layer : m_MapLayers)
                layer->Update();
        }

        void Clean()
        {
            for(auto layer : m_MapLayers)
                delete layer;
            m_MapLayers.clear();
        }

        //Lay' cac' Layer ra de? check Collision
        std::vector<Layer*> GetLayers() {return m_MapLayers;}

    private:
        //MapParser co' the? truy cap^. toi bien' Private trong class nay`
        friend class MapParser;

        //Trong 1 GameMap, co' cac' Layer, cac' Layer nay` co' the? la` TileLayer, ImageLayer, ...
        std::vector<Layer*> m_MapLayers;
};

#endif // TILEMAP_H
