#pragma once

#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "../game.h"
#include "engine.h"

using namespace std; // Standard namespace
using namespace sf; // SFML namespace

class PauseMenu : public Component
{
protected:


    RectangleShape _background;
    Text _title;
    Text _subText;
    shared_ptr<Font> _font;
    
    

   

    

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
    
    

    
};