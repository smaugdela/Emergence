#include "emergence.hpp"

int loop(sf::RenderWindow &window)
{
	std::time_t t = std::time(0);
	std::time_t deltat = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		window.clear();

		my_settings.update_particles();

		deltat = std::time(0) - t;
		my_settings.draw_particles(window);

		sf::Font font;
		if (!font.loadFromFile("/usr/share/fonts/open-sans/OpenSans-BoldItalic.ttf"))
		{
			std::cerr << "Error loading font" << std::endl;
			return EXIT_FAILURE;
		}
		sf::Text text;
		// choix de la police à utiliser
		text.setFont(font); // font est un sf::Font
		// choix de la chaîne de caractères à afficher
		std::string fps = std::to_string(1.0f / deltat);
		text.setString(fps);
		// choix de la taille des caractères
		text.setCharacterSize(24); // exprimée en pixels, pas en points !
		// choix de la couleur du texte
		text.setFillColor(sf::Color::White);
		// choix de la position
		text.setPosition(100, 100);

		window.draw(text);

		t = std::time(0);

		window.display();
	}

	return EXIT_SUCCESS;
}
