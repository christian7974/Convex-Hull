// this is the file that contains all of the code for the gui for the final project

#include <iostream>
#include <SFML/Graphics.hpp>
//#include <VertexArray.hpp>
#include <vector>
/*
 below is the command line that runs the code

make && ./game 
*/

int main()
{
    // create the window that will open when the program is launched
    // first parameter is width, second is height, third is title of the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Convex Hull Generator");

    // the number of points goes into the parantheses
    std::vector<int> xValues;
    xValues.push_back(5);
    xValues.push_back(100);
    xValues.push_back(200);
    xValues.push_back(45);
    xValues.push_back(25);
    //xValues.push_back(400);

    std::vector<int> yValues;
    yValues.push_back(5);
    yValues.push_back(15);
    yValues.push_back(75);
    yValues.push_back(120);
    yValues.push_back(25);
    //yValues.push_back(400);
    // the first number is the size, the second number is the number of points in the circle

    // the outline pertrudes out
    // circle.setRadius(15);
    // circle.setPointCount(12);
    // the parameter is the number of points in the shape
    int numPoints = xValues.size();
    sf::ConvexShape convexHull(numPoints);
    // this is the fill color for the convex hull
    convexHull.setFillColor(sf::Color(0, 255, 0));
    // this sets the thickeness of the outline
    convexHull.setOutlineColor(sf::Color(255,255,255));
    convexHull.setOutlineThickness(3);
    // 0-4
    

    // this is the loop that sets the points of the convex hull
    // have the x and y values of the stack be put into here

    // right now, the point is lying directly on top of the x and y value of the convex hull
    // the only problem is i have to now print out n number of points on there respective x,y
    // sf::CircleShape point;
    // point.setRadius(10);
    // point.setFillColor(sf::Color(255,255,255));
    // point.setPosition(xValues[4] - 10,yValues[4] - 7);
    for (int i = 0; i < numPoints; i++)
    {
        // loop thru the stack and put in the x and y values of the tuples instead
        // the +100 just moves the polygon away from the edge so that it is easier to visualize
        convexHull.setPoint(i, sf::Vector2f(xValues[i]+100, yValues[i]+100));
    }
    // important to have the points in clockwise or anticlockwise order

//--------------------------------------------------------------------------------
    // below is the code that will create the x axis of the euclidean plane
    sf::RectangleShape xAxis(sf::Vector2f(500,0));    
    xAxis.setOutlineThickness(10);
    xAxis.setPosition(0,500);

    // below is the code that will create the y axis of the euclidean plane
    sf::RectangleShape yAxis;    
    yAxis.setSize(sf::Vector2f(0,500));
    yAxis.setOutlineThickness(10);
    yAxis.setPosition(10,0);
    

    // the code below is how the window will open and what will display on the window
    sf::Event event;

    sf::Text text;
    text.setString("Hello World");
    text.setCharacterSize(20);
    text.setPosition(750,750);
    // this is the while loop that will display the gui and the visualization of the convex hull
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // if the user presses the window to close it, the window will close
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }
        window.clear(sf::Color::Black);
        //window.draw(circle);
        window.draw(convexHull);
        //window.draw(xAxis);
        //window.draw(yAxis);
        window.draw(text);
        // this draws all of the points on the polygon at the correct points
        for (int i = 0; i < numPoints; i ++) {
            sf::CircleShape point;
            point.setRadius(10);
            point.setFillColor(sf::Color(255,255,255));
            // change the values inside of set position to all of the points, not just the ones that are in 
                // the convex hull
            point.setPosition(xValues[i] - 10 + 100,yValues[i] - 7 + 100);
            window.draw(point);
        }
        window.display();
    }

    return 0;
}