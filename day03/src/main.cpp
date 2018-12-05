#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

// Forward declarations
struct Claim {
    int id;
    int left_offset;
    int top_offset;
    int width;
    int height;
    std::string to_string() {
        std::string claim_string =  id+" ";
        claim_string.append(left_offset +" ");
        claim_string.append(top_offset +" ");
        claim_string.append(width +" ");
        claim_string.append(height + " ");
        return claim_string;
    }
};
std::map<int, Claim> load(std::ifstream& input);
int part1(std::map<int, Claim>);
Claim parse_claim(const std::string& claim_string);

int main(int argc, const char * argv[]) {
    std::ifstream input ("../input.txt");
    std::map<int, Claim> claims (load(input));
    input.close();

    int overlap = part1(claims);

    std::cout << "The number of overlap claims is: " << overlap << std::endl;
}
std::map<int, Claim> load(std::ifstream& input) {
    std::map<int, Claim> claims;
    std::string line;
    while (getline(input, line)) {
        Claim claim = parse_claim(line);
        claims[claim.id] = claim;
    }
    return claims;
}
Claim parse_claim(const std::string& claim_string) {
    Claim claim;
    std::regex pattern {R"(#(\d+)\s@\s(\d+),(\d+):\s(\d+)x(\d+))"};
    std::smatch matches;
    std::regex_search(claim_string, matches, pattern);
    claim.id = std::stoi(matches[1]);
    claim.left_offset = std::stoi(matches[2]);
    claim.top_offset = std::stoi(matches[3]);
    claim.width = std::stoi(matches[4]);
    claim.height = std::stoi(matches[5]);
    return claim;
}
int part1(std::map<int, Claim> claims) {
    int overlap = 0;
    std::map<std::pair<int, int>, int> claim_map;
    for(auto& item : claims) {
        Claim claim = item.second;
        for (int row = claim.top_offset; row < claim.top_offset + claim.height; row++) {
            for (int column = claim.left_offset; column < claim.left_offset + claim.width; column++) {
                claim_map[std::pair<int, int> {row, column}] = claim_map[std::pair<int, int> {row, column}] + 1;
                if (claim_map[std::pair<int, int> {row, column}] == 2)
                    overlap++;
            }
        }
    }
    return overlap;
}
