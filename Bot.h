#include"Entity.h"
#include"Physics.h"
class Bot : public Entity {
private:
	int id;
	bool onGround;
	bool isLeft, isRight;
	float currentFrame;
	float dx, dy; float speed, S;
	//list<Weapon*>weapons;
	//list<Weapon*>::iterator iterW;
public:
	RectangleShape shootBox; bool isDamage;
	int dirD;
	enum { left, right, up, down, stay } state;
	Clock cD; float timeD;
	float health;
	Bot(float X, float Y, float W, float H, float Speed, float Health, Color C) :Entity(X, Y, W, H, C), health(Health), speed(Speed), S(Speed)
	{
		///shootBox.setFillColor(Color::Blue);
		currentFrame = 0;
		shootBox.setSize(Vector2f(getW()*1.5, getH()));
		onGround = false; isDamage = false; state = left; dx = dy = 0; //speed = 0.1;
	}
	Bot(Level& lev, float X, float Y, float W, float H, float Speed, float Health, String File) :Entity(X, Y, W, H, File), health(Health), speed(Speed), S(Speed)
	{
		

		//obj = lev.GetAllObjects();
		id = 2;
		obj = lev.GetAllObjects();
		///shootBox.setFillColor(Color::Blue);
		currentFrame = 0;
		isLeft = isRight = false;
		shootBox.setSize(Vector2f(getW()*1.5, getH())); dirD = -1;
		onGround = false; isDamage = false; state = left; dx = dy = 0; //speed = 0.1;
	}
	void checkCollisioonWithMap(float Dx, float Dy) {
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) { setY(obj[i].rect.top - getH()); /*y = obj[i].rect.top - getH();*/  dy = 0; onGround = true; }
					if (Dy < 0) { setY(obj[i].rect.top + obj[i].rect.height); /*y = obj[i].rect.top + obj[i].rect.height;*/   dy = 0; }
					if (Dx > 0) { setX(obj[i].rect.left - getW()); /*x = obj[i].rect.left - getW();*/ state = up;	onGround = false;	dy = -0.4; }
					if (Dx < 0) { setX(obj[i].rect.left + obj[i].rect.width);/* x = obj[i].rect.left + obj[i].rect.width;*/ state = up;	onGround = false;	dy = -0.4; }
				}
			}
	}
	void animation(float time) {
		if (isLeft) {
			currentFrame += 0.005*time;
			if (currentFrame > 9) currentFrame -= 9;
			sprite->setTextureRect(IntRect(getW() * int(currentFrame) + getW(), 0, -getW(), getH()));

		}
		if (isRight) {
			currentFrame += 0.005*time;
			if (currentFrame > 9) currentFrame -= 9;
			sprite->setTextureRect(IntRect(getW() * int(currentFrame), 0, getW(), getH()));

		}
		if (isDamage) {
			switch (dirD)
			{
			case 0:currentFrame += 0.00005*time;//MOVE Right
				if (currentFrame > 5) currentFrame -= 5;
				sprite->setTextureRect(IntRect(getW() * int(currentFrame), getH(), getW(), getH())); break;
			case 1:currentFrame += 0.00005*time;//MOVE LEFT
				if (currentFrame > 5) currentFrame -= 5;
				sprite->setTextureRect(IntRect(getW() * int(currentFrame) + getW(), getH(), -getW(), getH())); break;
			}

		}
	}
	void control(float tX, float tY) {
		if (!isDamage) {
			if (tX > getX())state = right;
			if (tX < getX()) state = left;
		}


	}
	void drawWeapons(RenderWindow* window) {
		/*for (iterW = weapons.begin(); iterW != weapons.end(); iterW++) {
			if ((*iterW)->id = id) {
				window->draw((*iterW)->sprite);
			}
			(*iterW)->drawBullets(window);
		}*/
	}
	void update(Time time) {
		animation(time.asMicroseconds() / 800);
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right:speed = S; dx = speed; shootBox.setPosition(getX() + getW(), getY()); isRight = true; isLeft = false; dirD = 0; break;//состояние идти вправо
		case left:speed = S; dx = -speed; shootBox.setPosition(getX() - getW() * 1.5, getY()); isLeft = true; isRight = false; dirD = 1; break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: break;//будет состояние во время спуска персонажа (например по лестнице)
		case stay:dx = 0; break;//и здесь тоже		
		}
		if (isDamage) dx = 0;
		//x += dx * time.asMicroseconds() / 800;
		setXPlus(dx * time.asMicroseconds() / 800);
		checkCollisioonWithMap(dx, 0);

		//y += dy * time.asMicroseconds() / 800;
		setYPlus(dy * time.asMicroseconds() / 800);
		checkCollisioonWithMap(0, dy);

		speed = 0;
		sprite->setPosition(getX(), getY()); //задаем позицию спрайта в место его центра
		Physics::gravity2D(&dy,time);
		//dy = dy + 0.0015*time.asMicroseconds() / 800;
		/*for (iterW = weapons.begin(); iterW != weapons.end();iterW++) {
			(*iterW)->x = x;	(*iterW)->y = y;
			(*iterW)->shoot(time);
			(*iterW)->sprite.setPosition(x, y);
			(*iterW)->setTextureWeapon(&dirD);
			(*iterW)->setWeapon(&dirD);
		}*/
		//cout << "X" << x << " Y" << y;
	}
};