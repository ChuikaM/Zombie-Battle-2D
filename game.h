#pragma once
//#include<SFML/Graphics.hpp>
#include<algorithm>
//#include<list>
//#include"someClasses.h"
#include"Reshim.h"
//#include"GMenu.h"
//#include"GMenu.h"
using namespace sf;
float SCREEN_WIDTH = VideoMode::getDesktopMode().width; float SCREEN_HEIGHT = VideoMode::getDesktopMode().height;
string text = "menu";
string fileButton = "Images/icons/buttons2.png";
string pathFileButtons = "Images/icons/buttons/";
bool isPlayMusic = true;

class Game {
private:
	Reshim* r;
	Clock* c;
private:
	RenderWindow* _window;
	Event* _event;
private:
	void deleteButtons();
	//void setButtons2();
	//void setButtons();
	void setGameButtons();
private:
	void pollEvents();
	void update();
	void render();
private:
	Resourse* resourse;
private:
	//list<Button*> bPlay;
	//list<Button*> bReshims;
	//list<Button*> bShop;
	//list<Button*> bSettings;
	//list<Button*> bSetFPS;
	//list<Button*> bSetButtons;
	//list<Button*> bSetVolamue;
	list<Slider*> bSliders;
	list<Button*>::iterator iter;
	list<Slider*>::iterator iterS;

	list<Button*> buttons;

	list<Menu*> menues;
	list<Menu*>::iterator iterM;
public:
	Game();
	~Game();
	void play();
};
Game::Game() {
	readConfig();
	resourse = new Resourse();
	if (isSetConfig)
		setDefaultConfig();
	resourse->loadMusics({ "Music/menu.wav" }); resourse->returnMusic(0)->setLoop(true);
	resourse->loadFonts({ "Comfortaa.ttf" });
	resourse->loadText({"FPS"}, { 25 });
	c = new Clock(); 
	
	r = new Reshim("map.tmx", "zombie", *c,resourse);//RESHIM
	_window = new RenderWindow(VideoMode::getDesktopMode(), "Gurk game",Style::Default);

	_event = new Event();
	_window->setVerticalSyncEnabled(true);
	
	setGameButtons();
}
Game::~Game() {
	saveConfig();
	//_musicLobby->stop();
	//delete _musicLobby;
	
	//delete _f; delete _textFPS;
	delete c;
	//delete p;
	//delete map;
	 delete r;
	delete _window;
	delete _event;
	if(!menues.empty())
		deleteButtons();
	delete resourse;
}
void Game::deleteButtons() {
	static bool a = false;
	if (a) return;
	for (iterS = bSliders.begin(); iterS != bSliders.end();) {
		Slider* b = *iterS;
		iterS = bSliders.erase(iterS);
		delete b;
		if (iterS == bSliders.end()) {
			break;
		}
		++iterS;
	}
	/////
	for (iter = buttons.begin(); iter != buttons.end(); ) {
		Button* b = *iter;
		iter = buttons.erase(iter);
		delete b;
		if (iter == buttons.end()) {
			break;
		}
		++iter;
	}
	/////
	for (iterM = menues.begin(); iterM != menues.end(); ) {
		Menu* m = *iterM;
		iterM = menues.erase(iterM);
		delete m;
		if (iterM == menues.end()) {
			break;
		}
		++iterM;
	}
	a = true;
}

