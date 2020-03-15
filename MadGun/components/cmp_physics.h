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
 * PHYSICS COMPONENT- cmp_physics.h
 *
 * Header file for physics component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#pragma once
#include "cmp_sprite.h"
#include "ecm.h"
#include <Box2D/Dynamics/b2Body.h>

// Namespaces
using namespace std; // Standard namespace
using namespace sf; // SFML namespace

/*
 * PHYSICS COMPONENT CLASS
 */
class PhysicsComponent : public Component 
{
	protected:
		// Box2D body
		b2Body* _body;

		// Dynamic boolean
		const bool _dynamic;

		// Box2D fixture
		b2Fixture* _fixture;

	public:
		// Physics component constructor
		PhysicsComponent(Entity* p, bool dyn, const Vector2f& size);

		// Get Fixture function
		b2Fixture* const getFixture() const;

		// Is Touching function
		bool isTouching(const PhysicsComponent& pc) const;

		// Is Touching function
		bool isTouching(const PhysicsComponent& pc, b2Contact const* bc) const;

		// Get Touching function
		vector<const b2Contact*> getTouching() const;

		// Get Velocity function
		const Vector2f getVelocity() const;

		// Set Restitution function
		void setRestitution(float r);

		// Set Friction function
		void setFriction(float r);

		// Set Mass function
		void setMass(float m);

		// Update Function
		void update(double dt) override;

		// Render function
		void render() override;
		
		// Impulse function
		void impulse(const Vector2f& i);

		// Dampen function
		void dampen(const Vector2f& s);

		// Set Velocity function
		void setVelocity(const Vector2f& v);

		// Teleport function
		void teleport(const Vector2f& v);

		// Physics Component deconstructor
		~PhysicsComponent() override;
};
