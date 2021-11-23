// this is the file that contains all of the code for the gui for the final project

#include <iostream>
#include <SFML/Graphics.hpp>
//#include <VertexArray.hpp>
#include <vector>
#include <string>
/*
 below is the command line that runs the code

make && ./game 
*/

int main()
{
    sf::Font font;
    if (!font.loadFromFile("res/roboto/Roboto-Black.ttf")) {
        std::cout << "Error loading file" << std::endl;
    }
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

    // the number of all of the points, even the ones that are not on the convex hull
    // I NEED A DATA STRUCTURE THAT HAS ALL OF THE POINTS, EVEN THE ONES THAT ARE NOT ON THE CONVEX HULL
    int numPoints = xValues.size();
    sf::ConvexShape convexHull(numPoints);
    // this is the fill color for the convex hull
    convexHull.setFillColor(sf::Color(sf::Color::Black));
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

    // I NEED A VECTOR/DATA STRUCTURE CONTAINING THE POINTS THAT ARE WITHIN THE CONVEX HULL
    // I ALSO NEED THE NUMBER OF POINTS THAT ARE IN THE CONVEX HULL, LOOP FROM 0 UNTIL THAT POINT
    for (int i = 0; i < numPoints; i++)
    {
        // loop thru the stack and put in the x and y values of the tuples instead
        // the +100 just moves the polygon away from the edge so that it is easier to visualize
        // the points that are apart of the convex hull
        // LOOP THRU THE POINTS THAT ARE ON THE CONVEX HULL AND PUT THE X AND Y VALUES IN THE CORRECT SPOTS
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
        // this draws all of the points on the polygon at the correct points
        // LOOP THRU 0 UNTIL THE NUMBER OF POINTS ON THE CONVEX HULL
        for (int i = 0; i < numPoints; i ++) {
            sf::CircleShape point;
            point.setRadius(10);
            point.setFillColor(sf::Color(255,255,255));
            // change the values inside of set position to all of the points, not just the ones that are in 
                // the convex hull
    // LOOP THRU ALL OF THE POINTS (EVEN THE ONES NOT ON THE CONVEX HULL)
            // INSERT THE XVALUES OF THE POINTS ON THE CONVEX HULL AND THE Y VALUES OF THE POINTS ON THE CONVEX HULL
            point.setPosition(xValues[i] - 10 + 100, yValues[i] - 7 + 100);


            // this is the text that will be next to the point so that the user can see what the point is referring to
            sf::Text xText;
            xText.setString("(" + std::to_string(xValues[i]) + "," + std::to_string(yValues[i]) + ")");
            xText.setPosition(xValues[i] - 40 + 100, yValues[i] - 7 + 125);
            xText.setFillColor(sf::Color::Red);
            xText.setCharacterSize(25);
            xText.setFont(font);

            window.draw(xText);
            window.draw(point);
            
        }
        window.display();
    }

    return 0;
}