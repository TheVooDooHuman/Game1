#include <SFML\Graphics.hpp>

const int HEIGHT_MAP = 25;
const int WIDHT_MAP = 40;

sf::String tileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   s                                  0",
	"0                   f     f            0",
	"0               f    f        f        0",
	"0                          f           0",
	"0                                      0",
	"0                                      0",
	"0      h h                             0",
	"0                     h                0",
	"0           h                          0",
	"0                 h                    0",
	"0                                      0",
	"0                    h                 0",
	"0              h                       0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerate() 
{
	int randomElementX = 0;
	int randomElementY = 0;
	srand(time(0));
	int countStone = 1;

	while (countStone > 0)
	{
		randomElementX = 1 + rand() % (WIDHT_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);
		if (tileMap[randomElementY][randomElementX] == ' ')
		{
			tileMap[randomElementY][randomElementX] = 's';
			std::cout << "coordinate of stone x: " << randomElementX << "\n" << "coordinate of stone Y: " << randomElementY << "\n\n";
			countStone--;
		}
	}

}






