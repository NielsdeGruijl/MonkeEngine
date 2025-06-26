#pragma once
#include "../Framework/Core/Scene.h"
#include "LeftObject.h"

class PerformanceTestScene : public Scene
{
public:
	PerformanceTestScene();

	std::vector<shared_ptr<LeftObject>> objects;
};