#include <Polycode.h>

using namespace Polycode;

class Level
{
	private:
		SceneEntity * obj;
		double Pressure;
		double Area;
		double length;
		ScenePrimitive * floor;
		ScenePrimitive * lwall;
		ScenePrimitive * rwall;
		ScenePrimitive * ceil;
		
		
		
	public:
		vector<Enemy> enemies;
		CollisionScene * scene;
		
		Level(int size, int length, Vector3 pos, int pressure, CollisionScene * scene)
			: Area(size*size),length(length), Pressure(pressure), scene(scene)
		{
			
			Vector3 Color = Vector3( (rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0 );
			obj = new SceneEntity();
			obj->setPosition(pos);
			obj->Scale(size,size,length);
			scene->addCollisionChild(obj);
			floor = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			lwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			rwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			ceil = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			//scene->addCollisionChild(floor);
			//scene->addCollisionChild(lwall);
			//scene->addCollisionChild(rwall);
			//scene->addCollisionChild(ceil);
			obj->addChild(floor);
			obj->addChild(lwall);
			obj->addChild(rwall);
			obj->addChild(ceil);
			
			//Enemy e(SHARK,Vector3(0,0,-75),5);
			//obj->addChild(e.getBox());
			//enemies.push_back(e);
			//scene->addCollisionChild(e.getBox());
			
			//Enemy e1(COLUMN,Vector3(0,0,2),5);			
			//enemies.push_back(e1);			
			//obj->addChild(e1.getBox());

			floor->setPosition(Vector3( 0,-.5, 1) );
			floor->setMaterialByName("GroundMaterial");
			//floor->loadTexture("Resources/green_texture.png");
			//floor->setColor(Color.x,Color.y,Color.z, 1);

			rwall->Roll(90);
			rwall->setPosition(Vector3( 0.5,0,1 ) );
			rwall->setMaterialByName("GroundMaterial");
			//rwall->loadTexture("Resources/green_texture.png");
			//rwall->setColor(Color.x,Color.y,Color.z, 1);

			lwall->Roll(-90);
			lwall->setPosition(Vector3 ( -0.5,0,1 ) );
			lwall->setMaterialByName("GroundMaterial");
			//lwall->loadTexture("Resources/green_texture.png");
			//lwall->setColor(Color.x,Color.y,Color.z, 1);
			
			ceil->Roll(180);
			ceil->setPosition(Vector3 ( 0,.5,1));
			ceil->setMaterialByName("GroundMaterial");
			//ceil->loadTexture("Resources/green_texture.png");
			//ceil->setColor(Color.x,Color.y,Color.z, 1);


			SceneLight * light = new SceneLight(SceneLight::AREA_LIGHT, scene,  33);
			light->setPosition(pos);
			scene->addLight(light);

			
		}

		double getspeed(  )
		{
			return Pressure / Area;
		}
	
		bool isIn(const Vector3 & pos)
		{
			Vector3 obPos = obj->getPosition(); 
			std::cout<< obPos.z << " - " <<obPos.z+length <<" , "<< pos.z <<std::endl;
			return (  pos.z >= obPos.z ) && ( pos.z <= obPos.z + length ) ;
		}
		
		void collideUpdate(Player player)
		{
			vector<CollisionResult> v;
			v.push_back(scene->testCollision(floor, player.obj));
			v.push_back(scene->testCollision(lwall, player.obj));
			v.push_back(scene->testCollision(rwall, player.obj));
			v.push_back(scene->testCollision(ceil, player.obj));
			v.push_back(scene->testCollision(obj, player.obj));
			v.push_back(scene->testCollision(enemies[0].getBox(), player.obj));
			//for every enemy, push back collision result
			
			for(int i = 0;i<v.size();i++)
			{
				CollisionResult cr = v[i];
				std::cout<<cr.collided<<" "<<std::endl;
				if(cr.collided)
				{
					player.vel.z = .1;
				}
			}
			
			//player.move
		}
		
		

		~Level()
		{
			
		}
};
