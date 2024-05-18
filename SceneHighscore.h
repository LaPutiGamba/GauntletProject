#pragma once
#include "Scene.h"
#include <vector>
#include <string>

/// \class SceneHighscore
/// \brief Scene for the highscore
class SceneHighscore : public Scene
{
private:
	std::vector<std::string> _scoreList; ///< List of names ordered
	class FontManager* _pFontManager; ///< Font manager
	class VideoManager* _pVideoManager; ///< Video manager
	class InputManager* _pInputManager; ///< Input manager

	/// \brief Read the score
	void ReadScore();

public:
	SceneHighscore();
	~SceneHighscore();

	/// \brief Init
	void Init() override;

	/// \brief ReInit
	void ReInit() override;

	/// \brief Update
	void Update() override;

	/// \brief Render
	void Render() override;
};