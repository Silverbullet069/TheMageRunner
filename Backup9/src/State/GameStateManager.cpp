#include "GameStateManager.h"

GameStateManager* GameStateManager::s_Instance = nullptr;

void GameStateManager::PushState(GameState* state)
{
    m_GameStates.push_back(state);
    m_GameStates.back()->IsInit();
}

void GameStateManager::ChangeState(GameState* state)
{
    if(m_GameStates.empty() == false)
    {
        if(m_GameStates.back()->GetStateID() == state->GetStateID())
        {
            return;
        }
        m_GameStates.back()->IsExit();
        m_GameStates.pop_back();
    }

    m_GameStates.push_back(state);
    m_GameStates.back()->IsInit();

}

void GameStateManager::PopState()
{
    //Pop the current state
    if(m_GameStates.empty() == false)
    {
        if(m_GameStates.back()->IsExit() == true)
        {
            m_GameStates.erase(m_GameStates.end() - 2);
        }
    }
}

void GameStateManager::Update()
{
    if(m_GameStates.empty() == false)
    {
        m_GameStates.back()->Update();
    }
}

void GameStateManager::Render()
{
    if(m_GameStates.empty() == false)
    {
        m_GameStates.back()->Render();
    }
}

void GameStateManager::Events()
{
    if(m_GameStates.empty() == false)
    {
        m_GameStates.back()->Events();
    }
}
