#include "Meyer_PhysicsProgramApp.h"

int main() {
	
	// allocation
	auto app = new Meyer_PhysicsProgramApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}