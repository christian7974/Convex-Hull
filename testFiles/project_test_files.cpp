#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
// this program generates 10 files with random numbers as points
    // for the convex hull program

// function to write a file
void WriteFile(std::string file_name){
    // Opens the outfile file, prepares it for writing
    std::ofstream output_file(file_name);
    // the program generates at most 4000 points in one file
    for (int i = 0; i < rand() % 4000; i ++) {
        // the x and y will be no greater than 1000 
        output_file << rand() % 1000 << " " << rand() % 1000 << "\n";
    }
    //for (int i = 0; i < )
}

int main() {
    srand (time(NULL));
    // generates 10 different files
    for (int i = 1; i <= 10; i ++) {
        WriteFile("TestFile_" + std::to_string(i) + ".txt");
    }
    // WriteFile("Test File 11");
    return 0;
}