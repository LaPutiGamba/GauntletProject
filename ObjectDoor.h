#pragma once
#include "Object.h"
#include "Camera.h"

class ObjectDoor : public Object
{
    Camera* _camera;

public:
    ObjectDoor();
    ~ObjectDoor() {}

    void Init() override;
    void Update() override;
    void UseInteraction() override;

    /// \brief Set the camera
    /// \param camera The camera
    void SetCamera(Camera* camera) { _camera = camera; }
};