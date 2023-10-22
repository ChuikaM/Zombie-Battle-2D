#pragma once
#include"Entity.h"
class ProgressBar : public Entity, public sf::Drawable {
private:
	RectangleShape bar;
public:
	ProgressBar(float X, float Y, float W, float H, Color C,Color c):Entity(X,Y,W,H,C) {
		bar.setSize(Vector2f(0, 0)); bar.setPosition(X, Y); bar.setFillColor(c);
	}
	void setValue(float progress) {
		entity.setSize((progress * getW())/100);
	}
	virtual void draw(sf::RenderWindow& window,sf::RenderStates states) const {
		window.draw(entity);
	}
};