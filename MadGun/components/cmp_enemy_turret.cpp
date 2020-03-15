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
 * Date Last Modified: 15/03/2020
 * -------------------------------------
 * ENEMY TURRET COMPONET
 * - cmp_enemy_ai.cpp
 *
 * Enemy turret component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#include "cmp_enemy_turret.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>

// Update function
//
// Function updates the Enemy Turret Component
void EnemyTurretComponent::update(double dt) 
{
	// Decrement firetime by time slice
	_firetime -= dt;

	// Check if fire time is less than, or equal to, 0
	if (_firetime <= 0.f) 
	{
		// Invoke fire function
		fire();

		// Set fire time to 1 second
		_firetime = 1.f;
	}

	// Angle of turret
	static float angle = 0.f;

	// Increment angle by time slice
	angle += 1.f * dt;

	// Rotate the parent of the enemy turret
	_parent->setRotation(180.f + sin(angle) * 45.f);
}

// Fire function
//
// Function allows the turret to fire bullet
void EnemyTurretComponent::fire() const 
{
	// Make bullet entity
	auto bullet = _parent->scene->makeEntity();

	// Set position of the bullet
	bullet->setPosition(_parent->getPosition());

	// Add hurt component
	bullet->addComponent<HurtComponent>();

	// Add Bullet component
	bullet->addComponent<BulletComponent>();

	// Add shape component to bullet
	auto s = bullet->addComponent<ShapeComponent>();

	// Set shape of the bullet component to a circle of radius 8
	s->setShape<CircleShape>(8.f);

	// Set bullet colour to red
	s->getShape().setFillColor(Color::Red);

	// Set bullet origin
	s->getShape().setOrigin(8.f, 8.f);

	// Add Physics component to bullet
	auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f));

	// Set Bullet restitution
	p->setRestitution(.4f);

	// Set bullet friction
	p->setFriction(.005f);

	// Apply impulese
	p->impulse(rotate(Vector2f(0, 15.f), -_parent->getRotation()));
}

// Enemy Turret Component constructor
EnemyTurretComponent::EnemyTurretComponent(Entity* p)
	: Component(p), _firetime(2.f) {};
