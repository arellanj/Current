CC=g++ -g
CFLAGS=-I${POLY_HOME}/Core/Dependencies/include -I${POLY_HOME}/Core/Dependencies/include/AL -I${POLY_HOME}/Core/include -I${POLY_HOME}/Modules/include -I${POLY_HOME}/Modules/Dependencies/include -I${POLY_HOME}/Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread ${POLY_HOME}/Core/lib/libPolycore.a ${POLY_HOME}/Core/Dependencies/lib/libfreetype.a ${POLY_HOME}/Core/Dependencies/lib/liblibvorbisfile.a ${POLY_HOME}/Core/Dependencies/lib/liblibvorbis.a ${POLY_HOME}/Core/Dependencies/lib/liblibogg.a ${POLY_HOME}/Core/Dependencies/lib/libopenal.so ${POLY_HOME}/Core/Dependencies/lib/libphysfs.a ${POLY_HOME}/Core/Dependencies/lib/libpng15.a ${POLY_HOME}/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ${POLY_HOME}/Modules/lib/libPolycode2DPhysics.a ${POLY_HOME}/Modules/Dependencies/lib/libBox2D.a ${POLY_HOME}/Modules/lib/libPolycode3DPhysics.a ${POLY_HOME}/Modules/Dependencies/lib/libBulletDynamics.a ${POLY_HOME}/Modules/Dependencies/lib/libBulletCollision.a ${POLY_HOME}/Modules/Dependencies/lib/libLinearMath.a

default: LevelManager.o player.o CurrentApp.o
	$(CC) $(CFLAGS) main.cpp CurrentApp.o player.o LevelManager.o -o current $(LDFLAGS)
	cp ${POLY_HOME}/Core/Assets/default.pak .
CurrentApp.o: CurrentApp.cpp CurrentApp.h LevelManager.o player.o
	$(CC) $(CFLAGS) -c CurrentApp.cpp LevelManager.o player.o

LevelManager.o: LevelManager.cpp player.o Enemy.cpp EnemyManager.cpp
	$(CC) $(CFLAGS) -c LevelManager.cpp player.o EnemyManager.cpp Enemy.cpp 

player.o: player.cpp player.h
	$(CC) $(CFLAGS) -c player.cpp 

clean:
	rm ./current
	rm default.pak
	rm *.o
