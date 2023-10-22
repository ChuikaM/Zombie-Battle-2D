#include"Weapon.h"
#include"Physics.h"
#include"view.h"
#include"configButtons.h"
class Player : public Entity {
private:
	int currentWeapon;
	int dirW;
private:
	float dx, dy; float speed;
	float force;
	float currentFrame[3];
private:
	enum { left, right, up, down, stay } state;

	Entity healthBar; Entity armorBar;
	Font f; Text infoOfAmmo, infoHealth, infoArmor;
private:
	bool isLeft, isRight, isStay; bool onGround;
private:
	Level* lev;
public:
	list<Weapon*> weapons;
	list<Weapon*>::iterator iterW;
	
	float health, armor;
	Player(String fileMap, float W, float H, String File) 
	{
		lev = new Level();
		lev->LoadFromFile(fileMap);
		obj = lev->GetAllObjects();
		
		setX(lev->GetObject("player").rect.left); setY(lev->GetObject("player").rect.top);
		setW(W); setH(H);
		setSpriteFromFile(File);

		armorBar.texture.loadFromFile("Images/icons/barsForGame.png"); armorBar.sprite->setTexture(armorBar.texture); armorBar.sprite->setTextureRect(IntRect(0, 0, armorBar.texture.getSize().x / 2, armorBar.texture.getSize().y));
		healthBar.texture.loadFromFile("Images/icons/barsForGame.png"); healthBar.sprite->setTexture(healthBar.texture); healthBar.sprite->setTextureRect(IntRect(healthBar.texture.getSize().x / 2, 0, healthBar.texture.getSize().x / 2, healthBar.texture.getSize().y));
		f.loadFromFile("Comfortaa.ttf");
		infoOfAmmo.setFont(f); infoOfAmmo.setFillColor(Color::Black); infoOfAmmo.setCharacterSize(25);
		infoHealth.setFont(f); infoHealth.setFillColor(Color::Black); infoHealth.setCharacterSize(25);
		infoArmor.setFont(f); infoArmor.setFillColor(Color::Black); infoArmor.setCharacterSize(25);
		//setWalls(&wall);
		/*weapons.push_front(new Weapon(lev, X, Y, "ak-47", 0));
		weapons.push_front(new Weapon(lev, X, Y, "usp-s", 1));
		weapons.push_front(new Weapon(lev, X, Y, "huntingknife", 2));*/
		weapons.push_front(new Weapon(*lev, getX(), getY() + getW() / 2, "ak-47"));
		weapons.push_front(new Weapon(*lev, getX(), getY() + getW() / 2, "usp-s"));
		weapons.push_front(new Weapon(*lev, getX(), getY() + getW() / 2, "huntingknife"));
		//iterW = weapons.begin();
		currentWeapon = 2; dirW = 0; health = 100; armor = 100;
		currentFrame[0] = 0; currentFrame[1] = 0; currentFrame[2] = 0;
		speed = 0.2; onGround = false;
		isLeft = isRight = isStay = false;
		dx = dy = 0;
		state = stay;
	}
	~Player(){
		
		for (iterW = weapons.begin(); iterW != weapons.end(); iterW++ ) {
			cout << "\n1~Payer()\n";
			Weapon* w = *iterW;
			cout << "\n2~Payer()\n";
			iterW = weapons.erase(iterW);
			cout << "\n3~Payer()\n";
			delete w;
			cout << "\n4~Payer()\n";
			if (iterW == weapons.end()) {
				break;
			}
			cout << "\n5~Payer()\n";
			
			cout << "\n6~Payer()\n";
		}
		cout << "\n~Payer()\n";
		delete lev;
	}
	void animation(float time) {
		if (isLeft) {
			currentFrame[0] += 0.005*time;
			if (currentFrame[0] > 5) currentFrame[0] -= 5;
			sprite->setTextureRect(IntRect(getW() * int(currentFrame[0]) + getW(), getH(), -getW(), getH()));

		}
		if (isRight) {
			currentFrame[0] += 0.005*time;
			if (currentFrame[0] > 5) currentFrame[0] -= 5;
			sprite->setTextureRect(IntRect(getW() * int(currentFrame[0]), getH(), getW(), getH()));

		}

		if (isStay) {
			currentFrame[2] += 0.005*time;
			if (currentFrame[2] > 1) currentFrame[2] -= 1;
			switch (dirW)
			{
			case 0:sprite->setTextureRect(IntRect(getW() * int(currentFrame[2]), getH(), getW(), getH()));

				break;//right animation
			case 1:sprite->setTextureRect(IntRect(getW() * int(currentFrame[2]) + getW(), getH(), -getW(), getH()));

				break;//left animation
			}

		}

	}
	
