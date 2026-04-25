#include "CollisionManager.h"

void CollisionManager::Init()
{
	
}

void CollisionManager::Update(void)
{
	RemoveColliders();

	CheckCollisions();
}

void CollisionManager::Destroy()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i] != NULL)
		{
			colliders[i]->Destroy();
			delete colliders[i];
			colliders[i] = NULL;
		}
	}

	DestroySingleton();
}

void CollisionManager::AddCollider(Collider* _collider)
{
	colliders.push_back(_collider);
}

void CollisionManager::RemoveColliders()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->GetParent() == NULL)
		{
			collidersToRemove.push_back(colliders[i]);
		}
	}

	while (collidersToRemove.size() > 0)
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			Collider* colliderToRemove = collidersToRemove[0];
			if (colliders[i] == colliderToRemove)
			{
				delete colliders[i];

				colliders.erase(colliders.begin() + i);
				collidersToRemove.erase(collidersToRemove.begin());

				colliderToRemove = NULL;

				break;
			}
		}
	}
}

bool CollisionManager::CheckSquaresCollision(Collider* r1, Collider* r2)
{
	float leftX1 = r1->GetParent()->GetXWithoutPivot() + r1->GetLeftX();
	float rightX1 = r1->GetParent()->GetXWithoutPivot() + r1->GetRightX();
	float topY1 = r1->GetParent()->GetYWithoutPivot() + r1->GetTopY();
	float bottomY1 = r1->GetParent()->GetYWithoutPivot() + r1->GetBottomY();

	float leftX2 = r2->GetParent()->GetXWithoutPivot() + r2->GetLeftX();
	float rightX2 = r2->GetParent()->GetXWithoutPivot() + r2->GetRightX();
	float topY2 = r2->GetParent()->GetYWithoutPivot() + r2->GetTopY();
	float bottomY2 = r2->GetParent()->GetYWithoutPivot() + r2->GetBottomY();

	return (leftX1 < rightX2 && leftX2 < rightX1 && topY1 < bottomY2 && topY2 < bottomY1);
}

bool CollisionManager::CheckCirclesCollision(Collider* c1, Collider* c2)
{
	float c1CenterX = c1->GetParent()->GetPosX() + c1->GetCenter().GetX();
	float c1CenterY = c1->GetParent()->GetPosY() + c1->GetCenter().GetX();

	float c2CenterX = c2->GetParent()->GetPosX() + c2->GetCenter().GetX();
	float c2CenterY = c2->GetParent()->GetPosY() + c2->GetCenter().GetX();

	float distanceX = c2CenterX - c1CenterX;
	float distanceY = c2CenterY - c1CenterY;

	float radius = c1->GetRadius() + c2->GetRadius();

	return (distanceX * distanceX + distanceY * distanceY <= radius * radius);
}

bool CollisionManager::CheckCircleSquareCollision(Collider* c, Collider* r)
{
	// Get the center of the ball
	float circleCenterX = c->GetParent()->GetPosX() + c->GetCenter().GetX();
	float circleCenterY = c->GetParent()->GetPosY() + c->GetCenter().GetY();

	// Calculate the closest point on the rectangle to the center of the ball
	float closestX = max(r->GetParent()->GetXWithoutPivot() + r->GetLeftX(), min(circleCenterX, r->GetParent()->GetXWithoutPivot() + r->GetRightX()));
	float closestY = max(r->GetParent()->GetYWithoutPivot() + r->GetTopY(), min(circleCenterY, r->GetParent()->GetYWithoutPivot() + r->GetBottomY()));

	// Calculate the distance between the closest point and the center of the ball
	float distanceX = circleCenterX - closestX;
	float distanceY = circleCenterY - closestY;

	// Check if the distance is less than or equal to the radius of the ball
	return (pow(distanceX, 2) + pow(distanceY, 2)) <= pow(c->GetRadius	(), 2);
}

