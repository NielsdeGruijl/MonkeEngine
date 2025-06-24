#pragma once
#include "SpatialNode.h"
#include "TwoDimensionalSAP.h"

class SpatialGrid
{
public:
	Vector2 gridSize = Vector2(2000, 1100);
	Vector2 nodeSize = Vector2(200, 200);

public:
	void GenerateGrid();
	void SetGridCell(std::weak_ptr<AABBCollider> pCollider, Vector2 pPosition);
	void UpdateGridCell();
	void CheckCollisions(TwoDimensionalSAP* pSap);

	std::vector<std::shared_ptr<AABBCollider>> SweepGridCell(int pColumn, int pRow);
	SpatialNode GetGridCell(int pColumn, int pRow);

private:
	std::vector<std::vector<SpatialNode>> columns;
};