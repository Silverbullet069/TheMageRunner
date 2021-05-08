#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

//Tao. kieu? du~ lieu. GameMap
class GameMap
{
    public:
        void Render()
        {
            //Render tung` Layer mot^. tu` duoi' cung` len^ tren^ cung`
            for(unsigned int i = 0 ; i < m_MapLayers.size(); ++i)
            {
                m_MapLayers[i]->Render();
            }
        }

        void Update()
        {
            //Update tung` Layer mot^.
            for(unsigned int i = 0 ; i < m_MapLayers.size(); ++i)
            {
                m_MapLayers[i]->Update();
            }
        }

        //Lay' cac' Layer ra de? check Collision
        std::vector<Layer*> GetMapLayers() {return m_MapLayers;}

    private:
        friend class MapParser;
        //MapParser co' the? truy cap^. toi bien' Private trong class nay`

        std::vector<Layer*> m_MapLayers;
        //Trong 1 GameMap, co' cac' Layer, cac' Layer nay` co' the? la` TileLayer, ImageLayer, ...
};

#endif // GAMEMAP_H
