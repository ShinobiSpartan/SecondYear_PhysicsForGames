#include "Box.h"

Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 extents, glm::vec4 colour) :
	Rigidbody(RECT, position, velocity, 0, mass, 1), m_extents(extents), m_colour(colour)
{
}

Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, m_extents * 0.5f, m_colour);
}
