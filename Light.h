#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Light{
private:
	Vertex light[];
public:
	Light(float x,float y,float size);
};
