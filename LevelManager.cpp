#include "LevelManager.h"

LevelManager::LevelManager()
:scene(NULL)
{

}

LevelManager::LevelManager(Number levelNum, CollisionScene * scene)
	 :scene(scene), next_pos(0), pressure(4000)
{
  enemies = EnemyManager(scene);
  int size = 5;
  for(int i = 0; i < levelNum ; i++)
	{
  	  //int size = ( rand() % 10 ) +10;
  	  size-= 2;
  	  if ( size < 6)
		{
	  	  size = 20;
		}
	  int length = 100 ; //( rand() % 40) +85;
  	  next_pos += length;
  	  levels.push_back(new Level(size,length, Vector3(0,0,-next_pos), pressure, scene));
  	  enemies.addEnemy(levels[levels.size()-1]->enemies);//add enemies to enemy manager		
	}
	
	addLastRoom();
}


void LevelManager::Update( Number elapsed, Player & player)
{
	for ( int i  = 0 ; i < levels.size() ; i++ )
	{
  	  //std::cout<< player.getPosition().z <<std:: endl;
  	  Vector3 position = player.getPosition();
  	  if( levels[i]->isIn(position) && i != player.levelPos)
		{
	  	  player.levelPos = i;
	  	  player.setMaxSpeed( levels[i]->getspeed());


		  levels[player.levelPos]->addLevelScene();
	  	  if (player.levelPos < levels.size()-1 )
	  		{
		  	  levels[player.levelPos +1 ]->addLevelScene();
			}
		  if (player.levelPos > 1  )
	  		{
		  	  levels[player.levelPos - 2 ]->removeLevelScene();
			}
		  break;
		}

	}

  	levels[player.levelPos]->collideUpdate(player);

	Number r = 0.52;

	Vector3 pos = player.getPosition();
	double size = 0.5*levels[player.levelPos]->size;
	if( ( pos.x - r ) < -size + .1)
	{
		pos.x = (-size+0.1) + r;
	}
	else if( ( pos.x + r ) > size - .1)
	{
		pos.x = (size - 0.1) - r;
	}

	if( ( pos.y - r ) < -5 + .1)
	{
		pos.y = -5+0.1 + r;
	}
	else if( ( pos.y + r ) > 5 - .1)
	{
		pos.y = (5 - 0.1) - r;
	}
	player.obj->setPositionX(pos.x);
	player.obj->setPositionY(pos.y);

  	enemies.update(elapsed, player);
 
}

void LevelManager::addLastRoom()
{
	double length = 100;
	double size = 100;
	next_pos += 100;
	levels.push_back(new Level(size,length, Vector3(0,0,-next_pos), 4000, scene, EMPTY));
}

int LevelManager::getLevelSize()
{
	return levels.size();
}

Level* LevelManager::getLevel(int index)
{
	return levels[index];
}

LevelManager::~LevelManager()
{
	for ( int i =0  ;  i < levels.size() ; i++ )
	{
		delete levels[i];
	}
}
