#pragma once

#include <SFML/Graphics.hpp>
#include <ecm.h>

using namespace std; // Standard namespace
using namespace sf; // SFML namespace

class PauseMenu : public Component
{
protected:


    RectangleShape _background;
    
    

   

    

public:
    PauseMenu() = delete;

    explicit PauseMenu(Entity* p);
    ~PauseMenu() override = default;

    //Functions

    void update(double dt) override;
    void render() override;
    void setSize(Vector2f size);
    void setFillColor(Color color);
    void setPosition(Vector2f);
    void setOrigin(Vector2f);
};