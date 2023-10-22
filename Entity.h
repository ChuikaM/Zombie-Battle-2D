#pragma once
#include<cstdlib>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<fstream>
#include<list>
#include<string>
#include<vector>
#include<map>
#include<iostream>

#include"Resourses.h"
#include"levelMy.h"
#include"TinyXML/tinyxml2.h"
//#include"lvlM.h"
//#include"level.h"
#include "TinyXML/tinyxml.h"
using namespace sf;
using namespace std;

class Entity{

private:
	float  w, h;
	float x, y;
public:
	Resourse* r;
public:
	
	String File;
	Texture texture;
	Sprite* sprite;
	RectangleShape* entity;
	std::vector<Object> obj;
	Entity() {
		entity = new RectangleShape();
		sprite = new Sprite();
	}
	~Entity() {
		
		if (r) delete r;
		if (sprite)delete sprite;
		if (entity)delete entity;
		cout << "\nEnd";
	}
	Entity(float X, float Y, float W, float H) :x(X), y(Y), w(W), h(H) {
		entity = new RectangleShape();
		entity->setSize(Vector2f(w, h));
		entity->setFillColor(Color::White);
	}
	Entity(Level& lev,float X, float Y, float W, float H) :x(X), y(Y), w(W), h(H) {
		//obj = lev.GetAllObjects();
		entity = new RectangleShape();
		obj = lev.GetAllObjects();
		entity->setSize(Vector2f(w, h));
		entity->setFillColor(Color::White);
	}
	Entity(float X,float Y,float W,float H,Color c) :x(X),y(Y),w(W),h(H) {
		entity = new RectangleShape();
		entity->setSize(Vector2f(w,h));
		entity->setFillColor(c);
		entity->setPosition(x,y);
	}
	Entity(float X,float Y,float W,float H,String File) :x(X), y(Y), w(W), h(H) {
		sprite = new Sprite();
		r = new Resourse();
		this->File = File;
		r->loadTextures({ File });
		//texture.loadFromFile(this->File); 
		cout << " Hi ";
		sprite->setTexture(*r->getTexture(0));
		sprite->setTextureRect(IntRect(0,0,w,h));
		sprite->setPosition(x,y);
	}

	Entity(float X, float Y, String File) :x(X), y(Y) {
		sprite = new Sprite();
		r = new Resourse();
		this->File = File;
		cout << " Hi1 ";
		r->loadTextures({ this->File });
		//texture.loadFromFile(this->File);
		w = r->getTexture(0)->getSize().x; h = r->getTexture(0)->getSize().y;
		sprite->setTexture(*r->getTexture(0));
		sprite->setTextureRect(IntRect(0, 0, w, h));
		sprite->setPosition(x, y);
	}
	Entity(String File){
		sprite = new Sprite();
		r = new Resourse();
		this->File = File;
		cout << "Hi2";
		r->loadTextures({ File });
		//texture.loadFromFile(this->File);
		w = r->getTexture(0)->getSize().x; h = r->getTexture(0)->getSize().y;
		sprite->setTexture(*r->getTexture(0));
	}
	//Entity(float xT, float yT,float W,float H, String File):w(W),h(H) {
	//	sprite = new Sprite();
	//	r = new Resourse();
	//	r->loadTextures({ File });
	//	//texture.loadFromFile(this->File);
	//	sprite->setTexture(*r->getTexture(0));
	//	sprite->setTextureRect(IntRect(xT, yT, w, h));
	//}
	Entity(float X, float Y,float xT,float yT, float W, float H, String File) :x(X), y(Y), w(W), h(H) {
		sprite = new Sprite();
		r = new Resourse();
		this->File = File; 
		cout << "Hi3";
		r->loadTextures({ File });
		//texture.loadFromFile(this->File); 
		sprite->setTexture(*r->getTexture(0));
		sprite->setTextureRect(IntRect(xT, yT, w, h));
		sprite->setPosition(x, y);
	}
	void setXPlus(float x) {
		this->x += x;
	}
	void setYPlus(float y) {
		this->y += y;
	}
	void setX(float x) {
		this->x = x;
	}
	void setY(float y) {
		this->y = y;
	}
	void setW(float w) {
		this->w = w;
	}
	void setH(float h) {
		this->h = h;
	}
	float* getXPtr() {
		return &x;
	}
	float* getYPtr() {
		return &y;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getW() {
		return w;
	}
	float getH() {
		return h;
	}
	void setSpriteFromFile(String File) {
		
		sprite = new Sprite();
		r = new Resourse();
		//this->File = File;
		cout << " Hi7 ";
		r->loadTextures({ File });
		//texture.loadFromFile(this->File);
		sprite->setTexture(*r->getTexture(0));
		sprite->setTextureRect(IntRect(0, 0, w, h));
		sprite->setPosition(x, y);
	}
	FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}
	Resourse* getResourse() {
		return r;
	}
};