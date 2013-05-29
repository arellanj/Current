#include "CurrentApp.h"

CurrentApp::CurrentApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);


	CollisionScene *scene = new CollisionScene();
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	scene->addCollisionChild(obj);

	ScenePrimitive * ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,25);
	ground->setMaterialByName("GroundMaterial");
	ground->setPosition(0,-5,0);
	scene->addEntity(ground);
	
	ScenePrimitive * wall1 = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,25);
	wall1->setMaterialByName("GroundMaterial");
	scene->addEntity(wall1);
	
	wall1->Roll(-90);
	wall1->setPosition(-5,0 ,0);


	SceneLight * light = new SceneLight ( SceneLight:: AREA_LIGHT, scene, 33 );
	light->setPosition(0,4,4);
	light->lookAt(Vector3(0,0,0));
	scene->addLight(light);

	Screen *hud = new Screen();
	keys_pressed = new ScreenLabel("Keys that are pressed:",16);
	hud->addChild(keys_pressed);
	a_pressed = new ScreenLabel("a:no", 16);
	a_pressed->setPosition(0,20);
	d_pressed = new ScreenLabel("d:no", 16);
	d_pressed->setPosition(0,40);
	hud->addChild(a_pressed);
	hud->addChild(d_pressed);

	scene->getDefaultCamera()->setPosition(0,1,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));
	
	player = Player(obj, scene->getDefaultCamera());

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	
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
						player.dir.y = 10;
						break;
					case KEY_DOWN:
						player.dir.y = -10;
						break;
					case KEY_LEFT:
						player.dir.x = -10;
						a_pressed->setText("a:yes");
						break;
					case KEY_RIGHT:
						player.dir.x = 10;
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
						player.dir.y = 0;
						break;
					case KEY_DOWN:
						player.dir.y = 0;
						break;
					case KEY_LEFT:
						player.dir.x = 0;
						a_pressed->setText("a:no");
						break;
					case KEY_RIGHT:
						player.dir.x =0;
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
    return core->updateAndRender();
}
