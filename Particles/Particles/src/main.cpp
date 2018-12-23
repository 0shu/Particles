//TODO: Mass spheres
#include "main.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "10000 Particles!");
	sf::Vector2u windowSize = window.getSize();

	Handler myHandler;

	//We create timers and the tickhealth checker
	sf::Clock timer;
	float fFrameTime = 1.f / 120.f;
	float fElapsedTime = 0;
	float fLastTime = 0;
	TickHealth myTick;
	sf::Font font;
	if (!font.loadFromFile("Font-Regular.ttf")) std::cout << "Error loading font!\n";
	myTick.passFont(font);
	myHandler.passFont(font);
	//myHandler.setSize(sf::Vector2f(windowSize.x, windowSize.y));

	while (window.isOpen())
	{
		fElapsedTime = timer.getElapsedTime().asSeconds() - fLastTime;

		//EVENTS:
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				myHandler.setSize(sf::Vector2f(event.size.width, event.size.height));
			}
			//This bool changes depending if the click is down or up
			if (event.type == sf::Event::MouseButtonPressed)
			{
				myHandler.click(sf::Mouse::getPosition(window), true);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				myHandler.click(sf::Mouse::getPosition(window), false);
			}
		}

		//UPDATES HERE:
		//Each time the full frame time elapses we do a complex physics update
		if (fElapsedTime> fFrameTime)
		{
			myHandler.complexUpdate(sf::Mouse::getPosition(window));
			fLastTime = fElapsedTime;
		}
		
		myHandler.simpleUpdate(timer.getElapsedTime().asSeconds());
		myTick.update(timer.getElapsedTime().asMilliseconds());

		//DRAWING HERE:
		window.clear();
		window.draw(myHandler);
		window.draw(myTick);
		window.display();
	}

	return 0;
}