/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */


#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
    b2Body* b1;  
    //Ground
    //~ {
      //~ 
      //~ b2EdgeShape shape; 
      //~ shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      //~ b2BodyDef bd; 
      //~ b1 = m_world->CreateBody(&bd); 
      //~ b1->CreateFixture(&shape, 0.0f);
    //~ }
    
    
    //~ {
      //~ 
      //~ b2EdgeShape shape; 
      //~ shape.Set(b2Vec2(-10.0f, 7.0f), b2Vec2(0.0f, 7.0f));
      //~ b2BodyDef bd; 
      //~ b1 = m_world->CreateBody(&bd); 
      //~ b1->CreateFixture(&shape, 0.0f);
    //~ }
    //~ 
    //~ 
    //~ {
      //~ 
      //~ b2EdgeShape shape; 
      //~ shape.Set(b2Vec2(-10.0f, 5.0f), b2Vec2(0.0f, 5.0f));
      //~ b2BodyDef bd; 
      //~ b1 = m_world->CreateBody(&bd); 
      //~ b1->CreateFixture(&shape, 0.0f);
    //~ }
    
    //Edge on which long rod rests
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-5.0f, 10.0f), b2Vec2(5.0f, 10.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    
    
     //Hole Edge
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-24.0f, 12.0f), b2Vec2(-16.1f, 10.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
     
     
     //Hole Edge 
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-12.0f, 10.0f), b2Vec2(-9.0f, 10.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    
    
    //Left Vertical side
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-16.1f, 10.0f), b2Vec2(-16.1f, 6.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    
    //Right vertical side
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-11.9f, 10.0f), b2Vec2(-11.9f, 6.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
     
    //Base of hole
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-12.0f, 6.0f), b2Vec2(-16.0f, 6.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    
    
     //~ {
      //~ b2PolygonShape shape;
      //~ shape.SetAsBox(2.0f, 0.25f, b2Vec2(-10.f,15.f), 0.0f);
	//~ 
      //~ b2BodyDef bd;
      //~ bd.position.Set(10.0f, 18.0f);
      //~ b2Body* ground = m_world->CreateBody(&bd);
      //~ ground->CreateFixture(&shape, 0.0f);
    //~ }
     
  //Two cornered pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,25);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 15.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-2.0f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(10,25);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 35); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 35); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    
    
    
    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 28.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 28.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 24.1f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 30.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
    
    
    
    
    //Single Cornered pulley system
    {
		
		 b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(18,9);
      bd->fixedRotation = true;
		
       //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-2.0f), 0);
      fd1->shape = &bs1;
      
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(-10,10);	
      fd1->density = 34.0;
      bs1.SetAsBox(6,0.2, b2Vec2(0.f,0.2f), 0);
      fd1->shape = &bs1;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      //b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      //b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      //b2Vec2 worldAnchorGround1(10, 10.2); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(18, 10.2); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround2, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
      
      
      //The bar
      bd->position.Set(-14,12);	
      fd1->density = 34.0;
      fd1->friction=0.0;
      bs1.SetAsBox(2,2, b2Vec2(0.f,0.2f), 0);
      fd1->shape = &bs1;	  
      b2Body* box3 = m_world->CreateBody(bd);
      box3->CreateFixture(fd1);
      
      
    }
    
    
    
    
       
     
     
          
}

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
