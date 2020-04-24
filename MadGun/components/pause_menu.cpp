#include "pause_menu.h"
#include <system_renderer.h>
#include <system_resources.h>




void PauseMenu::update(double dt) {}

void PauseMenu::render() 
{
	Renderer::queue(&_background);
	
}
PauseMenu::PauseMenu(Entity* const p)
	: Component(p)
{

	 
	
	
	
}

void PauseMenu::setSize(Vector2f size)
{
	// Set Character size of text
	_background.setSize(size);
}

void PauseMenu::setFillColor(Color color) 
{
	_background.setFillColor(color);
}

void PauseMenu::setPosition(Vector2f cord) 
{
	_background.setPosition(cord);
}

void PauseMenu::setOrigin(Vector2f orig)
{
	_background.setOrigin(orig);
}