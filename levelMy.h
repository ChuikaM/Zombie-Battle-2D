﻿#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include<list>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TinyXML/tinyxml.h"
struct Vertexes {
	int x, x2;
	int y, y2;
	Vertexes() : x(0), y(0), x2(0), y2(0)
	{}
};
struct Object
{
	int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
	std::string name;//объявили переменную name типа string
	std::string type;//а здесь переменную type типа string
	sf::Rect<float> rect;//тип Rect с нецелыми значениями
	std::map<std::string, std::string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый
	sf::Sprite sprite;//объявили спрайт
};
struct Layer//слои
{
	int opacity;//непрозрачность слоя
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};
class Level//главный класс - уровень
{
public:
	Level();
	~Level();
	bool LoadFromFile(std::string filename);//возвращает false если не получилось загрузить
	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
	void Draw(sf::RenderWindow &window);//рисуем в окно
	sf::Vector2i GetTileSize();//получаем размер тайла
private:
	float w, h, w2, h2;
	float X, Y;
	int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
	int firstTileID;//получаем айди первого тайла
	sf::Rect<float> drawingBounds;//размер части карты которую рисуем
	sf::Texture tilesetImage;//текстура карты
	std::list<Vertexes> vertecies; std::list<Vertexes>::iterator iter;
	std::vector<Object> objects;//массив типа Объекты, который мы создали
	std::vector<Layer> layers;
	void copyTileSetImage(const sf::Image* im, sf::Image* imCopy);
	void clearImage(sf::Image* im);
};
Level::Level():w(0),h(0),w2(0),h2(0)
{}
Level::~Level() {
	/*if (tilesetImage)
		delete tilesetImage;*/
}
///////////////////////////////////////
int Object::GetPropertyInt(std::string name)//возвращаем номер свойства в нашем списке
{
	return atoi(properties[name].c_str());
}
float Object::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}
std::string Object::GetPropertyString(std::string name)//получить имя в виде строки.вроде понятно
{
	return properties[name];
}
bool Level::LoadFromFile(std::string filename)//двоеточия-обращение к методам класса вне класса 
{
	
	//tilesetImage = new sf::Texture();
	TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument
	// загружаем XML-карту
	if (!levelFile.LoadFile())//если не удалось загрузить карту
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
		return false;
	}
	// работаем с контейнером map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");
	// пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	tileHeight = atoi(map->Attribute("tileheight"));
	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement *tilesetElement;
	std::vector<sf::Rect<int>> subRects;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	TiXmlElement *image;
	
	sf::Image img;
	sf::Image imgC;  sf::Image im;

	w = img.getSize().x; h = img.getSize().y;

	imgC.create(w, h, sf::Color(0, 0, 0, 0));
	while (tilesetElement) {//Пока TileSet: Выполнять
		if (!tilesetElement) break; 
		image = tilesetElement->FirstChildElement("image");
		std::string imagepath = image->Attribute("source");

		if (!img.loadFromFile(imagepath))
		{
			std::cout << "Failed to load tile sheet." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
			return false;
		}
		
		w = imgC.getSize().x; w += img.getSize().x;
		h = imgC.getSize().y; h = (h > img.getSize().y) ? h : img.getSize().y;
		
		im.create(w, h, sf::Color(0, 0, 0, 0));
		copyTileSetImage(&imgC, &im);
		imgC.create(w, h, sf::Color(0, 0, 0, 0));
		clearImage(&imgC); 
		copyTileSetImage(&im, &imgC);
		
		for (int i = 0, i2 = 0; i < img.getSize().y, i2 < img.getSize().y; i++, i2++)
			for (int j = w2, j2 = 0; j < w2 + img.getSize().x, j2 < img.getSize().x; j++, j2++)
				imgC.setPixel(j, i, img.getPixel(j2, i2));
		
		Vertexes v;
		v.x = w2; v.x2 = img.getSize().x; v.y2 = img.getSize().y;
		vertecies.push_back(v);
		w2 += img.getSize().x;
		tilesetImage.loadFromImage(imgC);
		tilesetImage.setSmooth(false);//сглаживание
		// получаем количество столбцов и строк тайлсета
		int columns = tilesetImage.getSize().x / tileWidth;
		int rows = tilesetImage.getSize().y / tileHeight;

		for (int y = 0; y < rows; y++)
			for (int x = 0; x < columns; x++) {
				if (!subRects.empty())
					subRects.pop_back();
			}
		for (iter = vertecies.begin(); iter != vertecies.end(); iter++)
			for (int y = (*iter).y / tileHeight; y < (*iter).y2 / tileHeight; y++)
				for (int x = (*iter).x / tileWidth; x < (*iter).x2 / tileWidth + (*iter).x / tileWidth; x++) {
					sf::Rect<int> rect;
					rect.top = y * tileHeight;
					rect.height = tileHeight;
					rect.left = x * tileWidth;
					rect.width = tileWidth;
					subRects.push_back(rect);
				}
		tilesetElement = tilesetElement->NextSiblingElement("tileset");
	}

	// работа со слоями
	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;
		// если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}
		//  контейнер <data> 
		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");
		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}
		//  контейнер <tile> - описание тайлов каждого слоя
		TiXmlElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");
		if (tileElement == NULL)
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			return false;
		}
		int x = 0;
		int y = 0;
		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;
			// Устанавливаем TextureRect каждого тайла
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
				layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
			}
			tileElement = tileElement->NextSiblingElement("tile");
			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}
		layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");
	}
	// работа с объектами
	TiXmlElement *objectGroupElement;
	// если есть слои объектов
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			//  контейнер <object>
			TiXmlElement *objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");
			while (objectElement)
			{
				// получаем все данные - тип, имя, позиция, и тд
				std::string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));
				int width, height;
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);
				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}
				// экземпляр объекта
				Object object;
				object.name = objectName;
				object.type = objectType;
				object.sprite = sprite;
				sf::Rect <float> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object.rect = objectRect;
				// "переменные" объекта
				TiXmlElement *properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement *prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							std::string propertyName = prop->Attribute("name");
							std::string propertyValue = prop->Attribute("value");
							object.properties[propertyName] = propertyValue;
							prop = prop->NextSiblingElement("property");
						}
					}
				}
				objects.push_back(object);
				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No object layers found..." << std::endl;
	}
	return true;
}
void Level::copyTileSetImage(const sf::Image* im, sf::Image* imCopy) {
	for (int i = 0; i < im->getSize().y; i++)
		for (int j = 0; j < im->getSize().x; j++)
			imCopy->setPixel(j, i, im->getPixel(j, i));
}
void Level::clearImage(sf::Image* im) {
	for (int i = 0; i < im->getSize().y; i++)
		for (int j = 0; j < im->getSize().x; j++)
			im->setPixel(j, i, sf::Color(0, 0, 0, 0));
}
Object Level::GetObject(std::string name)
{
	// только первый объект с заданным именем
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}
std::vector<Object> Level::GetObjects(std::string name)
{
	// все объекты с заданным именем
	std::vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);
	return vec;
}
std::vector<Object> Level::GetAllObjects()
{
	return objects;
};
sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}
void Level::Draw(sf::RenderWindow &window)
{
	const sf::FloatRect viewportRect = window.getView().getViewport();

	// Draw all tiles (and don't draw objects)
	for (const auto &layer : layers)
	{
		for (const auto &tile : layer.tiles)
		{
			if (viewportRect.intersects(tile.getLocalBounds()))
			{
				window.draw(tile);
			}
		}
	}
}
#endif
