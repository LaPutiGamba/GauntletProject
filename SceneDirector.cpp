#include "SceneDirector.h"
#include "SceneMain.h"
#include "SceneOptions.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
//#include "SceneSaveLoad.h"
//#include "SceneIntro.h"
//#include "SceneGameOver.h"

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
	//SceneSaveLoad *save	= new SceneSaveLoad();
	//SceneIntro *intro = new SceneIntro();
	SceneGame* game	= new SceneGame();
	SceneGameOver *gameOver	= new SceneGameOver();

	_vectorScenes[MAIN] = main;
	_vectorScenes[OPTIONS] = options;
	//_vectorScenes[SAVE_LOAD] = save;
	//_vectorScenes[INTRO] = intro;
	_vectorScenes[GAME] = game;
	_vectorScenes[GAMEOVER] = gameOver;

	main->Init();
	options->Init();
	//save->init();
	//config->init();
	//intro->init();
	game->Init();
	gameOver->Init();

	_currentScene = MAIN;
}

void SceneDirector::ChangeScene(SceneEnum nextScene, bool reInit) 
{
	_vectorScenes[nextScene]->SetReInit(reInit);
	_currentScene = nextScene;
}
