
# include "Core.h"
# include "JuiceBox2d.h"
# include <Box2D/Box2D.h>

JUICEIMPL_BEGIN

WSIDECL_PRIVATE_BEGIN_CXX(PhysicsBox2d)

void init()
{
    b2Vec2 gravity(0, -10.f);
    world = new b2World(gravity, true);
    ground_def = new b2BodyDef;
    ground_body = NULL;
}

void dealloc()
{
    safe_delete(world);
    safe_delete(ground_def);
}

b2World* world;
b2BodyDef* ground_def;
b2Body* ground_body;

WSIDECL_PRIVATE_END_CXX

PhysicsBox2d::PhysicsBox2d()
{
    WSIDECL_PRIVATE_CONSTRUCT(PhysicsBox2d);
}

PhysicsBox2d::~PhysicsBox2d()
{
    WSIDECL_PRIVATE_DESTROY();
}

void PhysicsBox2d::set_gravity(real y, real x)
{
    b2Vec2 gravity(x, y);
    d_ptr->world->SetGravity(gravity);
}

void PhysicsBox2d::prepare()
{
    //d_ptr->ground_def->position.Set(this->box.x, this->box.y);
    d_ptr->ground_body = d_ptr->world->CreateBody(d_ptr->ground_def);
    b2PolygonShape ground_box;
    //ground_box.SetAsBox(this->box.size.w, this->box.size.h);
    d_ptr->ground_body->CreateFixture(&ground_box, 0);
}

void PhysicsBox2d::update()
{
    for (int i = 0; i < 16; ++i)
    {
        d_ptr->world->Step(this->time, this->velocity, this->offset);
    }
}

phyobj_t* PhysicsBox2d::add_box(const bounding_type & box, phyparam_t const& param)
{
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    //body_def.position.Set(box.x, box.y);
    b2Body* body = d_ptr->world->CreateBody(&body_def);
    b2PolygonShape shape;
    //shape.SetAsBox(box.size.w, box.size.h);
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = param.density;
    fixture.friction = param.friction;
    fixture.restitution = param.restitution;
    body->CreateFixture(&fixture);
    return (phyobj_t*)body;
}

PhysicsBox2d::position_type PhysicsBox2d::position(const phyobj_t * obj) const
{
    b2Body* body = (b2Body*)obj;
    b2Vec2 pos = body->GetPosition();
    return *(position_type*)(void*)&pos;
}

real PhysicsBox2d::angle(const phyobj_t * obj) const
{
    b2Body* body = (b2Body*)obj;
    return body->GetAngle();
}

JUICEIMPL_END