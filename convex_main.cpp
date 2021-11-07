#include <iostream>

int main (){
    //initialize stack
    //Read file of points, put into a vector
    //Find lowest point in set
        //If lowest y == another y, use one with lowest X
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