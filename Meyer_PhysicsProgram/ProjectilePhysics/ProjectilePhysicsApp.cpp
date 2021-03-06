#include "ProjectilePhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <glm/ext.hpp>


ProjectilePhysicsApp::ProjectilePhysicsApp() {

}

ProjectilePhysicsApp::~ProjectilePhysicsApp() {

}

bool ProjectilePhysicsApp::startup() {
	// Increase the 2D line cout to maximise the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.5f);

	float radius = 1.0f;
	float speed = 30.f;
	glm::vec2 startPos(-40, 0);
	float inclination = 0.785;

	glm::vec2 pVelocity = glm::vec2(sinf(inclination) * speed, cosf(inclination) * speed);

	m_physicsScene->addActor(new Circle(startPos, pVelocity, 1, radius, glm::vec4(1,0,0,1)));
	
	setupContinuousDemo(glm::vec2(-40, 0), 0.785f, 30.f, -10.f);

	return true;
}

void ProjectilePhysicsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void ProjectilePhysicsApp::setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 32;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	glm::vec2 velocity = glm::vec2(sinf(inclination) * speed, cosf(inclination) * speed);

	while (t <= 5)
	{
		// pos = ut + 1/2 a t ^2														
		glm::vec2 pos = startPos + velocity * t + 0.5f * glm::vec2(0, gravity) * t * t; 

		aie::Gizmos::add2DCircle(pos, radius, segments, colour);
		t += tStep;
	}
}

void ProjectilePhysicsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update physics
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ProjectilePhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}