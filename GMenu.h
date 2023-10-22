#pragma once
#include"GButton.h"
#include"Slider.h"
class Menu {
private:
	string tag, tagView;
	list<Button> buttons;
	list<Button*> _buttons;
	list<Button*>::iterator iterB;
	list<Slider*>::iterator iterS;
	list<Slider*> _sliders;
	map<bool, View*, less<bool>> _views;
public:
	Menu(list<Button*>* Buttons);
	Menu(list<Button*>* Buttons, list<Slider*>* Sliders);
	Menu(string tag, list<Button>* Buttons);
	Menu(string tag, list<Button*>* Buttons);
	Menu(string tag, list<Slider*>* Sliders);
	~Menu();
	void _setView(View* view, bool isStay);
	void draw(RenderWindow* window, string* tag);
	void pollButtonsKey(string* tag, Event* event, Vector2i* mousePoz);
	void pollButtons(string* tag, Event* event, Vector2i* mousePoz);
	void pollSliders(string* tag, Event* event, Vector2i* mousePoz);
	void pollViews(string* tag, Event* event, Vector2i* mousePoz);
	void deleteMenu();
};
Menu::Menu(list<Button*>* Buttons) {
	list<Button*>::iterator iter;
	for (iter = Buttons->begin(); iter != Buttons->end(); iter++) {
		_buttons.push_back((*iter));
	}
}
Menu::Menu(list<Button*>* Buttons, list<Slider*>* Sliders) {
	list<Button*>::iterator iter;
	for (iter = Buttons->begin(); iter != Buttons->end(); iter++) {
		_buttons.push_back((*iter));
	}
	list<Slider*>::iterator iterS;
	for (iterS = Sliders->begin(); iterS != Sliders->end(); iterS++) {
		_sliders.push_back((*iterS));
	}
}
Menu::Menu(string tag, list<Button>* Buttons) {
	this->tag = tag;
	list<Button>::iterator iter;
	for (iter = Buttons->begin(); iter != Buttons->end(); iter++) {
		buttons.push_back((*iter));
	}
}
Menu::Menu(string tag, list<Button*>* Buttons) {
	this->tag = tag;
	list<Button*>::iterator iter;
	for (iter = Buttons->begin(); iter != Buttons->end(); iter++) {
		_buttons.push_back((*iter));
	}
}
Menu::Menu(string tag, list<Slider*>* Sliders) {
	this->tag = tag;
	list<Slider*>::iterator iter;
	for (iter = Sliders->begin(); iter != Sliders->end(); iter++) {
		_sliders.push_back((*iter));
	}
}
Menu::~Menu() {
	for (iterB = _buttons.begin(); iterB != _buttons.end();) {
		Button* b = *iterB;
		iterB = _buttons.erase(iterB);
		delete b;
		if (iterB == _buttons.end()) {
			break;
		}
		++iterB;
	}
	for (iterS = _sliders.begin(); iterS != _sliders.end();) {
		Slider* b = *iterS;
		iterS = _sliders.erase(iterS);
		delete b;
		if (iterS == _sliders.end()) {
			break;
		}
		++iterS;
	}
}
void Menu::_setView(View* view, bool isStay) {
	_views[isStay] = view;
}
void Menu::draw(RenderWindow* window, string* tag) {

	list<Button*>::iterator iter;
	list<Slider*>::iterator iterS;
	for (iter = _buttons.begin(); iter != _buttons.end(); iter++) {
		if ((*iter)->tag == *tag) {
			window->draw(*((*iter)->sprite));
			window->draw(*((*iter)->getText()));
		}
	}
	for (iterS = _sliders.begin(); iterS != _sliders.end(); iterS++) {
		if ((*iterS)->getTag() == *tag)
			window->draw(**iterS);
	}

}
void Menu::pollButtons(string* tag, Event* event, Vector2i* mousePoz) {

	list<Button*>::iterator  iter;
	for (iter = _buttons.begin(); iter != _buttons.end(); iter++) {
		if ((*iter)->tag == *tag) {
			(*iter)->isPressedButton(*event, *mousePoz, tag);
		}
	}
}
void Menu::pollButtonsKey(string* tag, Event* event, Vector2i* mousePoz) {

	list<Button*>::iterator  iter;
	for (iter = _buttons.begin(); iter != _buttons.end(); iter++) {
		if (*tag == "setButtons" && (*iter)->text == "") {
			(*iter)->isPressedButtonKey(*event, *mousePoz);
		}
	}
}
void Menu::pollSliders(string* tag, Event* event, Vector2i* mousePoz) {
	list<Slider*>::iterator  iter;
	for (iter = _sliders.begin(); iter != _sliders.end(); iter++) {
		if ((*iter)->getTag() == *tag) {
			(*iter)->move(*mousePoz, *event);
		}
	}

}
void Menu::pollViews(string* tag, Event* event, Vector2i* mousePoz) {
	if (this->tag == *tag) {
		map<bool, View*, less<bool>>::iterator iter;
		for (iter = _views.begin(); iter != _views.end(); iter++) {

		}
	}
}
void Menu::deleteMenu() {
	for (iterB = _buttons.begin(); iterB != _buttons.end(); iterB++) {
		Button* b = *iterB;
		iterB = _buttons.erase(iterB);
		delete b;
		if (iterB == _buttons.end())break;
	}
	for (iterS = _sliders.begin(); iterS != _sliders.end(); iterB++) {
		Slider *s = *iterS;
		iterS = _sliders.erase(iterS);
		delete s;
		if (iterS == _sliders.end())break;
	}
}

