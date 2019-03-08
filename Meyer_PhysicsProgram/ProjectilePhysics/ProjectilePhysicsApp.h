#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Circle.h"

#define M_PI 3.14159265358979323846

class ProjectilePhysicsApp : public aie::Application {
public:

	ProjectilePhysicsApp();
	virtual ~ProjectilePhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	void setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);

	virtual void update(float deltaTime);
	virtual void draw();


protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
};