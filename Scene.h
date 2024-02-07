#pragma once

//! Scene class
/*!
	Handles the Scenes for all the game.
*/
class Scene
{
	public:
		//! Constructor of an empty Scene.
		Scene();

		//! Destructor
		virtual ~Scene();

		//! Initializes the Scene.
		virtual void Init();

		//! Function to withdraw anything owned by the class and to call init
		virtual void ReInit();

		//! Handles the updating of the scene
		virtual void Update() = 0;

		//! Handles the drawing of the scene
		virtual void Render() = 0;

		void SetReInit(bool loaded = true) { _reInit = loaded; };
		bool MustReInit() { return _reInit; };

	protected:
		bool _reInit; // Reload when returning to scene
};