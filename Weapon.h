#include<SFML/Graphics.hpp>
#include"Bullet.h"
#include"configButtons.h"

class Weapon : public Entity {
private:
	bool isRemaing;
private:
	Clock remaing;
	Clock shootTimer;
private:
	float timeR;
	float timeRemaingWeapon;
	float timeST;
	float timeS;
private:
	float damage;
	int countOfAmmoShootC;//сколько в одной обойме(Копия)
	int countOfAmmo;//сколько патронов вообще в оружие
	int countOfAmmoShoot;
	int countOfAmmoC;//сколько патронов вообще в оружие(Копия)
	Level lev;
private:
	static int idInc;
private:
	void setCurrentWeapon();
public:
	
	list<Bullet*> bullets;
	list<Bullet*>::iterator iter;
	int id;
	bool isSetWeapon;
	string type;
	Texture texIcon;
	Sprite weaponIcon;
	Weapon(){}
	Weapon(Level& Lev, float X, float Y, string Type, int Id);
	Weapon(Level& Lev, float X, float Y, string Type);
	~Weapon() {
		for (iter = bullets.begin(); iter != bullets.end(); iter++) {
			
			Bullet* b = *iter;
			iter = bullets.erase(iter);
			delete b;
			if (iter == bullets.end()) {
				break;
			}
			
		}
		idInc = id;
		cout << "\~Weapon()\n";
	}
	/*Weapon(String File, float X, float Y, float W, float H) : Entity::Entity(X, Y, W, H, File)
	{

	}*/
	void setTimeS(float timeS);
	void setTimeRemaingWeapon(float timeR);
	void setDamage(float damage);
	void setCountOfAmmo();
	void setCountOfAmmo(float ammo);
	void setCountOfAmmoShoot(float ammoS);
	float getDamage();
	int getCountOfAmmo();
	int getCountOfAmmoShoot();
	void remaning();
	
	
	void shoot(Time time);
	void shoot(Event even, Time time);
	void updateBullets(Time time, int Dir);
	void drawBullets(RenderWindow* window);
	void setWeaponT(int* dir);
	void setWeapon(int* dir);
	void setIconweaponT();
	void setIconweapon();
	void setTextureWeapon(const int* dir);
	void setPosOfIcon(float X, float Y);

	void processAllFunctions(float X,float Y,float W,int dirW,Event event,Time time);
	void showInforation(sf::RenderWindow* window);

	virtual void draw(RenderTarget& target, RenderStates states) const;
};
int Weapon::idInc = 0;

