//#include"Weapon.h"
#pragma once
#include"Player.h"
#include"Bot.h"
#include"GMenu.h"
#include"Resourses.h"
#include"saveConfig.h"
//#include"GameMenu.h"
//#include"game.h"



//const float FPS_MAX = 60.f;

void setDefaultConfig() {
	isSetConfig = false;
	buttonsConfig["ButtonRight"] = Keyboard::D;
	buttonsConfig["ButtonLeft"] = Keyboard::A;
	buttonsConfig["ButtonJump"] = Keyboard::Space;
	buttonsConfig["ButtonHeavy"] = Keyboard::Num1;
	buttonsConfig["ButtonPistol"] = Keyboard::Num2;
	buttonsConfig["ButtonKnife"] = Keyboard::Num3;
	buttonsConfig["ButtonRemaing"] = Keyboard::R;
	saveConfig();
}
void readConfig() {
	TiXmlDocument configFile(file.c_str());
	if (!configFile.LoadFile())return;
	TiXmlElement* config;
	config = configFile.FirstChildElement("Config");

	TiXmlElement* isSet;
	isSet = config->FirstChildElement("IsSet");
	
	isSetConfig = (atoi(isSet->Attribute("IsSet")) == 1) ? true : false;

	TiXmlElement* buttonRight;
	buttonRight = config->FirstChildElement("ButtonRight");
	buttonsConfig["ButtonRight"] = atoi(buttonRight->Attribute("ButtonRight"));

	TiXmlElement* buttonLeft;
	buttonLeft = config->FirstChildElement("ButtonLeft");
	buttonsConfig["ButtonLeft"] = atoi(buttonLeft->Attribute("ButtonLeft"));

	TiXmlElement* buttonJump;
	buttonJump = config->FirstChildElement("ButtonJump");
	buttonsConfig["ButtonJump"] = atoi(buttonJump->Attribute("ButtonJump"));

	TiXmlElement* buttonHeavy;
	buttonHeavy = config->FirstChildElement("ButtonHeavy");
	buttonsConfig["ButtonHeavy"] = atoi(buttonHeavy->Attribute("ButtonHeavy"));

	TiXmlElement* buttonPistol;
	buttonPistol = config->FirstChildElement("ButtonPistol");
	buttonsConfig["ButtonPistol"] = atoi(buttonPistol->Attribute("ButtonPistol"));

	TiXmlElement* buttonKnife;
	buttonKnife = config->FirstChildElement("ButtonKnife");
	buttonsConfig["ButtonKnife"] = atoi(buttonKnife->Attribute("ButtonKnife"));

	TiXmlElement* buttonRemaing;
	buttonRemaing = config->FirstChildElement("ButtonRemaing");
	buttonsConfig["ButtonRemaing"] = atoi(buttonRemaing->Attribute("ButtonRemaing"));

	TiXmlElement* buttonMusic;
	buttonMusic = config->FirstChildElement("MusicVolume");
	volamueMusic = atof(buttonMusic->Attribute("value"));
}
void makeAHit(Player* p,list<Bot*>* bots) {
	list<Bot*>::iterator iter;
	for (iter = bots->begin(); iter != bots->end(); iter++) {
		if ((*iter)->shootBox.getGlobalBounds().intersects(p->sprite->getGlobalBounds())) {
			(*iter)->isDamage = true;
			//(*iter)->dir = 0;
		}
		else {
			(*iter)->isDamage = false; //(*iter)->dir = -1;
		}
		if ((*iter)->isDamage) {
			(*iter)->timeD = (*iter)->cD.getElapsedTime().asSeconds();
			if ((*iter)->timeD >= 1.5) {
				p->health -= 10;
			//	cout << "Health" << p->health << endl;
				(*iter)->cD.restart();
			}
		}
		list<Weapon*>::iterator iterW = p->iterW;
		list<Bullet*>::iterator iterB;
		for (iterW = p->weapons.begin(); iterW != p->weapons.end();iterW++) {
			for (iterB = (*iterW)->bullets.begin(); iterB != (*iterW)->bullets.end(); iterB++) {
				if ((*iterB)->entity->getGlobalBounds().intersects((*iter)->sprite->getGlobalBounds())) {
					(*iterB)->isLive = false;  (*iter)->health -= (*iterW)->getDamage();// cout << "HealthZ: "<< (*iter)->health;
				}
			}
		}
	}
	
}

