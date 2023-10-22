#pragma once
#include<SFML/Graphics.hpp>
#include"someClasses.h"
//#include"Player.h"
using namespace sf;
class Reshim {
private:
	Level _map;
	std::vector<Object> _objects; //std::list<Bot*> _bots;
	std::string _type;
	sf::Clock _clock;
	Clock clock;
	Font* _f;
	Text _info;
	bool isPush;
	Time TimePerFrame;
	Time timeSinceLastUpdate = Time::Zero;
private:
	Player* p;
	list<Bot*> bots;
	list<Bot*>::iterator iterBot;
	Object _shop;
	int size;
public:
	Reshim(String mapLevel, String type, sf::Clock clock,Resourse* res) :_type(type), _clock(clock)
	{
		p = new Player("map.tmx", 26, 38, "Images/tP1Anim.png");//PLAYER
		//_f = Resourse::getFont(0);
		_f = new Font();
		_f->loadFromFile("Comfortaa.ttf");
		_info.setFont(*_f); _info.setCharacterSize(30); _info.setFillColor(Color::Black);
		isPush = true;
		_map.LoadFromFile(mapLevel);
		TimePerFrame = sf::seconds(1.f / FPS_MAX);
		//_clock.restart().Zero;
	}
	~Reshim() {
		delete p; delete _f; deleteBots(&bots);
	}
	Time getTimePerFrame() {
		return timeSinceLastUpdate;
	}
	void playZombie(RenderWindow* window, Event* event) {


		timeSinceLastUpdate += clock.restart();
		/*clock.restart();*/
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			if (isPush) {
				_clock.restart();
				isPush = false;
				size = 1;

				_objects = _map.GetObjects(_type);

				_shop = _map.GetObject("shop");

			}

			p->update(*event, TimePerFrame);
			intersectsWithShop(p, &_shop);
			updateBots(&bots, TimePerFrame, p);
			makeAHit(p, &bots);

			if (bots.empty()) {
				float time = _clock.getElapsedTime().asSeconds();
				ostringstream infoOfLevel; infoOfLevel << size;
				_info.setString("Level " + infoOfLevel.str()); _info.setPosition(p->getX() - 50, p->getY() - 90);

				if (time >= 5) {
					int num; int pos; float speed, health;
					for (int i = 0; i < size; i++) {
						num = rand() % 5;
						pos = rand() % 2;
						switch (num)
						{
						case 0:speed = 0.15; health = 60; break;
						case 1:speed = 0.1; health = 80; break;
						case 2:speed = 0.05; health = 105; break;
						case 3:speed = 0.02; health = 120; break;
						case 4:speed = 0.01; health = 160; break;
						}
						bots.push_back(new Bot(_map, _objects[pos].rect.left, _objects[pos].rect.top, 19, 28, speed, health, "Images/zombieAnim.png")); time = 0;

					}
					++size;
					//cout << size;
				}
			}
			else {
				_clock.restart();
			}
		}

		_map.Draw(*window);
		if (bots.empty())
			window->draw(_info);

		//window->draw(p->sprite);
		p->draw(window);
		//window->draw(*p);
		drawBots(window, &bots);

	}
	/*void playCommand(RenderWindow* window, Event* event, Player* p, list<Bot*>* bots, float& time) {
		for (int i = 0; i < 5; i++) {
			int pos = rand() % 2; bots->push_back(new Bot(_map, _objects[pos].rect.left, _objects[pos].rect.top, 19, 28, 0.2, 100, "Images/zombieAnim.png"));
		}
		window->draw(_map);
		p->update(*event, time);
		intersectsWithShop(p, &_shop);
		updateBots(bots, time, p);
		makeAHit(p, bots);

		window->draw(p->sprite);
		p->drawWeapon(window);
		drawBots(window, bots);

	}*/
	void playBomb() {

	}
};