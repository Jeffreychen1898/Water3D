#pragma once

#include <random>
#include <array>

#include <renderer/Renderer.hpp>

// constants
#define PI 3.1415926535897932385
#define TWO_PI 2.0 * PI

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "Water Rendering"

// randoms
class Random
{
	public:
		static float Get();
		static float Get(float begin, float end);

	private:
		static std::mt19937 gen;
		static std::uniform_real_distribution<float> distribution;
};

Renderer::Mat4<float> genViewMatrix(
		Renderer::Vec3<float> position,
		Renderer::Vec3<float> lookat,
		Renderer::Vec3<float> up);

// key held container
class KeyHeldContainer
{
	public:
		int32_t mouseX, mouseY;
		int32_t pmouseX, pmouseY;

		KeyHeldContainer();

		bool keyAt(std::size_t key) const { return keysHeld[key]; };
		bool mouseButtonAt(std::size_t button) const { return mouseHeld[button]; };

		void setKey(std::size_t key, bool value) { keysHeld[key] = value; };
		void setMouseButton(std::size_t button, bool value) { mouseHeld[button] = value; };

		void update();

	private:
		std::array<bool, GLFW_MOUSE_BUTTON_LAST> mouseHeld;
		std::array<bool, GLFW_KEY_LAST> keysHeld;
};
