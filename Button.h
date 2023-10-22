//#pragma once
//#include"Entity.h"
//#include"saveConfig.h"
//bool isReset = false;
//bool isShowFPS = false;
//class Button : public Entity {
//private:
//	Event ev;
//	bool isChoice;
//	Font* _font;
//	Text* _text;
//public:
//	string tag, text,state;
//	Button(float X, float Y, float W, float H, Color c, string tag, string text);
//	Button(float X, float Y, float W, float H, String F, string tag, string text);
//	Button(float X, float Y, float xT, float yT, float wT, float hT, float scaleX, float scaleY, String F, string tag, string text);
//	~Button();
//	Text* getText();
//	void setTextureButton(float x, float y);
//	void setScaleButton(float sX,float sY);
//	void setState(string state);
//	void isPressedButton(Event& event, Vector2i mousePoz, string* txt);
//	void isPressedButtonKey(Event event, Vector2i mousePoz);
//};
//
//Button::~Button() {
//	delete _text; delete _font;
//}
//Button::Button(float X, float Y, float W, float H, Color c, string tag, string text) :Entity(X, Y, W, H, c) {
//	state = "";
//	_font = new Font(); _font->loadFromFile("Comfortaa.ttf"); _text = new Text("", *_font, 60); _text->setFillColor(Color::Black); _text->setPosition(getX(), getY());
//	this->tag = tag; this->text = text; isChoice = false;
//}
//Button::Button(float X, float Y, float W, float H, String F, string tag, string text):Entity(X,Y,W,H,F) {
//	ev.type = Event::MouseMoved;
//	sprite.setScale(getW()/20, getH()/20);
//	state = "";
//	_font = new Font(); _font->loadFromFile("Comfortaa.ttf"); _text = new Text("", *_font, 60); _text->setFillColor(Color::Black); _text->setPosition(getX(), getY());
//	this->tag = tag; this->text = text; isChoice = false;
//}
//Button::Button(float X, float Y, float xT, float yT, float wT, float hT,float scaleX,float scaleY, String F, string tag, string text) :Entity(X, Y,xT,yT, wT, hT, F) {
//	ev.type = Event::MouseMoved;
//	//sprite.setScale(getW() / 20, getH() / 20);
//	state = "";
//	_font = new Font(); _font->loadFromFile("Comfortaa.ttf"); _text = new Text("", *_font, 60); _text->setFillColor(Color::Black); _text->setPosition(getX(), getY());
//	sprite.setScale(scaleX,scaleY);
//	this->tag = tag; this->text = text; isChoice = false;
//}
//Text* Button::getText() {
//	return _text;
//}
//void Button::setTextureButton(float x,float y) {
//	sprite.setTextureRect(IntRect(x,y,20,20));
//}
//void Button::setScaleButton(float sX,float sY) {
//	sprite.setScale(sX,sY);
//}
//void Button::setState(string state) {
//	this->state = state;
//}
//void Button::isPressedButton(Event& event, Vector2i mousePoz, string* txt) {
//	
//	if (sprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
//		if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
//			//if (event.type == Event::MouseButtonReleased) {
//			event.type = Event::MouseMoved;
//			//*txt = (text != "") ? text : *txt;
//				if (text == "play") {
//					isReset = true;
//					*txt = "play";
//				}
//				else if (text == "menu") {
//					cout << "\Menu\n";
//					*txt = "menu";
//				}
//				else if (text == "choiceReshim") {
//					*txt = "choiceReshim";
//				}
//				else if (text == "shop") {
//					*txt = "shop";
//				}
//				else if (text == "settings") {
//					cout << "\nSettings\n";
//					*txt = "settings";
//				}
//				else if (text == "showFPS") {//FPS
//					std::cout << "isShowFPS";
//					isShowFPS = true;
//				}
//				else if (text == "setFPS") {
//					cout << "\SetFPS\n";
//					*txt = "setFPS";
//				}
//				else if (text == "setButtons") {
//					*txt = "setButtons";
//				}
//				else if (text == "setVolamue") {
//					*txt = "setVolamue";
//				}
//				else if (text == "exit") {
//					*txt = "exit";
//				}
//			//}
//		}
//	}
//}
//void Button::isPressedButtonKey(Event event, Vector2i mousePoz) {
//	//_text->setString(to_string(buttonsConfig[state]));
//	if (sprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y)) {
//		if (event.type == Event::MouseButtonReleased) {
//			isChoice = true;
//		}	
//	}
//	if((!sprite.getGlobalBounds().contains(mousePoz.x, mousePoz.y) && event.type == Event::MouseButtonReleased))
//		isChoice = false;
//	if (isChoice && state !="") {
//		//cout << "\nChoice\n";
//		
//		for (size_t i = Keyboard::A; i < Keyboard::Pause;i++) {
//			if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(i))) {
//				_text->setString(event.text.unicode);
//				cout << "\nPressed\n";
//			//	isChoice = false;
//				buttonsConfig[state] = i;		
//				saveConfig();
//			}
//		}
//	}
//}