void Game::setGameButtons() {
	/*BEGIN Play menu*/

	buttons.push_back(new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, pathFileButtons + "button_play.png", "menu", "play"));
	buttons.push_back(new Button(0, 0, pathFileButtons + "button_profile.png", "menu", ""));
	buttons.push_back(new Button(0, SCREEN_HEIGHT / 3, pathFileButtons + "button_shop.png", "menu", "shop"));
	buttons.push_back(new Button(0, 2 * SCREEN_HEIGHT / 3, pathFileButtons + "button_settings.png", "menu", "settings"));
	buttons.push_back(new Button(SCREEN_WIDTH / 2, 0, pathFileButtons + "button_exit.png", "menu", "exit"));
	buttons.push_back(new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, pathFileButtons + "button_empty.png", "menu", "choiceReshim"));
	/*END Play menu*/
	/*BEGIN Choice Reshim*/
	buttons.push_back(new Button(0, 0, pathFileButtons+ "button_back.png", "choiceReshim", "menu"));
	buttons.push_back(new Button(SCREEN_WIDTH / 2, 80, pathFileButtons + "button_empty.png", "choiceReshim", "zombie"));
	buttons.push_back(new Button(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, pathFileButtons + "button_empty.png", "choiceReshim", "1vs1"));
	/*END Choice Reshim*/
	/*BEGIN Shop menu*/

	buttons.push_back(new Button(0, 0, pathFileButtons + "button_profile.png", "shop", "menu"));
	buttons.push_back(new Button(0, SCREEN_HEIGHT / 3, pathFileButtons + "button_shop.png", "shop", ""));
	buttons.push_back(new Button(0, 2 * SCREEN_HEIGHT / 3, pathFileButtons + "button_settings.png", "shop", "settings"));
	buttons.push_back(new Button(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, pathFileButtons + "button_empty.png", "shop", "buy the pack"));
	/*END Shop menu*/
	/*BEGIN Settings menu*/

	buttons.push_back(new Button(0, 0, pathFileButtons + "button_profile.png", "settings", "menu"));
	buttons.push_back(new Button(0, SCREEN_HEIGHT / 3, pathFileButtons + "button_shop.png", "settings", "shop"));
	buttons.push_back(new Button(0, 2 * SCREEN_HEIGHT / 3, pathFileButtons  + "button_settings.png", "settings", ""));
	buttons.push_back(new Button(SCREEN_WIDTH - SCREEN_HEIGHT / 3, 0, pathFileButtons + "button_empty.png", "settings", "setFPS"));
	buttons.push_back(new Button(SCREEN_WIDTH - SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, pathFileButtons + "button_empty.png", "settings", "setButtons"));
	buttons.push_back(new Button(SCREEN_WIDTH - SCREEN_HEIGHT / 3, 2 * SCREEN_HEIGHT / 3, pathFileButtons + "button_empty.png", "settings", "setVolamue"));
	/*END Settings menu*/
	/*BEGIN SetFPS menu*/
	buttons.push_back(new Button(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, pathFileButtons + "button_empty.png", "setFPS", "showFPS"));
	buttons.push_back(new Button(0, 0, pathFileButtons + "button_back.png", "setFPS", "settings"));
	/*END SetFPS menu*/
	/*BEGIN SetButtons menu*/


	buttons.push_back(new Button(0, 0, pathFileButtons + "button_back.png", "setButtons", "settings"));//Exit to settings menu
	buttons.push_back(new Button(SCREEN_WIDTH / 3, 0, pathFileButtons + "button_empty.png", "setButtons", ""));//ButtonRight
	buttons.push_back(new Button(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, pathFileButtons + "button_empty.png", "setButtons", ""));//ButtonLeft
	buttons.push_back(new Button(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, pathFileButtons + "button_empty.png", "setButtons", ""));//ButtonJump
	buttons.push_back(new Button(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, pathFileButtons + "button_empty.png", "setButtons", ""));//ButtonHeavy
	buttons.push_back(new Button(SCREEN_WIDTH / 3, 2 * SCREEN_HEIGHT / 3, pathFileButtons + "button_empty.png", "setButtons", ""));//ButtonPistol
	buttons.push_back(new Button(SCREEN_WIDTH / 3, 5 * SCREEN_HEIGHT / 6, pathFileButtons + "button_empty.png", "setButtons", ""));//ButtonKnife

	getButtonSet(&buttons, &iter);
	++iter; (*iter)->setState("ButtonRight");
	++iter; (*iter)->setState("ButtonLeft");
	++iter; (*iter)->setState("ButtonJump");
	++iter; (*iter)->setState("ButtonHeavy");
	++iter; (*iter)->setState("ButtonPistol");
	++iter; (*iter)->setState("ButtonKnife");

	/*END SetButtons menu*/
	/*BEGIN SetVolamue menu*/
	buttons.push_back(new Button(0, 0, pathFileButtons + "button_back.png", "setVolamue", "settings"));
	bSliders.push_back(new Slider(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, Color::Yellow, "setVolamue"));
	iterS = bSliders.begin();
	(*iterS)->setRange(volamueMusic);
	(*iterS)->setMaxRange(10.0f);
	(*iterS)->setPos(volamueMusic);
	/*End SetVolamue menu*/
	menues.push_back(new Menu(&buttons, &bSliders));
	iterM = menues.begin();
}
void Game::pollEvents() {
	setButtonsMenu(&menues,&iterM,&buttons,&bSliders,&text);
	srand(static_cast<unsigned int>(time(0)));
	Vector2i mousePoz = Mouse::getPosition(*_window);
	
	while (_window->pollEvent(*_event)){
		if (_event->type == Event::Closed || _event->key.code == Keyboard::Escape) {
			//deleteBots(&bots);
			_window->close();
		}
	}
	if (text != "play") {
		//_musicLobby->setVolume((*iterS)->getRange());
		if (*iterS != NULL) {
			resourse->returnMusic(0)->setVolume((*iterS)->getRange());
			volamueMusic = (*iterS)->getRange();
		}
	}
	//for (iterM = menues.begin(); iterM != menues.end(); iterM++) {
	if (iterM != menues.end()) {
		(*iterM)->pollButtons(&text, _event, &mousePoz);
		(*iterM)->pollSliders(&text, _event, &mousePoz);
		(*iterM)->pollButtonsKey(&text, _event, &mousePoz);
	}
	//}
	if (text == "play") {
		deleteButtons();
		
		resourse->returnMusic(0)->stop();
		//_musicLobby->stop();
		_window->setView(view);
		//file.write(reinterpret_cast<char*>(&silvers),sizeof(int)); file.write(reinterpret_cast<char*>(&gold), sizeof(int));
	}
	if (isPlayMusic) {// _musicLobby->play(); 
		resourse->returnMusic(0)->play();
	isPlayMusic = false; }
	if (isReset) { view.reset(FloatRect(0, 0, VideoMode::getDesktopMode().width / 3, VideoMode::getDesktopMode().height / 3)); isReset = false; }
	
	if (text == "exit")
		_window->close();
}
void Game::update() {
	
}
void Game::render() {
	
	//for (iterM = menues.begin(); iterM != menues.end(); iterM++) {
	if(iterM != menues.end())
		(*iterM)->draw(_window, &text);
	//}
	
	if (text == "play") {
		
		r->playZombie(_window, _event);
		//if (isShowFPS) {
		//	//->setPosition(p->getX() - 150, p->getY() - 90);
		//	resourse->getText(0)->setPosition(p->getX()-150,p->getY() - 90);
		//	Time t = r->getTimePerFrame();
		//	std::ostringstream tFps;
		//	tFps << floor(1.f/t.asSeconds());
		//	resourse->getText(0)->setString("FPS: " + tFps.str());
		//	_window->draw(*resourse->getText(0));
		//}
	}
	//sleep(milliseconds(50));
}
void Game::play() {
	while (_window->isOpen()) {
		pollEvents();
		_window->clear(Color::Blue);
		
		//update();
		render();
		_window->display();
	}
}