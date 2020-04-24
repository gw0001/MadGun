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

	 
	/*_background.setSize(sf::Vector2f(static_cast<float>(gameHeight), static_cast<float>(window.getSize().y)));
	_background.setFillColor(sf::Color(20, 20, 20, 100));*/
	
	/*_container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, static_cast<float>(window.getSize().y) - 60.f));
	_container.setFillColor(sf::Color(20, 20, 20, 200));
	_container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->_container.getSize().x / 2.f, 30.f);*/
	
	
	
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

void PauseMenu::setPosition(float x, float y) 
{
	_background.setPosition(x, y);
}