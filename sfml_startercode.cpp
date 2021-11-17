#include <iostream>
#include <SFML/Graphics.hpp>
//#include <VertexArray.hpp>
#include <vector>

int main()
{
    // create the window that will open when the program is launched
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Title");

    // the number of points goes into the parantheses

    // the first number is the size, the second number is the number of points in the circle
    sf::CircleShape circle(65);
    circle.setFillColor(sf::Color(255, 0, 0));
    circle.setOutlineColor(sf::Color(0, 255, 0));

    // the outline pertrudes out
    circle.setOutlineThickness(-15);
    // circle.setRadius(15);
    // circle.setPointCount(12);
    // the parameter is the number of points in the shape
    sf::ConvexShape convex(5);
    // 0-4
    std::vector<int> xValues;
    xValues.push_back(0);
    xValues.push_back(100);
    xValues.push_back(200);
    xValues.push_back(45);
    xValues.push_back(0);

    std::vector<int> yValues;
    yValues.push_back(0);
    yValues.push_back(15);
    yValues.push_back(75);
    yValues.push_back(120);
    yValues.push_back(400);

    for (int i = 0; i < 5; i++)
    {
        convex.setPoint(i, sf::Vector2f(xValues[i], yValues[i]));
    }
    // important to have the points in clockwise or anticlockwise order
    // convex.setPoint(0, sf::Vector2f(0, 0));
    // convex.setPoint(1, sf::Vector2f(100, 15));
    // convex.setPoint(2, sf::Vector2f(200, 75));
    // convex.setPoint(3, sf::Vector2f(45, 120));
    // convex.setPoint(4, sf::Vector2f(0, 70));
    convex.setFillColor(sf::Color(0, 255, 0));
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Q)
                {
                    window.close();
                }

                break;
            default:
                break;
            }
        }
        window.clear(sf::Color::Black);
        //window.draw(circle);
        window.draw(convex);
        window.display();
    }

    return 0;
}