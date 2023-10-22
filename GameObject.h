#pragma once
#include<SFML/Graphics.hpp>
#include"Resourses.h"
#include"Entity.h"
using namespace sf;
class GameObject : public Entity,public sf::Transformable,public sf::Drawable {
public:
	GameObject(String File,String Text,String FileFont,int size):Entity(File) {
		getResourse()->loadFonts({ FileFont });	getResourse()->loadText({ Text }, {size});
	}
	GameObject(String File,float tX,float tY,float W,float H):Entity(tX,tY,W,H, File) {

	}
	virtual void setPosition(float x,float y) {
		sprite->sf::Transformable::setPosition(x,y);
	}
	virtual void draw(RenderTarget& target,RenderStates states) const {
		if(sprite)target.draw(*sprite);
		//if(getResourse()->getText(0))
	}
};