#pragma once

#include <renderer/Renderer.hpp>

#include "../utils.hpp"
#include "terrain.hpp"

class Scene
{
	public:
		Scene();
		~Scene();

		void Init(Renderer::Window* windowPtr, Renderer::Render* rendererPtr);

		void ClearBuffers();
		void Render();
		void Update();

		void trackKeysHeld(const KeyHeldContainer* getKeysHeld) { keysHeld = getKeysHeld; };

	private:
		Renderer::Window* window;
		Renderer::Render* renderer;

		Water water;

		// camera parameters
		Renderer::Vec3<float> position;
		Renderer::Vec3<float> lookat;
		Renderer::Vec3<float> up;

		Renderer::Mat4<float> viewMatrix;

		// movement control
		const KeyHeldContainer* keysHeld;
};
