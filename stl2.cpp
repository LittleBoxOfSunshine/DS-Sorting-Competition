#include <fstream>
#include <vector>
#include <algorithm>

/**
 * This is a "naive" implementation using the stl
 */

int main(int argc, char* argv[]) {

    // Read the input file
    std::ifstream input(argv[1], std::ios::in | std::ios::binary);

    // Get number of words
    int N;
    input >> N;

    // Get number of words to return
    int K;
    input >> K;

    // Preallocate vector with N elements
    std::vector<std::string> words((unsigned long)N);

    // Flush buffer
    input.ignore();

    // Load Strings
    for(int i = 0; i < N; i++)
        std::getline(input, words[i]);

    input.close();

    // Find first K strings
    std::nth_element(words.begin(), words.begin() + K, words.end(),
                     [](const std::string & a, const std::string & b) {
                         return a.length() < b.length() || (a.length() == b.length() && a < b);
                     }
    );

    // Sort first K strings
    std::sort(words.begin(), words.begin() + K,
              [](const std::string & a, const std::string & b) {
                  return a.length() < b.length() || (a.length() == b.length() && a < b);
              }
    );

    std::ofstream output(argv[2]);

    for(int i = 0; i < K; i++)
        output << words[i] << std::endl;

    output.close();

    return 0;
}