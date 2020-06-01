#include "graphs.h"

/**
 * dfs - depth first traversal of a graph
 * @vertex: starting vertex
 * @action: function to take action
 * @depth: current depth in bfs tree
 * @seen: table of seen vertices
 * @max: max depth
 * Return: depth
 */
void dfs(vertex_t *vertex,
	 void (*action)(const vertex_t *v, size_t depth), size_t depth,
	   int *seen, size_t *max)
{
	edge_t *edge;

	if (!vertex || seen[vertex->index])
		return;
	seen[vertex->index] = 1;
	action(vertex, depth);
	*max = MAX(depth, *max);
	++depth;
	edge = vertex->edges;
	while (edge)
	{
		dfs(edge->dest, action, depth, seen, max);
		edge = edge->next;
	}
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
	size_t max = 0;

	if (!graph || !action)
		return (0);
	seen = calloc(graph->nb_vertices, sizeof(*seen));
	if (!seen)
		return (0);
	dfs(graph->vertices, action, 0, seen, &max);
	free(seen);
	return (max);
}
