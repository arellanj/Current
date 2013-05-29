#include "player.h"

Player::Player( ScenePrimitive * obj)
	:obj(obj), cam(NULL), spotlight(NULL), timer(NULL)
{
	vel = Vector3(0,0,0);
	accl = Vector3(0,0,-1);
	minutes =0;
	seconds = 0;
	milliseconds = 0;
}

void Player::Load(Scene* scene, Screen * screen)
{
	cam = scene->getDefaultCamera();
	spotlight = new SceneLight(SceneLight::SPOT_LIGHT, scene, 33, .02, .5, .5);
	scene->addLight(spotlight);
	
	timer = new ScreenLabel("Time: 00:00:00", 16);
	timer->setPosition(320,0);
	screen->addChild(timer);

}

void Player::translate(const Number& x, const Number& y, const Number& z)
{
	obj->Translate(x,y,z);
}

void Player::rotate(const Quaternion& q)
{
	Quaternion rotated =q+ obj->getRotationQuat() ; 
	rotated.Normalize();
	obj->setRotationQuat(rotated.w, rotated.x, rotated.y, rotated.z);
}

void Player::Update(Number elapsed)
{

	milliseconds += elapsed * 1000;
	if( milliseconds >= 1000)
	{
		seconds++;
		milliseconds -=1000;
		if(seconds >= 60)
		{
			minutes++;
			seconds -= 60;
		}
	}
	std::cout<<"Timer:"<<minutes<<":"<<seconds<<":"<<milliseconds<<std::endl;
	vel += accl*elapsed;
	if(vel.z > 100)
	{
		vel.z = 100;
	}

	obj->Translate(vel*elapsed);
	
	cam-> Translate(0,0, vel.z*elapsed);
	cam->lookAt(obj->getPosition());
	spotlight->setPosition( cam -> getPosition() );
	spotlight->lookAt( obj->getPosition() );
}

const Vector3& Player::getPosition()
{
	return obj->getPosition();
}
