#pragma once
#include "Scene.h"

/// \class SceneMain
/// \brief Main Scene
class SceneMain : public Scene
{
private:
	class FontManager* _pFontManager; ///< Font manager
	class VideoManager* _pVideoManager; ///< Video manager
	class InputManager* _pInputManager; ///< Input manager
	class SoundManager* _pSoundManager; ///< Sound manager
	class ResourceManager* _pResourceManager; ///< Resource manager
	int _menuID; ///< Menu ID of the texture

public:
	SceneMain();
	~SceneMain();

	/// \brief Init
	void Init() override;

	/// \brief ReInit
	void ReInit() override;

	/// \brief Update
	void Update() override;

	/// \brief Render
	void Render() override;
};