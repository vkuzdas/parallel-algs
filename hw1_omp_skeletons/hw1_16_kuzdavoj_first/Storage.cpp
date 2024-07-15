//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "openmp-use-default-none"
#include <vector>
#include <omp.h>

#include "Utils.h"

#include <bits/stdc++.h>
using namespace std;


/// Distance of other record from original record
// https://www.geeksforgeeks.org/edit-distance-dp-5/
int levenstein(vector<int> original, vector<int> other) {
    int m = original.size();
    int n = other.size();
    int previous;
    vector<int> curr(n + 1, 0);

    for (int j = 0; j <= n; j++) {
        curr[j] = j;
    }
    for (int i = 1; i <= m; i++) {
        previous = curr[0];
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            int temp = curr[j];
            if (original[i - 1] == other[j - 1]) {
                curr[j] = previous;
            }
            else {
                curr[j] = 1 + min({ previous, curr[j - 1],curr[j] });
            }
            previous = temp;
        }
    }
    return curr[n];
}




/// Compute all-pair L. distance
vector<vector<int>> levenstein_all_pairs(vector<vector<int>> records) {
    int n = records.size();
    vector<vector<int>> dist_m(n, vector<int>(n)); // all zeroes

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for (int orig = 0; orig < n; ++orig) {
//        printf("orig = %d, threadId = %d \n", orig, omp_get_thread_num());
        for (int oth = orig + 1; oth < n; ++oth) {
            int l = levenstein(records[orig], records[oth]);
            //TODO: one record is enough
            dist_m[orig][oth] = l;
            dist_m[oth][orig] = l;
        }
    }
    return dist_m;
}


// return index of minimum
int find_min(vector<int>& distances, vector<bool>& in_MST) {
    int min = INT_MAX;
    int min_idx;
    int size = distances.size();
    #pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < size; ++i) {
        if (!in_MST[i]) {
            if (distances[i] < min ) {
                min_idx = i;
                min = distances[i];
            }
        }
    }
    return min_idx;
}

// chceme updatnout vzdalenost uzlu k MST
// index je nove pridany uzel
void update(vector<vector<int>>& dist_m, vector<bool>& in_MST, vector<int>& d, int index) {
    // projeď sousedy INDEXu, dle dist_m uprav vektor d aby zrcadlil pridani INDEXu do MST

    vector<int> neighs = dist_m[index]; // sousedi indexu

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for (int i = 0; i < neighs.size(); ++i) {
        if (!in_MST[i]) {
            if (neighs[i] < d[i])
                d[i] = neighs[i];           // pokud je v matici nizsi cena, pridavam do d
        }
    }
}

// record může být vzdálen 0 od MST
int prim(vector<vector<int>>& dist_m) {

    int total_cost = 0;
    vector<bool> in_MST(dist_m.size(), false);
    vector<int> d(dist_m.size(), INT_MAX);

    size_t MST_size = 1;
    int start = 0;                              // najdi kandidata do MST
    d[start] = 0;                               // setni cost
    in_MST[start] = true;                       // pridej do in_MST
    update(dist_m, in_MST, d, start);     // updatni vzdalenost sousedu

    while(MST_size < dist_m.size()) {
        int closest = find_min(d, in_MST);       // najdi kandidata do MST
        total_cost += d[closest];                       // updatni cost MST
        in_MST[closest] = true;                         // pridej do in_MST
        d[closest] = 0;                                 // setni cost
        update(dist_m, in_MST, d, closest); // updatni vzdalenost sousedu
        MST_size ++;
    }
    return total_cost;
}

int main(int argc, char *argv[]) {
    auto programArguments = ProgramArguments::Parse(argc, argv);
    // The input records, e.g., records[0] is the first record in the input file.
    vector<vector<int>> records = readRecords(programArguments.mInputFilePath);
    vector<vector<int>> dist_m = levenstein_all_pairs(records);

    // TODO: fill the treeCost variable with the MST of the records' edit distances graph.
    int treeCost = prim(dist_m);

    cout << treeCost << endl;
    writeCost(treeCost, programArguments.mOutputFilePath);
    cout << "\n";
    cout << records.size();
}

//int main1() {
//    readBins("2x5.bin");
//    readBins("2x10.bin");
//    readBins("5x5.bin");
//    readBins("5000x20.bin");
//}

//#pragma clang diagnostic pop