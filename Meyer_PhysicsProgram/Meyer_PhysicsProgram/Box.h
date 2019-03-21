#pragma once
#include "Rigidbody.h"
#include <Gizmos.h>
class Box : public Rigidbody
{
public:
	Box(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 extents, glm::vec4 colour, bool isKinematic);
	~Box();

	virtual void makeGizmo();

	glm::vec2 getExtents() { return m_extents; }

	glm::vec4 getColour() { return m_colour; }

protected:
	glm::vec2 m_extents;
	glm::vec4 m_colour;
};

