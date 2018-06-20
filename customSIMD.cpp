//
// Created by Chris Henk on 3/8/17.
//

#define SORT_COMP_SIMD

#include "lowLevelUtils.hpp"

/**
 * This is a fully custom implementation that avoids the stl when possible
 * and uses SIMD instructions (by leveraging SSE4.2 in particular)
 */

inline void maxHeapify(string* & heap, int index, int & size) {
    string temp = heap[index];
    int j = index << 1;

    while (j <= size) {
        if (j < size && heap[j] < heap[j+1] )
            j++;
        if (heap[j] < temp)
            break;
        else {
            heap[j >> 1] = heap[j];
            j <<= 1;
        }
    }
    heap[j >> 1] = temp;
    return;
}

// Build the max heap bottom up [linear time; O(K)]
inline void buildMaxHeap(string* & heap, int & size) {
    for(int i = size >> 1; i >= 1; i--)
        maxHeapify(heap, i, size);
}

int main(int argc, char* argv[]) {

    // Read the input file
    file input = getFileContents(argv[1]);

    int index = 0;

    // Get number of words
    int N = std::atoi(getLine(input.data, index).data);

    // Get number of words to return
    int K = std::atoi(getLine(input.data, index).data);

    // Create Strings
    string* heap = new string[K+1];
    string temp;

    // Load K data into strings
    for(int i = 1; i <= K; i++)
        heap[i] = getLine(input.data, index);

    // Build max heap
    buildMaxHeap(heap, K);

    // Load remaining N words
    for(int i = K; i < N; i++) {
        temp = getLine(input.data, index);
        if(temp < heap[1]) {
            heap[1] = temp;
            maxHeapify(heap, 1, K);
        }
    }

    // Reorder heap to ascending order
    int size = K;
    for (int i = size; i > 1; i--) {
        temp = heap[1];
        heap[1] = heap[i];
        heap[i] = temp;
        size--;
        maxHeapify(heap, 1, size);
    }

    std::ofstream output(argv[2]);

    for(int i = 1; i <= K; i++)
        output << heap[i].data << std::endl;

    output.close();

    delete[] input.data;

    return 0;
}