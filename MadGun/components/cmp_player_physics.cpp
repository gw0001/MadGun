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
 * Date Last Modified: 13/04/2020
 * -------------------------------------
 * PLAYER PHYSICS COMPONENT
 * - cmp_player_physics.cpp
 *
 * Player physics component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Joystick.hpp>

// Namespace
using namespace Physics; // Physics namespace

//creating audio variables
sf::SoundBuffer bufferWalk;
sf::SoundBuffer bufferJump;
sf::Sound soundWalk;
sf::Sound soundJump;

float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);


// Is Grounded function
//
// Function determines if player physics component is grounded
bool PlayerPhysicsComponent::isGrounded() const 
{
	// Obtain touch
	auto touch = getTouching();

	// Obtain position
	const auto& pos = _body->GetPosition();

	// Half the player height
	const float halfPlayerHeight = _size.y * 0.5f;

	// Half the player width
	const float halfPlayerWidth = _size.x * 0.5f;

	// Box2D manifold
	b2WorldManifold manifold;

	// Iterate over each touch
	for (const auto& contact : touch) 
	{
		// Obtain world manifold
		contact->GetWorldManifold(&manifold);

		// Obtain the number of points
		const int numPoints = contact->GetManifold()->pointCount;

		// Set On Top
		bool onTop = numPoints > 0;

		// If all contacts are below the player.
		for (int j = 0; j < numPoints; j++) 
		{
			onTop &= (manifold.points[j].y < pos.y - halfPlayerHeight);
		}
		// Check if on top is true
		if (onTop) 
		{
			// Return true
			return true;
		}
	}

	// Return false
	return false;
}

// Update function
//
// Function updates the player physics component
void PlayerPhysicsComponent::update(double dt) 
{
	
	// Obtain Position
	const auto pos = _parent->getPosition();

	// Check if player has fallen off the map
	if (pos.y > ls::getHeight() * ls::getTileSize())
	{
		// Teleport player to start tile
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}

	// Check if player is has pressed right or left
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)) 
	{
		//soundfx loaded in the buffer
		//bufferWalk.loadFromFile("res/audio/fx/footsteps.wav");
		//soundWalk.setBuffer(bufferWalk);
		//soundWalk.setLoop(true);

			// Check if right key pressed
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				

				// Check if velocity of the player is less than the max velocity
				if (getVelocity().x < _maxVelocity.x)
				{
					

					// Apply impulse (move player right)
					impulse({ (float)(dt * _groundspeed), 0 });
				}
			}
			// Else left key has been pressed
			else
			{
				
				
				// Check if velocity of the player is less than the negative max velocity
				if (getVelocity().x > -_maxVelocity.x)
				{

					
					// Apply negative impulse (move player left)
					impulse({ -(float)(dt * _groundspeed), 0 });
				}
			}
			
				
			

			

		
	}
	// Check if player is has pressed right or left
	if (x < -20)
	{
		//soundfx loaded in the buffer
		//bufferWalk.loadFromFile("res/audio/fx/footsteps.wav");
		//soundWalk.setBuffer(bufferWalk);
		//soundWalk.setLoop(true);

			// Check if right key pressed
		if (x > 20)
		{


			// Check if velocity of the player is less than the max velocity
			if (getVelocity().x < _maxVelocity.x)
			{


				// Apply impulse (move player right)
				impulse({ (float)(dt * _groundspeed), 0 });
			}
		}
		// Else left key has been pressed
		else
		{


			// Check if velocity of the player is less than the negative max velocity
			if (getVelocity().x > -_maxVelocity.x)
			{


				// Apply negative impulse (move player left)
				impulse({ -(float)(dt * _groundspeed), 0 });
			}
		}







	}
	// No keys pressed
	else 
	{
		soundWalk.setLoop(false);
		// Dampen X axis movement
		dampen({0.9f, 1.0f});
	}

	// Handle Jump
	if (Keyboard::isKeyPressed(Keyboard::Up)) 
	{
		// Obtain status of player being grounded
		_grounded = isGrounded();

		// Check if player is grounded
		if (_grounded) 
		{
			//jump audio played
			bufferJump.loadFromFile("res/audio/fx/jump.wav");
			soundJump.setBuffer(bufferJump);
			soundJump.play();

			// Set velocity
			setVelocity(Vector2f(getVelocity().x, 0.f));

			// Teleport player
			teleport(Vector2f(pos.x, pos.y - 2.0f));

			// Impulse
			impulse(Vector2f(0, -6.f));
		}
	}

	// Check if player is in the air
	if (!_grounded) 
	{
		// Check if player has landed
		_grounded = isGrounded();

		// Remove friction whilst jumping
		setFriction(0.0f);
	} 
	// Player is on the ground
	else 
	{
		// Set friction to 0.1
		setFriction(0.1f);
	}

	// Obtain velocity of the player
	auto v = getVelocity();

	// Clamp X value
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);

	// Clamp Y value
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	
	// Set velocity of the player to the clamped velocity values
	setVelocity(v);

	// Update the physics component
	PhysicsComponent::update(dt);
}

// Player Physics Component constructor
PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p, const Vector2f& size)
    : PhysicsComponent(p, true, size) 
{
	// Set Size
	_size = sv2_to_bv2(size, true);

	// Set Maximum velocity in X and Y direction
	_maxVelocity = Vector2f(200.f, 400.f);

	// Set Ground Speed
	_groundspeed = 30.f;

	// Set Grounded to false
	_grounded = false;

	// Disable sleeping allowed
	_body->SetSleepingAllowed(false);

	// Fix rotation of the player
	_body->SetFixedRotation(true);

	//Bullet items have higher-res collision detection
	_body->SetBullet(true);
};
