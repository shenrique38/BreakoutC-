#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}


LText * GameManager::scoreText;
LText * GameManager::livesText;
LText * GameManager::finalScoreText;

Mix_Chunk * GameManager::s_ballBounce;
Mix_Chunk * GameManager::S_backgroundM;
Mix_Chunk * GameManager::s_enemyDestroy;

Mix_Chunk * GameManager::s_war_cry;
Mix_Chunk * GameManager::s_thorArrival;
Mix_Chunk * GameManager::s_boatScale;
Mix_Chunk * GameManager::s_eating;

Mix_Chunk * GameManager::s_win;
Mix_Chunk * GameManager::s_lose;

int  GameManager::FrameRate;
int  GameManager::Score;
int  GameManager::lives;
float GameManager::DeltaTime;
int GameManager::enemyCount;
bool GameManager::showFinal;

SDL_Renderer * GameManager::gRenderer;