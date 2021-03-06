/*
 * GAMES ENGINEERING - COURSEWORK
 * -------------------------------------
 * MadGun: Gears and Blood
 * -------------------------------------
 * Franceso Fico - 40404272
 * Graeme White - 40415739
 * -------------------------------------
 * Code Author(s): G. White
 * Date Created: 14/03/2020
 * Date Last Modified: 27/04/2020
 * -------------------------------------
 * HURT PLAYER COMPONET
 * - cmp_hurt_player.cpp
 *
 * Hurt player component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#include "cmp_hurt_player.h"
#include "cmp_player_physics.h"
#include <engine.h>
#include <levelsystem.h>

// Update function
//
// Function updates the hurt player component
void HurtComponent::update(double dt) 
{
	// Check
	if (auto pl = _player.lock()) 
	{
		// Check if player is within distance of the entity with the hurt player component
		if (length(pl->getPosition() - _parent->getPosition()) < 25.0) 
		{
			// Obtain physics component
			auto playerPhysics = pl->get_components<PlayerPhysicsComponent>();

			// Teleport player to start of level
			playerPhysics[0]->teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		}
	}
}

// Hurt Player Component constructor
HurtComponent::HurtComponent(Entity* p)
	: Component(p), _player(_parent->scene->ents.find("player")[0]) {};
