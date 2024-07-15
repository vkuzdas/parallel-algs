#include <mpi.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

// Spot with permanent temperature on coordinates [x,y].
struct Spot {
    int mX;
    int mY;
    float mTemperature;

    bool operator==(const Spot &b) const {
        return (mX == b.mX) && (mY == b.mY);
    }
};

tuple<int, int, vector<Spot>> readInstance(string instanceFileName) {
    int width, height;
    vector<Spot> spots;
    string line;

    ifstream file(instanceFileName);
    if (file.is_open()) {
        int lineId = 0;
        while (std::getline(file, line)) {
            stringstream ss(line);
            if (lineId == 0) {
                ss >> width;
            } else if (lineId == 1) {
                ss >> height;
            } else {
                int i, j, temperature;
                ss >> i >> j >> temperature;
                spots.push_back({i, j, (float)temperature});
            }
            lineId++;
        }
        file.close();
    } else {
        throw runtime_error("It is not possible to open instance file!\n");
    }
    return make_tuple(width, height, spots);
}

void writeOutput(
        const int myRank,
        const int width,
        const int height,
        const string outputFileName,
        const vector<float> &temperatures) {
    // Draw the output image in Netpbm format.
    ofstream file(outputFileName);
    if (file.is_open()) {
        if (myRank == 0) {
            file << "P2\n" << width << "\n" << height << "\n" << 255 << "\n";
            for (auto temperature: temperatures) {
                file << (int)max(min(temperature, 255.0f), 0.0f) << " ";
            }
        }
    }
}

void printHelpPage(char *program) {
    cout << "Simulates a simple heat diffusion." << endl;
    cout << endl << "Usage:" << endl;
    cout << "\t" << program << " INPUT_PATH OUTPUT_PATH" << endl << endl;
}


float calculateDifference(vector<vector<float>> &temperaturesMatrix, vector<vector<int>> &hotspotsMatrix, int &width, int &height, int &startRow, int &endRow){
    float maxDiff = 0;

    for (int i = startRow; i <= endRow; i++) {
        for (int j = 0; j < width; j++) {
            if (hotspotsMatrix[i][j] != 1) {
                float sum = 0;
                int count = 0;

                sum += temperaturesMatrix[i][j];
                count++;

                if (i - 1 >= 0 && j - 1 >= 0) {
                    sum += temperaturesMatrix[i - 1][j - 1];
                    count++;
                }
                if (i - 1 >= 0) {
                    sum += temperaturesMatrix[i - 1][j];
                    count++;
                }
                if (i - 1 >= 0 && j + 1 < width) {
                    sum += temperaturesMatrix[i - 1][j + 1];
                    count++;
                }
                if (j - 1 >= 0) {
                    sum += temperaturesMatrix[i][j - 1];
                    count++;
                }
                if (j + 1 < width) {
                    sum += temperaturesMatrix[i][j + 1];
                    count++;
                }
                if (i + 1 < height && j - 1 >= 0) {
                    sum += temperaturesMatrix[i + 1][j - 1];
                    count++;
                }
                if (i + 1 < height) {
                    sum += temperaturesMatrix[i + 1][j];
                    count++;
                }
                if (i + 1 < height && j + 1 < width) {
                    sum += temperaturesMatrix[i + 1][j + 1];
                    count++;
                }
                float average = sum / count;
                maxDiff = max(abs(temperaturesMatrix[i][j] - average), maxDiff);
                temperaturesMatrix[i][j] = average;
            }
        }
    }

    return maxDiff;
}


