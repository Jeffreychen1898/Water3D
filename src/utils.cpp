#include "utils.hpp"

std::uniform_real_distribution<float> Random::distribution(0.f, 1.f);
std::mt19937 Random::gen(std::random_device{}());

float Random::Get()
{
	return Random::Get(0.f, 1.f);
}

float Random::Get(float begin, float end)
{
	return static_cast<float>(distribution(gen)) * (end - begin) + begin;
}

Renderer::Mat4<float> genViewMatrix(
		Renderer::Vec3<float> position,
		Renderer::Vec3<float> lookat,
		Renderer::Vec3<float> up)
{
	lookat.normalize();
	up.normalize();
	Renderer::Vec3<float> right = lookat.cross(up);
	up = right.cross(lookat);

	return Renderer::Mat4(
			right.x, right.y, right.z, -right.dot(position),
			up.x, up.y, up.z, -up.dot(position),
			-lookat.x, -lookat.y, -lookat.z, lookat.dot(position),
			0.f, 0.f, 0.f, 1.f
	);
}

KeyHeldContainer::KeyHeldContainer()
	: mouseX{ 0 }, mouseY{ 0 }, pmouseX{ 0 }, pmouseY{ 0 }
{
	mouseHeld.fill(false);
	keysHeld.fill(false);
}

void KeyHeldContainer::update()
{
	pmouseX = mouseX;
	pmouseY = mouseY;
}
