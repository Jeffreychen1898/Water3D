#pragma once

#include <renderer/Renderer.hpp>
#include <cmath>

#include "../utils.hpp"
#include "terrain.hpp"

struct Wave
{
	float spikey;
	float amplitude;
	float period;
	
	float dirX;
	float dirY;
};

class Water
{
	public:
		Water();
		~Water();

		void Init(Renderer::Window* windowPtr, Renderer::Render* rendererPtr);

		void Render(const Renderer::Mat4<float>& view, const Renderer::Vec3<float>& position);
	private:
		// the renderer and window
		Renderer::Window* window;
		Renderer::Render* renderer;

		// the shader
		Renderer::Shader surfaceShader;

		// position for the camera
		float gridSize;
		int32_t grids;

		float t;
};
