#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

void bucketSort(vector<int>& vec);

void heapSort(vector<int>& vec);
void buildHeap(vector<int>& vec);
void heapify(vector<int>& vec,int size, int i);

void countingSort(vector<int>& vec);


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

void bucketSort(vector<int>& vec) {
    
    int n = vec.size();
   
    int max_val = *max_element(vec.begin(), vec.end());
    
    vector<vector<int>> buckets(n);
    
    for (int i = 0; i < n; ++i) {
        int bucketIdx = static_cast<int>(vec[i] * n / (max_val + 1));
        buckets[bucketIdx].push_back(vec[i]);
    }
    
 
    for (int i = 0; i < n; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
    }
    
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < buckets[i].size(); ++j) {
            vec[index++] = buckets[i][j];
        }
    }
}

void heapify(vector<int>& vec, int size, int i) {
     int largest = i;    
    int left = 2 * i + 1;  
    int right = 2 * i + 2;  
    
    if (left < n && vec[left] > vec[largest])
        largest = left;
    
    if (right < n && vec[right] > vec[largest])
        largest = right;
    
    if (largest != i) {
        swap(vec[i], vec[largest]);

        heapify(vec, n, largest);
    }

}
void buildHeap(vector<int>& vec) {
    int n = vec.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(vec, n, i);
}
void heapSort(vector<int>& vec) {
     int n = vec.size();
    buildHeap(vec); 

    for (int i = n - 1; i > 0; --i) {
        swap(vec[0], vec[i]);
        
        heapify(vec, i, 0);
    }
}

void countingSort(vector<int>& vec) {
     int n = vec.size();

    int max_val = *max_element(vec.begin(), vec.end());

    vector<int> count(max_val + 1, 0);
    
    for (int i = 0; i < n; ++i)
        ++count[vec[i]];

    for (int i = 1; i <= max_val; ++i)
        count[i] += count[i - 1];

    vector<int> output(n);

    for (int i = n - 1; i >= 0; --i) {
        output[count[vec[i]] - 1] = vec[i];
        --count[vec[i]];
    }

    for (int i = 0; i < n; ++i)
        vec[i] = output[i];

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
