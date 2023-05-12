#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;


vector<int> generateRandomDataset(int size) {
    vector<int> dataset(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 10000);

    for (int i = 0; i < size; ++i) {
        dataset[i] = distribution(gen);
    }

    return dataset;
}


void measureSortingTime(const vector<int>& dataset, const string& algorithmName, void (*sortingFunction)(vector<int>&)) {
    vector<int> temp = dataset; 
  
    auto start = chrono::high_resolution_clock::now();
    sortingFunction(temp);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duration = end - start;
    cout << "Time taken by " << algorithmName << " for dataset size " << dataset.size() << ": " << duration.count() << " milliseconds" << endl;
}



int main() {
    vector<int> datasetSizes = {500, 1000, 1500};

    for (int size : datasetSizes) {
        vector<int> dataset = generateRandomDataset(size);
        cout << "Dataset size: " << size << endl;

        measureSortingTime(dataset, "Bucket Sort", bucketSort);
        measureSortingTime(dataset, "Counting Sort", countingSort);
        measureSortingTime(dataset, "Heap Sort", heapSort);

        cout << endl;
    }

    return 0;
}
