#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include "Plane.h"
#include <list>
#include <iostream>


PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(0,0)
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

bool PhysicsScene::removeActor(PhysicsObject * actor)
{
	for (int i = 0; i < m_actors.size(); ++i)
	{
		if (m_actors[i] == actor)
		{
			m_actors.erase(m_actors.begin() + i);
			return true;
		}
	}
	return false;
}

void PhysicsScene::update(float dt)
{
	// Update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}

	checkForCollision();
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane,	PhysicsScene::plane2Circle,		PhysicsScene::plane2Rect,
	PhysicsScene::circle2Plane, PhysicsScene::circle2Circle,	PhysicsScene::circle2Rect,
	PhysicsScene::rect2Plane,	PhysicsScene::rect2Circle,		PhysicsScene::rect2Rect
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	// Need to check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* obj1 = m_actors[outer];
			PhysicsObject* obj2 = m_actors[inner];

			int shapeId1 = obj1->getShapeID();
			int shapeId2 = obj2->getShapeID();

			// Using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				// Did a collision occur?
				collisionFunctionPtr(obj1, obj2);
			}
		}
	}
}


/* Plane Interactions */
bool PhysicsScene::plane2Plane(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::plane2Circle(PhysicsObject * obj1, PhysicsObject * obj2)
{
	return circle2Plane(obj2, obj1);
}

bool PhysicsScene::plane2Rect(PhysicsObject * obj1, PhysicsObject * obj2)
{
	return rect2Plane(obj2, obj1);
}

/* Circle Interactions */
bool PhysicsScene::circle2Plane(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Circle *circle = dynamic_cast<Circle*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	// If we are successful then test for collision
	if (!(circle == nullptr || plane == nullptr))
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float circleToPlane = glm::dot(circle->getPosition(), plane->getNormal()) - plane->getDistance();

		// If we are behind the plane then we flip the normal
		if (circleToPlane < 0)
		{
			collisionNormal *= -1;
			circleToPlane *= -1;
		}

		float intersection = circle->getRadius() - circleToPlane;
		if (intersection > 0)
		{
			circle->setPosition(circle->getPosition() + collisionNormal * intersection);

			glm::vec2 contact = circle->getPosition() + (collisionNormal * -circle->getRadius());
			
			plane->resolveCollision(circle, contact);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::circle2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Try to cast objects to circle and circle
	Circle *circle1 = dynamic_cast<Circle*>(obj1);
	Circle *circle2 = dynamic_cast<Circle*>(obj2);
	// If we are successful then test for collision
	if (!(circle1 == nullptr || circle2 == nullptr))
	{
		glm::vec2 dist = circle1->getPosition() - circle2->getPosition();
		if (glm::length(dist) < circle1->getRadius() + circle2->getRadius())
		{
			circle1->resolveCollision(circle2);

			return true;
		}
	}
	return false;
}

bool PhysicsScene::circle2Rect(PhysicsObject * obj1, PhysicsObject * obj2)
{
	return rect2Circle(obj2, obj1);
}

/* Rectangle Interactions */
bool PhysicsScene::rect2Plane(PhysicsObject * obj1, PhysicsObject * obj2)
{
	// Try to cast objects to Box and Plane
	Box *box = dynamic_cast<Box*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);
	// If we are successful then test for collision
	if (!(box == nullptr || plane == nullptr))
	{
		glm::vec2 planeNormal = plane->getNormal();

		// v1	 v2
		//	  []
		// v4	 v3

		// v1
		glm::vec2 v1(box->getExtents().x * -0.5f, box->getExtents().y * 0.5f);
		float v1ToPlane = glm::dot(box->getPosition() + v1, plane->getNormal()) - plane->getDistance();

		// v2
		glm::vec2 v2(box->getExtents().x * 0.5f, box->getExtents().y * 0.5f);
		float v2ToPlane = glm::dot(box->getPosition() + v2, plane->getNormal()) - plane->getDistance();
		
		// v3
		glm::vec2 v3(box->getExtents().x * 0.5f, box->getExtents().y * -0.5f);
		float v3ToPlane = glm::dot(box->getPosition() + v3, plane->getNormal()) - plane->getDistance();
		
		// v4
		glm::vec2 v4(box->getExtents().x * -0.5f, box->getExtents().y * -0.5f);
		float v4ToPlane = glm::dot(box->getPosition() + v4, plane->getNormal()) - plane->getDistance();

		if (v1ToPlane < 0)
		{
			box->setPosition(box->getPosition() + planeNormal * (-v1ToPlane));
			glm::vec2 contact = box->getPosition() + (planeNormal * -v1);
			plane->resolveCollision(box, contact);
			
			return true;
		}
		if (v2ToPlane < 0)
		{
			box->setPosition(box->getPosition() + planeNormal * (-v2ToPlane));
			glm::vec2 contact = box->getPosition() + (planeNormal * -v2);
			plane->resolveCollision(box, contact);
			
			return true;
		}
		if (v3ToPlane < 0)
		{
			box->setPosition(box->getPosition() + planeNormal * (-v3ToPlane));
			glm::vec2 contact = box->getPosition() + (planeNormal * -v3);
			plane->resolveCollision(box, contact);
			
			return true;
		}
		if (v4ToPlane < 0)
		{
			box->setPosition(box->getPosition() + planeNormal * (-v4ToPlane));
			glm::vec2 contact = box->getPosition() + (planeNormal * -v4);
			plane->resolveCollision(box, contact);
			
			return true;
		}

	}
	return false;
}

bool PhysicsScene::rect2Circle(PhysicsObject * obj1, PhysicsObject * obj2)
{
	// Try to cast objects to Box and Circle
	Box *box = dynamic_cast<Box*>(obj1);
	Circle *circle = dynamic_cast<Circle*>(obj2);
	// If we are successful then test for collision
	if (!(box == nullptr || circle == nullptr))
	{
		glm::vec2 boxMin(	box->getPosition().x - (box->getExtents().x * 0.5f),
							box->getPosition().y - (box->getExtents().y * 0.5f)		);
		glm::vec2 boxMax(	box->getPosition().x + (box->getExtents().x * 0.5f),
							box->getPosition().y + (box->getExtents().y * 0.5f)		);

		glm::vec2 boxClamp = glm::clamp(circle->getPosition(), boxMin, boxMax);

		glm::vec2 dist = boxClamp - circle->getPosition();

		if (glm::length(dist) < circle->getRadius())
		{
			box->resolveCollision(circle, &glm::normalize(circle->getPosition() - boxClamp));
			return true;
		}
	}

	return false;
}

bool PhysicsScene::rect2Rect(PhysicsObject * obj1, PhysicsObject * obj2)
{
	// Try to cast objects to Box and Box
	Box *box1 = dynamic_cast<Box*>(obj1);
	Box *box2 = dynamic_cast<Box*>(obj2);
	// If we are successful then test for collision
	if (!(box1 == nullptr || box2 == nullptr))
	{
		glm::vec2 box1Min(	box1->getPosition().x - (box1->getExtents().x * 0.5f),
							box1->getPosition().y - (box1->getExtents().y * 0.5f)	);
		glm::vec2 box1Max(	box1->getPosition().x + (box1->getExtents().x * 0.5f), 
							box1->getPosition().y + (box1->getExtents().y * 0.5f)	);

		glm::vec2 box2Min(	box2->getPosition().x - (box2->getExtents().x * 0.5f),
							box2->getPosition().y - (box2->getExtents().y * 0.5f)	);
		glm::vec2 box2Max(	box2->getPosition().x + (box2->getExtents().x * 0.5f),
							box2->getPosition().y + (box2->getExtents().y * 0.5f)	);

		if (!(box1Max.x < box2Min.x || box2Max.x < box1Min.x || box1Max.y < box2Min.y || box2Max.y < box1Min.y))
		{
			float x1 = box2Max.x - box1Min.x;
			float x2 = box1Max.x - box2Min.x;
			
			float y1 = box2Max.y - box1Min.y;
			float y2 = box1Max.y - box2Min.y;

			float smallestDist = x1;

			if (x2 < smallestDist)
				smallestDist = x2;
			if (y1 < smallestDist)
				smallestDist = y1;
			if (y2 < smallestDist)
				smallestDist = y2;

			if (smallestDist == x1)
			{
				glm::vec2 collisionNormal = glm::vec2(1, 0);

				box1->setPosition(box1->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box1->resolveCollision(box2, &collisionNormal);
			}
			else if (smallestDist == x2)
			{
				glm::vec2 collisionNormal = glm::vec2(-1, 0);

				box1->setPosition(box1->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box1->resolveCollision(box2, &collisionNormal);
			}
			else if (smallestDist == y1)
			{
				glm::vec2 collisionNormal = glm::vec2(0, 1);

				box1->setPosition(box1->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box1->resolveCollision(box2, &collisionNormal);
			}
			else if (smallestDist == y2)
			{
				glm::vec2 collisionNormal = glm::vec2(0, -1);

				box1->setPosition(box1->getPosition() + collisionNormal * smallestDist * 0.5f);
				box2->setPosition(box2->getPosition() - collisionNormal * smallestDist * 0.5f);

				box1->resolveCollision(box2, &collisionNormal);
			}

			return true;
		}
	}

	return false;
}
