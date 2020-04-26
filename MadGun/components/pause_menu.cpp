#include "pause_menu.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>
#include <LevelSystem.h>




void PauseMenu::update(double dt) {}

void PauseMenu::render() 
{
	Renderer::queue(&_background);
	//Renderer::queue(&_title);
	
	
	
}
PauseMenu::PauseMenu(Entity* const p)
	: Component(p)
	
{

	/*sf::Vector2f titleSize(_title.getLocalBounds().width, _title.getLocalBounds().height);
	sf::Vector2f backgroundSize(_background.getLocalBounds().width , _background.getLocalBounds().height);
	sf::Vector2f containerPosition(_background.getLocalBounds().left, _background.getLocalBounds().top);*/

	sf::FloatRect textRect = _title.getLocalBounds();
	sf::FloatRect backSize = _background.getLocalBounds();
	sf::Vector2f backCenter(floor(_background.getSize().x / 2.0f), floor(_background.getSize().y / 2.0f));
	
	

	//_font = Resources::get<Font>("gotham.ttf");

	 _background.setSize(sf::Vector2f(gameHeight, gameWidth));
	 _background.setFillColor(sf::Color(20, 20, 20, 200));	
	 _background.setOrigin(_background.getSize().x / 2.f , _background.getSize().y / 2.f);

	 //_title.setString("PAUSE");
	 //_title.setFont(*_font);
	 //_title.setCharacterSize(150.0f);
	 //_title.setLetterSpacing(5.0f);
	 //_title.setFillColor(Color::White);
	 ///*_title.setOrigin(_title.getLocalBounds().width / 2.f, _title.getLocalBounds().height / 2.f);
	 //_title.setPosition(_background.getSize().x /2.f, _background.getSize().y /2.f);*/
	 //_title.setPosition(backCenter.x, backCenter.y);
	 //_title.setOrigin(backSize.width, backSize.height);
	 



	 
	
	
	
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





