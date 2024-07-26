#include "winevents.hpp"

WinEvents::WinEvents()
	: scene{ nullptr }
{ }

void WinEvents::KeyPressed(int _key, int _scancode, int _mods)
{
	keysHeld.setKey(_key, true);
}

void WinEvents::KeyReleased(int _key, int _scancode, int _mods)
{
	keysHeld.setKey(_key, false);
}

void WinEvents::MousePressed(int _button, int _mods)
{
	keysHeld.setMouseButton(_button, true);
}

void WinEvents::MouseReleased(int _button, int _mods)
{
	keysHeld.setMouseButton(_button, false);
}

void WinEvents::MouseMove(double _x, double _y)
{
	keysHeld.mouseX = _x;
	keysHeld.mouseY = _y;
}
