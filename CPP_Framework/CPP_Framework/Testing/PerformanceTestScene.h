#pragma once
#include "../Framework/Core/Scene.h"
#include "LeftObject.h"

class PerformanceTestScene : public Scene
{
public:
	PerformanceTestScene();
	void Update() override;

	std::vector<shared_ptr<LeftObject>> objects;
	bool started = false;
};