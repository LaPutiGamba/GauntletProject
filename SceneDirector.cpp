#include "SceneDirector.h"
#include "SceneMain.h"
#include "SceneOptions.h"
#include "SceneGame.h"
#include "SceneHighscore.h"
#include "SceneGameOver.h"

SceneDirector* SceneDirector::_pInstance = NULL;

SceneDirector::SceneDirector() 
{
	Init();
}

SceneDirector::~SceneDirector() 
{
}

void SceneDirector::Init() 
{
	_vectorScenes.resize(NUM_SCENES);

	SceneMain* main	= new SceneMain();
	SceneOptions* options = new SceneOptions();
	SceneHighscore* highscore = new SceneHighscore();
	SceneGame* game	= new SceneGame();
	SceneGameOver *gameOver	= new SceneGameOver();

	_vectorScenes[MAIN] = main;
	_vectorScenes[OPTIONS] = options;
	_vectorScenes[HIGHSCORE] = highscore;
	_vectorScenes[GAME] = game;
	_vectorScenes[GAMEOVER] = gameOver;

	main->Init();
	options->Init();
	highscore->Init();
	game->Init();
	gameOver->Init();

	_currentScene = MAIN;
}

void SceneDirector::ChangeScene(SceneEnum nextScene, bool reInit) 
{
	_vectorScenes[nextScene]->SetReInit(reInit);
	_currentScene = nextScene;
}
