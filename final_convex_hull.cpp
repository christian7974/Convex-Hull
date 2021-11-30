#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>

void GUI_VISUALIZATION(std::vector<std::tuple<int, int, double>>&plotted_points, std::stack<std::tuple<int, int, double>> &GS_stack) {
	
	sf::Font font;
	if (!font.loadFromFile("res/roboto/Roboto-Black.ttf")) {
		std::cout << "Error loading file" << std::endl;
	}
	// create the window that will open when the program is launched
	// first parameter is width, second is height, third is title of the window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Convex Hull Generator");
	
	//This creates a 2d camera to allow us to orient the screen properly
	//Allows origin to be in the bottom left
	sf::View viewPoint;
	viewPoint.setRotation(90);
	window.setView(viewPoint);

	// the first number is the size, the second number is the number of points in the circle

	// the outline pertrudes out
	// circle.setRadius(15);
	// circle.setPointCount(12);
	// the parameter is the number of points in the shape
	int numPoints = GS_stack.size();
	sf::ConvexShape convexHull(numPoints);
	// this is the fill color for the convex hull
	convexHull.setFillColor(sf::Color(0, 255, 0));
	// this sets the thickeness of the outline
	convexHull.setOutlineColor(sf::Color(255, 255, 255));
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
	
	//Loop that runs for the stack amount and allows for us to make the hull
	for (int i = 0; i < numPoints; i++)
	{
		// loop thru the stack and put in the x and y values of the tuples instead
		// the +100 just moves the polygon away from the edge so that it is easier to visualize
		convexHull.setPoint(i, sf::Vector2f(std::get<0>(GS_stack.top()) + 100, std::get<1>(GS_stack.top()) + 100));
		GS_stack.pop();
	}
	// important to have the points in clockwise or counterclockwise order

//--------------------------------------------------------------------------------
	// below is the code that will create the x axis of the euclidean plane
	sf::RectangleShape xAxis(sf::Vector2f(500, 0));
	xAxis.setOutlineThickness(10);
	xAxis.setPosition(0, 500);

	// below is the code that will create the y axis of the euclidean plane
	sf::RectangleShape yAxis;
	yAxis.setSize(sf::Vector2f(0, 500));
	yAxis.setOutlineThickness(10);
	yAxis.setPosition(10, 0);


	// the code below is how the window will open and what will display on the window
	sf::Event event;

	sf::Text text;
	text.setString("Hello World");
	text.setCharacterSize(20);
	text.setPosition(750, 750);
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
		for (int i = 0; i < plotted_points.size(); i++) {
			sf::CircleShape point;
			point.setRadius(8.5);
			point.setFillColor(sf::Color(255, 255, 255));
			// change the values inside of set position to all of the points, not just the ones that are in 
				// the convex hull
			point.setPosition(std::get<0>(plotted_points[i]) + 94, std::get<1>(plotted_points[i]) + 95);
			sf::Text xText;
			xText.setString("(" + std::to_string(std::get<0>(plotted_points[i])) + "," + std::to_string(std::get<1>(plotted_points[i])) + ")");
			xText.setPosition(std::get<0>(plotted_points[i])+ 100, std::get<1>(plotted_points[i]) + 110);
			xText.setFillColor(sf::Color::Red);
			xText.setCharacterSize(20);
			xText.setFont(font);
			xText.setRotation(90);

			window.draw(xText);
			window.draw(point);
		}
		window.display();
	}
}

void InsertionSort(std::vector<std::tuple<int, int, double>> &bucket) {
    std::tuple<int, int, double> temp;
    for (int i = 0; i < bucket.size(); i++) {
        for (int j = i; j > 0; j--) {
            if ( std::get<2>(bucket[j]) < std::get<2>(bucket[j-1]) ) {
                temp = bucket[j];
                bucket[j] = bucket[j-1];
                bucket[j-1] = temp;
            }
            // consider if the points are colinear(same angle from lowest point), if so consider x value
            else if ( std::get<2>(bucket[j]) == std::get<2>(bucket[j-1]) ) {
                if ( std::get<0>(bucket[j]) < std::get<0>(bucket[j-1]) ) {
                    temp = bucket[j];
                    bucket[j] = bucket[j-1];
                    bucket[j-1] = temp;
                }
            }
        }
    }
}

