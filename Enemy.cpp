#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include <iostream>

#ifndef __ENEMY_CPP__
#define __ENEMY_CPP__

using namespace std;
using namespace Polycode;

enum EnemyType { SHARK, SEAWEED, COLUMN, COIN };

class Enemy {
public:
	Enemy(EnemyType type, Vector3 position, int height, int width) : type(type), swingValue(0), swingRange(width), visible(true), inside(false){		
		switch(type){
			case SHARK :
				box = new ScenePrimitive(ScenePrimitive::TYPE_BOX,1,1,1);
				position.y = rand() % 8  - 4;
				box->loadTexture("Resources/pink_texture.png");					
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
	
	void update(Number elapsed, Number dist){
			

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
			
		}
		if(type == SHARK){
			swingValue += elapsed*(rand() % 6 + 1);
			box->setPosition(sin(swingValue) * 4.5,box->getPosition().y,box->getPosition().z);	
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
	Number swingRange;
	Number swingValue;
	
	
};
#endif // __ENEMY_CPP__
