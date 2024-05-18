#pragma once
#include "Player.h"

class Camera
{
private:
	int _x; ///< The x position of the camera
	int _y; ///< The y position of the camera
	int _margin; ///< The margin around the player that the camera will move
	Player* _pPlayer; ///< The player that the camera will follow
	int _left; ///< The left position of the camera
	int _top; ///< The top position of the camera
	int _right; ///< The right position of the camera
	int _down; ///< The down position of the camera

public:
	Camera();
	~Camera();

	/// \brief Get the x position of the camera
	/// \return The x position of the camera
	int GetX() { return _x; }

	/// \brief Set the x position of the camera
	/// \param x The x position of the camera
	void SetX(int x) { _x = x; }

	/// \brief Get the y position of the camera
	/// \return The y position of the camera
	int GetY() { return _y; }

	/// \brief Set the y position of the camera
	/// \param y The y position of the camera
	void SetY(int y) { _y = y; }

	/// \brief Set the player that the camera will follow
	void SetPlayer(Player* player) { _pPlayer = player; }

	/// \brief Update the camera position
	void Update();
};

