#include "level.h"
#include "EnemyManager.cpp"
#include "player.h"
#include <vector>

#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__

class LevelManager
{
private:
	std::vector<Level*> levels;
	EnemyManager enemies;
	CollisionScene * scene;
public:
	LevelManager();
	LevelManager(const LevelManager & man);
	LevelManager(Number levelNum, CollisionScene * scene);
	~LevelManager();
	void Update( Number elapsed , Player & player);
  
};


#endif // __LEVELMANAGER_H__
