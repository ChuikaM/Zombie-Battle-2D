#pragma once
#include"Entity.h"

class Slider : public Entity,public Drawable{
private:
	string tag;
	float range,max_range;
	float x2,w2;
	RectangleShape slider;
	bool isSelect;
public:
	Slider(float X,float Y,float W,float H,Color c, string tag);
	void setMaxRange(float max_range);
	float getRange();
	string getTag();
	void setPos(float range);
	void setRange(float range);
	void move(Vector2i v,Event& event);
	void draw(RenderTarget& target,RenderStates states) const;
	void draw(RenderTarget& target) const;
};
Slider::Slider(float X, float Y, float W, float H, Color C, string tag) :Entity(X, Y, W, H, C), isSelect(false), x2(X + getW() - w2), w2(16), range(0), max_range(0) {
	this->tag = tag;
	slider.setSize(Vector2f(w2, getH()));
	slider.setFillColor(Color::Red);
	slider.setPosition(x2, getY());
}

void Slider::setMaxRange(float max_range) {
	this->max_range = max_range;
	//this->range = max_range;
}
float Slider::getRange() {
	return range;
}
string Slider::getTag() {
	return tag;
}
void Slider::setPos(float range) {
	x2 = ((range*getW()) / max_range) + getX();
	slider.setPosition(x2,getY());
}
void Slider::setRange(float range) {
	this->range = range;
}
void Slider::move(Vector2i v,Event& event) {
	if (event.type == Event::MouseButtonPressed) {
		if (slider.getGlobalBounds().contains(v.x, v.y)) 
			isSelect = true;
		
	}
	else if (event.type == Event::MouseButtonReleased)
		isSelect = false;
	if (isSelect) {
		slider.setPosition(x2, getY()); x2 = v.x;

		if (v.x < getX()) {
			x2 = getX();
		}
		else if (v.x > getX() + getW() - w2) {
			x2 = getX() + getW() - w2;
		}
		
	}
	range = (x2 - getX())*max_range / getW();
}
void Slider::draw(RenderTarget& target, RenderStates states) const {
	target.draw(*entity); target.draw(slider);
}
void Slider::draw(RenderTarget& target) const {
	target.draw(*entity); target.draw(slider);
}