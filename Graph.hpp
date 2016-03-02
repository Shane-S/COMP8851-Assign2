#include <vector>
#include <queue>
#include <cstdlib>
#include <unordered_map>
#include "pb_graph.h"

template <typename T>
class Graph
{
public:
	Graph()
		: _graph(pb_graph_create()) {}

	~Graph()
	{
		if (_graph != nullptr);
		pb_graph_free(_graph, 1);
	}

	Graph(Graph&& other)
		: _graph(other._graph)
	{
		other._graph = nullptr;
	}

	Graph(Graph& other) 
		: _graph(pb_graph_create())
	{
		// Make a deep copy of the graph
		for (int i = 0; i < other._graph->size; i++) {
			void *dataCopy = (T*)malloc(sizeof(T));
			memcpy(dataCopy, other._graph->vertices[i]->data, sizeof(T));
			
			pb_vertex* vert = pb_vertex_create((void*)dataCopy);
			pb_graph_add_vertex(_graph, vert);
			for (int j = 0; j < other._graph->vertices[i]->adj_size; j++) {
				pb_graph_add_edge(_graph, i, other._graph->vertices[i]->adjacent[j]);
			}
		}
	}

	Graph& operator=(Graph other)
	{
		return *this;
	}
	
	void AddVertex(T data)
	{
		T* contents = new T(data);
		pb_vertex *vert = pb_vertex_create((void*)contents);
		pb_graph_add_vertex(_graph, vert);
	}

	void AddEdge(size_t from, size_t to)
	{
		pb_graph_add_edge(_graph, from, to);
	}

	void RemoveVertex(size_t vert)
	{
		pb_graph_remove_vertex(_graph, vert);
	}

	void RemoveEdge(size_t from, size_t to)
	{
		pb_graph_remove_edge(_graph, from, to);
	}

	T& GetData(size_t vert)
	{
		return *((T*)_graph->vertices[vert]->data);
	}

	size_t Size() const
	{
		return _graph->size;
	}

	std::vector<int> TopologicalSort() const
	{
		int *inDegree = new int[Size()]();
		std::vector<int> order;

		// Get in-degree of every vertex
		for (int i = 0; i < _graph->size; ++i) {
			pb_vertex *v = _graph->vertices[i];
			for (int j = 0; j < v->adj_size; j++) {
				inDegree[v->adjacent[j]]++;
			}
		}

		std::queue<int> q;

		// Add all vertices with in-degree 0 to the queue
		for (int i = 0; i < _graph->size; ++i) {
			if (inDegree[i] == 0) q.emplace(i);
		}

		while (!q.empty()) {
			int current = q.front();
			q.pop();
			order.push_back(current);
			
			pb_vertex *v = _graph->vertices[current];
			for (int i = 0; i < v->adj_size; ++i) {
				int adj = v->adjacent[i];
				inDegree[adj]--;
				if (inDegree[adj] == 0) q.emplace(adj);
				// Shouldn't need to remove since vertices processed multiple times will end up at -1
				// Inefficient, but it avoids a lot of problems
			}
		}

		delete inDegree;
		return order;
	}

private:
	pb_graph *_graph;
};