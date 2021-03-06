#include <Polycode.h>
#include "PolycodeView.h"
#include "Enemy.cpp"
#include "Polycode3DPhysics.h"
#include <vector>

#ifndef __ENEMYMANAGER_CPP__
#define __ENEMYMANAGER_CPP__

using namespace Polycode;

class EnemyManager {
public:

	EnemyManager(){		
	}

	EnemyManager(Scene * scene) : scene(scene){		
	}
	
	void addEnemy(Enemy* e){
		enemies.push_back(e);	
		scene->addEntity(e->getBox());
	}
	
	void addEnemy(vector<Enemy*> v){
		for(int i = 0;i<v.size();i++)
		{
			enemies.push_back(v[i]);	
			scene->addEntity(v[i]->getBox());
		}
	}
	
	Enemy getEnemy(int i){
		return *enemies[i];
	}
	
	void update(Number elapsed, Player player){
		for(int i = 0;i<enemies.size();i++)
			enemies[i]->update(elapsed, player);
	}
    
    vector <Enemy*> enemies;
private:
	
	Scene * scene;
};
#endif // __ENEMYMANAGER_CPP__
