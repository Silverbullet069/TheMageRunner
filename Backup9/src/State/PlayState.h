#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <iostream>
#include "TileMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Timer.h"
#include "GameState.h"
#include "Input.h"
#include "Camera.h"
#include "MapParser.h"
#include "ImgLayer.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"

class PlayState : public GameState
{
    public:
        PlayState(){};

        virtual bool IsInit();
        virtual bool IsExit();

        virtual void Update();
        virtual void Render();

        virtual void Events();

        virtual inline std::string GetStateID() const {return m_PlayID;}
        //inline TileMap* GetMap() { return m_LevelMap; }

    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        static const std::string m_PlayID;
        TileMap* m_LevelMap;
        std::vector<ImgLayer*> m_ParallexBkg;
        std::vector<GameObject*> m_GameObjects;
};

#endif // PLAYSTATE_H
