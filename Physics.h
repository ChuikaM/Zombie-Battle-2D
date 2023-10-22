#pragma once
#include<SFML/Graphics.hpp>
class Physics {
private:
	static const float G;
	
public:
	static float U;
	static float y0;
	static void gravity2D(float* dy, sf::Time time);
	static void subVectorMove(float* dy,sf::Time time);
	static void subVectorJump_if(float* force,const float* const y,sf::Time time,bool onGround);
	static void physics2D(float* dx,float* dy,sf::Time time);
};

const float Physics::G = 0.0015;
float Physics::U = 10;

float Physics::y0 = 0;
void Physics::gravity2D(float* dy,sf::Time time) {
	*dy = *dy + G * time.asMicroseconds() / 800;
}
void Physics::subVectorMove(float* dy,sf::Time time) {
	if (U > 0) {
		*dy -=U * G * time.asMicroseconds() / 800;
		U -=0.0001;
	}
}
void Physics::subVectorJump_if(float* force,const float* const y,sf::Time time,bool onGround) {
	static float u = U;
	u -= (abs(*y - y0) > 32) ? 0.0005 : 0.0001;
}
void Physics::physics2D(float* dx, float* dy, sf::Time time) {
	//gravity2D(dx,time);
	//subVectorMove(dx,time);
	gravity2D(dy, time);
	//subVectorMove(dy, time);
}