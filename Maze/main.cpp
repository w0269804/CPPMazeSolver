#include <iostream>
#include "MazeSolver.h"

int main(int argc, char **argv) {
 
  
    try {
        MazeSolver maze(argv[1], argv[2]);
    } catch (FileException ex)
    {
		std::cout << ex.getMessage();
    }
    catch(std::exception e)
    {
      std::cout << "Error reading file: \n " << e.what();
    }
    return 0;

}
