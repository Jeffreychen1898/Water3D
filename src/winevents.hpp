#pragma once

#include <renderer/Renderer.hpp>

#include "utils.hpp"
#include "scene/scene.hpp"

class WinEvents : public Renderer::WindowEvents
{
	public:
		WinEvents();

		void trackScene(Scene* _scene) { scene = _scene; };

		void KeyPressed(int _key, int _scancode, int _mods) override;
		void KeyReleased(int _key, int _scancode, int _mods) override;

		void MousePressed(int _button, int _mods) override;
		void MouseReleased(int _button, int _mods) override;
		void MouseMove(double _x, double _y) override;

		KeyHeldContainer& getKeysHeld() { return keysHeld; };

	private:
		Scene* scene;
		KeyHeldContainer keysHeld;
};
