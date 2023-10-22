#include<SFML/Graphics.hpp>
//#include"Entity.h"
#include"Entity.h"
class Bullet : public Entity {
private:
	float speed, dx;
	float S;
	int dir;
	Clock c;
	Time t;
	Time t2;
public:
	bool isLive;
	bool isPush;
	Bullet(Level& lev, float X, float Y, float W, float H, float speed) : Entity::Entity(lev, X, Y, W, H) {
		this->speed = speed; dx = 0;
		S = speed;
		isLive = true;
		isPush = true;
		t2 = seconds(1);
	}
	
	void checkCollisionWithMap() {
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					isLive = false;
				}
			}
	}
	void update(float* pX, float* pY, int Dir) {
		t += c.restart();
		if (t >= t2) {
			isLive = false;
		}
		switch (Dir)
		{
		case 0: setX(*pX + 19); /*x = *pX + 19;*/  break;
		case 1:setX(*pX - 19);/* x = *pX - 19;*/  break;
		}
		//y = *pY;
		setY(*pY);
		entity->setPosition(getX(), getY());
	}
	void control(float* pX, float* pY, Time time, int Dir) {
		if (isPush) {// чтобы пуля не танцевала
			dir = Dir;
			setX(*pX); setY(*pY);
			//x = *pX; y = *pY;
			isPush = false;
		}
		speed = S;
		switch (dir)
		{
		case 0:dx = speed; break;
		case 1:dx = -speed; break;
		}

		//x += dx * time.asMicroseconds() / 800;//пуля летит по оси X
		setXPlus(dx * time.asMicroseconds() / 800);
		speed = 0;
		entity->setPosition(getX(), getY());
		checkCollisionWithMap();
		//interactionWithMap(mapP);
	}
};