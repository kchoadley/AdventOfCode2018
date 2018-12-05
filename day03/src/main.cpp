#include <fstream>
#include <iostream>
#include <string>
#include <map>

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
    int at = claim_string.find('@', 0);
    int comma = claim_string.find(',', 0);
    int colon = claim_string.find(':', 0);
    int x = claim_string.find('x', 0);
    claim.id = std::stoi(claim_string.substr(1, at - 2));
    claim.left_offset = std::stoi(claim_string.substr(at + 2, comma - at - 2));
    claim.top_offset = std::stoi(claim_string.substr(comma + 1, colon - comma - 1));
    claim.width = std::stoi(claim_string.substr(colon + 2, x - colon - 2));
    claim.height = std::stoi(claim_string.substr(x + 1, claim_string.length() - x - 2));
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
