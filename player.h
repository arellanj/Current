#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <Polycode.h>
using namespace Polycode;



class Player
{
	private:
		ScenePrimitive * obj;
		Camera * cam;
	public:
		Vector3 dir;
		Player(ScenePrimitive * obj = NULL, Camera * cam = NULL);
		void translate(const Number& x, const Number& y, const Number& z);
		void rotate(const Quaternion & q);
		const Vector3& getPosition();
		void Update(Number elapsed);
};

#endif // __PLAYER_H__