Weapon::Weapon(Level& Lev, float X, float Y, string Type, int Id) {
	lev = Lev;
	damage = 10; id = Id; isSetWeapon = true; isRemaing = false; setX(X); setY(Y); type = Type;
	setCurrentWeapon();
}
Weapon::Weapon(Level& Lev, float X, float Y, string Type) {
	lev = Lev;
	damage = 10; id = idInc++; isSetWeapon = true; isRemaing = false; setX(X); setY(Y); type = Type;
	setCurrentWeapon();
	setIconweaponT();
}
void Weapon::setTimeRemaingWeapon(float timeR) {
	this->timeRemaingWeapon = timeR;
}
void Weapon::setTimeS(float timeS) {
	this->timeS = timeS;
}
void Weapon::setDamage(float damage) {
	this->damage = damage;
}
void Weapon::setCountOfAmmo() {
	countOfAmmo = countOfAmmoC;
}
void Weapon::setCountOfAmmo(float ammo) {
	countOfAmmo = ammo;
}
void Weapon::setCountOfAmmoShoot(float ammoS) {
	countOfAmmoShoot = ammoS;
}
float Weapon::getDamage() {
	return damage;
}
int Weapon::getCountOfAmmo() {
	return countOfAmmo;
}
int Weapon::getCountOfAmmoShoot() {
	return countOfAmmoShoot;
}
void Weapon::remaning() {
	if (isRemaing) {
		timeR = remaing.getElapsedTime().asSeconds();
		//isRemaing = false;
		if (timeR > timeRemaingWeapon) {
			cout << "\nRem\n";
			//countOfAmmo -= countOfAmmoShootC - countOfAmmoShoot;//Исправить БАГ
			while (countOfAmmo > 0) {
				--countOfAmmo;
				if (countOfAmmoShoot == countOfAmmoShootC) {
					break;
				}
				++countOfAmmoShoot;
			}
			/*for (; countOfAmmoShoot <= countOfAmmoShootC; countOfAmmoShoot++) {
				if (countOfAmmoShoot == countOfAmmoShootC) {
					break;
				}
			}*/
			isRemaing = false;
			timeR = 0;
		}
	}
	else {
		remaing.restart();
	}
}
void Weapon::shoot(Time time) {
	remaning();
	timeST = shootTimer.getElapsedTime().asSeconds();
	if (timeST > timeS && !isRemaing) {
		cout << "Hello";
		shootTimer.restart();
		timeST = 0;
		cout << "Ammo: " << countOfAmmo;
		cout << "AmmoS: " << countOfAmmoShoot;
		if (countOfAmmo >= 0 && countOfAmmoShoot > 0) {
			--countOfAmmoShoot;
			bullets.push_back(new Bullet(lev, getX(), getY(), 4, 2, 0.3));
		}
	}
}
void Weapon::shoot(Event even, Time time) {
	remaning();
	timeST = shootTimer.getElapsedTime().asSeconds();
	if (Mouse::isButtonPressed(Mouse::Left) && type == "huntingknife"&& timeST > timeS) {
		bullets.push_back(new Bullet(lev, getX(), getY(), 12, 20, 0));
		shootTimer.restart();
		timeST = 0;
	}
	if (Mouse::isButtonPressed(Mouse::Left) && timeST > timeS && !isRemaing && type != "huntingknife") {
		//cout << "Hello";
		shootTimer.restart();
		timeST = 0;
		cout << "Ammo: " << countOfAmmo;
		cout << "AmmoS: " << countOfAmmoShoot;
		if (countOfAmmo >= 0 && countOfAmmoShoot > 0) {
			--countOfAmmoShoot;
			bullets.push_back(new Bullet(lev, getX(), getY(), 4, 2, 0.3));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::R) && countOfAmmoShoot >= 0 && countOfAmmoShoot < countOfAmmoShootC) {
		isRemaing = true;
		cout << "Remaing";
	}
	if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(buttonsConfig["ButtonRemaing"]))) {
		if (countOfAmmoShoot >= 0 && countOfAmmoShoot < countOfAmmoShootC) {
			isRemaing = true;
			cout << "Remaing";
		}

	}
}
void Weapon::updateBullets(Time time, int Dir) {

	for (iter = bullets.begin(); iter != bullets.end(); ) {
		//list<Bot*>::iterator iterB;
		Bullet* b = *iter;
		if (type == "huntingknife")
			b->update(getXPtr(), getYPtr(), Dir);
		else
			b->control(getXPtr(), getYPtr(), time, Dir);
		/*for (iterB = bots->begin(); iterB != bots->end(); iterB++) {
			if (b->entity.getGlobalBounds().intersects((*iterB)->sprite.getGlobalBounds())) {
				(*iterB)->health -= 10; b->isLive = false;
			}
		}*/
		if (!b->isLive) {
			iter = bullets.erase(iter);
			delete b;
			cout << "Byu";
		}
		else {
			iter++;
		}
	}
}
void Weapon::drawBullets(RenderWindow* window)
{
	for (iter = bullets.begin(); iter != bullets.end(); iter++) {
		(*iter)->entity->setSize(Vector2f((*iter)->getW(), (*iter)->getH()));
		(*iter)->entity->setFillColor(Color::White);
		window->draw(*(*iter)->entity);
		//cout << " " << (*iter)->x << " " << (*iter)->y << " ";
	}

}
void Weapon::setWeaponT(int* dir) {
	if (isSetWeapon) {
		texture.loadFromFile("Images/weapons/" + type + ".png");
		setW(texture.getSize().x); setH(texture.getSize().y);
		sprite->setTexture(texture);
		sprite->setScale(0.5, 0.5);

		texIcon.loadFromFile("Images/icons/icon_" + type + ".png");

		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
		switch (*dir)
		{
		case 0:sprite->setTextureRect(IntRect(0, 0, getW(), getH())); break;
		case 1:sprite->setTextureRect(IntRect(getW(), 0, -getW(), getH())); break;
		}
		countOfAmmoC = countOfAmmo;
		countOfAmmoShootC = countOfAmmoShoot;
		isSetWeapon = false;
	}

	//timeS = 1;
	//timeRemaingWeapon = 0.2;
}
void Weapon::setWeapon(int* dir) {
	if (isSetWeapon) {
		if (type == "huntingknife") {
			//w = 37; h = 9;
			setW(37); setH(9);
			texture.loadFromFile("Images/weapons/huntingknife.png");
			sprite->setTexture(texture);
			sprite->setScale(0.5, 0.5);

			texIcon.loadFromFile("Images/icons/icon_huntingknife.png");
			weaponIcon.setTexture(texIcon);
			weaponIcon.setScale(0.5, 0.5);
			timeS = 1;
			timeRemaingWeapon = 0.2;
			cout << "Knife";
		}
		if (type == "usp-s") {
			//w = 31; h = 14;
			setW(31); setH(14);
			texture.loadFromFile("Images/weapons/usp-s.png");
			sprite->setTexture(texture);
			sprite->setScale(0.5, 0.5);

			texIcon.loadFromFile("Images/icons/icon_usp-s.png");
			weaponIcon.setTexture(texIcon);
			weaponIcon.setScale(0.5, 0.5);

			timeS = 0.2;
			countOfAmmo = 120;
			countOfAmmoShoot = 10;
			timeRemaingWeapon = 1.5;
			cout << "Usp-s";
		}
		if (type == "glock") {
			//w = 24; h = 16;
			setW(24); setH(16);
			texture.loadFromFile("Images/weapons/glock.png");
			sprite->setTexture(texture);
			sprite->setScale(0.5, 0.5);

			texIcon.loadFromFile("Images/icons/icon_glock.png");
			weaponIcon.setTexture(texIcon);
			weaponIcon.setScale(0.5, 0.5);

			timeS = 0.2;
			countOfAmmo = 120;
			countOfAmmoShoot = 12;
			timeRemaingWeapon = 2;
		}
		if (type == "deagle") {
			//w = 32; h = 18;
			setW(32); setH(18);

			texture.loadFromFile("Images/weapons/deagle.png");
			sprite->setTexture(texture);
			sprite->setScale(0.5, 0.5);

			texIcon.loadFromFile("Images/icons/icon_deagle.png");
			weaponIcon.setTexture(texIcon);
			weaponIcon.setScale(0.5, 0.5);

			timeS = 0.3;
			countOfAmmo = 32;
			countOfAmmoShoot = 7;
			timeRemaingWeapon = 0.5;
		}
		if (type == "ak-47") {
			//w = 56; h = 21;
			setW(56); setH(21);
			texture.loadFromFile("Images/weapons/ak-47.png");
			sprite->setTexture(texture);
			sprite->setScale(0.5, 0.5);

			texIcon.loadFromFile("Images/icons/icon_ak-47.png");
			weaponIcon.setTexture(texIcon);
			weaponIcon.setScale(0.5, 0.5);

			timeS = 0.15;
			countOfAmmo = 90;//сколько патронов вообще в оружие
			countOfAmmoShoot = 30;//сколько в одной обойме
			timeRemaingWeapon = 0.5;
		}
		if (type == "m4a1") {
			//w = 64; h = 21;
			setW(64); setH(21);
			texture.loadFromFile("Images/weapons/m4a1.png");
			sprite->setTexture(texture);
			sprite->setScale(0.5, 0.5);

			texIcon.loadFromFile("Images/icons/icon_m4a1.png");
			weaponIcon.setTexture(texIcon);
			weaponIcon.setScale(0.5, 0.5);

			timeS = 0.15;
			countOfAmmo = 90;//сколько патронов вообще в оружие
			countOfAmmoShoot = 30;//сколько в одной обойме
			timeRemaingWeapon = 1.7;
		}
		switch (*dir)
		{
		case 0:sprite->setTextureRect(IntRect(0, 0, getW(), getH())); break;
		case 1:sprite->setTextureRect(IntRect(getW(), 0, -getW(), getH())); break;
		}
		countOfAmmoC = countOfAmmo;
		countOfAmmoShootC = countOfAmmoShoot;
		isSetWeapon = false;
	}

}
void Weapon::setIconweaponT() {
	
	texIcon.loadFromFile("Images/icons/icon_" + type + ".png");
	weaponIcon.setTexture(texIcon);
	weaponIcon.setScale(0.5, 0.5);
	
}
void Weapon::setIconweapon() {
	if (type == "huntingknife") {
		texIcon.loadFromFile("Images/icons/icon_huntingknife.png");
		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
	}
	if (type == "usp-s") {
		texIcon.loadFromFile("Images/icons/icon_usp-s.png");
		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
	}
	if (type == "glock") {
		texIcon.loadFromFile("Images/icons/icon_glock.png");
		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
	}
	if (type == "deagle") {
		texIcon.loadFromFile("Images/icons/icon_deagle.png");
		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
	}
	if (type == "ak-47") {
		texIcon.loadFromFile("Images/icons/icon_ak-47.png");
		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
	}
	if (type == "m4a1") {
		texIcon.loadFromFile("Images/icons/icon_m4a1.png");
		weaponIcon.setTexture(texIcon);
		weaponIcon.setScale(0.5, 0.5);
	}
}
void Weapon::setTextureWeapon(const int* dir) {
	switch (*dir)
	{
	case 0: sprite->setTextureRect(IntRect(0, 0, getW(), getH())); break;
	case 1:sprite->setTextureRect(IntRect(getW(), 0, -getW(), getH())); break;
	}
}
void Weapon::setPosOfIcon(float X,float Y) {
	if (id == 0)
		weaponIcon.setPosition(X+ 40,Y + 40);
	else if(id == 1)
		weaponIcon.setPosition(X + 40, Y + 20);
	else if(id == 2)
		weaponIcon.setPosition(X + 40, Y);
}
void Weapon::setCurrentWeapon() {

	if (type == "huntingknife") {
		timeS = 1;
		timeRemaingWeapon = 0.2;
		damage = 20;
		cout << "Knife";
	}
	if (type == "usp-s") {
		timeS = 0.2;
		countOfAmmo = 120;
		countOfAmmoShoot = 10;
		timeRemaingWeapon = 1.5;
		damage = 25;
		cout << "Usp-s";
	}
	if (type == "glock") {
		timeS = 0.2;
		countOfAmmo = 120;
		countOfAmmoShoot = 12;
		timeRemaingWeapon = 2;
		damage = 18;
	}
	if (type == "deagle") {
		timeS = 0.3;
		countOfAmmo = 32;
		countOfAmmoShoot = 7;
		timeRemaingWeapon = 0.5;
		damage = 25;
	}
	if (type == "ak-47") {
		timeS = 0.15;
		countOfAmmo = 90;//сколько патронов вообще в оружие
		countOfAmmoShoot = 30;//сколько в одной обойме
		timeRemaingWeapon = 0.5;
		damage = 28;
		cout << "\nAk-47\n";
	}
	if (type == "m4a1") {
		timeS = 0.15;
		countOfAmmo = 90;//сколько патронов вообще в оружие
		countOfAmmoShoot = 30;//сколько в одной обойме
		timeRemaingWeapon = 1.7;
		damage = 28;
	}
}
void Weapon::processAllFunctions(float X, float Y, float W, int dirW, Event event, Time time) {
	shoot(event, time);
	setY(Y + W / 2);
	sprite->setPosition(X, Y + W / 2);
	setTextureWeapon(&dirW);
}
void Weapon::showInforation(sf::RenderWindow* window) {
	//window->draw();
	//window->draw();
}
void Weapon::draw(RenderTarget& target, RenderStates states) const {
	target.draw(*sprite);
	
}