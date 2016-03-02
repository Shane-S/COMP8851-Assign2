#include <iostream>
#include <algorithm>
#include <random>
#include "Graph.hpp"
#include "CTimer.h"

using std::vector;
using std::cout;
using std::cin;

bool Naive_K_Sum(vector<int> & numbers, int k)
{
	size_t size = numbers.size();
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (numbers[i] + numbers[j] == k) return true;
		}
	}
	return false;
}

bool Fast_K_Sum(vector<int> & numbers, int k)
{
	std::sort(numbers.begin(), numbers.end());
	for (auto i : numbers)
	{
		int tofind = k - i;
		if (std::binary_search(numbers.begin(), numbers.end(), tofind)) return true;
	}
	return false;
}

void Question_7_53()
{
	// Not really the best demo since the other one could theoretically find the combination
	// very early on depending on the input; it should be run multiple times
	vector<int> numbers;
	CTimer timer;

	numbers.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		numbers.push_back(rand());
	}

	int num = rand();
	
	double naive;
	timer.Start();
	Naive_K_Sum(numbers, num);
	timer.End();
	timer.Diff(naive);

	double fast;
	timer.Start();
	Fast_K_Sum(numbers, num);
	timer.End();
	timer.Diff(fast);

	cout << "Question 7.53: Naive time: " << naive << "s; Fast time: " << fast << "s" << std::endl;
}

void Question_9_3() 
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

	cout << "Question 9.3: ";
	vector<int> order = graph.TopologicalSort();
	for (auto index : order) {
		cout << graph.GetData(index) << " ";
	}
}

int main()
{
	Question_7_53();
	cout << std::endl;

	Question_9_3();
	cout << std::endl;

	cin.get();
	return 0;
}
