
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

void sortList(std::vector<std::tuple<int,int ,double>>&plotted_points){
    //When sorting, consider if the points are colinear(same angle from lowest point), if so consider x value
    std::tuple<int,int ,double> temp;
    for(int i = 0; i < plotted_points.size(); i ++){
        for(int j = i; j > 0 ; j --){
            if( std::get<2>(plotted_points[j]) < std::get<2>(plotted_points[j-1]) ){
                temp = plotted_points[j];
                plotted_points[j] = plotted_points[j-1];
                plotted_points[j-1] = temp;
            } else if (std::get<2>(plotted_points[j]) == std::get<2>(plotted_points[j-1])){
                if(std::get<0>(plotted_points[j]) < std::get<0>(plotted_points[j-1])){
                    temp = plotted_points[j];
                    plotted_points[j] = plotted_points[j-1];
                    plotted_points[j-1] = temp;
                }
            }
        }
    }
}

void findAngle(std::tuple<int,int,double> &lowest, std::tuple<int,int,double> &newPoint){
    double angle;
    //use the math function atan2, this will spit out the angle in radians
    //convert to degrees by multiplying by 180, then dividing by pi using the built
    //in definition M_PI
    angle = std::atan2(std::get<1>(newPoint) -  std::get<1>(lowest) , std::get<0>(newPoint) - std::get<0>(lowest));
    angle = angle * 180 / M_PI;
    std::get<2>(newPoint) = angle;
    
}

std::tuple<int,int, double> findLowest(std::vector<std::tuple<int,int ,double>>&plotted_points){
    std::tuple<int,int, double> lowestPair = plotted_points[0];
    //iterate through vector to find lowest value
    for(int i = 0; i < plotted_points.size(); i++){
        //if the y value is less than lowest's y, then lowest becomes the new pair
        if(std::get<1>(plotted_points[i]) < std::get<1>(lowestPair)){
            lowestPair = plotted_points[i];
        } else if (std::get<1>(plotted_points[i]) == std::get<1>(lowestPair)){
            //If lowestPair y ==  sorted_points y, use one with lowest X
            if(std::get<0>(plotted_points[i]) < std::get<0>(lowestPair)){
                lowestPair = plotted_points[i];
            }
        }
    }
    return lowestPair;
}

void getData(std::string fileName, std::vector<std::tuple<int,int, double>>&plotted_points){
    //opens file
    std::ifstream fileOpen(fileName);
    std::string row;
    //traverses file until the end of file is reached
    while(getline(fileOpen, row)){
        std::vector<std::tuple<int,int, double>> vecRow;
        std::stringstream rowStrings(row);
        int xCord, yCord;
        rowStrings >> xCord;
        rowStrings >> yCord;
        plotted_points.push_back(std::make_tuple(xCord, yCord, 0));
    }


}

//Function that calculates the cross product(Used to determine clockwise or counter Clockwise)
int crossProduct(int x1, int y1, int x2, int y2, int x3, int y3){
    int crossProductValue;
    crossProductValue = (x2 - x1)*(y3 - y1) - (x3 - x1) * (y2 - y1);
    return crossProductValue;

}

//This is an easily callable function to get item two spaces into the stack
std::tuple<int,int,double> previousPointStack(std::stack<std::tuple<int,int,double>> &GS_stack){
    std::tuple<int,int,double> tempPoint = GS_stack.top();
    GS_stack.pop();
    std::tuple<int,int,double> previousPoint = GS_stack.top();
    GS_stack.push(tempPoint);
    return previousPoint;
}

//Function that fills the stack following the Graham Scan Algorithm
void graham_scan(std::stack<std::tuple<int,int,double>> &GS_stack, std::vector<std::tuple<int,int, double>> &plotted_points, std::tuple<int,int, double> lowestPair){
    //Initialize a tuple to hold next point inside loop
    std::tuple<int,int,double> nextPoint;

    //We know that both the lowest point and first point of the vector will be in the stack, so we can push them in before the loop
    GS_stack.push(lowestPair);
    GS_stack.push(plotted_points[0]);
    
    //This loop from the second element on due to us knowing the the lowest and first element of the vector will be in the hull and on the stack
    for(int i = 1; i < plotted_points.size(); i ++){
        //push current value into the stack
        GS_stack.push(plotted_points[i]);
        
        //Conditional to make sure that when we reach final point it is compared back to the first value
        if( i + 1 < plotted_points.size()){
            nextPoint = plotted_points[i + 1];
        }else {
            nextPoint = lowestPair;
        }

        //While loop
            //This will continously call the cross Product until it produces a value above 0
            //Inorder to allow the value to change, we pop a value out and call the previousPointStack Function to get the value right before the new top
            //We call the new top in the next set of x and y
            //The only values that remain consistent is our next value, as we are only editing the points we have visited in order to produce the convex hull
        while(crossProduct(std::get<0>(previousPointStack(GS_stack)), std::get<1>(previousPointStack(GS_stack)), std::get<0>(GS_stack.top()), std::get<1>(GS_stack.top()), std::get<0>(nextPoint), std::get<1>(nextPoint)) <=  0){
            GS_stack.pop();
        }
    }



}


int main (int argc, char**argv){
    //initialize vector of sorted points
    //A vector of tuples, the tuples have x val, y val, and angle in relation to intial point
    std::vector<std::tuple<int,int, double>> plotted_points;

    //initializes stack
    std::stack<std::tuple<int,int, double>> graham_scan_stack;

    //Read file of points, put into a vector
    getData(argv[1], plotted_points);
    
    // for(int i = 0; i < sorted_points.size();i++){
    //     std::cout << std::get<0>(sorted_points[i]) << ", " << std::get<1>(sorted_points[i]) << '\n';
    // }

    //Find lowest point in set
    //Initialize tuple to hold lowest pair, set to lowest function
    std::tuple<int,int, double> lowestPair = findLowest(plotted_points);

    // std::cout << std::get<0>(lowestPair) << ", " <<std::get<1>(lowestPair);

    //Find angles between initial point and ALL other points
    int startPoint;
    for(int i = 0; i < plotted_points.size(); i++){
        findAngle(lowestPair,plotted_points[i]);
        //Finds the lowest point again and saves its index
        if(std::get<2>(plotted_points[i]) == 0 && std::get<0>(plotted_points[i]) == std::get<0>(lowestPair) && std::get<1>(plotted_points[i]) == std::get<1>(lowestPair)){
            startPoint = i;
        }
    }
    //removes the lowest point from the vector so that we do not check during stack stage
    plotted_points.erase(plotted_points.begin()+startPoint);

    //Sort the vector to determine the order we look at the points
    // Determine order of points based on angles
    sortList(plotted_points);

    // for(int i = 0; i < plotted_points.size(); i++){
    //     std::cout << "X: " <<std::get<0>(plotted_points[i])<< " Y: " <<std::get<1>(plotted_points[i]) << " Angle: ";
    //     std::cout << std::get<2>(plotted_points[i]) << '\n';
    // }

    //Call function to begin Gramham Scan
    graham_scan(graham_scan_stack, plotted_points, lowestPair);


    //temp print to see if we have the right points
    int stackSize = graham_scan_stack.size();
    for(int i = 0; i < stackSize; i++){
        std::cout << std::get<0>(graham_scan_stack.top()) << ' ' << std::get<1>(graham_scan_stack.top()) << '\n';
        graham_scan_stack.pop();
    }

}
