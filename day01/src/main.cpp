
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {
    std::cout << "I'm alive!" << std::endl;

    std::ifstream input ("../input.txt");
    std::string line;
    while (getline(input, line)) {
        std::cout << line << std::endl;
    }
    input.close();
    std::cout << "Good night!" << std::endl;
}
