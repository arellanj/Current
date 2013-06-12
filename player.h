#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Polycode.h>
#include <iostream>
using namespace Polycode;



class Player
{
	private:
		
		Camera * cam;
		SceneLight * spotlight;
		double maxSpeed;
	public:
		Number coins;
		ScenePrimitive * obj;
		int levelPos;
		Vector3 accl;
		Vector3 vel;
		Player(ScenePrimitive * obj = NULL);
		void Load(Scene * scene);
		void translate(const Number& x, const Number& y, const Number& z);
		void rotate(const Quaternion & q);
		const Vector3& getPosition();
		void Update(Number elapsed);
		void setMaxSpeed(double speed);
};


#endif // __PLAYER_H__

