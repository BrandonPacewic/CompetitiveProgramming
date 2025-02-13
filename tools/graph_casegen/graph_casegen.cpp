// Copyright (c) Brandon Pacewic
// SPDX-License-Identifier: MIT

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "tree.h"

using namespace std;
using namespace cpl;

inline pair<vector<Edge<int>>, vector<Edge<int>>> large_test_case_pair() {
    vector<Edge<int>> graph;
    constexpr int     V = 100;
    graph.reserve((V * (V - 1)) / 2);
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            graph.push_back({i, j, static_cast<int>((i * j) % 100 + 1)});
        }
    }

    vector<Edge<int>> mst;
    kruskal(100, graph.begin(), graph.end(), back_inserter(mst));

    return {graph, mst};
}

inline pair<vector<Edge<int>>, vector<Edge<int>>> large_sparse_test_case_pair() {
    constexpr int     V = 1000;
    vector<Edge<int>> graph;
    graph.reserve(2 * V);

    for (int i = 0; i < V - 1; ++i) {
        graph.push_back({i, i + 1, (i % 100) + 1});

        if (i < V - 2) {
            graph.push_back({i, i + 2, static_cast<int>(((int64_t) i * i) % 100 + 1)});
        }
    }

    for (int i = 0; i < V / 2; ++i) {
        graph.push_back({i, V - i - 1, static_cast<int>(((int64_t) i * V) % 100 + 1)});
    }

    vector<Edge<int>> mst;
    kruskal(V, graph.begin(), graph.end(), back_inserter(mst));

    return {graph, mst};
}

int main() {
    cout << "Generating large test case...\n";
    auto [graph, mst] = large_test_case_pair();
    ofstream large_file("large_test_case.txt");

    large_file << "constexpr std::pair<std::vector<cpl::Edge<int>>, std::vector<cpl::Edge<int>>> large_test_case() {\n "
                  "   return {\n        {\n";
    for (const auto& edge : graph) {
        large_file << "            {" << edge.from << ", " << edge.to << ", " << edge.weight << "},\n";
    }

    large_file << "        },\n        {\n";
    for (const auto& edge : mst) {
        large_file << "            {" << edge.from << ", " << edge.to << ", " << edge.weight << "},\n";
    }

    large_file << "        }\n    };\n}\n";

    cout << "Generating large sparse test case...\n";
    auto [graph_sparse, mst_sparse] = large_sparse_test_case_pair();
    ofstream large_sparse_file("large_sparse_test_case.txt");

    large_sparse_file << "constexpr std::pair<std::vector<cpl::Edge<int>>, std::vector<cpl::Edge<int>>> "
                         "large_sparse_test_case() {\n    return {\n        {\n";
    for (const auto& edge : graph_sparse) {
        large_sparse_file << "            {" << edge.from << ", " << edge.to << ", " << edge.weight << "},\n";
    }

    large_sparse_file << "        },\n        {\n";
    for (const auto& edge : mst_sparse) {
        large_sparse_file << "            {" << edge.from << ", " << edge.to << ", " << edge.weight << "},\n";
    }

    large_sparse_file << "        }\n    };\n}\n";

    large_file.close();
    large_sparse_file.close();

    return 0;
}
