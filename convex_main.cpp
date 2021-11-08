#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>

std::tuple<int,int> findLowest(std::vector<std::tuple<int,int>>&sorted_points){
    std::tuple<int,int> lowestPair = sorted_points[0];
    //iterate through vector to find lowest value
    for(int i = 0; i < sorted_points.size(); i++){
        //if the y value is less than lowest's y, then lowest becomes the new pair
        if(std::get<1>(sorted_points[i]) < std::get<1>(lowestPair)){
            lowestPair = sorted_points[i];
        } else if (std::get<1>(sorted_points[i]) == std::get<1>(lowestPair)){
            //If lowestPair y ==  sorted_points y, use one with lowest X
            if(std::get<0>(sorted_points[i]) < std::get<0>(lowestPair)){
                lowestPair = sorted_points[i];
            }
        }
    }
    return lowestPair;
}

void getData(std::string fileName, std::vector<std::tuple<int,int>>&sorted_points){
    //opens file
    std::ifstream fileOpen(fileName);
    std::string row;
    //traverses file until the end of file is reached
    while(getline(fileOpen, row)){
        std::vector<std::tuple<int,int>> vecRow;
        std::stringstream rowStrings(row);
        int xCord, yCord;
        rowStrings >> xCord;
        rowStrings >> yCord;
        sorted_points.push_back(std::make_tuple(xCord, yCord));
    }


}

int main (int argc, char**argv){
    //initialize vector of sorted points
    std::vector<std::tuple<int,int>> sorted_points;

    //initializes stack
    std::stack<std::tuple<int,int>> graham_scan_stack;

    //Read file of points, put into a vector
    getData(argv[1], sorted_points);
    
    // for(int i = 0; i < sorted_points.size();i++){
    //     std::cout << std::get<0>(sorted_points[i]) << ", " << std::get<1>(sorted_points[i]) << '\n';
    // }

    //Find lowest point in set
    //Initialize tuple to hold lowest pair, set to lowest function
    std::tuple<int,int> lowestPair = findLowest(sorted_points);

    // std::cout << std::get<0>(lowestPair) << ", " <<std::get<1>(lowestPair);

    //Find angles between initial point and ALL other points
        //use cross product for this, if they are colinear, make sure you consider the x and y
        //cross product:
        //(x2 *y1) - (x1 * y2)
        // or 
        // -run / rise
    // Determine order of points based on angles
    //iterate through sorted order
        //determining if its clockwise or counter clock wise
            //cross product:
            //(x2 - x1) * (x3 - x1) - (y2 - y1) * (y3 - y1)
            //if result is negative its clockwise and should be popped off
        //if makes a counterclock wise turn, place on stack
        // else pop off stack, move to next point

}