#include "EnemyGhost.h"
#include "VideoManager.h"

void EnemyGhost::Init()
{
	Enemy::Init();

	_animations[AN_UP].Init(0, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_UP_RIGHT].Init(32, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_RIGHT].Init(32 * 2, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN_RIGHT].Init(32 * 3, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN].Init(32 * 4, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN_LEFT].Init(32 * 5, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_LEFT].Init(32 * 6, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_UP_LEFT].Init(32 * 7, RECT_WIDTH * 4, RECT_WIDTH, RECT_HEIGHT, 3, 8);

	_currentAnimation = AN_DOWN_RIGHT;

	_position.x = 600;
	_position.y = 400;
}

void EnemyGhost::Update()
{
	Enemy::Update();
}

void EnemyGhost::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
}

EnemyGhost::EnemyGhost()
{
}

EnemyGhost::~EnemyGhost()
{
}