void BucketSort(std::vector<std::tuple<int,int ,double>> &plotted_points) {
    // 1. Create n empty buckets that stores the tuples
    int n = plotted_points.size();
    //std::vector<std::tuple<int, int, double>> buckets[n + 1];
    std::vector<std::vector<std::tuple<int, int, double>>> buckets(n);

    // find the max value of the array
    double max = std::get<2>(plotted_points[0]);
    for (int i = 0; i < plotted_points.size(); i++) {
        if (std::get<2>(plotted_points[i]) > max) {
            max = std::get<2>(plotted_points[i]);
        }
    }

    // 2. Put elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = std::floor(n * std::floor(std::get<2>(plotted_points[i])) / max); // Index in bucket
        buckets[bucketIndex].push_back(plotted_points[i]);

    }

    // 3. Sort individual buckets using insertion sort
    for (int i = 0; i < n; i++) {
        InsertionSort(buckets[i]);
    }


    // 4. Go through the list of buckets in order and insert the values into the original list
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            plotted_points[index] = buckets[i][j];
            index++;
        }
    }
}

void findAngle(std::tuple<int, int, double> &lowest, std::tuple<int, int, double> &newPoint) {
	double angle;
	//use the math function atan2, this will spit out the angle in radians
	//convert to degrees by multiplying by 180, then dividing by pi using the built
	//in definition M_PI
	angle = std::atan2(std::get<1>(newPoint) - std::get<1>(lowest), std::get<0>(newPoint) - std::get<0>(lowest));
	angle = angle * 180 / 3.14;
	std::get<2>(newPoint) = angle;

}

std::tuple<int, int, double> findLowest(std::vector<std::tuple<int, int, double>>&plotted_points) {
	std::tuple<int, int, double> lowestPair = plotted_points[0];
	//iterate through vector to find lowest value
	for (int i = 0; i < plotted_points.size(); i++) {
		//if the y value is less than lowest's y, then lowest becomes the new pair
		if (std::get<1>(plotted_points[i]) < std::get<1>(lowestPair)) {
			lowestPair = plotted_points[i];
		}
		else if (std::get<1>(plotted_points[i]) == std::get<1>(lowestPair)) {
			//If lowestPair y ==  sorted_points y, use one with lowest X
			if (std::get<0>(plotted_points[i]) < std::get<0>(lowestPair)) {
				lowestPair = plotted_points[i];
			}
		}
	}
	return lowestPair;
}

void getData(std::string fileName, std::vector<std::tuple<int, int, double>>&plotted_points) {
	//opens file
	std::ifstream fileOpen("C:\\Users\\tfarg\\Documents\\GitHub\\Convex-Hull\\test.txt");
	bool isOpen = fileOpen.is_open();
	std::string row;
	//traverses file until the end of file is reached
	while (getline(fileOpen, row)) {
		std::vector<std::tuple<int, int, double>> vecRow;
		std::stringstream rowStrings(row);
		int xCord, yCord;
		rowStrings >> xCord;
		rowStrings >> yCord;
		plotted_points.push_back(std::make_tuple(xCord, yCord, 0));
	}


}

//Function that calculates the cross product(Used to determine clockwise or counter Clockwise)
int crossProduct(int x1, int y1, int x2, int y2, int x3, int y3) {
	int crossProductValue;
	crossProductValue = (x2 - x1)*(y3 - y1) - (x3 - x1) * (y2 - y1);
	return crossProductValue;

}

//This is an easily callable function to get item two spaces into the stack
std::tuple<int, int, double> previousPointStack(std::stack<std::tuple<int, int, double>> &GS_stack) {
	std::tuple<int, int, double> tempPoint = GS_stack.top();
	GS_stack.pop();
	std::tuple<int, int, double> previousPoint = GS_stack.top();
	GS_stack.push(tempPoint);
	return previousPoint;
}