void CollisionManager::CheckCollisions()
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i] != NULL) 
		{
			colliders[i]->GetCollidingBefore()->clear();

			for (int j = 0; j < colliders[i]->GetCollidingWith()->size(); j++)
			{
				Collider* colliderToAdd = (*colliders[i]->GetCollidingWith())[j];
				colliders[i]->GetCollidingBefore()->push_back(colliderToAdd);
			}

			colliders[i]->GetCollidingWith()->clear();
		}
	}

	for (int i = 0; i < colliders.size(); i++)
	{
		for (int j = i + 1; j < colliders.size(); j++)
		{
			if (colliders[i]->GetParent() != NULL && colliders[j]->GetParent() != NULL)
			{
				if (colliders[i]->GetParent() != colliders[j]->GetParent())
				{
					if (colliders[i]->GetParent()->isActive() && colliders[j]->GetParent()->isActive())
					{
						bool collisionDetected = false;

						if (colliders[i]->GetIsSquare() && colliders[j]->GetIsSquare())
						{
							collisionDetected = CheckSquaresCollision(colliders[i], colliders[j]);
						}
						else if (colliders[i]->GetIsSquare() && !colliders[j]->GetIsSquare())
						{
							collisionDetected = CheckCircleSquareCollision(colliders[j], colliders[i]);
						}
						else if (!colliders[i]->GetIsSquare() && colliders[j]->GetIsSquare())
						{
							collisionDetected = CheckCircleSquareCollision(colliders[i], colliders[j]);
						}
						else
						{
							collisionDetected = CheckCirclesCollision(colliders[i], colliders[j]);
						}

						if (collisionDetected)
						{
							colliders[i]->GetCollidingWith()->push_back(colliders[j]);
							colliders[j]->GetCollidingWith()->push_back(colliders[i]);

							if (!colliders[i]->isTrigger() && !colliders[j]->isTrigger())
							{
								colliders[i]->GetParent()->UndoMovement(colliders[i], colliders[j]);
								colliders[j]->GetParent()->UndoMovement(colliders[j], colliders[i]);
							}

							if (!colliders[i]->CollidingBeforeIncludes(colliders[j]))
							{
								if (!colliders[i]->isTrigger() && !colliders[j]->isTrigger())
								{
									colliders[i]->GetParent()->OnCollisionEnter(colliders[j]);
								}
								else
								{
									colliders[i]->GetParent()->OnTriggerEnter(colliders[j]);
								}
							}
							else
							{
								if (!colliders[i]->isTrigger() && !colliders[j]->isTrigger())
								{
									colliders[i]->GetParent()->OnCollisionStay(colliders[j]);
								}
								else
								{
									colliders[i]->GetParent()->OnTriggerStay(colliders[j]);
								}
							}

							if (!colliders[j]->CollidingBeforeIncludes(colliders[i]))
							{
								if (!colliders[i]->isTrigger() && !colliders[j]->isTrigger())
								{
									colliders[j]->GetParent()->OnCollisionEnter(colliders[i]);
								}
								else
								{
									colliders[j]->GetParent()->OnTriggerEnter(colliders[i]);
								}
							}
							else
							{
								if (!colliders[i]->isTrigger() && !colliders[j]->isTrigger())
								{
									colliders[j]->GetParent()->OnCollisionStay(colliders[i]);
								}
								else
								{
									colliders[j]->GetParent()->OnTriggerStay(colliders[i]);
								}
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < colliders.size(); i++)
	{
		for (int j = 0; j < colliders[i]->GetCollidingBefore()->size(); j++)
		{
			if (colliders[i]->GetParent() != NULL && (*colliders[i]->GetCollidingBefore())[j]->GetParent() != NULL)
			{
				if (!colliders[i]->CollidingWithIncludes((*colliders[i]->GetCollidingBefore())[j]))
				{
					if (!colliders[i]->isTrigger() && !(*colliders[i]->GetCollidingBefore())[j]->isTrigger())
						colliders[i]->GetParent()->OnCollisionExit((*colliders[i]->GetCollidingBefore())[j]);
					else
						colliders[i]->GetParent()->OnTriggerExit((*colliders[i]->GetCollidingBefore())[j]);
				}
			}
		}
	}
}