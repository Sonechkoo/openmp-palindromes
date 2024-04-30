#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <omp.h>
#include <chrono>
#include <algorithm>

using namespace std;
vector<int> all_pos;

int getNumPalindromes(string line, int start, int step)
{
    int l = start;
    int ans = 0;
    while (l < line.size())
    {
        int j = 0;
        while (l - j >= 0 and l + j < line.size() and line[l - j] == line[l + j]) {
            ans += 1;
            j += 1;
        }
        j = 0;
        while (l - j >= 0 and l + j + 1 < line.size() and line[l - j] == line[l + j + 1]) {
            ans += 1;
            j += 1;
        }
        l += step;
    }
    return ans;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <num_threads> <input_file>" << std::endl;
        return 1;
    }

    int numThreads = std::atoi(argv[1]);
    string filename = argv[2];

    string line;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open input file: " << filename << "\n";
        return 1;
    }
    getline(file, line);
    auto start = chrono::high_resolution_clock::now();
    vector<long long> results(numThreads);

#pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i < numThreads; ++i) {
        int start = i;

        results[i] = getNumPalindromes(line, start, numThreads);
    }

    long long result = 0;
    for (int i = 0; i < numThreads; ++i){
        result += results[i];
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "RESULT :: " << result << "\n";
    cout << "DURATION :: " << duration.count() << " ms\n";

    return 0;
}