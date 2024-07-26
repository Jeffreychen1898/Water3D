#include "scene.hpp"

Scene::Scene()
	: window{ nullptr }, renderer{ nullptr }, position{ 0, 2, 0 }, lookat{ 0, 0, -1 }, up{ 0, 1, 0 },
	keysHeld{ nullptr }
{
	viewMatrix = genViewMatrix(position, lookat, up);
}

void Scene::Init(Renderer::Window* windowPtr, Renderer::Render* rendererPtr)
{
	window = windowPtr;
	renderer = rendererPtr;

	water.Init(window, renderer);
}

void Scene::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::Render()
{
	water.Render(viewMatrix, position);
}

void Scene::Update()
{
	viewMatrix = genViewMatrix(position, lookat, up);

	if(!keysHeld)
		return;

	Renderer::Vec3<float> right = lookat.cross(up);
	Renderer::Vec3<float> forward = up.cross(right);

	if(keysHeld->keyAt(GLFW_KEY_W))
		position = position + forward * 10.f;
	if(keysHeld->keyAt(GLFW_KEY_S))
		position = position - forward * 10.f;
	if(keysHeld->keyAt(GLFW_KEY_A))
		position = position - right * 10.f;
	if(keysHeld->keyAt(GLFW_KEY_D))
		position = position + right * 10.f;
	if(keysHeld->keyAt(GLFW_KEY_Q))
		position = position - up * 10.f;
	if(keysHeld->keyAt(GLFW_KEY_E))
		position = position + up * 10.f;

	if(keysHeld->mouseButtonAt(GLFW_MOUSE_BUTTON_LEFT) &&
			keysHeld->keyAt(GLFW_KEY_LEFT_SHIFT))
	{
		float one_over_focal_dist = 1.f / 1024.f;
		float diffx = (keysHeld->mouseX - keysHeld->pmouseX) * one_over_focal_dist;
		float diffy = (keysHeld->mouseY - keysHeld->pmouseY) * one_over_focal_dist;

		lookat = lookat + right * -diffx + up * diffy;
		lookat.normalize();
	}
}

Scene::~Scene()
{ }
