#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Circle.h"
#include "Plane.h"
#include "Box.h"

class Meyer_PhysicsProgramApp : public aie::Application {
public:

	Meyer_PhysicsProgramApp();
	virtual ~Meyer_PhysicsProgramApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
	Circle*				m_rocket;
	float				m_massReduction = 1.f;
	float				m_eInterval = 0.f;
};