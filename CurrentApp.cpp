#include "CurrentApp.h"

CurrentApp::CurrentApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);

	scene = new CollisionScene();
	//PhysicsScene * physScene = new PhysicsScene();
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	//obj->loadTexture("Resources/pink_texture.png");
	//scene->addCollisionChild(obj);


	//scene->addCollisionChild(obj);
/*
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

	scene->addEntity(ceiling);
*/
	scene->addCollisionChild(obj);
		double next_pos = 0;
		enemies = EnemyManager(scene);
		int size = 5;
	for(int i = 0; i < 50 ; i++)
	{
		//int size = ( rand() % 10 ) +10;
		size-= 2;
		if ( size < 6)
		{
			size = 20;
		}
		int length = ( rand() % 40) +15;
		//std::cout<<"MADE: "<<size<<" , "<<length<<" at :" << next_pos + length<< std::endl;
		next_pos += length;
		Level * newlevel = new Level(size,length, Vector3(0,0,-next_pos), 4000, scene);
		path.push_back(newlevel);
		enemies.addEnemy(newlevel->enemies);//add enemies to enemy manager		
	}

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
	
	ScreenLabel * coins = new ScreenLabel("Coins: ",16);
	coins->setPosition(0,460);
	hud->addChild(coins);

	player = Player(obj);

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	


	//player.Load(scene, hud);
	//physScene->addPhysicsChild(obj, PhysicsSceneEntity::SHAPE_SPHERE, 1.0);
	player.Load(scene, hud);
	
}

CurrentApp::~CurrentApp() {

}

void CurrentApp::handleEvent(Event *e)
{

	if(e -> getDispatcher() == core->getInput())
	{
		InputEvent * inputEvent = (InputEvent*)e;
		switch(e->getEventCode())
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
	double elapsed = core->getElapsed();
	
	player.Update(elapsed);
	for ( int i  = 0 ; i < 50 ; i++ )
	{
		//std::cout<< player.getPosition().z <<std:: endl;
		Vector3 position = player.getPosition();
		if( path[i]->isIn(position) && i != player.levelPos)
		{
			//std::cout<< "Player is now in: "<< i<<std::endl;
			player.levelPos = i;
			player.setMaxSpeed( path[i]->getspeed());
			break;
		}
		
	}
	
	path[player.levelPos]->collideUpdate(player);
	/*
	CollisionResult cr = scene->testCollision(enemies.enemies[0].getBox(), player.obj);
	std::cout<<cr.collided<<" "<<std::endl;
	if(cr.collided)
	{
		player.vel.z = .1;
	}
	*/

	enemies.update(elapsed, player.getPosition().z);
    return core->updateAndRender();
}
