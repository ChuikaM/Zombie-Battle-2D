#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<list>
#include<vector>
#include<map>
using namespace std;
using namespace sf;
const float FPS_MAX = 60.f;

class Resourse {
private:
	bool isLoad;
private:
	Texture* tex;
	Music* m;
	Font* f;
	Text* t;
private:
	map<string,Texture*,less<string>> texturesM;
	map<string, Texture*, less<string>>::iterator iterTM;
	map<string, Music*, less<string>> musicsM;
	map<string, Music*, less<string>>::iterator iterMM;
	map<string, Font*, less<string>> fontsM;
	map<string, Font*, less<string>>::iterator iterFM;
	map<string, Text*, less<string>> textsM;
	map<string, Text*, less<string>>::iterator iterTxtM;
private:
	vector<Texture*> textures;
	vector<Texture*>::iterator iterT;
	vector<Music*> musics;
	vector<Music*>::iterator iterM;
	vector<Font*> fonts;
	vector<Font*>::iterator iterF;
	vector<Text*> texts;
	vector<Text*>::iterator iterTxt;
private:
	Clock clock;
	Time TimePerFrame;
	Time timeSinceLastUpdate = Time::Zero;
public:
	Resourse();
	~Resourse();
	void loadTextures(vector<String> files);
	void loadFonts(vector<String> files);
	void loadMusics(vector<String>files);
	void loadText(vector<string>names,vector<int>size);


	void loadTextures(vector<String>names, vector<String>files);
	void loadFonts(vector<String>names, vector<String>files);
	void loadMusics(vector<String>names, vector<String>files);
	//void loadText(vector<string>names, vector<int>size);

	Texture* getTexture(int i);
	Music* returnMusic(int i);
	Font* getFont(int i);
	Text* getText(int i);

	Texture* getTexture(string name);
	Music* returnMusic(string name);
	Font* getFont(string name);
	
};
Resourse::Resourse() {
	TimePerFrame = sf::seconds(1.f / FPS_MAX);
	isLoad = true;
}
Resourse::~Resourse() {
	cout << "ReS";
	for (iterT = textures.begin(); iterT != textures.end();iterT++) {
		Texture* te = *iterT;
		iterT = textures.erase(iterT);
		delete te;
		if (iterT == textures.end()) break;
	}
	for (iterM = musics.begin(); iterM != musics.end(); iterM++) {
		Music* mu = *iterM;
		(*iterM)->stop();
		//delete mu;
		iterM = musics.erase(iterM);
		if (iterM == musics.end()) break;
		
	}
	for (iterF = fonts.begin(); iterF != fonts.end(); iterM++) {
		Font* mu = *iterF;
		//delete mu;
		iterF = fonts.erase(iterF);
		if (iterF == fonts.end()) break;
		delete mu;
	}
	for (iterTxt = texts.begin(); iterTxt != texts.end(); iterTxt++) {
		Text* mu = *iterTxt;
		//delete mu;
		iterTxt = texts.erase(iterTxt);
		if (iterTxt == texts.end()) break;
		delete mu;
	}

	for (iterTM = texturesM.begin(); iterTM != texturesM.end(); iterTM++) {
		Texture* tex = (*iterTM).second;
		iterTM = texturesM.erase(iterTM);
		delete tex;
		if (iterTM == texturesM.end()) break;
	}
	for (iterMM = musicsM.begin(); iterMM != musicsM.end(); iterMM++) {
		Music* mu = (*iterMM).second;
		(*iterMM).second->stop();
		//delete mu;
		iterMM = musicsM.erase(iterMM);
		if (iterMM == musicsM.end()) break;

	}
	for (iterFM = fontsM.begin(); iterFM != fontsM.end(); iterFM++) {
		Font* mu = (*iterFM).second;
		//delete mu;
		iterFM = fontsM.erase(iterFM);
		if (iterFM == fontsM.end()) break;
		delete mu;
	}
	for (iterTxtM = textsM.begin(); iterTxtM != textsM.end(); iterTxtM++) {
		Text* mu = (*iterTxtM).second;
		//delete mu;
		iterTxtM = textsM.erase(iterTxtM);
		if (iterTxtM == textsM.end()) break;
		delete mu;
	}
	
	if (m)delete m;
	if (f)delete f;
	if (t)delete t;
	cout << "\nReS";
	if (tex)delete tex;
	cout << "\nReS";
}
void Resourse::loadTextures(vector<String>files) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < files.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				tex = new Texture;
				tex->loadFromFile(files[i]);
				//cout << "Load";
				textures.push_back(tex);
			}
			if (textures.size() == files.size()) { isLoad = false; break; }
			//if (i == files.size()-1)isLoad = false;
		}
	}
	//cout << textures.size();
	isLoad = true;
}
void Resourse::loadFonts(vector<String>files) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < files.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				f = new Font();
				f->loadFromFile(files[i]);
				fonts.push_back(f);
				if (fonts.size() == files.size()) { isLoad = false; break; }
			}

		}
	}
	isLoad = true;
}
void Resourse::loadMusics(vector<String>files) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < files.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				m = new Music;
				m->openFromFile(files[i]);
				musics.push_back(m);
				//delete m;
				if (musics.size() == files.size()) { isLoad = false; break; }
			}
		
		}
	}
	isLoad = true;
}
void Resourse::loadText(vector<string>names,vector<int>size) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < fonts.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				t = new Text(names[i],*fonts[i],size[i]);
				texts.push_back(t);
				if (texts.size() == fonts.size()) { isLoad = false; break; }
			}

		}
	}
	isLoad = true;
}
void Resourse::loadTextures(vector<String>names,vector<String>files) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < files.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				tex = new Texture;
				tex->loadFromFile(files[i]);
				//textures.push_back(tex);
				texturesM[names[i]] = tex;
			}
			if (i == files.size() - 1)isLoad = false;
		}
	}
	isLoad = true;
}
void Resourse::loadFonts(vector<String>names, vector<String>files) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < files.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				f = new Font();
				f->loadFromFile(files[i]);
				fontsM[names[i]] = f;
				//fonts.push_back(f);
				if (i == files.size() - 1)isLoad = false;
			}

		}
	}
	isLoad = true;
}
void Resourse::loadMusics(vector<String>names, vector<String>files) {
	while (isLoad) {
		timeSinceLastUpdate += clock.restart();
		for (int i = 0; i < files.size(); i++) {
			if (timeSinceLastUpdate > TimePerFrame) {
				timeSinceLastUpdate -= TimePerFrame;
				m = new Music;
				m->openFromFile(files[i]);
				musicsM[names[i]] = m;
				//musics.push_back(m);
				//delete m;
				if (i == files.size() - 1)isLoad = false;
			}

		}
	}
	isLoad = true;
}
Texture* Resourse::getTexture(int i) {
	return textures[i];
}
Music* Resourse::returnMusic(int i) {
	return musics[i];
}
Font* Resourse::getFont(int i) {
	return fonts[i];
}
Text* Resourse::getText(int i) {
	return texts[i];
}

Texture* Resourse::getTexture(string name) {
	return texturesM[name];
}
Music* Resourse::returnMusic(string name) {
	return musicsM[name];
}
Font* Resourse::getFont(string name) {
	return fontsM[name];
}