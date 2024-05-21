#pragma once
#include "Scene.h"

class SceneWin : public Scene
{
    int _winID;

public:
    SceneWin();
    ~SceneWin();

    void Init() override;

    void ReInit() override;
    void Update() override;
    void Render() override;
};