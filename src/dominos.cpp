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
    
     //nithish scope starts here  
    { 
     float x=-1.0,y=5.0;
     float a=-1.0,b=-1.0;
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
      bs1.SetAsBox(2,0.2, b2Vec2(x+0.f,y-2.0f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(x+2.0f,y+0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(x-2.0f,y+0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(10,25);	
      fd1->density = 35.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(x-10, y+15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(x+10, y+15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(x-10, y+35); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(x+10, y+35); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    //The revolving horizontal platform
    {
		
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(x+14.0f, y+28.0f);
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
      bd2.position.Set(x+14.0f, y+28.0f);
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
      ballbd.position.Set(x+14.0f, y+30.0f);
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
      bs1.SetAsBox(2,0.2, b2Vec2(a+0.f,b-2.0f), 0);
      fd1->shape = &bs1;
      
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(a+2.0f,b+0.f), 0);
      fd2->shape = &bs2;
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(a-2.0f,b+0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(-10,10);	
      fd1->density = 34.0;
      bs1.SetAsBox(6,0.2, b2Vec2(a+0.f,b+0.2f), 0);
      fd1->shape = &bs1;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      //b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      //b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      //b2Vec2 worldAnchorGround1(10, 10.2); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(a+18, b+10.2); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround2, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
      
      
      //The Box on the bar
      bd->position.Set(-14,12);	
      fd1->density = 34.0;
      fd1->friction=0.0;
      bs1.SetAsBox(2,2, b2Vec2(a+0.f,b+0.2f), 0);
      fd1->shape = &bs1;	  
      b2Body* box3 = m_world->CreateBody(bd);
      box3->CreateFixture(fd1);
      
      
    }
    
    
    //Base of pulley to stop the pulley
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a+16.0f, b-4.0f), b2Vec2(a+20.0f, b-4.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }

    //Edge on which long rod rests
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a-5.0f, b+10.0f), b2Vec2(a+5.0f, b+10.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }

     //Slant Hole Edge
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a-18.0f, b+12.0f), b2Vec2(a-16.1f, b+10.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
      //Small Horizontal edge
      shape.Set(b2Vec2(a-24.0f, b+12.0f), b2Vec2(a-18.0f, b+12.0f));
      b1->CreateFixture(&shape,0.0f);
    

      //The sphere on the small hole edge
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 24.1f;
      ballfd.friction = 1.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(a-23.0f,b+13.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    }
     
     
     //Hole Edge 
    {
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a-12.0f, b+10.0f), b2Vec2(a-9.0f, b+10.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    
    
    //Left Vertical side
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a-16.1f, b+10.0f), b2Vec2(a-16.1f, b+6.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    
    //Right vertical side
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a-11.9f, b+10.0f), b2Vec2(a-11.9f, b+6.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
     
    //Base of hole
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(a-12.0f, b+6.0f), b2Vec2(a-16.0f, b+6.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
    //curve to guide the ball
    {
      b2Body * curve1;
      b2EdgeShape shape1[10];
      b2BodyDef shape1bd[10];
      b2FixtureDef shape1fd[10];
      float32 x1 = a+5.0f; float32 y1 = -5.0f;
      float32 radius = 10;

      for(int i = 5 ; i < 10 ; i++){
        shape1[i].Set(b2Vec2( x1+radius*cos(i*b2_pi/20.0-b2_pi) , y1 +radius*sin(i*b2_pi/20.0-b2_pi) ) , 
          b2Vec2( x1+radius*cos((i+1)*b2_pi/20.0-b2_pi) , y1 + radius*sin((i+1)*b2_pi/20.0-b2_pi)));

        shape1fd[i].friction = 0;
        shape1fd[i].shape = &shape1[i];
        shape1fd[i].restitution = 0;
        curve1 = m_world->CreateBody(&shape1bd[i]);
        curve1->CreateFixture(&shape1fd[i]);
      }
    }
    //another ball just for chutiyap
    {
      b2Body* spherebody;   
      b2CircleShape circle;
      circle.m_radius = 0.5;
   
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 8.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.7f;

   
     b2BodyDef ballbd;
     ballbd.type = b2_dynamicBody;
     ballbd.position.Set(a+5.5f,-15.0f);
     spherebody = m_world->CreateBody(&ballbd);
     spherebody->CreateFixture(&ballfd);

    }
    //curve to guide the balls
    {
      b2Body * curve1;
      b2EdgeShape shape1[10];
      b2BodyDef shape1bd[10];
      b2FixtureDef shape1fd[10];
      float32 x1 = a+20.0f; float32 y1 = -5.0f;
      float32 radius = 10;

      for(int i = 0; i < 8 ; i++){
        shape1[i].Set(b2Vec2( x1+radius*cos(i*b2_pi/20.0-b2_pi/2) , y1 +radius*sin(i*b2_pi/20.0-b2_pi/2) ) , 
          b2Vec2( x1+radius*cos((i+1)*b2_pi/20.0-b2_pi/2) , y1 + radius*sin((i+1)*b2_pi/20.0-b2_pi/2)));

        shape1fd[i].friction = 0;
        shape1fd[i].shape = &shape1[i];
        shape1fd[i].restitution = 0;
        curve1 = m_world->CreateBody(&shape1bd[i]);
        curve1->CreateFixture(&shape1fd[i]);
      }
    }
}
//nithish scope ends here       
     
     //*************************************************
     
     //Devanshu scope
  {
   float x=-62.0;
   // float y=38.0;//for perfect matching
   float y=43.0;
    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, -15.0f), b2Vec2(90.0f, -15.0f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }   
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
   
      b2BodyDef bd;
      bd.position.Set(x+0.0f, y+10.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
   
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      
      for (int i = 0; i < 9; ++i)
   {
     b2BodyDef bd;
     bd.type = b2_dynamicBody;
     bd.position.Set(x-4.0f + 1.0f * i, y+10.0f+1.25f);
     b2Body* body = m_world->CreateBody(&bd);
     body->CreateFixture(&fd);
   }
    }
    //ball at the end of dominos
    {
      b2Body* spherebody;   
      b2CircleShape circle;
      circle.m_radius = 0.5;
   
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 6.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;

   
     b2BodyDef ballbd;
     ballbd.type = b2_dynamicBody;
     ballbd.position.Set(x+5.0f,y+10.25f);
     spherebody = m_world->CreateBody(&ballbd);
     spherebody->CreateFixture(&ballfd);

     b2BodyDef ball1bd;
     ball1bd.type = b2_dynamicBody;
     ball1bd.position.Set(x-5.0f,y+0.25f);
     spherebody = m_world->CreateBody(&ball1bd);
     spherebody->CreateFixture(&ballfd);

     b2BodyDef ball2bd;
     ball2bd.type = b2_dynamicBody;
     ball2bd.position.Set(x+5.0f,y-10.0+0.2f);
     ballfd.density = 20.0f;
     ballfd.friction = 0.5f;
     spherebody = m_world->CreateBody(&ball2bd);
     spherebody->CreateFixture(&ballfd);

    }

    //the curves that guide the ball
        {

      b2Body * curve1; b2Body * curve2;b2Body * curve3; b2Body * curve4;
      b2EdgeShape shape1[20]; b2EdgeShape shape2[20];b2EdgeShape shape3[20]; b2EdgeShape shape4[20];
      b2BodyDef shape1bd[20]; b2BodyDef shape2bd[20];b2BodyDef shape3bd[20]; b2BodyDef shape4bd[20];
      b2FixtureDef shape1fd[20]; b2FixtureDef shape2fd[20];b2FixtureDef shape3fd[20]; b2FixtureDef shape4fd[20];
		
		//~ x+0.0f, y+10.0f
		//~ x+0.0f, y+0.0f
		float32 x1 = x+6.0f; float32 y1 = y+6.0f;
      float32 x2=x-6.0f;  float32 y2 = y-4.0f;
      float32 radius = 4.3;
      float32 radius1= 5.7;

      for(int i = 0 ; i < 20 ; i++){
        shape1[i].Set(b2Vec2( x1+radius*cos(i*b2_pi/20.0-b2_pi/2.0) , y1 +radius*sin(i*b2_pi/20.0-b2_pi/2.0) ) , 
          b2Vec2( x1+radius*cos((i+1)*b2_pi/20.0-b2_pi/2.0) , y1 + radius*sin((i+1)*b2_pi/20.0-b2_pi/2.0)));

        shape2[i].Set(b2Vec2( x2+radius*cos(i*b2_pi/20.0+b2_pi/2.0) , y2 + radius*sin(i*b2_pi/20.0+b2_pi/2.0)) , 
          b2Vec2( x2+radius*cos((i+1)*b2_pi/20.0+b2_pi/2.0) , y2 + radius*sin((i+1)*b2_pi/20.0+b2_pi/2.0)));

        shape3[i].Set(b2Vec2( x1+radius1*cos(i*b2_pi/20.0-b2_pi/2.0) , y1 +radius1*sin(i*b2_pi/20.0-b2_pi/2.0) ) , 
          b2Vec2( x1+radius1*cos((i+1)*b2_pi/20.0-b2_pi/2.0) , y1 + radius1*sin((i+1)*b2_pi/20.0-b2_pi/2.0)));

        shape4[i].Set(b2Vec2( x2+radius1*cos(i*b2_pi/20.0+b2_pi/2.0) , y2 + radius1*sin(i*b2_pi/20.0+b2_pi/2.0)) , 
          b2Vec2( x2+radius1*cos((i+1)*b2_pi/20.0+b2_pi/2.0) , y2 + radius1*sin((i+1)*b2_pi/20.0+b2_pi/2.0)));

        shape1fd[i].friction = 0; shape2fd[i].friction = 0;
        shape1fd[i].shape = &shape1[i]; shape2fd[i].shape = &shape2[i];
        shape1fd[i].restitution = 0; shape2fd[i].restitution = 0;

        shape3fd[i].friction = 0; shape4fd[i].friction = 0;
        shape3fd[i].shape = &shape3[i]; shape4fd[i].shape = &shape4[i];
        shape3fd[i].restitution = 0; shape4fd[i].restitution = 0;
        curve1 = m_world->CreateBody(&shape1bd[i]);

        curve1->CreateFixture(&shape1fd[i]);
        curve2 = m_world->CreateBody(&shape2bd[i]);
        curve2->CreateFixture(&shape2fd[i]);
        curve3 = m_world->CreateBody(&shape3bd[i]);
        curve3->CreateFixture(&shape3fd[i]);
        curve4 = m_world->CreateBody(&shape4bd[i]);
        curve4->CreateFixture(&shape4fd[i]);
      }
    }

   //another shelf and more Dominos and ball
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
      b2BodyDef bd;
      bd.position.Set(x+0.0f, y+0.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);

   
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      
      for (int i = 0; i < 10; ++i)
   {
     b2BodyDef bd;
     bd.type = b2_dynamicBody;
     bd.position.Set(x-4.0f+ 1.0f * i, y+0.0f+1.25f);
     b2Body* body = m_world->CreateBody(&bd);
     body->CreateFixture(&fd);

   }
    }
    //one more dominos ka table
    {
      b2PolygonShape shape1;
      shape1.SetAsBox(6.0f, 0.25f);
      b2BodyDef bd1;
      bd1.position.Set(x+0.0f, y-10.0f);
      b2Body* ground = m_world->CreateBody(&bd1);
      ground->CreateFixture(&shape1, 0.0f);
    }
    {
      b2PolygonShape shape1;
      shape1.SetAsBox(0.1f, 1.0f);
      b2FixtureDef fd;
      fd.shape = &shape1;
      fd.density = 20.0f;
      fd.friction = 0.2f;
      for (int i = 0; i < 9; ++i)
   {

     b2BodyDef bd1;
     bd1.type = b2_dynamicBody;
     bd1.position.Set(x-4.0f+ 1.0f * i, y-10.0f+1.25f);
     b2Body* body = m_world->CreateBody(&bd1);
     body->CreateFixture(&fd); 
   }
    }

    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
         b2PolygonShape shape;
         shape.SetAsBox(0.25f, .25f);
           
         b2BodyDef bd;
   

         bd.position.Set(x-6.5f, y+10.0f);
         b2 = m_world->CreateBody(&bd);
         b2->CreateFixture(&shape, 10.0f);
      }
   
      b2Body* b4;
      {
         b2PolygonShape shape;
         shape.SetAsBox(.25f, 0.25f);
           
         b2BodyDef bd;
         bd.type = b2_dynamicBody;
         bd.position.Set(x-12.0f, y+13.5f);
         b4 = m_world->CreateBody(&bd);
         b4->CreateFixture(&shape, 2.0f);
      }
   
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(x-7.0f, y+20.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
    //the single curves guiding the ball at the end
   {

      b2Body * curve1; b2Body * curve2;b2Body * curve3; b2Body * curve4;
      b2EdgeShape shape1[10]; b2EdgeShape shape2[10];b2EdgeShape shape3[10]; b2EdgeShape shape4[10];
      b2BodyDef shape1bd[10]; b2BodyDef shape2bd[10];b2BodyDef shape3bd[10]; b2BodyDef shape4bd[10];
      b2FixtureDef shape1fd[10]; b2FixtureDef shape2fd[10];b2FixtureDef shape3fd[10]; b2FixtureDef shape4fd[10];
      
      //~ x+0.0f, y+10.0f
      //~ x+0.0f, y+0.0f
      float32 x1 = x+6.0f; float32 y1 = y-10.0f;
      float32 x2=x+6.0f;  float32 y2 = y-14.0f;
      float32 x3=x+6.0f;  float32 y3 = y-18.0f;
      float32 x4=x+6.0f;  float32 y4 = y-22.0f;
      float32 radius = 4;
      float32 radius1= 4;

      for(int i = 0 ; i < 10 ; i++){
        shape1[i].Set(b2Vec2( x1+radius*cos(i*b2_pi/20.0-b2_pi/2.0) , y1 +radius*sin(i*b2_pi/20.0-b2_pi/2.0) ) , 
          b2Vec2( x1+radius*cos((i+1)*b2_pi/20.0-b2_pi/2.0) , y1 + radius*sin((i+1)*b2_pi/20.0-b2_pi/2.0)));

        shape2[i].Set(b2Vec2( x2+radius*cos(i*b2_pi/20.0+b2_pi) , y2 + radius*sin(i*b2_pi/20.0+b2_pi)) , 
          b2Vec2( x2+radius*cos((i+1)*b2_pi/20.0+b2_pi) , y2 + radius*sin((i+1)*b2_pi/20.0+b2_pi)));

        shape3[i].Set(b2Vec2( x3+radius1*cos(i*b2_pi/20.0-b2_pi/2.0) , y3 +radius1*sin(i*b2_pi/20.0-b2_pi/2.0) ) , 
          b2Vec2( x3+radius1*cos((i+1)*b2_pi/20.0-b2_pi/2.0) , y3 + radius1*sin((i+1)*b2_pi/20.0-b2_pi/2.0)));

        shape4[i].Set(b2Vec2( x4+radius1*cos(i*b2_pi/20.0+b2_pi) , y4 + radius1*sin(i*b2_pi/20.0+b2_pi)) , 
          b2Vec2( x4+radius1*cos((i+1)*b2_pi/20.0+b2_pi) , y4 + radius1*sin((i+1)*b2_pi/20.0+b2_pi)));

        shape1fd[i].friction = 0; shape2fd[i].friction = 0;
        shape1fd[i].shape = &shape1[i]; shape2fd[i].shape = &shape2[i];
        shape1fd[i].restitution = 0; shape2fd[i].restitution = 0;

        shape3fd[i].friction = 0; shape4fd[i].friction = 0;
        shape3fd[i].shape = &shape3[i]; shape4fd[i].shape = &shape4[i];
        shape3fd[i].restitution = 0; shape4fd[i].restitution = 0;
        curve1 = m_world->CreateBody(&shape1bd[i]);
        curve1->CreateFixture(&shape1fd[i]);
        curve2 = m_world->CreateBody(&shape2bd[i]);
        curve2->CreateFixture(&shape2fd[i]);
        curve3 = m_world->CreateBody(&shape3bd[i]);
        curve3->CreateFixture(&shape3fd[i]);
        curve4 = m_world->CreateBody(&shape4bd[i]);
        curve4->CreateFixture(&shape4fd[i]);
      }
    }
    //pathway for the ball at the end
  {
    b2EdgeShape shape;
    shape.Set(b2Vec2(x+5.0,y-26.0),b2Vec2(x+15.6,y-26.0));
    b2BodyDef bd;
    b1=m_world->CreateBody(&bd);
    b1->CreateFixture(&shape,0.0f);
  }
    //pathway for the ball after the rotating rods and the ball at the start of it
  {
    b2EdgeShape shape;
    shape.Set(b2Vec2(x+15.4f,y-6.8f),b2Vec2(x+45.0f,y-6.8f));
    b2BodyDef bd;
    b1=m_world->CreateBody(&bd);
    b1->CreateFixture(&shape,0.0f);
    //ball on the pathway
    b2Body* spherebody;   
    b2CircleShape circle;
    circle.m_radius = 0.5;
 
    b2FixtureDef ballfd;
    ballfd.shape = &circle;
    ballfd.density = 5.0f;
    ballfd.friction = 0.0f;
    ballfd.restitution = 1.0f;

     b2BodyDef ballbd;
     ballbd.type = b2_dynamicBody;
     ballbd.position.Set(x+15.7f,y-6.8f);
     spherebody = m_world->CreateBody(&ballbd);
     spherebody->CreateFixture(&ballfd);

     b2BodyDef balls[11];
     for(int i=0;i<11;i++){
      balls[i].type=b2_dynamicBody;
      balls[i].position.Set(x+15.7f+2.5f*(i+1),y-6.8f);
      // ballfd.density = 6.0f-i;
      if(i==10)ballfd.restitution = 0.0f;
      spherebody = m_world->CreateBody(&balls[i]);
      spherebody->CreateFixture(&ballfd);
     }
  }
  //hinged rotating rods
  {
    b2PolygonShape shape;
    shape.SetAsBox(0.2f,5.0f);
    b2BodyDef bd;
    bd.position.Set(x+15.0,y-21.0f);
    bd.type=b2_dynamicBody;
    b2Body* body=m_world->CreateBody(&bd);

    b2FixtureDef *fd=new b2FixtureDef;
    fd->density=1.0f;
    fd->shape=new b2PolygonShape;
    fd->shape=&shape;
    body->CreateFixture(fd);

    b2PolygonShape shape2;
    shape2.SetAsBox(0.2f, 2.0f);
    b2BodyDef bd2;
    bd2.position.Set(x+16.0f, y-20.6f);
    b2Body* body2 = m_world->CreateBody(&bd2);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.bodyB = body2;
    jointDef.localAnchorA.Set(0,0);
    jointDef.localAnchorB.Set(0,0);
    jointDef.collideConnected = false;
    m_world->CreateJoint(&jointDef);
  }
  //second hinged rotating rod
  {
    b2PolygonShape shape;
    shape.SetAsBox(0.2f,5.0f);
    b2BodyDef bd;
    bd.position.Set(x+15.0f,y-11.0f);
    bd.type=b2_dynamicBody;
    b2Body* body=m_world->CreateBody(&bd);

    b2FixtureDef *fd=new b2FixtureDef;
    fd->density=1.0f;
    fd->shape=new b2PolygonShape;
    fd->shape=&shape;
    body->CreateFixture(fd);

    b2PolygonShape shape2;
    shape2.SetAsBox(0.2f, 2.0f);
    b2BodyDef bd2;
    bd2.position.Set(x+14.8,y-11.2f);
    b2Body* body2 = m_world->CreateBody(&bd2);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.bodyB = body2;
    jointDef.localAnchorA.Set(0,0);
    jointDef.localAnchorB.Set(0,0);
    jointDef.collideConnected = false;
    m_world->CreateJoint(&jointDef);
  }
  //The see-saw system at the bottom
{
    float sx=x+27.0,sy=6.0;
    // //Temporary ball
    // {
    // b2Body* spherebody;
    // b2CircleShape circle;
    // circle.m_radius = 0.5;

    // b2FixtureDef ballfd;
    // ballfd.shape = &circle;
    // ballfd.density = 36.0f;
    // ballfd.friction = 0.0f;
    // ballfd.restitution = 0.5f;


    // b2BodyDef ballbd;
    // ballbd.type = b2_dynamicBody;
    // ballbd.position.Set(sx-8.0f,sy+9.0f);
    // spherebody = m_world->CreateBody(&ballbd);
    // spherebody->CreateFixture(&ballfd);
    // }

    //The triangle wedge

    b2Body* sbody;
    b2PolygonShape poly;
    b2Vec2 vertices[3];
    vertices[0].Set(-1.5,-1.5);
    vertices[1].Set(1.5,-1.5);
    vertices[2].Set(0,1);
    poly.Set(vertices, 3);
    b2FixtureDef wedgefd;
    wedgefd.shape = &poly;
    wedgefd.density = 10.0f;
    wedgefd.friction = 0.0f;
    wedgefd.restitution = 0.0f;
    b2BodyDef wedgebd;
    wedgebd.position.Set(sx+0.0f, sy-2.0f);
    sbody = m_world->CreateBody(&wedgebd);
    sbody->CreateFixture(&wedgefd);


    //Base of seesaw
    {
    b2EdgeShape shape;
    shape.Set(b2Vec2(sx-20.0f, sy-2.0f-1.5), b2Vec2(sx+20.0f, sy-2.0f-1.5));
    b2BodyDef bd;
    b1 = m_world->CreateBody(&bd);
    b1->CreateFixture(&shape, 0.0f);
    }


    //The plank on top of the wedge
    b2PolygonShape shape;
    shape.SetAsBox(8.0f, 0.1f);
    b2BodyDef bd2;
    bd2.position.Set(sx, sy-2.0f+1.0f);
    bd2.type = b2_dynamicBody;
    b2Body* body = m_world->CreateBody(&bd2);
    b2FixtureDef *fd2 = new b2FixtureDef;
    fd2->density = 1.0f;
    //~ fd2->density = 5.0f;
    fd2->shape = new b2PolygonShape;
    fd2->shape = &shape;
    body->CreateFixture(fd2);

    b2RevoluteJointDef jd;
    b2Vec2 anchor;
    anchor.Set(sx+0.0f, sy-0.9f);
    jd.Initialize(sbody, body, anchor);
    m_world->CreateJoint(&jd);

    //The light box on the right side of the see-saw
    b2PolygonShape shape2;
    shape2.SetAsBox(0.5f, 0.5f);
    b2BodyDef bd3;
    bd3.position.Set(sx+7.4f, sy);
    bd3.type = b2_dynamicBody;
    b2Body* body3 = m_world->CreateBody(&bd3);
    b2FixtureDef *fd3 = new b2FixtureDef;
    fd3->density = 3.0f;
    fd3->friction=2.0f;
    fd3->shape = new b2PolygonShape;
    fd3->shape = &shape2;
    body3->CreateFixture(fd3);

    //~ b2PolygonShape shape4;
    //~ shape4.SetAsBox(0.2f, 0.2f);
    //~ b2BodyDef bd4;
    //~ bd4.position.Set(lx+8.0f, ly-7.0f);
    //~ b2Body* body4 = m_world->CreateBody(&bd4);
    //~ b2FixtureDef *fd4 = new b2FixtureDef;
    //~ fd4->shape = new b2PolygonShape;
    //~ fd4->shape = &shape4;
    //~ body4->CreateFixture(fd4);

    }
    //Seesaw part done 
    
}
//Devanshu scope ends here
    
    
    //Kuladeep Scope
    { float x= 23.5;
      float y=-7.3;
    

    b2Body* b1;
    
    b2BodyDef *bd = new b2BodyDef;//for the hydraulic part world
      bd->type = b2_staticBody;
      bd->position.Set(x,y);
      b2FixtureDef *fd1 = new b2FixtureDef;//for the leftmost half
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(0.2,7.5, b2Vec2(x-10.0f,y+7.5f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;//downhalf of the right most 
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,4, b2Vec2(x+10.0f,y+4.0f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd7 = new b2FixtureDef;//downhalf of the right most 
      fd7->shape = new b2PolygonShape;
      b2PolygonShape bs7;
      bs7.SetAsBox(0.2,2.5, b2Vec2(x+10.0f,y+12.5f), 0);
      fd7->shape = &bs7;
      b2FixtureDef *fd3 = new b2FixtureDef;//second left most
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,6, b2Vec2(x-4.0f,y+9.0f), 0);
      fd3->shape = &bs3;
      b2FixtureDef *fd4 = new b2FixtureDef;//first right
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(0.2,6, b2Vec2(x+8.0f,y+9.0f), 0);
      fd4->shape = &bs4;
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->shape = new b2PolygonShape;//centre upper
      b2PolygonShape bs5;
      bs5.SetAsBox(6,0.2, b2Vec2(x+2.0f,y+3.0f), 0);
      fd5->shape = &bs5;
      b2FixtureDef *fd6 = new b2FixtureDef;//centre lower
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(10,0.2, b2Vec2(x+0.0f,y+0.0f), 0);
      fd6->shape = &bs6;
      b2FixtureDef *fd8 = new b2FixtureDef;//for the pot left
      fd8->shape = new b2PolygonShape;
      b2PolygonShape bs8;
      bs8.SetAsBox(0.2,2.5, b2Vec2(x+15.0f,y+2.5f), (b2_pi/6));
      fd8->shape = &bs8;
      b2FixtureDef *fd9 = new b2FixtureDef;//for the pot right
      fd9->shape = new b2PolygonShape;
      b2PolygonShape bs9;
      bs9.SetAsBox(0.2,2.5, b2Vec2(x+20.0f,y+2.5f), -(b2_pi/6));
      fd9->shape = &bs9;
      b2FixtureDef *fd10 = new b2FixtureDef;//for the pot bottom
      fd10->shape = new b2PolygonShape;
      b2PolygonShape bs10;
      bs10.SetAsBox(1.1,0.2, b2Vec2(x+17.5f,y+0.0f), 0);
      fd10->shape = &bs10;
      b2FixtureDef *fd11 = new b2FixtureDef;//for the plant stem
      fd11->shape = new b2PolygonShape;
      b2PolygonShape bs11;
      bs11.SetAsBox(0.2,1, b2Vec2(x+17.5f,y+3.5f), 0);
      fd11->shape = &bs11;
      b2Body* box1 = m_world->CreateBody(bd);//drawing the parts
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->CreateFixture(fd5);
      box1->CreateFixture(fd6);
      box1->CreateFixture(fd7);
      box1->CreateFixture(fd8);
      box1->CreateFixture(fd9);
      box1->CreateFixture(fd10);
      box1->CreateFixture(fd11);
      b2EdgeShape plantedge;//this is for the surface of the soil 
      plantedge.Set(b2Vec2(2*x+15.5f, 2*y+2.5f), b2Vec2(2*x+19.5f, 2*y+2.5f));
      b2BodyDef bdd;
      b1 = m_world->CreateBody(&bdd); 
      b1->CreateFixture(&plantedge, 0.0f);
      
     {
      b2Body* spherebody1;//for the plant
        b2CircleShape circle;
        circle.m_radius = 1.0;
	    b2FixtureDef ballfd1;
        ballfd1.shape = &circle;
        b2BodyDef ballbd1;
	  	//~ ballbd1.type = b2_dynamicBody;
	  	ballfd1.friction = 0.0f;
     	ballfd1.restitution = 0.1f;
	    ballbd1.position.Set(2*x+17.5f ,2*y+5.5f);
	    spherebody1 = m_world->CreateBody(&ballbd1);
	    spherebody1->CreateFixture(&ballfd1);
	    
	    b2Body* spherebody2;//for the plant
        circle.m_radius = 0.6;
	    b2FixtureDef ballfd2;
        ballfd2.shape = &circle;
        b2BodyDef ballbd2;
	  	//~ ballbd2.type = b2_dynamicBody;
	  	ballfd2.friction = 0.0f;
     	ballfd2.restitution = 0.1f;
	    ballbd2.position.Set(2*x+17.5f ,2*y+7.1f);
	    spherebody2 = m_world->CreateBody(&ballbd2);
	    spherebody2->CreateFixture(&ballfd2);
	    }
      { 
        
      for(int i=0;i<15;i++){//fluid in the right piston
      for(int j=0;j<27;j++){
      	b2Body* spherebody;
        b2CircleShape circle;
        circle.m_radius = 0.2;
	    b2FixtureDef ballfd;
        ballfd.shape = &circle;
        b2BodyDef ballbd;
	  	ballbd.type = b2_dynamicBody;
	  	ballfd.friction = 0.0f;
     	ballfd.restitution = 0.1f;
        ballfd.density= 0.05f;
	    ballbd.position.Set(2*x-9.0f+i*0.3f ,2*y+9.2f-j*0.3f);
	    spherebody = m_world->CreateBody(&ballbd);
	    spherebody->CreateFixture(&ballfd);
      }}}
      {        
        
      for(int i=0;i<3;i++){
      for(int j=0;j<27;j++){//fluid in the left piston

      	b2Body* spherebody;
        b2CircleShape circle;
        circle.m_radius = 0.2;
	    b2FixtureDef ballfd;
        ballfd.shape = &circle;
        b2BodyDef ballbd;
	  	ballbd.type = b2_dynamicBody;
	  	ballfd.friction = 0.0f;
     	ballfd.restitution = 0.1f;
        ballfd.density= 0.05f;
	    ballbd.position.Set(2*x+8.8f+i*0.3f ,2*y+9.2f-j*0.3f);
	    spherebody = m_world->CreateBody(&ballbd);
	    spherebody->CreateFixture(&ballfd);
      }}
      for(int i=0;i<25;i++){
      for(int j=0;j<4;j++){//fluid in the centre

      	b2Body* spherebody;
        b2CircleShape circle;
        circle.m_radius = 0.2;
	    b2FixtureDef ballfd;
        ballfd.shape = &circle;
        b2BodyDef ballbd;
	  	ballbd.type = b2_dynamicBody;
	  	ballfd.friction = 0.0f;
     	ballfd.restitution = 0.1f;
        ballfd.density= 0.05f;
	    ballbd.position.Set(2*x-2.0f+i*0.4f ,2*y+2.6f-j*0.4f);
	    spherebody = m_world->CreateBody(&ballbd);
	    spherebody->CreateFixture(&ballfd);
      }}}
     {
     
      
       b2PolygonShape shape;//piston piece on right
      shape.SetAsBox(2.80f, 0.6f);
      b2BodyDef bda;
      bda.position.Set(2*x-7.0f,2*y+12.0f);
      bda.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bda);
      b2FixtureDef *fda = new b2FixtureDef;
      fda->density = 0.01f;
      fda->shape = new b2PolygonShape;
      fda->shape = &shape;
      body->CreateFixture(fda);
      }
      /*
            b2PolygonShape shape1;//piston piece on left 
      shape1.SetAsBox(0.6f, 0.2f);

      b2BodyDef bda1;
      bda1.position.Set(x+9.1f, y+8.9f);
      bda1.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bda1);
      b2FixtureDef *fda1 = new b2FixtureDef;
      fda1->density = 1.0f;
      fda1->shape = new b2PolygonShape;
      fda1->shape = &shape1;
      body1->CreateFixture(fda1);
      }*/
      //bd->fixedRotation = true;
      
      //Mouth of Hydraulic Machine
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(x+31.0f, y+8.0f-0.3), b2Vec2(x+34.0f, y+8.0f-0.3));
      b2BodyDef bd; 
      // bd.bullet=true;
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
      
      shape.Set(b2Vec2(2*x+10.2f, 2*y+10.0), b2Vec2(2*x+12.0f, 2*y+10.0));
      b1->CreateFixture(&shape, 0.0f);
      
      shape.Set(b2Vec2(2*x+10.2f, 2*y+8.0), b2Vec2(2*x+12.0f, 2*y+8.0));
      b1->CreateFixture(&shape, 0.0f);
      
    }
      
      
  }
	//Kuladeep Scope ends here
    
    
}

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
