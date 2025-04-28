#pragma once
#include "../Framework/Core/Scene.h"
#include "LeftObject.h"

class PerformanceTestScene : public Scene
{
public:
	PerformanceTestScene();
	void UpdateScene() override;
};