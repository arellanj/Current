#include <Polycode.h>
#include "EnemyManager.cpp"
#include "player.h"

using namespace Polycode;

enum RoomType { COINS, MIXED, EMPTY, RANDOM }; //needs to be in this order

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
		double size;
		bool inScene;
		
		Level(int size, int length, Vector3 pos, int pressure, CollisionScene * scene, RoomType roomType = RANDOM)
			:pos(pos), Area(size*10),length(length), Pressure(pressure), scene(scene), size(size)
	{			
			Vector3 Color = Vector3( (rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0 );
			
			inScene = false;
			
			//setupEnemies(roomType, size);

			floor = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*size,0.2,1*length);
			lwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*10,0.2,1*length);
			rwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*10,0.2,1*length);
			ceil = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*size,0.2,1*length);
			lblind = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 6,10);
			rblind = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 6,10);
			
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
		
		void setupEnemies(RoomType roomType, int size)
		{
			if(roomType == EMPTY)
			{
				SceneParticleEmitter * emitter = new SceneParticleEmitter("TestParticle", 
					Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, 4, 1000,
					Vector3(0.0,1.0,0.0), Vector3(0.0,0.0,0.0), Vector3(0.3, 0.0, 0.3),
					Vector3(30,10,100));		

				emitter->setPosition(Vector3(0,0,length));
				emitter->Translate(pos);
				emitter->useScaleCurves = true;
				emitter->scaleCurve.addControlPoint2d(0, 0.3);
				emitter->scaleCurve.addControlPoint2d(0.5, 1);
				emitter->scaleCurve.addControlPoint2d(1, 0);
				
				emitter->useColorCurves = true;
				emitter->colorCurveR.addControlPoint2d(0, 0.3);
				emitter->colorCurveR.addControlPoint2d(0.1, 1);	
				emitter->colorCurveR.addControlPoint2d(0.4, 1);		
				emitter->colorCurveR.addControlPoint2d(0.5, 0);	
				emitter->colorCurveR.addControlPoint2d(1, 0);
				
				emitter->colorCurveG.addControlPoint2d(0, 0.3);
				emitter->colorCurveG.addControlPoint2d(0.1, 0.6);	
				emitter->colorCurveG.addControlPoint2d(0.4, 0.6);		
				emitter->colorCurveG.addControlPoint2d(0.5, 0);		
				emitter->colorCurveG.addControlPoint2d(1, 0.0);
				
				emitter->colorCurveB.addControlPoint2d(0, 1);
				emitter->colorCurveB.addControlPoint2d(0.1, 0);	
				emitter->colorCurveB.addControlPoint2d(1, 0);
				
				emitter->colorCurveA.addControlPoint2d(0, 0);
				emitter->colorCurveA.addControlPoint2d(0.05, 1);
				emitter->colorCurveA.addControlPoint2d(0.6, 1);
				emitter->colorCurveA.addControlPoint2d(1, 0);

				
				scene->addEntity(emitter);
				
				return;
			}
			int coin_x = (rand()%(size-1) - (size-1)/2);
			int coin_y = (rand()%8 - 4);
			if(roomType == RANDOM) roomType = static_cast<RoomType>(rand() % 2); //rand() % (total_room_types - 2)
			for(int i = 0;i<length/10;i++)
			{
				Enemy * e;
				
				switch(roomType)
				{
					case COINS:
						if(i < (length/10)/2)
						{
							e = new Enemy(COIN,Vector3(coin_x,0,i*10 ),0,size);
							e->setPosition(Vector3(coin_x, coin_y,e->getPosition().z));
						}
						else
							e = new Enemy(static_cast<EnemyType>(rand() % 4),Vector3(0,0,i*10 ),0,size);
						break;
					case MIXED:
						if(rand() % 5 == 0) continue;
						e = new Enemy(static_cast<EnemyType>(rand() % 4),Vector3(0,0,i*10 ),0,size);
						break;
					default:
						break;
				}
				if(roomType == EMPTY)  break;
				e->getBox()->Translate(pos);
				enemies.push_back(e);
				scene->addCollisionChild(e->getBox());	
			}
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
					Vector3 perpen = (cr.colNormal*-1).crossProduct(negZ);
					player.vel = negZ * player.vel.dot(negZ) + perpen * player.vel.dot(perpen);
					//std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;				
				}
			}
			
			for(int i = 0;i<enemies.size();i++)
			{
				CollisionResult cr = scene->testCollision(enemies[i]->getBox(), player.obj);
				if(cr.collided)
				{
					if(enemies[i]->getType() == SHARK)
					{
						if(cr.colNormal.dot(player.vel) < 0)
							break;
						Vector3 mv = cr.colNormal *cr.colDist *- 1;
						//std::cout<<mv.x<<" "<<mv.y<<" "<<mv.z<<" "<<std::endl;
						player.translate(mv.x,mv.y,mv.z);
						
						player.vel = ((cr.colNormal*-1)*player.vel.dot(cr.colNormal*-1)*-2 + player.vel)* 0.5;
						//std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;
					}
					else if(enemies[i]->getType() == COLUMN)
					{
						Vector3 dist = player.obj->getPosition() - enemies[i]->getBox()->getPosition();
						dist.y = 0;
						if(dist.length() < .5 + 1)
						{

							dist.Normalize();
							if(dist*-1 != cr.colNormal)
							{
								std::cout<<"I FUCKING KNEW IT "<<std::endl;
							}
							if(dist.dot(player.vel) > 0)
								break;
							player.vel = ((dist)*player.vel.dot(dist)*-2 + player.vel)*0.5;
							
						}
					}
					else if(enemies[i]->getType() == SEAWEED)
					{						
						if(!enemies[i]->inside){ //first time inside seaweed
							enemies[i]->inside = true;
							player.vel = Vector3(0,0,0);						
							//std::cout<<"\n1st time Inside Seaweed\n ";
						}						
						//std::cout<<"\nVelocity: "<<player.vel.x<<" "<<player.vel.y<<" "<<player.vel.z<<std::endl;				
					}
					else if(enemies[i]->getType() == COIN)
					{
						scene->removeEntity(enemies[i]->getBox());
						if(!(enemies[i]->getVisible()))
							break;
						player.coins++;//increase coin count
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
