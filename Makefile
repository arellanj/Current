CC=g++
CFLAGS=-I${POLY_HOME}/Core/Dependencies/include -I${POLY_HOME}/Core/Dependencies/include/AL -I${POLY_HOME}/Core/include -I${POLY_HOME}/Modules/include -I${POLY_HOME}/Modules/Dependencies/include -I${POLY_HOME}/Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread ${POLY_HOME}/Core/lib/libPolycore.a ${POLY_HOME}/Core/Dependencies/lib/libfreetype.a ${POLY_HOME}/Core/Dependencies/lib/liblibvorbisfile.a ${POLY_HOME}/Core/Dependencies/lib/liblibvorbis.a ${POLY_HOME}/Core/Dependencies/lib/liblibogg.a ${POLY_HOME}/Core/Dependencies/lib/libopenal.so ${POLY_HOME}/Core/Dependencies/lib/libphysfs.a ${POLY_HOME}/Core/Dependencies/lib/libpng15.a ${POLY_HOME}/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ${POLY_HOME}/Modules/lib/libPolycode2DPhysics.a ${POLY_HOME}/Modules/Dependencies/lib/libBox2D.a ${POLY_HOME}/Modules/lib/libPolycode3DPhysics.a ${POLY_HOME}/Modules/Dependencies/lib/libBulletDynamics.a ${POLY_HOME}/Modules/Dependencies/lib/libBulletCollision.a ${POLY_HOME}/Modules/Dependencies/lib/libLinearMath.a

default:
	$(CC) $(CFLAGS) main.cpp player.cpp CurrentApp.cpp Enemy.cpp EnemyManager.cpp -o current $(LDFLAGS)
	cp ${POLY_HOME}/Core/Assets/default.pak .
clean:
	rm current
	rm default.pak
	
