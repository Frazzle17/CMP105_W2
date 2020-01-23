#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error Loading Font" << std::endl;
	}

	text.setFont(font);
	text.setString("");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);

	circle.setRadius(50);
	circle.setPosition(50,50);
	circle.setFillColor(sf::Color::Red);

	drag = false;
	startDragX = 0;
	startDragY = 0;
	endDragX = 0;
	endDragY = 0;
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		std::cout << "Nailed it" << std::endl;
	}

	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		std::cout << "Really nailed it" << std::endl;
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

	std::string output = "Mouse X: ";
	output.append(std::to_string(input->getMouseX()));
	output.append("  Mouse Y: ");
	output.append(std::to_string(input->getMouseY()));
	text.setString(output);


	if (input->isMouseLDown() && drag == false)
	{
		startDragX = input->getMouseX();
		startDragY = input->getMouseY();
		drag = true;
	}
	if (!input->isMouseLDown() && drag == true)
	{
		endDragX = input->getMouseX();
		endDragY = input->getMouseY();
		int diffX = startDragX - endDragX;
		int diffY = startDragY - endDragY;
		if (diffX < 0)
		{
			diffX *= -1;
		}
		if (diffY < 0)
		{
			diffY *= -1;
		}
		int distance = (diffX ^ 2 + diffY ^ 2) ^ (1/2);
		std::cout << "You dragged a distance of: " << distance << std::endl;

		drag = false;
		startDragX = 0;
		startDragY = 0;
		endDragX = 0;
		endDragY = 0;
	}

	if (input->isMouseRDown())
	{
		circle.setPosition(input->getMouseX(), input->getMouseY());
	}
}

// Update game objects
void Level::update()
{

}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(text);
	window->draw(circle);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}