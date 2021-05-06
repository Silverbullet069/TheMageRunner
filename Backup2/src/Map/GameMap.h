#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

//Tao. kieu? du~ lieu. GameMap
class GameMap
{
    public:
        GameMap() {}
        void Render()
        {
            //Render tung` Layer mot^. ra man` hinh`
            for(unsigned int i = 0 ; i < m_MapLayers.size(); ++i)
            {
                m_MapLayers[i]->Update();
            }
        }

        void Update()
        {
            //Update tung` Layer mot^.
            for(unsigned int i = 0 ; i < m_MapLayers.size(); ++i)
            {
                m_MapLayers[i]->Render();
            }
        }

        //Lay' cac' Layer ra de? check Collision
        std::vector<Layer*> GetMapLayers() {return m_MapLayers;}

    private:
        std::vector<Layer*> m_MapLayers; //Trong 1 GameMap, co' cac' Layer
};

#endif // GAMEMAP_H
