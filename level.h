#include <Polycode.h>
#include "EnemyManager.cpp"
#include "player.h"

using namespace Polycode;

class Level
{
	private:
		Vector3 pos;
		double Pressure;
		double Area;
		double length;
				
	public:
		vector<Enemy *> enemies;
		CollisionScene * scene;
		ScenePrimitive * floor;
		ScenePrimitive * lwall;
		ScenePrimitive * rwall;
		ScenePrimitive * ceil;
		ScenePrimitive * lblind;
		ScenePrimitive * rblind;
		SceneLight * light;
		bool inScene;
		
		Level(int size, int length, Vector3 pos, int pressure, CollisionScene * scene)
			:pos(pos), Area(size*10),length(length), Pressure(pressure), scene(scene)
		{			
			Vector3 Color = Vector3( (rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0 );
			
			inScene = false;

			floor = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1*size,0.1*10,1*length);
			lwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*10,0.1*size,1*length);
			rwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*10,0.1*size,1*length);
			ceil = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1*size,0.1*10,1*length);
			lblind = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 6,10);
			rblind = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 6,10);

			// one enemy
			/*
			Enemy e(COIN,Vector3(0,0,rand()%length),0,size);
			e.getBox()->Translate(pos);
			enemies.push_back(e);
			scene->addCollisionChild(e.getBox());	
			*/
			
			for(int i = 0;i<length/10;i++)
			{
				Enemy * e = new Enemy(static_cast<EnemyType>(rand() % 4),Vector3(0,0,i*10 ),0,size);
				e->getBox()->Translate(pos);
				enemies.push_back(e);
				scene->addCollisionChild(e->getBox());	
			}
			
			floor->setPosition(Vector3( 0,-.5*10, 0.5*length) );
			floor->setMaterialByName("GroundMaterial");

			rwall->Roll(90);
			rwall->setPosition(Vector3( 0.5*size,0,0.5*length ) );
			rwall->setColor(1,1,1,.3);
			rwall->loadTexture("Resources/blue_texture.png");
			//rwall->setColor(Color.x,Color.y,Color.z, 1);
			lwall->Roll(-90);
			lwall->setPosition(Vector3 ( -0.5*size,0,0.5*length ) );
			lwall->setMaterialByName("GroundMaterial");
			
			ceil->Roll(180);
			ceil->setPosition(Vector3 ( 0,.5*10 + 0.01,0.5*length) );
			ceil->setColor(1,1,1,.3);
			//ceil->visible = false;
			ceil->loadTexture("Resources/blue_texture.png");
			//ceil->setColor(Color.x,Color.y,Color.z, 1);

			rblind->Pitch(90);
			rblind->setColor(1,1,1,0.3);
			rblind->loadTexture("Resources/blue_texture.png");
			rblind->setPosition( Vector3( 3+0.5*size, 0, length+0.01 ) );

			lblind->Pitch(90);
			lblind->setMaterialByName("GroundMaterial");
			lblind->setPosition( Vector3( -(3+0.5*size), 0, length+0.01 ) );

			ceil->alphaTest = true;
			rblind->alphaTest = true;
			lblind->alphaTest = true;


			floor->Translate(pos);
			lwall->Translate(pos);
			rwall->Translate(pos);
			ceil->Translate(pos);
			rblind->Translate(pos);
			lblind->Translate(pos);



			light = new SceneLight(SceneLight::AREA_LIGHT, scene,  33+ size);
			light->setPosition(0,0,pos.z + .5*length);

			//addLevelScene();
		}

		double getspeed(  )
		{
			return Pressure / Area;
		}
	
		bool isIn(const Vector3 & pos)
		{
			return (  pos.z >= this->pos.z ) && ( pos.z <= this->pos.z + length ) ;
		}
		
		void collideUpdate(Player &  player)
		{
			// Test Walls
			vector<CollisionResult> v;
			v.push_back(scene->testCollision(floor, player.obj));
			v.push_back(scene->testCollision(lwall, player.obj));
			v.push_back(scene->testCollision(rwall, player.obj));
			v.push_back(scene->testCollision(ceil, player.obj));
			v.push_back(scene->testCollision(rblind, player.obj));
			v.push_back(scene->testCollision(lblind, player.obj));

	//		v.push_back(scene->testCollision(obj, player.obj));
//			v.push_back(scene->testCollision(enemies[0].getBox(), player.obj));
			
			//for every enemy, push back collision result
			
			for(int i = 0;i<v.size();i++)
			{
				CollisionResult cr = v[i];
				//std::cout<<cr.collided<<" "<<std::endl;
				if(cr.collided)
				{
					if(cr.colNormal.dot(player.vel) > 0)
						break;
					std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;
					Vector3 mv = cr.colNormal *cr.colDist * -1;
					player.translate(mv.x,mv.y,mv.z);
					//player.vel = (cr.colNormal*player.vel.dot(cr.colNormal)*-2 + player.vel)* 0.5;
					Vector3 negZ = Vector3(0,0,-1);
					Vector3 perpen = mv.crossProduct(negZ);
					player.vel = negZ * player.vel.dot(negZ) + perpen * player.vel.dot(perpen);
					//std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;				
				}
			}
			
			for(int i = 0;i<enemies.size();i++)
			{
				CollisionResult cr = scene->testCollision(enemies[i]->getBox(), player.obj);
				if(cr.collided)
				{
					if(enemies[i]->getType() == SHARK || enemies[i]->getType() == COLUMN )
					{
						if(cr.colNormal.dot(player.vel) < 0)
							break;
						Vector3 mv = cr.colNormal *cr.colDist *- 1;
						std::cout<<mv.x<<" "<<mv.y<<" "<<mv.z<<" "<<std::endl;
						player.translate(mv.x,mv.y,mv.z);
						
						player.vel = ((cr.colNormal*-1)*player.vel.dot(cr.colNormal*-1)*-2 + player.vel)* 0.5;
						//std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;
					}
					else if(enemies[i]->getType() == SEAWEED)
					{
						/*
						if(!enemies[i]->inside){ //first time inside seaweed
							enemies[i]->inside = true;
							enemies[i]->tempSpeed = player.vel;
							std::cout<<"\n1st time Inside Seaweed\n ";
						}
						player.vel = enemies[i]->tempSpeed * .5;						
						std::cout<<"\nVelocity: "<<player.vel.x<<" "<<player.vel.y<<" "<<player.vel.z<<std::endl;
						*/
						player.vel = player.vel * .7;						
					}
					else if(enemies[i]->getType() == COIN)
					{
						scene->removeEntity(enemies[i]->getBox());
						if(!(enemies[i]->getVisible()))
							break;
						player.incrCoins();//increase coin count
						enemies[i]->setVisible(false);
						enemies[i]->getBox()->visible = false;
					} 
				}
			}
			
			
		}
		void addLevelScene()
		  {
			if ( inScene ) return;
			inScene = true;
			scene->addCollisionChild(floor,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(lwall,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(rwall,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(ceil,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(rblind,CollisionSceneEntity::SHAPE_PLANE);
			scene->addCollisionChild(lblind,CollisionSceneEntity::SHAPE_PLANE);	
			scene->addLight(light);
		  }		


		void removeLevelScene()
		  {
			if ( inScene)
			  {
				inScene = false;
				scene->removeEntity(floor);
				scene->removeEntity(lwall);
				scene->removeEntity(rwall);
				scene->removeEntity(ceil);
				scene->removeEntity(rblind);
				scene->removeEntity(lblind);
				scene->removeLight(light);
			  }
		  }		


		~Level()
		  {
			std::cout<<"removing level"<<std::endl;
			removeLevelScene();
			delete floor;
			delete lwall;
			delete rwall;
			delete ceil;
			delete rblind;
			delete lblind;
			delete light;
		  }
};
