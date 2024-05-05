#pragma once
#include "Object.h"

/// \class ObjectChest
/// \brief The chest object class
class ObjectChest : public Object
{
public:
	ObjectChest();
	~ObjectChest() {}

	void Init() override;
	void Update() override;
	void UseInteraction() override;
};