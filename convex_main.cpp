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
    sortList(plotted_points);

    for(int i = 0; i < plotted_points.size(); i++){
        std::cout << "X: " <<std::get<0>(plotted_points[i])<< " Y: " <<std::get<1>(plotted_points[i]) << " Angle: ";
        std::cout << std::get<2>(plotted_points[i]) << '\n';
    }

    // Determine order of points based on angles
    //iterate through sorted order
        //determining if its clockwise or counter clock wise
            //cross product:
            //(x2 - x1) * (x3 - x1) - (y2 - y1) * (y3 - y1)
            //if result is negative its clockwise and should be popped off
        //if makes a counterclock wise turn, place on stack
        // else pop off stack, move to next point

}