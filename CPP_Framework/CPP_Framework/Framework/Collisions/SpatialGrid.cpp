#include "SpatialGrid.h"
#include "../Math/Timer.h"

void SpatialGrid::GenerateGrid()
{
	Vector2 startPosition = Vector2(nodeSize.x * 0.5f, nodeSize.y * 0.5f);

	for (int i = 0; i < gridSize.x; i += nodeSize.x)
	{
		std::vector<SpatialNode> column;
		for (int j = 0; j < gridSize.y; j += nodeSize.y)
		{
			column.push_back(SpatialNode(startPosition + Vector2(i, j), nodeSize));
		}

		columns.push_back(column);
	}
}

void SpatialGrid::SetGridCell(std::weak_ptr<AABBCollider> pCollider, Vector2 pPosition)
{
	columns[pPosition.x][pPosition.y].colliders.push_back(pCollider);
}

std::vector<std::shared_ptr<AABBCollider>> SpatialGrid::SweepGridCell(int pColumn, int pRow)
{
	std::vector<std::shared_ptr<AABBCollider>> collidersToSweep;

	for (int i = pColumn - 1; i < pColumn + 1; i++)
	{
		if (i < 0)
			continue;
		if (i > gridSize.x / nodeSize.x)
			break;

		for (int j = pRow - 1; j <= pRow + 1; j++)
		{
			if (j < 0)
				continue;
			if (j > gridSize.y / nodeSize.y)
				break;

			for (std::weak_ptr<AABBCollider> collider : columns[i][j].colliders)
			{
				collidersToSweep.push_back(collider.lock());
			}
		}
	}

	return collidersToSweep;
}

void SpatialGrid::UpdateGridCell()
{
	for (int i = 0; i < columns.size(); i++)
	{
		for (SpatialNode node : columns[i])
		{
			for (int j = node.colliders.size(); j > 0; j--)
			{
				//if (node == columns[2][0])
					//std::cout << node.colliders.size() << ", " << "\n";

				std::shared_ptr<AABBCollider> collider = node.colliders[j - 1].lock();
				int column = int(collider->position->x / nodeSize.x);
				int row = int(collider->position->y / nodeSize.y);

				if (column > columns.size() - 1 || row > columns[column].size() - 1)
				{
					//std::cout << column << ", " << row << "\n";
					continue;
				}

				if (columns[column][row] == node)
				{
					continue;
				}
				else
				{
					//std::cout << node.colliders.size() << ", ";
					node.colliders.erase(
						std::find_if(node.colliders.begin(), node.colliders.end(), [collider](std::weak_ptr<AABBCollider> other)
							{
								return collider == other.lock();
							}),
						node.colliders.end());

					//std::cout << node.colliders.size() << "\n";

					columns[column][row].colliders.push_back(collider);
				}
			}
		}
	}
}

void SpatialGrid::CheckCollisions(TwoDimensionalSAP* pSap)
{
	Timer timer;
	for (int i = 0; i < columns.size(); i++)
	{
		for (int j = 0; j < columns[i].size(); j += 2)
		{
			//pSap->RegisterColliders(SweepGridCell(i, j));
		}
	}
}

SpatialNode SpatialGrid::GetGridCell(int pColumn, int pRow)
{
	return columns[pColumn][pRow];
}