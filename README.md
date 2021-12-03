# Convex Hull
### Christian Tropeano, Thomas Fargnoli, Benjamin Chau
This final project for our Data Structures and Abstractions Class involves us implementing convex hulls using Graham's Scan Algorithm.
We used the programming language C++ in order to implement the algorithm. This repo includes our project report as well as our presentation.
## **How to Run our Project**:
### Prerequisites:
- Have Visual Studios Community installed, [you will need the 2017 version](https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads).
- [Install SFML on machine](https://www.sfml-dev.org/download/sfml/2.5.0/)

<!---tom will work on this part of the markdown file. -->
### Steps to Run Program:
1. Follow the SFML and Visual Studio Community 2017 tutorial [found here](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)
2. Once installed, download the GitHub repo
3. Inside of Visual Studio Community, select open project
4. In the downloaded repo, open the Convex_Hull_project folder
5. Select the file Convex_Hull_project.sln file
![image](https://user-images.githubusercontent.com/71107413/144626320-e033bd29-e240-4cc3-8947-6d523559e61c.png)

6. Once open hit the Local Windows Debugger button to check if everything is in order
![image](https://user-images.githubusercontent.com/71107413/144627448-d67f75ee-c94f-439a-8c5c-02e44c3260da.png)

7. If there is an error, go back to the Convex_Hull_project folder
8. Look inside of the Release folder, it must look like this
![image](https://user-images.githubusercontent.com/71107413/144627831-2f789e96-1ac2-492e-b6c6-31f324e455a3.png)

9. Before running the project again, make sure the settings are set to Release and 32 bit, it will look like this:
![image](https://user-images.githubusercontent.com/71107413/144628113-1644e14b-da27-449d-a042-d76f3db58384.png)

10. Hit the Local Windows Debugger button again, if downloaded successfully, the file will produce a window like this:
![image](https://user-images.githubusercontent.com/71107413/144628347-5326691a-4551-48a7-aade-aed8d262a0f0.png)

### Setting up Input Test Files:
1. Go to the Project properties
2. Go to Configuration Properties
3. Enter the Debugging section
4. Look for the Command Arguments line
5. Enter the text file name that you would like to test from the test files folder, it **MUST** be the path to the file. It should look similar to this:
![image](https://user-images.githubusercontent.com/71107413/144647735-7883a005-5d14-4e61-92c9-faecd086b37f.png)


6. This will produce a convex hull from the file chosen
