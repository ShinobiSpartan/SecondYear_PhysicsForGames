#include "Circle.h"

Circle::Circle(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : 
		Rigidbody(CIRCLE, position, velocity, 0, mass, (0.5f * mass * radius * radius)), m_radius(radius), m_colour(colour)
{
}

Circle::~Circle()
{
}

void Circle::makeGizmo()
{
	//glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;

	aie::Gizmos::add2DCircle(m_position, m_radius, 30, m_colour);
	//aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1,1,1,1));
}