	void draw(RenderWindow* window) {
		window->draw(*sprite);
		for (iterW = weapons.begin(); iterW != weapons.end(); iterW++) {
			if ((*iterW)->id == currentWeapon) {
				window->draw(*(*iterW)->sprite);
			}

			(*iterW)->drawBullets(window);
			window->draw((*iterW)->weaponIcon);
		}
		window->draw(infoOfAmmo);	window->draw(infoHealth);	window->draw(infoArmor);
		window->draw(*healthBar.sprite); window->draw(*armorBar.sprite);
		
	}
	void checkCollisioonWithMap(float Dx, float Dy) {
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) { setY(obj[i].rect.top - getH());  dy = 0; onGround = true; }
					if (Dy < 0) { setY(obj[i].rect.top + obj[i].rect.height);   dy = 0; }
					if (Dx > 0) { setX(obj[i].rect.left - getW()); }
					if (Dx < 0) { setX(obj[i].rect.left + obj[i].rect.width); }
				}
			}

	}
	void control(Time time) {
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonHeavy"]))) {
			currentWeapon = 0;
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonPistol"]))) {
			currentWeapon = 1;
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonKnife"]))) {
			currentWeapon = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::G) && currentWeapon != 0) {
			//isDrop = false;
			for (iterW = weapons.begin(); iterW != weapons.end(); iterW++) {
				if ((*iterW)->id == currentWeapon) {
					currentWeapon = 0;
					Weapon* w = *iterW;
					iterW = weapons.erase(iterW);
					delete w;
					break;
				}
			}
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonJump"])) && onGround) {
			state = up; onGround = false; dy = -force; force = 0.3; Physics::U = 10;
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonLeft"])) || Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; speed = 0.2; dirW = 1; isLeft = true; 
		}
		else {
			isLeft = false;
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonRight"])) || Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; speed = 0.2; dirW = 0; isRight = true; 
		}
		else {
			isRight = false;
		}
		if ((!Keyboard::isKeyPressed(Keyboard::Right) && (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonRight"])))) && (!Keyboard::isKeyPressed(Keyboard::Left) && (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonLeft"])))) && (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonJump"])))) {
			isStay = true;
		}
		else {
			isStay = false;
		}
		setViewPlayer(getX(), getY());
	}
	void update(Event event, Time time) {
		animation(time.asMicroseconds() / 800);
		control(time);//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right: dx = speed;  break;//состояние идти вправо
		case left: dx = -speed;  break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
		case stay: break;//и здесь тоже		
		}
		
		setXPlus(dx * time.asMicroseconds() / 800);
		checkCollisioonWithMap(dx, 0);//обрабатываем столкновение по Х
	
		setYPlus(dy * time.asMicroseconds() / 800);
		checkCollisioonWithMap(0, dy);//обрабатываем столкновение по Y
		
		speed = 0;
		if (onGround) { 
			 if (force >= 0.4)force = 0.4; force += 0.01;
			 //if (dx <= speed) dx = speed;
			// Physics::subVectorMove(&dx, time);
			
		}
		sprite->setPosition(getX(), getY());

		std::ostringstream playerHealth, playerArmor;
		playerHealth << health; playerArmor << armor;
		infoHealth.setString(playerHealth.str()); infoArmor.setString(playerArmor.str());
		infoHealth.setPosition(getX() - 120, getY() + 90); infoArmor.setPosition(getX() + 30, getY() + 90);
		healthBar.sprite->setPosition(getX() - 150, getY() + 100); armorBar.sprite->setPosition(getX(), getY() + 100);

		//dy = dy + 0.0015*time.asMicroseconds() / 800;
		Physics::gravity2D(&dy,time);
		for (iterW = weapons.begin(); iterW != weapons.end(); iterW++) {
			//(*iterW)->setIconweaponT();
			
			(*iterW)->setX(getX()); (*iterW)->setY(getY());
			(*iterW)->setPosOfIcon(getX(),getY());
			if ((*iterW)->id == currentWeapon) {
				std::ostringstream playerAmmo, playerAmmoShoot;
				playerAmmoShoot << (*iterW)->getCountOfAmmoShoot(); playerAmmo << (*iterW)->getCountOfAmmo();
				infoOfAmmo.setString(playerAmmoShoot.str() + " / " + playerAmmo.str());
				(*iterW)->setWeaponT(&dirW);
				//(*iterW)->shoot(event, time);
				(*iterW)->shoot(event, time);
				(*iterW)->setY(getY() + getW() / 2);
				(*iterW)->sprite->setPosition(getX(), getY() + getW() / 2);
				(*iterW)->setTextureWeapon(&dirW);
			}
			(*iterW)->updateBullets(time, dirW);


			//(*iterW)->shoot(mousePos, pos, even, time);
		}
		infoOfAmmo.setPosition(getX() + 100, getY() + 100);
	}
};
