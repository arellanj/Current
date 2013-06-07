#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
using namespace Polycode;

enum EnemyType { SHARK, SEAWEED, COLUMN };

class Enemy {
public:
	Enemy(EnemyType type, Vector3 position, Number height = 1, Number width = 1) : type(type), swingValue(0) {		
		switch(type){
			case SHARK :
				box = new ScenePrimitive(ScenePrimitive::TYPE_BOX,1,1,1);
				box->setMaterialByName("CubeMaterial");								
				break;		
				
			case SEAWEED : 
				box = new ScenePrimitive(ScenePrimitive::TYPE_BOX,height,width,1);
				box->setMaterialByName("GroundMaterial");
				break;
				
			// Column y parameter = ceiling.y - ground.y
			//		  x parameter = x radius
			case COLUMN :
				box = new ScenePrimitive(ScenePrimitive::TYPE_CYLINDER,height,width,10);
				box->setMaterialByName("GroundMaterial");
			default : 
				break;
		}		
		box->setPosition(position);
	}
	
	void update(Number elapsed){
		//Shark's swing radius is hardcoded to 4.5 right now
		if(type == SHARK){
			swingValue += elapsed;
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
    
    
private:
	EnemyType type;
	ScenePrimitive * box;
	Number swingValue;
};
