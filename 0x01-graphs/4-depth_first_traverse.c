#include "graphs.h"

/**
 * dfs - depth first traversal of a graph
 * @vertex: starting vertex
 * @action: function to take action
 * @depth: current depth in bfs tree
 * @seen: table of seen vertices
 * Return: depth
 */
size_t dfs(vertex_t *vertex,
	   void (*action)(const vertex_t *v, size_t depth), size_t depth, int *seen)
{
	edge_t *edge;
	size_t dp = 0, tmp;

	if (!vertex || seen[vertex->index])
		return (0);
	seen[vertex->index] = 1;
	action(vertex, depth);
	edge = vertex->edges;
	while (edge)
	{
		tmp = dfs(edge->dest, action, depth + 1, seen);
		dp = MAX(tmp, dp);
		edge = edge->next;
	}
	return (dp + 1);
}

/**
 * depth_first_traverse - depth first traversal of a graph
 * @graph: a graph to traverse
 * @action: function to take action
 * Return: max depth
 */
size_t depth_first_traverse(
	const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	int *seen = NULL;
	size_t depth = 0;

	if (!graph || !action)
		return (0);
	seen = calloc(graph->nb_vertices, sizeof(*seen));
	if (!seen)
		return (0);
	depth = dfs(graph->vertices, action, depth, seen);
	free(seen);
	return (depth - 1);
}
