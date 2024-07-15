#include <vector>
#include <omp.h>

#include "Utils.h"

#include <bits/stdc++.h>
using namespace std;

int V;

int minKey(int key[], bool in_MST[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!in_MST[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

const int printMST(int from[], const vector<vector<int>>& graph) {
    int sum = 0;
    for (int i = 0; i < V; i++)
        sum += graph[i][from[i]];
    return sum;
}

int primMST(const vector<vector<int>>& graph) {
    V = graph.size();
    int from[V];
    int key[V];
    bool in_MST[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, in_MST[i] = 0;

    key[0] = 0;
    from[0] = -1;

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        const int u = minKey(key, in_MST);
        in_MST[u] = true;
        for (int v = 0; v < V; v++)
            if (!in_MST[v] && graph[u][v] < key[v])
                from[v] = u, key[v] = graph[u][v];
    }
    return printMST(from, graph);
}


/// Distance of other record from original record
// https://www.geeksforgeeks.org/edit-distance-dp-5/
const int levenstein(const vector<int>& original, const vector<int>& other) {
    const int m = original.size();
    const int n = other.size();
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
vector<vector<int>> levenstein_all_pairs(const vector<vector<int>>& records) {
    int n = records.size();
    vector<vector<int>> dist_m(n, vector<int>(n)); // all zeroes

    #pragma omp parallel for schedule(dynamic)
    for (int orig = 0; orig < n; ++orig) {
        for (int oth = orig + 1; oth < n; ++oth) {
            const int l = levenstein(records[orig], records[oth]);
            if (orig < oth) {
                dist_m[orig][oth] = l;
                dist_m[oth][orig] = l;
            }
        }
    }
    return dist_m;
}


// return index of minimum
int find_min(vector<int>& distances, vector<bool>& in_MST) {
    int min = INT_MAX;
    int min_idx;
    int size = distances.size();
    for (int i = 0; i < size; ++i) {
        if (!in_MST[i]) {
            if (distances[i] < min) {
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
            #pragma omp critical
            {
                if (neighs[i] < d[i])
                    d[i] = neighs[i];           // pokud je v matici nizsi cena, pridavam do d
            }
        }
    }
}

// record může být vzdálen 0 od MST
int prim(vector<vector<int>>& dist_m) {

    int total_cost = 0;
    vector<bool> in_MST(dist_m.size(), false);
    vector<int> d(dist_m.size(), INT_MAX);

    int start = 0;                              // najdi kandidata do MST
    d[start] = 0;                               // setni cost
    in_MST[start] = true;                       // pridej do in_MST
//    update(dist_m, in_MST, d, start);     // updatni vzdalenost sousedu

    for (int i = 0; i < dist_m.size()-1; ++i) {
        int closest = find_min(d, in_MST);       // najdi kandidata do MST
        total_cost += d[closest];                       // updatni cost MST
        in_MST[closest] = true;                         // pridej do in_MST
        d[closest] = 0;                                 // setni cost
//        update(dist_m, in_MST, d, closest); // updatni vzdalenost sousedu
        for (int i = 0; i < dist_m.size(); ++i)
            if (!in_MST[i] && dist_m[closest][i] < d[i])
                d[i] = dist_m[closest][i];// pokud je v matici nizsi cena, pridavam do d

    }
    return total_cost;
}

int main(int argc, char *argv[]) {
    Stopwatch s = Stopwatch();
//    for (int i = 0; i < 10; ++i) {
        
    s.start();
    auto programArguments = ProgramArguments::Parse(argc, argv);
    vector<vector<int>> records = readRecords(programArguments.mInputFilePath);
    s.stop();
    printf("readRecords %d ms\n", s.duration());

    s.start();
    vector<vector<int>> dist_m = levenstein_all_pairs(records);
    s.stop();
    printf("levenstein %d ms\n", s.duration());

    s.start();
    int treeCost = primMST(dist_m);
    s.stop();
    printf("prim %d ms\n", s.duration());

    cout << treeCost << endl;
    writeCost(treeCost, programArguments.mOutputFilePath);
    cout << "\n";
    cout << records.size();
//    }

}

//int main1() {
//    readBins("2x5.bin");
//    readBins("2x10.bin");
//    readBins("5x5.bin");
//    readBins("5000x20.bin");
//}