//Function that fills the stack following the Graham Scan Algorithm
void graham_scan(std::stack<std::tuple<int, int, double>> &GS_stack, std::vector<std::tuple<int, int, double>> &plotted_points, std::tuple<int, int, double> lowestPair) {
	//Initialize a tuple to hold next point inside loop
	std::tuple<int, int, double> nextPoint;

	//We know that both the lowest point and first point of the vector will be in the stack, so we can push them in before the loop
	GS_stack.push(lowestPair);
	GS_stack.push(plotted_points[0]);

	//This loop from the second element on due to us knowing the the lowest and first element of the vector will be in the hull and on the stack
	for (int i = 1; i < plotted_points.size(); i++) {
		//push current value into the stack
		GS_stack.push(plotted_points[i]);

		//Conditional to make sure that when we reach final point it is compared back to the first value
		if (i + 1 < plotted_points.size()) {
			nextPoint = plotted_points[i + 1];
		}
		else {
			nextPoint = lowestPair;
		}

		//While loop
			//This will continously call the cross Product until it produces a value above 0
			//Inorder to allow the value to change, we pop a value out and call the previousPointStack Function to get the value right before the new top
			//We call the new top in the next set of x and y
			//The only values that remain consistent is our next value, as we are only editing the points we have visited in order to produce the convex hull
		while (crossProduct(std::get<0>(previousPointStack(GS_stack)), std::get<1>(previousPointStack(GS_stack)), std::get<0>(GS_stack.top()), std::get<1>(GS_stack.top()), std::get<0>(nextPoint), std::get<1>(nextPoint)) <= 0) {
			GS_stack.pop();
		}
	}



}


int main(int argc, char**argv) {
	//initialize vector of sorted points
	//A vector of tuples, the tuples have x val, y val, and angle in relation to intial point
	std::vector<std::tuple<int, int, double>> plotted_points;

	//initializes stack
	std::stack<std::tuple<int, int, double>> graham_scan_stack;

	std::string textFile = argv[1];
	//Read file of points, put into a vector
	getData(argv[1], plotted_points);

	// for(int i = 0; i < sorted_points.size();i++){
	//     std::cout << std::get<0>(sorted_points[i]) << ", " << std::get<1>(sorted_points[i]) << '\n';
	// }

	//Find lowest point in set
	//Initialize tuple to hold lowest pair, set to lowest function
	std::tuple<int, int, double> lowestPair = findLowest(plotted_points);

	// std::cout << std::get<0>(lowestPair) << ", " <<std::get<1>(lowestPair);

	//Find angles between initial point and ALL other points
	int startPoint;
	for (int i = 0; i < plotted_points.size(); i++) {
		findAngle(lowestPair, plotted_points[i]);
		//Finds the lowest point again and saves its index
		if (std::get<2>(plotted_points[i]) == 0 && std::get<0>(plotted_points[i]) == std::get<0>(lowestPair) && std::get<1>(plotted_points[i]) == std::get<1>(lowestPair)) {
			startPoint = i;
		}
	}
	//removes the lowest point from the vector so that we do not check during stack stage
	plotted_points.erase(plotted_points.begin() + startPoint);

	//Sort the vector to determine the order we look at the points
	// Determine order of points based on angles
	BucketSort(plotted_points);

	// for(int i = 0; i < plotted_points.size(); i++){
	//     std::cout << "X: " <<std::get<0>(plotted_points[i])<< " Y: " <<std::get<1>(plotted_points[i]) << " Angle: ";
	//     std::cout << std::get<2>(plotted_points[i]) << '\n';
	// }

	//Call function to begin Gramham Scan
	graham_scan(graham_scan_stack, plotted_points, lowestPair);


	//push the lowest point back into the hull inorder to graph it
	plotted_points.push_back(lowestPair);
	GUI_VISUALIZATION(plotted_points, graham_scan_stack);



}
