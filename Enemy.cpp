#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include <iostream>
#include "player.h"

#ifndef __ENEMY_CPP__
#define __ENEMY_CPP__

using namespace std;
using namespace Polycode;

enum EnemyType { SHARK, SEAWEED, COLUMN, COIN };

class Enemy {
public:
	Enemy(EnemyType type, Vector3 position, int height, int width) : type(type), swingValue(0), swingRange(width), visible(true), inside(false), prev(0){		
		switch(type){
			case SHARK :
				box = new ScenePrimitive(ScenePrimitive::TYPE_BOX,1,1,1);
				tail= new ScenePrimitive(ScenePrimitive::TYPE_CONE,.5,.5,10);
				box->addChild(tail);
				position.y = rand() % 8  - 4;
				box->loadTexture("Resources/pink_texture.png");					
				tail->loadTexture("Resources/pink_texture.png");		
				tail->Roll(-90);
				tail->setPosition(Vector3(-.75,0,0));
				tail->alphaTest = true;			
				break;		
				
			case SEAWEED : 
				box = new ScenePrimitive(ScenePrimitive::TYPE_BOX,5,3,1);
				position.y = rand() % 2 == 0 ? 3 : -3;
				position.x = rand() % (width - 3)  - (width - 3)/2;
				box->loadTexture("Resources/green_texture.png");
				break;
			
			case COLUMN :
				box = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER,10,1,10);
				position.x = rand() % (width - 1)  - (width - 1)/2;
				box->loadTexture("Resources/blue_texture.png");
				break;
			case COIN:
				box = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER,.5,.5,10);
				box->Pitch(90);
				position.y = rand() % 8  - 4;
				position.x = rand() % width  - width/2;
				box->loadTexture("Resources/yellow_texture.png");
				
			default : 
				break;
		}		
		box->setPosition(position);
		box->alphaTest = true;
	}
	
	void update(Number elapsed, Player player){
			
		double dist = player.getPosition().z;
		Vector3 pos = player.getPosition();
		// cool alpha effect 
		if(visible){
			if((box->getPosition().z - 2) > dist){
				if(box->color.a > 0.0)
					box->color.a = box->color.a - .3;
				box->setColor(1,1,1,box->color.a);
			}
			else{
				if(box->color.a < 1.0)
					box->color.a = box->color.a + .3;
				box->setColor(1,1,1,box->color.a);
			}
		}
		else{
			box->setColor(1,1,1,0);
			//box->setColor(1,1,1,.1);
		}
		 
		
		if(type== COIN){
			box->Yaw(100*elapsed);
			Vector3 dist = player.getPosition() - box->getPosition();
			if(dist.length() < 2){
				dist.Normalize();
				box->Translate(dist*elapsed*10);
			}
		}
		if(type == SHARK){
			if(prev - sin(swingValue) < 0)
			{
				tail->setPosition(Vector3(-.75,0,0));
				tail->setYaw(0);
			}
			else
			{
				tail->setPosition(Vector3(.75,0,0));
				tail->setYaw(180);
			}
			prev = sin(swingValue);
			swingValue += elapsed*(rand() % 6 + 1);
			//std::cout<<"SWING: "<<sin(swingValue) * swingRange * .5<<std::endl;
			box->setPosition(sin(swingValue) * swingRange * .5,box->getPosition().y,box->getPosition().z);	
		}	
	}
	
	void setPosition(Vector3 position){
		box->setPosition(position);
	}
	
	Vector3 getPosition(){
		return box->getPosition();
	}
	
	ScenePrimitive* getBox(){
		return box;
	}
    
    Number getSwingRange(){
		return swingRange;
	}
	
	EnemyType getType(){
		return type;
	}
    
    void setVisible(bool v){
		visible = v;
	}
	
	bool getVisible(){
		return visible;
	}
    
    bool inside;
private:
	EnemyType type;
	bool visible;	
	ScenePrimitive * box;
	ScenePrimitive * tail;
	Number swingRange;
	Number swingValue;
	Number prev;
	
};
#endif // __ENEMY_CPP__
