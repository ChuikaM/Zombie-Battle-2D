#pragma once
#include"TextInput.h"
#include"GButton.h"
#include<functional>
class ConsoleDebug : public Entity {
private:
	string command;
	string usegeCommand;
	float value;
	map < string, function<void()>, less<string>> commands_functions;
	map < string, function<void()>, less<string>>::iterator iter;
private:
	TextInput* m_TextInput;
	Button* m_ButtonSend;
	Button* m_ButtonExit;
	bool m_isDebug;
public:
	ConsoleDebug(float xC, float yC, float wC, float hC, Color cC, float h, Color c);
	~ConsoleDebug();
	void isDebug(Event* event);
	void Debug(Vector2i& v,Event* event);
	void checkCommand();
	virtual void draw(RenderTarget& target, RenderStates states) const;
};
ConsoleDebug::ConsoleDebug(float xC, float yC, float wC, float hC, Color cC, float h, Color c):Entity(xC,yC,wC,hC,cC) {
	m_isDebug = false;
	m_ButtonExit = new Button(xC, yC, "Images/icons/buttons/button_empty.png", "", "");
	m_ButtonSend = new Button(xC + wC-100,yC + hC - h, "Images/icons/buttons/button_empty.png","","");
	m_TextInput = new TextInput(xC,yC + hC - h,wC,h,c,120);
}
ConsoleDebug::~ConsoleDebug() {
	delete m_ButtonExit;
	delete m_ButtonSend;
	delete m_TextInput;
}
void ConsoleDebug::isDebug(Event* event) {
	if (event->type == Event::KeyReleased && event->key.code == Keyboard::F10)
		m_isDebug = !m_isDebug;
}
void ConsoleDebug::Debug(Vector2i& v,Event* event) {
	if (m_isDebug) {

		m_TextInput->inputText(v, event,&command);
		if (m_TextInput->isEnterCommand() || m_ButtonSend->isPressed(*event,v)) {
			m_TextInput->setEnterCommand(false);
			checkCommand();
		}
	}
	
}
void ConsoleDebug::draw(RenderTarget& target, RenderStates states) const {
	target.draw(*entity);
	target.draw(*m_TextInput);
	target.draw(*m_ButtonSend);
	target.draw(*m_ButtonExit);
}

//KEEP AT MIND
void ConsoleDebug::checkCommand() {
	usegeCommand = command.substr(0,command.find(" "));
	value = strtof(command.substr(0,1).c_str(),NULL);
	for (iter = commands_functions.begin(); iter != commands_functions.end(); iter++) {
		if ((*iter).first == usegeCommand) {
			commands_functions[usegeCommand];
			break;
		}
	}
}