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
 * PHYSICS COMPONENT- cmp_physics.cpp
 *
 * Physics component
 *
 * Currently populated with boiler plate
 * code from platformer practical
 *
 */

// Libraries
#include "cmp_physics.h"
#include "system_physics.h"

// Namespace
using namespace Physics;

// Update function
//
// Function updates the physics component
void PhysicsComponent::update(double dt) 
{
	// Set position of the parent
	_parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));

	// Set rotation of the parent
	_parent->setRotation((180 / b2_pi) * _body->GetAngle());
}

// Physics Component constructor
PhysicsComponent::PhysicsComponent(Entity* p, bool dyn, const Vector2f& size)
    : Component(p), _dynamic(dyn) 
{
	// Body Definiton
	b2BodyDef BodyDef;

	// Is Dynamic(moving), or static(Stationary)
	BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;

	// Position of body
	BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

	// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);

	// Set body as active
	_body->SetActive(true);
	{
		// Create the fixture shape
		b2PolygonShape Shape;

		// SetAsBox box takes HALF-Widths!
		Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
		
		// Fixture Definituon
		b2FixtureDef FixtureDef;

		// Fixture properties
		
		// Fixture Density
		// FixtureDef.density = _dynamic ? 10.f : 0.f;
		
		// Fixture Friction
		FixtureDef.friction = _dynamic ? 0.1f : 0.8f;

		// Fixture restitution
		FixtureDef.restitution = .2;

		// Fixture shape
		FixtureDef.shape = &Shape;
		
		// Add to body
		_fixture = _body->CreateFixture(&FixtureDef);
		//_fixture->SetRestitution(.9)
		//FixtureDef.restitution = .2;
	}

	// An ideal Pod/capusle shape should be used for hte player,
	// this isn't built into B2d, but we can combine two shapes to do so.
	// This would allwo the player to go up steps
	
	//BodyDef.bullet = true;
	//b2PolygonShape shape1;
	//shape1.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	//{
	//	b2PolygonShape poly ;
	//	poly.SetAsBox(0.45f, 1.4f);
	//	b2FixtureDef FixtureDefPoly;

	//	FixtureDefPoly.shape = &poly;
	//	_body->CreateFixture(&FixtureDefPoly);

	//}
	//{
	//	b2CircleShape circle;
	//	circle.m_radius = 0.45f;
	//	circle.m_p.Set(0, -1.4f);
	//	b2FixtureDef FixtureDefCircle;
	//	FixtureDefCircle.shape = &circle;
	//	_body->CreateFixture(&FixtureDefCircle);
	//}
	
}

// Set Friction
//
// Method sets the friction of the physics component
void PhysicsComponent::setFriction(float r) 
{
	// Set friction of the component
	_fixture->SetFriction(r);
}

// Set Mass function
//
// Function sets the mass of the physics component
void PhysicsComponent::setMass(float m) 
{
	// Set Density
	_fixture->SetDensity(m);
}

// Teleport function
//
// Function allows the physics component to teleport
void PhysicsComponent::teleport(const Vector2f& v)
{
	// Set Transform
	_body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

// Get Velocity function 
//
// Function returns velocity of the physics component
const Vector2f PhysicsComponent::getVelocity() const 
{
	// Obtain Velocity
	return bv2_to_sv2(_body->GetLinearVelocity(), true);
}

// Set Velocity function
//
// Function allows the velocity of the physics component to be set
void PhysicsComponent::setVelocity(const Vector2f& v) {
  _body->SetLinearVelocity(sv2_to_bv2(v, true));
}

// Get Fixture function
//
// Function returns the fixture physics component
b2Fixture* const PhysicsComponent::getFixture() const 
{
	// Return Fixture
	return _fixture; 
}

// Physics Component Deconstructor
PhysicsComponent::~PhysicsComponent() 
{
	// Get World
	auto a = Physics::GetWorld();

	// Deactivate physics body
	_body->SetActive(false);

	// Destroy body
	Physics::GetWorld()->DestroyBody(_body);

	// Set body to null pointer
	_body = nullptr;
}

// Render function
//
// Function for rendering the physics component
void PhysicsComponent::render() 
{
}

// Impulse function
//
// Function allows an impulse to be applied to a physics component
void PhysicsComponent::impulse(const Vector2f& i) 
{
	// Transform argument vector
	auto a = b2Vec2(i.x, i.y * -1.0f);

	// Apply impulse to body
	_body->ApplyLinearImpulseToCenter(a, true);
}

// Dampen function
//
// Function dampens the physics component
void PhysicsComponent::dampen(const Vector2f& i) 
{
	// Obtain the velocity of the body
	auto vel = _body->GetLinearVelocity();
	
	// Dampen the x value
	vel.x *= i.x;

	// Dampen the y value
	vel.y *= i.y;

	// Set body to dampened velocity
	_body->SetLinearVelocity(vel);
}

// Is Touching function
//
// Function determines if a physics body is touching
bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const 
{
	// Body Contact 
	b2Contact* bc;

	// Invoke 
	return isTouching(pc, bc);
}

// Is Touching function
//
// Function determines if a physics body is touching
bool PhysicsComponent::isTouching(const PhysicsComponent& pc, b2Contact const* bc) const 
{
	// Obtain other fixture
	const auto _otherFixture = pc.getFixture();

	// Obtan world
	const auto& w = *Physics::GetWorld();

	// Obtain Contact list
	const auto contactList = w.GetContactList();

	// Count contacts
	const auto clc = w.GetContactCount();
	
	// Iterate over all contacts
	for (int32 i = 0; i < clc; i++) 
	{
		// Obtain contact at position i
		const auto& contact = (contactList[i]);

		// Check if contact is touching
		if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture && contact.GetFixtureA() == _otherFixture) || (contact.GetFixtureA() == _otherFixture && contact.GetFixtureA() == _fixture))) 
		{
			// Set contact
			bc = &contact;

			// Return true
			return true;
		}
	}

	// Return false
	return false;
}

// Get Touching function
//
// Function returns contacts of a physics component
vector<const b2Contact const*> PhysicsComponent::getTouching() const 
{
	// Empty return vector
	vector<const b2Contact const*> ret;

	// Obtain edge
	b2ContactEdge* edge = _body->GetContactList();

	// Loop whilst edge is not null
	while (edge != NULL) 
	{
		// Obtain contact from edge
		const b2Contact* contact = edge->contact;

		// Check if contact is touching
		if (contact->IsTouching()) 
		{
			// Add contact to return vector
			ret.push_back(contact);
		}

		// Look at next edge
		edge = edge->next;
	}
	
	// Return the return vector
	return ret;
}

// Set Restitution function
//
// Function allows the restitution of the physics component to be set
void PhysicsComponent::setRestitution(float r)
{
	// Set Restitution
	_fixture->SetRestitution(r);
}
