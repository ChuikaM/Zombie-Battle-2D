#pragma once
#include"Entity.h"
class TextInput : public Entity,public sf::Drawable{
private:
	bool m_isEnter;
	Font* _font;
	Text* _text;
	string txt;
	float _size;
public:
	TextInput(float x, float y, float w, float h, Color c, float size);
	~TextInput();
	bool isEnter(Vector2i& v);
	bool isEnterCommand();
	void setEnterCommand(bool isE);//WE SET 'm_isEnter'
	void setFocus(bool isF);
	void inputText(Vector2i& v,Event* e,string* command);
	virtual void draw(RenderTarget& target,RenderStates states) const;
	string getText();
};

TextInput::TextInput(float x, float y, float w, float h, Color c, float size):Entity(x,y,w,h,c),_size(size)
{
	m_isEnter = false;
	entity->setOutlineThickness(5);
	_font = new Font();
	_font->loadFromFile("Comfortaa.ttf");
	_text = new Text("",*_font,h-1);
	_text->setPosition(x,y);
	_text->setFillColor(Color::Black);
}
TextInput::~TextInput() {
	delete _text;
	delete _font;
}
bool TextInput::isEnter(Vector2i& v) {
	if (entity->getGlobalBounds().contains(v.x, v.y)) 
		return true;
	return false;
}
bool TextInput::isEnterCommand() {
	return m_isEnter;
}
void TextInput::setEnterCommand(bool isE) {
	m_isEnter = isE;
}
void TextInput::setFocus(bool isF) {
	if (isF)
		entity->setOutlineColor(Color::Blue);
	else
		entity->setOutlineColor(Color::Blue);
}

void TextInput::inputText(Vector2i& v, Event* e, string* command) {
	if (isEnter(v)) {
		setFocus(true);
		Cursor::Text;
	}
	else {
		Cursor::Arrow;
	}
	if (e->type == Event::TextEntered) {
		if (e->text.unicode < 128 && txt.size() < _size) {
			txt += e->text.unicode;
			_text->setString(txt);
		}
	}
	if (e->type == Event::KeyReleased) {
		if (e->key.code == Keyboard::BackSpace) {
			txt = txt.substr(0,txt.size() - 1);
			_text->setString(txt);
		}
	}
	if (e->type == Event::KeyReleased && e->key.code == Keyboard::Enter) {
		*command = getText(); m_isEnter = true;
	}
}
void TextInput::draw(RenderTarget& target, RenderStates states) const {
	target.draw(*entity);
	target.draw(*_text);
}
string TextInput::getText() {
	return txt;
}
