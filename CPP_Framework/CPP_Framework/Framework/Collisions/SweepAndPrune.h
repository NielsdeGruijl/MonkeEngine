
#include "CollisionChecker.h"
#include "AABBCollider.h"
#include "../Components/RigidBody.h"

struct EdgePoint
{
	EdgePoint(std::shared_ptr<AABBCollider> pCollider, bool pIsLeft)
		: collider(pCollider), isLeft(pIsLeft)
	{
		if (pIsLeft)
			position = &pCollider->left;
		else
			position = &pCollider->right;
	}

	std::weak_ptr<AABBCollider> collider;
	float* position;
	bool isLeft;
};

class SweepAndPrune
{
public:
	void Sweep();
	void Prune(std::weak_ptr<AABBCollider> pCollider);
	void RegisterCollider(std::shared_ptr<AABBCollider> pCollider);
	void SortEdgePoints();
	void RemoveTouchingCollider(std::weak_ptr<AABBCollider> pCollider);

public:
	CollisionChecker collisionChecker;
private:
	std::vector<EdgePoint> edgePoints;
	std::vector<std::weak_ptr<AABBCollider>> touchingColliders;
};