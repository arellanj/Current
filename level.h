#include <Polycode.h>

using namespace Polycode;

class Level
{
	private:
		Vector3 pos;
		double Pressure;
		double Area;
		double length;
		
		
		
	public:
		vector<Enemy> enemies;
		CollisionScene * scene;
		ScenePrimitive * floor;
		ScenePrimitive * lwall;
		ScenePrimitive * rwall;
		ScenePrimitive * ceil;
		ScenePrimitive * lblind;
		ScenePrimitive * rblind;
		
		Level(int size, int length, Vector3 pos, int pressure, CollisionScene * scene)
			:pos(pos), Area(size*10),length(length), Pressure(pressure), scene(scene)
		{			
			Vector3 Color = Vector3( (rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0 );
				
			floor = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1*size,0.1*10,1*length);
			lwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*10,0.1*size,1*length);
			rwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1*10,0.1*size,1*length);
			ceil = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1*size,0.1*10,1*length);
			lblind = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 6,10);
			rblind = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 6,10);

			//Enemy e(COLUMN,Vector3(0,0,0),5);
			//e.getBox()->Translate(pos);
			//enemies.push_back(e);
			//scene->addCollisionChild(e.getBox());

			Enemy e(SEAWEED,Vector3(0,0,rand()%length),0,size);
			e.getBox()->Translate(pos);
			enemies.push_back(e);
			scene->addCollisionChild(e.getBox());	
			
			/*
			for(int i = 0;i<length % 10;i++)
			{
				Enemy e(SHARK,Vector3(0,0,i ),0,size);
				e.getBox()->Translate(pos);
				enemies.push_back(e);
				scene->addCollisionChild(e.getBox());	
			}
			*/


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
			ceil->setPosition(Vector3 ( 0,.5*10,0.5*length) );
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
			floor->Translate(pos);
			lwall->Translate(pos);
			rwall->Translate(pos);
			ceil->Translate(pos);
			rblind->Translate(pos);
			lblind->Translate(pos);

			scene->addCollisionChild(floor,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(lwall,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(rwall,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(ceil,CollisionSceneEntity::SHAPE_BOX);
			scene->addCollisionChild(rblind,CollisionSceneEntity::SHAPE_PLANE);
			scene->addCollisionChild(lblind,CollisionSceneEntity::SHAPE_PLANE);

			SceneLight * light = new SceneLight(SceneLight::AREA_LIGHT, scene,  33+ size);
			light->setPosition(0,0,pos.z + .5*length);
			scene->addLight(light);
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
					std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;				}
			}
			
			for(int i = 0;i<enemies.size();i++)
			{
				CollisionResult cr = scene->testCollision(enemies[i].getBox(), player.obj);
				if(cr.collided)
				{
					if(enemies[i].getType() == SHARK || enemies[i].getType() == COLUMN )
					{
						if(cr.colNormal.dot(player.vel) > 0)
							break;
						Vector3 mv = cr.colNormal *cr.colDist * -1;
						player.translate(mv.x,mv.y,mv.z);
						player.vel = (cr.colNormal*player.vel.dot(cr.colNormal)*-2 + player.vel)* 0.5;
						//std::cout<<player.vel.x<<" "<<player.vel.y<<" "<<std::endl;
					}
					else if(enemies[i].getType() == SEAWEED)
					{
						player.vel = player.vel * 0.5;
					}
					//else(enemies[i].getType() == COIN)
					//{
						//increase coin count
					//} 
				}
			}
			
			
		}
		
		

		~Level()
		{
			
		}
};
