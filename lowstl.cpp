#include <vector>
#include <algorithm>

#include "lowLevelUtils.hpp"

/**
 * This is a "low-level" implementation that uses std::partial_sort with data structure optimizations
 */

int main(int argc, char* argv[]) {

    // Read the input file
    file input = getFileContents(argv[1]);

    int index = 0;

    // Get number of words
    int N = std::atoi(getLine(input.data, index).data);

    // Get number of words to return
    int K = std::atoi(getLine(input.data, index).data);

    // Create Strings
    std::vector<string> words((unsigned long)N);

    // Load data into strings
    for(int i = 0; i < N; i++)
        words[i] = getLine(input.data, index);

    // Sort first K strings
    std::partial_sort(words.begin(), words.begin() + K, words.end(),
                      [](const string & a, const string & b) {
                          return a.length < b.length || (a.length == b.length && std::strcmp(a.data, b.data) < 0);
                      }
    );

    std::ofstream output(argv[2]);

    for(int i = 0; i < K; i++)
        output << words[i].data << std::endl;

    output.close();

    delete[] input.data;

    return 0;
}