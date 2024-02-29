#pragma once

/// \class Scene
/// \brief Base class for all scenes
class Scene
{
protected:
	bool _reInit; ///< Reload when returning to scene

public:
	Scene();
	virtual ~Scene();

	/// \brief Init
	virtual void Init();

	/// \brief ReInit
	virtual void ReInit();

	/// \brief Update
	virtual void Update() = 0;

	/// \brief Render
	virtual void Render() = 0;

	/// \brief SetReInit
	void SetReInit(bool loaded = true) { _reInit = loaded; };

	/// \brief MustReInit
	bool MustReInit() { return _reInit; };
};