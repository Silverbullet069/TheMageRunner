#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "GameState.h"

class GameStateManager
{
    public:
        void Update();
        void Render();

        void PushState(GameState* state);
        void ChangeState(GameState* state);
        void PopState();

        void Events();

        inline static GameStateManager* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new GameStateManager();
        }

        inline std::vector<GameState*> GetGameStates() { return m_GameStates; }

    private:
        GameStateManager(){};
        static GameStateManager* s_Instance;

        std::vector<GameState*> m_GameStates;
};

#endif // GAMESTATEMANAGER_H
