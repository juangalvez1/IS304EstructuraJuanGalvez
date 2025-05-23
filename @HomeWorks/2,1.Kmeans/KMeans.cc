#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Point
{
public:
    vector<double> features;
    int cluster_id;

    Point(const vector<double> &f) : features(f), cluster_id(-1) {}
};

class KMeans
{
private:
    int k;
    int max_iters;
    vector<vector<double>> centroids;

    double euclideanDistance(const vector<double> &a, const vector<double> &b)
    {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); ++i)
            sum += pow(a[i] - b[i], 2);
        return sqrt(sum);
    }

    void assignClusters(vector<Point> &points)
    {
        for (auto &point : points)
        {
            double min_dist = numeric_limits<double>::max();
            int best_cluster = -1;
            for (int i = 0; i < k; ++i)
            {
                double dist = euclideanDistance(point.features, centroids[i]);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    best_cluster = i;
                }
            }
            point.cluster_id = best_cluster;
        }
    }

    void updateCentroids(vector<Point> &points)
    {
        vector<vector<double>> new_centroids(k, vector<double>(points[0].features.size(), 0.0));
        vector<int> counts(k, 0);

        for (const auto &point : points)
        {
            for (size_t j = 0; j < point.features.size(); ++j)
                new_centroids[point.cluster_id][j] += point.features[j];
            counts[point.cluster_id]++;
        }

        for (int i = 0; i < k; ++i)
        {
            if (counts[i] == 0)
                continue;
            for (size_t j = 0; j < new_centroids[i].size(); ++j)
                new_centroids[i][j] /= counts[i];
        }

        centroids = new_centroids;
    }

public:
    KMeans(int k, int max_iters) : k(k), max_iters(max_iters) {}

    void fit(vector<Point> &points)
    {
        centroids.clear();
        srand(time(0));
        for (int i = 0; i < k; ++i)
        {
            int index = rand() % points.size();
            centroids.push_back(points[index].features);
        }

        for (int iter = 0; iter < max_iters; ++iter)
        {
            assignClusters(points);
            updateCentroids(points);
        }
    }

    void printResults(const vector<Point> &points)
    {
        vector<int> cluster_counts(k, 0);

        for (const auto &point : points)
        {
            cluster_counts[point.cluster_id]++;
            cout << "Cluster " << point.cluster_id << ": ";
            for (double val : point.features)
                cout << val << " ";
            cout << endl;
        }

        cout << "\n--- Resumen por Clúster ---\n";
        for (int i = 0; i < k; ++i)
        {
            cout << "Clúster " << i << ": " << cluster_counts[i] << " elementos\n";
        }

        cout << "\n--- Centroides Finales ---\n";
        for (int i = 0; i < k; ++i)
        {
            cout << "Clúster " << i << " centroide: ";
            for (double val : centroids[i])
                cout << val << " ";
            cout << endl;
        }
    }
};

vector<Point> loadData(const string &filename)
{
    ifstream file(filename);
    string line;
    vector<Point> data;

    bool header_skipped = false;

    while (getline(file, line))
    {
        if (!header_skipped)
        {
            header_skipped = true;
            continue;
        }

        stringstream ss(line);
        string cell;
        vector<double> features;
        int col = 0;

        while (getline(ss, cell, '\t'))
        {
            // Column indices: Income = 4, MntWines = 9 to MntGoldProds = 14
            if (col == 4 || (col >= 9 && col <= 14))
            {
                try
                {
                    double val = cell.empty() ? 0.0 : stod(cell);
                    features.push_back(val);
                }
                catch (...)
                {
                    features.push_back(0.0); // fallback for non-numeric or missing values
                }
            }
            col++;
        }

        if (!features.empty())
        {
            data.emplace_back(features);
        }
    }

    return data;
}

int main()
{
    vector<Point> data = loadData("KMeansDataSet.txt");
    if (data.empty())
    {
        cerr << "No data loaded. Verifica el archivo.\n";
        return 1;
    }

    KMeans kmeans(3, 100);
    kmeans.fit(data);
    kmeans.printResults(data);

    return 0;
}
