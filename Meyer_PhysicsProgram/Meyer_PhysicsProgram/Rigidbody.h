#pragma once
#include "PhysicsObject.h"

#ifndef MIN_LINEAR_THRESHOLD
	#define MIN_LINEAR_THRESHOLD 0.1f
#endif

#ifndef MIN_ROTATION_THRESHOLD
	#define MIN_ROTATION_THRESHOLD 0.01f
#endif



class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float moment);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();

	void applyForce(glm::vec2 force);
	void applyForce(glm::vec2 force, glm::vec2 pos);
		
	void resolveCollision(Rigidbody* actor2, glm::vec2* collisionNormal = nullptr);

	glm::vec2 getPosition() const { return m_position; }
	void setPosition(glm::vec2 pPosition) { m_position = pPosition; }
	
	float getRotation() const { return m_rotation; }
	void setRotation(float pRotation) { m_rotation = pRotation; }

	glm::vec2 getVelocity() const { return m_velocity; }
	void setVelocity(glm::vec2 pVelocity) { m_velocity = pVelocity; }
	
	float getMass() const { return (m_isKinematic) ? INT_MAX : m_mass; }
	void setMass(float pMass) { m_mass = pMass; }

	float getLinearDrag() { return m_linearDrag; }

	float getElasticity() { return m_elasticity; }

	void setKinematic(bool state) { m_isKinematic = state; }
	bool isKinematic() { return m_isKinematic; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;

	float m_rotation;	// 2D so we only need a single float to represent our rotation
	float m_angularVelocity;
	float m_moment;
	
	float m_linearDrag;
	float m_angularDrag;
	
	float m_elasticity;

	bool m_isKinematic = false;
};

