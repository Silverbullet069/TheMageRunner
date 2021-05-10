
#include "IntroState.h"
#include "Engine.h"
#include "Input.h"

const std::string IntroState::m_IntroID = "INTRO";

bool IntroState::IsInit()
{
    SDL_Log("Intro Initialized !\n");





    return true;
}

bool IntroState::IsExit()
{
    SDL_Log("Intro Exit !\n");
    return true;
}

void IntroState::Render()
{
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 128, 128, 128, 255);
    SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}

void IntroState::Update()
{
    //
}

void IntroState::Events()
{
    //
}


