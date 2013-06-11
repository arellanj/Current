#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
using namespace Polycode;

enum EnemyType { SHARK, SEAWEED, COLUMN, COIN };

class Enemy {
public:
	Enemy(EnemyType type, Vector3 position, Number height, Number width) : type(type), swingValue(0), swingRange(width){		
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
				break;
			case COIN:
				box = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE,1,1,.5);
				box->setMaterialByName("GroundMaterial");
			default : 
				break;
		}		
		box->setPosition(position);
	}
	
	void update(Number elapsed){
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
    
    Number getSwingRange(){
		return swingRange;
	}
	
	EnemyType getType(){
		return type;
	}
    
private:
	EnemyType type;
	ScenePrimitive * box;
	Number swingRange;
	Number swingValue;
};
