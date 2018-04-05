#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Map.h"
#include "View.h"
#include <sstream>
#include "Mission.h"
;
using namespace sf;

class Player
{
private:
	
public:
	float x, y = 0;
	float w, h, dx, dy, speed;
	int dir, playerScore, health;
	bool life;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String F, float X, float Y, float W, float H)
	{
		dir = 0; speed = 0; playerScore = 0; health = 100;
		life = true;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(w, h, w, h));
	};


	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
		sprite.setOrigin(w / 2, h / 2);
		interactionWithMap();
		if (health <= 0) { life = false; }
	}

	float getPlayerCoordinateX() {
		return x;
	}
	float getPlayerCoordinateY() {
		return y;
	}

	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (tileMap[i][j] == '0')
				{
					if (dy > 0)
					{
						y = i * 32 - h;
					}
					if (dy < 0)
					{
						y = i * 32 + 32;
					}
					if (dx > 0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}

				if (tileMap[i][j] == 's')
				{
					playerScore++;
					tileMap[i][j] = ' ';
				}

				if (tileMap[i][j] == 'f')
				{
					health -= 40;
					tileMap[i][j] = ' ';
				}

				if (tileMap[i][j] == 'h')
				{
					health += 20;
					tileMap[i][j] = ' ';
				}
			}
	}

};

int main()
{
	RenderWindow window(VideoMode(640, 480), "Commandos");
	view.reset(FloatRect(0, 0, 640, 480));

	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));
	s_quest.setScale(0.6f, 0.6f);

	bool isMove = false;
	float dX = 0; float dY = 0;
	
	Player p("hero.png", 250, 250, 96, 96);
	bool showMissionText = true;
	float CurrentFrame = 0;
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;

	Font font;
	font.loadFromFile("hermes.ttf");
	Text text("", font, 20);
	text.setFillColor(Color::Black);
	//text.setStyle(Text::Bold);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	float createObjectForMapTimer = 0;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life) { gameTime = gameTimeClock.getElapsedTime().asSeconds(); }
		else { view.rotate(0.02); }
		clock.restart();
		time = time / 8000;

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		std::cout << pixelPos.x << "\n";
		std::cout << pos.x << "\n";


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))
					{
						std::cout << "isClicked!\n";
						dX = pos.x - p.sprite.getPosition().x;
						dY = pos.y - p.sprite.getPosition().y;
						isMove = true;
					}
				}
			}
			if (event.type == Event::MouseButtonReleased) {
				if (event.key.code == Mouse::Left) {
					isMove = false;
					p.sprite.setColor(Color::White);
				}
			}
				
			if(isMove)
			{
				p.sprite.setColor(Color::Green);
				p.sprite.setPosition(pos.x - dX, pos.y- dY);
				//p.x = pos.x - dX;
				//p.y = pos.y - dY;
			}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Tab)
				{
					switch (showMissionText)
					{
					case true:
					{
						std::ostringstream playerHealthString, task;
						playerHealthString << p.health;
						task << getTextMission(getCurrentMission(p.getPlayerCoordinateX()));
						text.setString("Çהמנמגüו: " + playerHealthString.str() + "\n" + task.str());
						text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
						s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
						showMissionText = false;
						break;
					}
					case false:
					{
						text.setString("");
						showMissionText = true;
						break;
					}
					}
				}
		}

		if (p.life) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				p.dir = 1; p.speed = 2;
				CurrentFrame += 0.05*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				p.dir = 0; p.speed = 2;
				CurrentFrame += 0.05*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				p.dir = 3; p.speed = 2;
				CurrentFrame += 0.05*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				p.dir = 2; p.speed = 2;
				CurrentFrame += 0.05*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			}
			getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}
		/*
		Vector2i localPosition = Mouse::getPosition(window);

		if (localPosition.x < 150) { view.move(-speed*time, 0); }
		if (localPosition.x > window.getSize().x - 150) { view.move(speed*time, 0); }
		if (localPosition.y > window.getSize().y - 150) { view.move(0, speed*time); }
		if (localPosition.y < 150) { view.move(0, -speed*time); }
		*/
		createObjectForMapTimer += time;
		if (createObjectForMapTimer >= 300) { randomMapGenerate(); createObjectForMapTimer = 0; }

		p.update(time);
		window.setView(view);
		window.clear();

		if ((getCurrentMission(p.getPlayerCoordinateX())) == 0)
		{
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDHT_MAP; j++)
				{
					if (tileMap[i][i] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
					if (tileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
					if (tileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));
					if (tileMap[i][j] == 'f') s_map.setTextureRect(IntRect(96, 0, 32, 32));
					if (tileMap[i][j] == 'h') s_map.setTextureRect(IntRect(128, 0, 32, 32));
					s_map.setPosition(j * 32, i * 32);
					window.draw(s_map);
				}
		}
		if ((getCurrentMission(p.getPlayerCoordinateX())) >= 1)
		{
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDHT_MAP; j++)
				{
					if (tileMap[i][i] == ' ') s_map.setTextureRect(IntRect(64, 0, 32, 32));
					if (tileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
					if (tileMap[i][j] == '0') s_map.setTextureRect(IntRect(0, 0, 32, 32));
					if (tileMap[i][j] == 'f') s_map.setTextureRect(IntRect(96, 0, 32, 32));
					if (tileMap[i][j] == 'h') s_map.setTextureRect(IntRect(128, 0, 32, 32));
					s_map.setPosition(j * 32, i * 32);
					window.draw(s_map);
				}
		}
		if (!showMissionText)
		{
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
			window.draw(s_quest); window.draw(text);
		}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}