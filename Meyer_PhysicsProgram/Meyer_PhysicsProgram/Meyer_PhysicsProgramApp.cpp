#include "Meyer_PhysicsProgramApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm/ext.hpp>

Meyer_PhysicsProgramApp::Meyer_PhysicsProgramApp() {

}

Meyer_PhysicsProgramApp::~Meyer_PhysicsProgramApp() {

}

bool Meyer_PhysicsProgramApp::startup() {
	// Increase the 2D line cout to maximise the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));	// Turn off gravity
	m_physicsScene->setTimeStep(0.01f);

	// m_rocket = new Circle(glm::vec2(0,-30), glm::vec2(0, 0), 50, 4, glm::vec4(1, 0, 0, 1));
	// m_physicsScene->addActor(m_rocket);

	// Draw - Walls 
	m_physicsScene->addActor(new Plane(glm::vec2(0, -1), -55.f));
	m_physicsScene->addActor(new Plane(glm::vec2(0, 1), -55.f));
	m_physicsScene->addActor(new Plane(glm::vec2(-1, 0), -95.f));
	m_physicsScene->addActor(new Plane(glm::vec2(1, 0), -95.f));

	// Diagonal Lines
	m_physicsScene->addActor(new Plane(glm::normalize(glm::vec2(1, 1)), -40));
	m_physicsScene->addActor(new Plane(glm::normalize(glm::vec2(-1, -1)), -40));

	// Draw - Circles
	m_physicsScene->addActor(new Circle(glm::vec2(50, -30), glm::vec2(-30, 5), 2, 2, glm::vec4(1, 1, 1, 1)));
	m_physicsScene->addActor(new Circle(glm::vec2(30, -30), glm::vec2(-10, 10), 5, 5, glm::vec4(1, 0, 0, 1)));
	m_physicsScene->addActor(new Circle(glm::vec2(-20, 0), glm::vec2(10, -3), 100, 10, glm::vec4(0, 1, 0, 1)));

	// Draw - AABB's
	m_physicsScene->addActor(new Box(glm::vec2(40, -30), glm::vec2(10, -10), 7.5f, glm::vec2(10, 05), glm::vec4(1, 0, 1, 1)));
	m_physicsScene->addActor(new Box(glm::vec2(20, 0), glm::vec2(-10, 6), 5, glm::vec2(5, 5), glm::vec4(0, 0, 1, 1)));
	m_physicsScene->addActor(new Box(glm::vec2(20, 20), glm::vec2(-10, 15), 10, glm::vec2(5, 15), glm::vec4(0, 1, 1, 1)));
	m_physicsScene->addActor(new Box(glm::vec2(0, 0), glm::vec2(-10, 15), 10, glm::vec2(15, 15), glm::vec4(1, 0, 0, 0.5)));

	return true;
}
	

void Meyer_PhysicsProgramApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void Meyer_PhysicsProgramApp::update(float deltaTime) {

	if (m_eInterval < 0.1f)
		m_eInterval += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE) && m_eInterval >= 0.1f)
	{
		if (m_rocket->getMass() > 5)
		{
			m_rocket->setMass(m_rocket->getMass() - m_massReduction);
			//Circle* exhaust = new Circle(glm::vec2(m_rocket->getPosition() - glm::vec2(0,4)), glm::vec2(0, 0), m_massReduction, 0.5f, glm::vec4(1, 1, 1, 1));
			//m_physicsScene->addActor(exhaust);
			//exhaust->applyForceToActor(m_rocket, glm::vec2(0, 10));
			m_eInterval -= 0.1f;
		}
	}

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Meyer_PhysicsProgramApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}