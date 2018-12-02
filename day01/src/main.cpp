#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>

// Forward declarations
std::vector<int> load(std::ifstream& input);
int part1(std::vector<int> inputs);
int part2(std::vector<int> inputs);

int main(int argc, const char * argv[]) {
    std::ifstream input ("../input.txt");
    std::vector<int> data (load(input));
    input.close();

    int offset = part1(data);
    int duplicate_frequency (part2(data));

    std::cout << "The result is: " << offset << std::endl;
    std::cout << "The duplicate frequency is: " << duplicate_frequency << std::endl;
}
std::vector<int> load(std::ifstream& input) {
    std::vector<int> data;
    std::string line;
    while (getline(input, line)) {
        if (line.at(0) == '-'){
            data.push_back(std::stoi(line.substr(0)));
        } else if (line.at(0) == '+'){
            data.push_back(std::stoi(line.substr(1)));
        } else {
            std::cerr << "Bad input: " << line << std::endl;
            exit(1);
        }
    }
    return data;
}
int part1(std::vector<int> inputs) {
    int offset = 0;
    for (const auto& number : inputs) {
        offset += number;
    }
    return offset;
}
int part2(std::vector<int> inputs) {
    std::set<int> frequencies { 0 };
    int frequency = 0;
    while (true) {
        for (const auto& number : inputs) {
            frequency += number;
            if (frequencies.find(frequency) == frequencies.end()) {
                frequencies.insert(frequency);
            } else {
                return frequency;
            }
        }
    }
}
