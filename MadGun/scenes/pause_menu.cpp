#include "pause_menu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
	// init background
	this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	//init container
	this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, static_cast<float>(window.getSize().y) - 60.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f);
}

PauseMenu::~PauseMenu()
{
}



//Functions


void PauseMenu::Update()
{
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
}