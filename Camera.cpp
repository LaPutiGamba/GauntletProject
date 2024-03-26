#include "Camera.h"
#include <iostream>
#include "VideoManager.h"

Camera::Camera()
{
	_x = 0;
	_y = 0;
	_margin = 200;
	_pPlayer = nullptr;
	_left = -30;
	_right = 490;
	_top = 30;
	_down = 540;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	
	int dx = _pPlayer->GetX() - _x;
	int dy = _pPlayer->GetY() - _y;

	if (dx < _margin) 
		_x-= _pPlayer->GetSpeed();
	else if (dx > SCREEN_WIDTH - _margin)
		_x+= _pPlayer->GetSpeed();

	if (dy < _margin)
		_y-= _pPlayer->GetSpeed();
	else if (dy > SCREEN_HEIGHT - _margin)
		_y+= _pPlayer->GetSpeed();


	if (_x < _left)
		_x = _left;
	else if (_x > _right)
		_x = _right;

	if (_y < _top)
		_y = _top;
	else if (_y > _down)
		_y = _down;

	
}
