#include <iostream>
#include "Graph.hpp"

using std::vector;
using std::cout;
using std::cin;

int main()
{
	Graph<int> graph;
	for (int i = 1; i < 8; i++) {
		graph.AddVertex(i);
	}

	// Re-create graph in the textbook
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 2);
	graph.AddEdge(0, 3);
	graph.AddEdge(1, 3);
	graph.AddEdge(1, 4);
	graph.AddEdge(2, 5);
	graph.AddEdge(3, 2);
	graph.AddEdge(3, 5);
	graph.AddEdge(3, 6);
	graph.AddEdge(4, 3);
	graph.AddEdge(4, 6);
	graph.AddEdge(6, 5);

	vector<int> order = graph.TopologicalSort();
	for (auto index : order) {
		cout << graph.GetData(index) << " ";
	}

	cout << std::endl;
	cin.get();

	return 0;
}