void intersectsWithShop(Player* p,Object* obj) {
	if (obj->rect.intersects(p->sprite->getGlobalBounds())) {
		list<Weapon*>::iterator iter = p->iterW;
		if (Keyboard::isKeyPressed(Keyboard::F1)) {//BUY AMMO FOR HEAVY
			
			for (iter = p->weapons.begin(); iter != p->weapons.end();iter++) {
				if ((*iter)->id == 0) {
					(*iter)->setCountOfAmmo();
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::F2)) {//BUY AMMO FOR PISTOL
			for (iter = p->weapons.begin(); iter != p->weapons.end(); iter++) {
				if ((*iter)->id == 1) {
					//(*iter)->countOfAmmo = (*iter)->countOfAmmoC;
					(*iter)->setCountOfAmmo();
				}
			}
		}
	}
}
void drawBots(RenderWindow* window, list<Bot*>* bots) {
	list<Bot*>::iterator iter;
	for (iter = bots->begin(); iter != bots->end(); iter++) {
		window->draw(*(*iter)->sprite);
	//	cout << "Draw";
	}
}

void deleteBots(list<Bot*>* bots) {
	list<Bot*>::iterator iter;
	for (iter = bots->begin(); iter != bots->end(); iter++) {
		Bot* b = *iter;
		iter = bots->erase(iter);
		delete b;
		//cout << "End bot\n";
		if (iter == bots->end()) break;
	}
}
void updateBots(list<Bot*>* bots, Time time, Player* p) {
	list<Bot*>::iterator iter;
//	cout << "Update";
	for (iter = bots->begin(); iter != bots->end(); iter++) {
		//cout << "\nBotUpdate\n";
		(*iter)->update(time);
		(*iter)->control(p->getX(), p->getY());
	//	(*iter)->shoot(p);
		if ((*iter)->health <= 0) {
			Bot* b = *iter;
			iter = bots->erase(iter);
			delete b;
		}
		if (iter == bots->end())break;
	}
}
void getButtonSet(list<Button*>* buttons,list<Button*>::iterator* iterB) {
	list<Button*>::iterator iter;
	for (iter = buttons->begin(); iter != buttons->end(); iter++) {
		if ((*iter)->tag == "setButtons") {
			*iterB = iter;
			break;
		}
	}
}
void setButtonsMenu(list<Menu*>* menu, list<Menu*>::iterator* iterMe, list<Button*>* Ñbuttons, list<Slider*>* Csliders, string* tag) {
	static string tempTag = "";
	if (tempTag == *tag)return;
	else {
		tempTag = *tag;
		list<Button*> buttons;
		list<Button*>::iterator iter;
		for (iter = Ñbuttons->begin(); iter != Ñbuttons->end(); iter++) {
			if ((*iter)->tag == *tag) {
				buttons.push_back(*iter);
			}
		}
		list<Slider*> sliders;
		list<Slider*>::iterator iterS;
		for (iterS = Csliders->begin(); iterS != Csliders->end(); iterS++) {
			if ((*iterS)->getTag() == *tag) {
				sliders.push_back(*iterS);
			}
		}
		menu->push_back(new Menu(&buttons, &sliders));
		list<Menu*>::iterator iterM;
		iterM = menu->begin();
		Menu* m = *iterM;
		iterM = menu->erase(iterM);
		delete m;

		*iterMe = menu->begin();
	}
}
