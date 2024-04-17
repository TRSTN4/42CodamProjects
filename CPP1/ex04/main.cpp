#include <iostream>
#include <fstream>
#include <sstream>

std::string replaceWords(const std::string content, const std::string findWord, const std::string newWord) {
    if (findWord.empty()) {
        return content;
    }

    std::string result;
    size_t current_pos = 0;
    size_t found_word = content.find(findWord, current_pos);

    while (found_word != std::string::npos) {
        result += content.substr(current_pos, found_word - current_pos) + newWord;
        current_pos = found_word + findWord.length();
        found_word = content.find(findWord, current_pos);
    }
    result += content.substr(current_pos);

    return result;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <filename> <s1> <s2>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cout << "Could not open file: " << filename << "\n";
        return 1;
    }

    std::ostringstream ss;
    ss << inFile.rdbuf();
    std::string content = ss.str();
    inFile.close();

    std::string newContent = replaceWords(content, s1, s2);

    std::ofstream outFile(filename + ".replace");
    if (!outFile) {
        std::cout << "Could not create file: " << filename << ".replace\n";
        return 1;
    }
    outFile << newContent;
    outFile.close();

    return 0;
}
