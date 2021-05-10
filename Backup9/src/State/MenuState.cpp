#include "MenuState.h"
#include "PlayState.h"
#include "Engine.h"
#include "Input.h"

const std::string MenuState::m_MenuID = "MENU";

bool MenuState::IsInit()
{
    SDL_Log("Menu Initialized !\n");
    return true;
}

bool MenuState::IsExit()
{
    SDL_Log("Menu Exit !\n");
    return true;
}

void MenuState::Render()
{
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 128, 128, 128, 255);
    SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}

void MenuState::Update()
{
    //
}

void MenuState::Events()
{
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN) == true)
    {
        GameStateManager::GetInstance()->ChangeState(new PlayState());
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Q) == true)
    {
        Engine::GetInstance()->Quit();
    }
}

void MenuState::StartGame()
{
    std::cout << "Start game!\n";
}

void MenuState::Editor()
{
    std::cout << "Editor mode!\n";
}

void MenuState::Settings()
{
    std::cout << "Settings mode!\n";
}

void MenuState::Quit()
{
    std::cout << "Quit mode!\n";
}


