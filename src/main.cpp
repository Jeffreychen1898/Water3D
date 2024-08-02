#include <renderer/Renderer.hpp>

#include "utils.hpp"
#include "winevents.hpp"
#include "scene/scene.hpp"

#include <chrono>

int main()
{
	// initialize the window
	Renderer::Window::GLFWInit();

	WinEvents* windowEvents = new WinEvents();
	KeyHeldContainer& getKeysHeld = windowEvents->getKeysHeld();

	Renderer::Window window;
	window.addEvents(windowEvents);
	window.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	window.setVSync(true);

	// initialize the renderer
	Renderer::Render renderer;
	renderer.attach(&window);
	renderer.init();

	// load the texture
	Renderer::Texture sky;
	sky.load(&window, "skybox.jpg");

	// GL Enables
	glEnable(GL_DEPTH_TEST);

	// Create the scene
	Scene scene;
	scene.Init(&window, &renderer);

	windowEvents->trackScene(&scene);
	scene.trackKeysHeld(&getKeysHeld);

	auto start = std::chrono::steady_clock::now();

	while(window.isOpened())
	{
		auto end = std::chrono::steady_clock::now();
		auto elapse_time = end - start;
		double dt = std::chrono::duration_cast<std::chrono::duration<double>>(elapse_time).count();
		std::cout << 1.0 / dt << "\n";
		start = end;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		scene.ClearBuffers();
		scene.Update();
		scene.Render();

		renderer.render();

		getKeysHeld.update();
		window.swapBuffers();
		Renderer::Window::pollEvents();
	}

	return 0;
}