int main(int argc, char **argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);
    int worldSize, myRank;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (argc == 1) {
        if (myRank == 0) {
            printHelpPage(argv[0]);
        }
        MPI_Finalize();
        exit(0);
    } else if (argc != 3) {
        if (myRank == 0) {
            printHelpPage(argv[0]);
        }
        MPI_Finalize();
        exit(1);
    }

    // Read the input instance.
    int width, height;  // Width and height of the matrix.
    vector<Spot> spots; // Spots with permanent temperature.
    if (myRank == 0) {
        tie(width, height, spots) = readInstance(argv[1]);
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();


    //-----------------------\\
    // Insert your code here \\
    //        |  |  |        \\
    //        V  V  V        \\

    MPI_Bcast(&height, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&width, 1, MPI_INT, 0, MPI_COMM_WORLD);

    vector<vector<int>> hotspotsMatrix(height, vector<int>(width, 0));
    vector<vector<float>> temperaturesMatrix(height, vector<float>(width, 128));


    if(myRank == 0){
        for (auto spot: spots) {
            temperaturesMatrix[spot.mY][spot.mX] = spot.mTemperature;
            hotspotsMatrix[spot.mY][spot.mX] = 1;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    for(int i = 0; i < height; i++){
        MPI_Bcast(&temperaturesMatrix[i][0], width, MPI_FLOAT, 0, MPI_COMM_WORLD);
    }

    for(int i = 0; i < height; i++){
        MPI_Bcast(&hotspotsMatrix[i][0], width, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int rowsPerProcessor = height / worldSize;
    int remainder = height % worldSize;
    int startRow = 0;
    int endRow = rowsPerProcessor - 1;
    int rootSize = rowsPerProcessor + remainder;

    if (myRank < remainder) {
        startRow = myRank * (rowsPerProcessor + 1);
        endRow = startRow + rowsPerProcessor;
    } else {
        startRow = myRank * rowsPerProcessor + remainder;
        endRow = startRow + rowsPerProcessor - 1;
    }

    float diff = 0;
    float maxDiff = 1;

    MPI_Bcast(&rowsPerProcessor, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&remainder, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    while (maxDiff > 0.0001) {
        if (myRank > 0) {
            MPI_Sendrecv(&temperaturesMatrix[startRow][0],
                         width,
                         MPI_FLOAT,
                         myRank - 1,
                         1,
                         &temperaturesMatrix[startRow - 1][0],
                         width,
                         MPI_FLOAT,
                         myRank - 1,
                         2,
                         MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
        }
        if (myRank < worldSize - 1) {
            MPI_Sendrecv(&temperaturesMatrix[endRow][0],
                         width,
                         MPI_FLOAT,
                         myRank + 1,
                         2,
                         &temperaturesMatrix[endRow + 1][0],
                         width,
                         MPI_FLOAT,
                         myRank + 1,
                         1,
                         MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
        }

        MPI_Barrier(MPI_COMM_WORLD);

        diff = calculateDifference(temperaturesMatrix, hotspotsMatrix, width, height, startRow, endRow);
        MPI_Allreduce(&diff, &maxDiff, 1, MPI_FLOAT, MPI_MAX, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    // TODO: Fill this array on processor with rank 0. It must have height * width elements and it contains the
    // linearized matrix of temperatures in row-major order
    // (see https://en.wikipedia.org/wiki/Row-_and_column-major_order)
    vector<float> temperatures(width * height);

    vector<float> localTemperatures;

    if (myRank == 0) {
        localTemperatures = vector<float>(width * rootSize);
        int index = 0;
        for (int row = 0; row < rootSize; row++) {
            for (int col = 0; col < width; col++) {
                localTemperatures[index] = temperaturesMatrix[row][col];
                index++;
            }
        }

    } else {
        localTemperatures = vector<float>(width * rowsPerProcessor);
        int index = 0;
        for (int row = startRow; row <= endRow; row++) {
            for (int col = 0; col < width; col++) {
                localTemperatures[index] = temperaturesMatrix[row][col];
                index++;
            }
        }
    }

    MPI_Gather(&localTemperatures[0],localTemperatures.size(),MPI_FLOAT,&temperatures[0],localTemperatures.size(),MPI_FLOAT,0,MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    //-----------------------\\

    double totalDuration = duration_cast<duration<double>>(high_resolution_clock::now() - start).count();
    cout << "computational time: " << totalDuration << " s" << endl;

    if (myRank == 0) {
        string outputFileName(argv[2]);
        writeOutput(myRank, width, height, outputFileName, temperatures);
    }

    MPI_Finalize();
    return 0;
}

