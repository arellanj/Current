#include <Polycode.h>
#include "PolycodeView.h"
#include "Enemy.cpp"
#include "Polycode3DPhysics.h"
#include <vector>
using namespace Polycode;

class EnemyManager {
public:

	EnemyManager(){		
	}

	EnemyManager(Scene * scene) : scene(scene){		
	}
	
	void addEnemy(Enemy e){
		enemies.push_back(e);	
		scene->addEntity(e.getBox());
	}
	
	Enemy getEnemy(int i){
		return enemies[i];
	}
	
	void update(Number elapsed){
		for(int i = 0;i<enemies.size();i++)
			enemies[i].update(elapsed);
	}
    
    
private:
	vector <Enemy> enemies;
	Scene * scene;
};
