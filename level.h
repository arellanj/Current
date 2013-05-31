#include <Polycode.h>

using namespace Polycode;

class Level
{
	private:
		SceneEntity * obj;
		double Pressure;
		double Area;
		double length;
	public:
		Level(int size, int length, Vector3 pos, int pressure, CollisionScene * scene)
			: Area(size*size),length(length), Pressure(pressure)
		{

			Vector3 Color = Vector3( (rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0, ( rand() % 255 ) / 255.0 );
			obj = new SceneEntity();
			obj->setPosition(pos);
			obj->Scale(size,size,length);
			scene->addCollisionChild(obj);
			ScenePrimitive *floor = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			ScenePrimitive *lwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			ScenePrimitive *rwall = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			ScenePrimitive *ceil = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.1,0.1,1);
			obj->addChild(floor);
			obj->addChild(lwall);
			obj->addChild(rwall);
			obj->addChild(ceil);

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
			return (  pos.z > obPos.z + length ) && ( pos.z < obPos.z ) ;
		}

		~Level()
		{
			
		}
};
