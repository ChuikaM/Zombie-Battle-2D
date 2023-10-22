#pragma once
#include"game.h"
#include"TinyXML/tinyxml2.h"
#include<string>
#include"configButtons.h"
using namespace std;
float volamueMusic = 10;
void saveConfig() {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
	doc.InsertFirstChild(decl);
	tinyxml2::XMLElement* config = doc.NewElement("Config");

	tinyxml2::XMLElement* isSet = doc.NewElement("IsSet");
	isSet->SetAttribute("IsSet", to_string(isSetConfig).c_str());
	config->InsertEndChild(isSet);

	tinyxml2::XMLElement* buttonRight = doc.NewElement("ButtonRight");
	//buttonRight->SetText("\n");
	buttonRight->SetAttribute("ButtonRight", to_string(buttonsConfig["ButtonRight"]).c_str());
	config->InsertEndChild(buttonRight);

	tinyxml2::XMLElement* buttonLeft = doc.NewElement("ButtonLeft");
	//buttonLeft->SetText("\n");
	buttonLeft->SetAttribute("ButtonLeft", to_string(buttonsConfig["ButtonLeft"]).c_str());
	config->InsertEndChild(buttonLeft);

	tinyxml2::XMLElement* buttonJump = doc.NewElement("ButtonJump");
	//buttonJump->SetText("\n");
	buttonJump->SetAttribute("ButtonJump", to_string(buttonsConfig["ButtonJump"]).c_str());
	config->InsertEndChild(buttonJump);

	tinyxml2::XMLElement* buttonHeavy = doc.NewElement("ButtonHeavy");
	//buttonHeavy->SetText("\n");
	buttonHeavy->SetAttribute("ButtonHeavy", to_string(buttonsConfig["ButtonHeavy"]).c_str());
	config->InsertEndChild(buttonHeavy);

	tinyxml2::XMLElement* buttonPistol = doc.NewElement("ButtonPistol");
	//	buttonPistol->SetText("\n");
	buttonPistol->SetAttribute("ButtonPistol", to_string(buttonsConfig["ButtonPistol"]).c_str());
	config->InsertEndChild(buttonPistol);

	tinyxml2::XMLElement* buttonKnife = doc.NewElement("ButtonKnife");
	//buttonKnife->SetText("\n");
	buttonKnife->SetAttribute("ButtonKnife", to_string(buttonsConfig["ButtonKnife"]).c_str());
	config->InsertEndChild(buttonKnife);

	tinyxml2::XMLElement* buttonRemaing = doc.NewElement("ButtonRemaing");
	buttonRemaing->SetAttribute("ButtonRemaing", to_string(buttonsConfig["ButtonRemaing"]).c_str());
	config->InsertEndChild(buttonRemaing);

	tinyxml2::XMLElement* buttonMusic = doc.NewElement("MusicVolume");
	buttonMusic->SetAttribute("value", to_string(volamueMusic).c_str());
	config->InsertEndChild(buttonMusic);

	doc.InsertEndChild(config);
	doc.SaveFile(file.c_str());
}