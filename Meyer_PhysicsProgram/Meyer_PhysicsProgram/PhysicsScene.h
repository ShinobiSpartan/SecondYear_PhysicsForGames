#pragma once

#include <vector>
#include "Circle.h"
#include "Box.h"
#include "Plane.h"

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	bool removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool plane2Circle(PhysicsObject*, PhysicsObject*);
	static bool plane2Rect(PhysicsObject*, PhysicsObject*);

	static bool circle2Plane(PhysicsObject*, PhysicsObject*);
	static bool circle2Circle(PhysicsObject*, PhysicsObject*);
	static bool circle2Rect(PhysicsObject*, PhysicsObject*);

	static bool rect2Plane(PhysicsObject*, PhysicsObject*);
	static bool rect2Circle(PhysicsObject*, PhysicsObject*);
	static bool rect2Rect(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

