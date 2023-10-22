//#include<SFML/Graphics.hpp>

#include"Game.h"
//float SCREEN_WIDTH = VideoMode::getDesktopMode().width; float SCREEN_HEIGHT = VideoMode::getDesktopMode().height;

int silvers, gold = 0;
bool isWrite = false;
//using namespace sf;

//int main() {
//	//ofstream file("date.dat", ios::binary | ios::app); 
//	//ifstream isfile;
//	string text = "menu";
//	TileMap lvl;
//	lvl.load("map.tmx");
//	list<Button> bPlay,bShop,bSettings;
//	//MENU
//	Button buttonPlay(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 200, 200, Color::Red, "menu", "play");
//	Button buttonMenu(0,0,SCREEN_HEIGHT/3,SCREEN_HEIGHT/3,Color::Blue,"menu","");
//	Button buttonShop(0,SCREEN_HEIGHT/3,SCREEN_HEIGHT/3,SCREEN_HEIGHT/3,Color::Cyan,"menu","shop");
//	Button buttonSettings(0, 2*SCREEN_HEIGHT / 3,SCREEN_HEIGHT/3,SCREEN_HEIGHT/3,Color::Magenta,"menu","settings");
//	Button buttonExit(SCREEN_WIDTH / 2, 0, 200, 200, Color::Yellow, "menu", "exit");
//
//	//SHOP
//	Button buttonMenuS(0, 0, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, Color::Blue, "shop", "menu");
//	Button buttonShopS(0, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, Color::Cyan, "shop", "");
//	Button buttonSettingsS(0, 2*SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, Color::Magenta, "shop", "settings");
//	Button buttonBuyPack(SCREEN_WIDTH/3,SCREEN_HEIGHT/3,200,100,Color::Magenta,"shop","buy the pack");
//	//SETTINGS
//	Button buttonMenuSet(0, 0, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, Color::Blue, "settings", "menu");
//	Button buttonShopSet(0, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, Color::Cyan, "settings", "shop");
//	Button buttonSettingsSet(0, 2*SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 3, Color::Magenta, "settings", "");
//
//	bPlay.push_back(buttonPlay); bPlay.push_back(buttonMenu); bPlay.push_back(buttonShop); bPlay.push_back(buttonSettings); bPlay.push_back(buttonExit);
//	bShop.push_back(buttonMenuS); bShop.push_back(buttonShopS); bShop.push_back(buttonSettingsS);
//	bSettings.push_back(buttonMenuSet); bSettings.push_back(buttonShopSet); bSettings.push_back(buttonSettingsSet);
//	//MENUES
//	Menu playMenu("menu",&bPlay);
//	Menu shopMenu("shop",&bShop);
//	Menu settingsMenu("settings",&bSettings);
//
//	//Font f; f.loadFromFile("Comfortaa.ttf"); Text info("", f, 30); info.setFillColor(Color::Black);
//	RenderWindow window(VideoMode::getDesktopMode(), "Gurk game", Style::None);
////	window.setFramerateLimit(60);
//	window.setVerticalSyncEnabled(true);
//	//window.
//	Object player = lvl.getObject("player"); Object zombie = lvl.getObject("zombie"); Object shop = lvl.getObject("shop");
//	vector<Object> zombies = lvl.getObjectsByName("zombie");
//	
//	RectangleShape wall; wall.setSize(Vector2f(32, 32)); wall.setFillColor(Color::Red);
//	
//	Player p(lvl, player.rect.left, player.rect.top, 19, 28, "Images/ctPlayerAnim.png");
//	
//	list<Bot*> bots;list<Bot*>::iterator iterBot;
//	
//	Clock c,clock;
//	Reshim r("map.tmx","zombie",clock);
//	while (window.isOpen()) {
//		Vector2i mousePoz = Mouse::getPosition(window);
//		srand(static_cast<unsigned int>(time(0)));
//		Event event;
//		
//		float time = c.getElapsedTime().asMicroseconds();
//		time /= 800;c.restart();
//		while (window.pollEvent(event)) {
//			if (event.type ==  Event::Closed || event.key.code == Keyboard::Escape) {
//				deleteBots(&bots);
//			
//				window.close();
//			}
//		}
//		//if (text == "menu")
//		//	isWrite = true;
//		//if (isWrite) {
//		//	//isfile.read(reinterpret_cast<char*>(&silvers),sizeof(int));	isfile.read(reinterpret_cast<char*>(&gold), sizeof(int));
//		//	isWrite = false;
//		//}
//		if (text == "play") {
//			window.setView(view);
//			//file.write(reinterpret_cast<char*>(&silvers),sizeof(int)); file.write(reinterpret_cast<char*>(&gold), sizeof(int));
//		}
//		
//		window.clear(Color::Yellow);
//		playMenu.pollButtons(&text, &event, &mousePoz);
//		shopMenu.pollButtons(&text,&event,&mousePoz);
//		settingsMenu.pollButtons(&text, &event, &mousePoz);
//		playMenu.draw(&window, &text); shopMenu.draw(&window,&text); settingsMenu.draw(&window, &text);
//		
//		if (text == "play")
//			r.playZombie(&window, &event, &p, &bots);
//		if (text == "exit") 
//			window.close();
//		
//		window.display();
//	}
//}
int main() {
	
	Game g;
	g.play();
}