#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

// Forward declarations
std::vector<std::string> load(std::ifstream& input);
int part1(std::vector<std::string> data);
std::string part2(std::vector<std::string> data);

int main(int argc, const char * argv[]) {
    std::ifstream input ("../input.txt");
    std::vector<std::string> data (load(input));
    input.close();

    int checksum = part1(data);
    std::string common_letters = part2(data);

    std::cout << "The checksum is: " << checksum << std::endl;
    std::cout << "The common letters are: " << common_letters << std::endl;
}
std::vector<std::string> load(std::ifstream& input) {
    std::vector<std::string> data;
    std::string line;
    while (getline(input, line)) {
        bool inserted = false;
        for (auto it = data.begin(); it != data.end(); it++ ) {
            if (line < *it) {
                data.insert(it, line.substr(0,26));  // trim '/r' if present
                inserted = true;
                break;
            }
        }
        if (!inserted)
            data.push_back(line);
    }
    return data;
}
int part1(std::vector<std::string> data) {
    int pairs = 0;
    int triplets = 0;
    for (const auto& line : data) {
        std::map<char, int> map;
        for (const auto& character : line) {
            map[character] = map[character] + 1;
        }
        bool found_pair = false;
        bool found_triplet = false;
        for (const auto& val : map) {
            if (!found_pair && val.second == 2) {
                pairs++ ;
                found_pair = true;
            } else if (!found_triplet && val.second == 3) {
                triplets++ ;
                found_triplet = true;
            }
        }
    }
    return pairs * triplets;
}
std::string part2(std::vector<std::string> data) {
    int line_length = 26;
    std::string common_letters;
    for (auto it = data.begin() + 1; it != data.end(); it++ ) {
        std::string first_line = *(it-1);
        std::string second_line = *it;
        int diff = 0;
        for (int i = 0; i < line_length; i++) {
            if (first_line.at(i) != second_line.at(i))
                diff++;
        }
        if (diff == 1) {
            for (int i = 0; i < line_length; i++) {
                if (first_line.at(i) == second_line.at(i))
                    common_letters.push_back(first_line.at(i));
            }
            break;
        }
    }
    return common_letters;
}
