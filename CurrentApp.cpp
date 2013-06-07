#include "CurrentApp.h"

CurrentApp::CurrentApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);


	//CollisionScene *scene = new CollisionScene();
	PhysicsScene * physScene = new PhysicsScene();
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	//obj->loadTexture("Resources/pink_texture.png");
	//scene->addCollisionChild(obj);
	physScene->addPhysicsChild(obj,PhysicsSceneEntity::SHAPE_SPHERE,1.0);

	ScenePrimitive * ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,1000);
	ground->setMaterialByName("GroundMaterial");
	//ground->loadTexture("Resources/green_texture.png");
	ground->setPosition(0,-5,-500);
	//scene->addEntity(ground);
	physScene->addPhysicsChild(ground,PhysicsSceneEntity::SHAPE_PLANE, 0.0);
	
	ScenePrimitive * wall1 = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,900);
	wall1->setMaterialByName("GroundMaterial");
	//wall1->loadTexture("Resources/green_texture.png");
	//scene->addEntity(wall1);
	wall1->Roll(-90);
	wall1->setPosition(-5,0 ,-500);
	physScene->addPhysicsChild(wall1,PhysicsSceneEntity::SHAPE_PLANE, 0.0);

	ScenePrimitive * wall2 = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,900);
	wall2->setMaterialByName("GroundMaterial");
	//wall2->loadTexture("Resources/green_texture.png");
	wall2->Roll(90);
	wall2->setPosition(5,0,-500);
	//scene->addEntity(wall2);
	physScene->addPhysicsChild(wall2,PhysicsSceneEntity::SHAPE_PLANE, 0.0);

	ScenePrimitive * ceiling = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,1000);
	ceiling->setMaterialByName("GroundMaterial");
	//ceiling->loadTexture("Resources/green_texture.png");
	ceiling->Roll(180);
	ceiling->setPosition(0,5,-500);
	//scene->addEntity(ceiling);
	physScene->addPhysicsChild(ceiling,PhysicsSceneEntity::SHAPE_PLANE, 0.0);


//	SceneLight * light = new SceneLight ( SceneLight:: SPOT_LIGHT, scene, 33 );
//	light->setPosition(0,4,4);
//	light->lookAt(Vector3(0,0,0));
//	scene->addLight(light);

	Screen *hud = new Screen();
	keys_pressed = new ScreenLabel("Keys that are pressed:",16);
	hud->addChild(keys_pressed);
	a_pressed = new ScreenLabel("a:no", 16);
	a_pressed->setPosition(0,20);
	d_pressed = new ScreenLabel("d:no", 16);
	d_pressed->setPosition(0,40);
	hud->addChild(a_pressed);
	hud->addChild(d_pressed);

	//scene->getDefaultCamera()->setPosition(0,1,7);
	//scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
	
	physScene->getDefaultCamera()->setPosition(0,1,7);
	physScene->getDefaultCamera()->lookAt(Vector3(0,0,0));
	
	player = Player(obj);

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	
	//player.Load(scene, hud);
	physScene->addPhysicsChild(obj, PhysicsSceneEntity::SHAPE_SPHERE, 1.0);
	player.Load(physScene, hud);
	
	
	enemies = EnemyManager(physScene);
	
	enemies.addEnemy(Enemy(COLUMN,Vector3(1.5,0,-50),10));
	enemies.addEnemy(Enemy(SEAWEED,Vector3(-1.5,5,-50)));
	enemies.addEnemy(Enemy(SHARK,Vector3(1,0,-75),5));
}

CurrentApp::~CurrentApp() {

}

void CurrentApp::handleEvent(Event *e)
{

	if(e -> getDispatcher() == core->getInput())
	{
		InputEvent * inputEvent = (InputEvent*)e;
		switch(e-> getEventCode())
		{
			case InputEvent::EVENT_KEYDOWN:
				switch(inputEvent->keyCode())
				{
					case KEY_UP:
						player.accl.y = 4;
						break;
					case KEY_DOWN:
						player.accl.y = -4;
						break;
					case KEY_LEFT:
						player.accl.x = -4;
						a_pressed->setText("a:yes");
						break;
					case KEY_RIGHT:
						player.accl.x = 4;
						d_pressed->setText("d:yes");
						break;
					default:
						break;
								
				}
				break;
			case InputEvent::EVENT_KEYUP:
				switch(inputEvent->keyCode())
				{
					case KEY_UP:
						player.accl.y = 0;
						break;
					case KEY_DOWN:
						player.accl.y = 0;
						break;
					case KEY_LEFT:
						player.accl.x = 0;
						a_pressed->setText("a:no");
						break;
					case KEY_RIGHT:
						player.accl.x =0;
						d_pressed->setText("d:no");
						break;
					default:
						break;
				}
				break;
			default:
				break;
					
		}
		
	}
}

bool CurrentApp::Update() {
	Number elapsed = core->getElapsed();
	player.Update(elapsed);
	cout<<player.getPosition().x<<" "<<player.getPosition().y<<" "<<player.getPosition().z<<endl;
	enemies.update(elapsed);
    return core->updateAndRender();
}
