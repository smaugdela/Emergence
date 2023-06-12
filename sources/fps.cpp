#include "emergence.hpp"

void fps_counter(sf::RenderWindow &window, std::string fps)
{
	sf::Font font;
	if (!font.loadFromFile("/usr/share/fonts/open-sans/OpenSans-BoldItalic.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setString(fps);
	text.setCharacterSize(24); // exprimée en pixels, pas en points !
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10);
	window.draw(text);
}
