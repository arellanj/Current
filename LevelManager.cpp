#include "LevelManager.h"

LevelManager::LevelManager()
:scene(NULL)
{

}

LevelManager::LevelManager(Number levelNum, CollisionScene * scene)
	 :scene(scene)
{
  enemies = EnemyManager(scene);
  double next_pos = 0;
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
  	  levels.push_back(new Level(size,length, Vector3(0,0,-next_pos), 4000, scene));
  	  enemies.addEnemy(levels[levels.size()-1]->enemies);//add enemies to enemy manager		
	}
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

  enemies.update(elapsed, player.getPosition().z);
 
}

LevelManager::~LevelManager()
{
	for ( int i =0  ;  i < levels.size() ; i++ )
	{
		delete levels[i];
	}
}
