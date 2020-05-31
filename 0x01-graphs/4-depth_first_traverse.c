#include "graphs.h"
#include <sys/types.h>

/**
 * check_and_mark - check if @vertex is visited, mark if not
 * @seen: seen table
 * @vertex: vertex to check
 * Return: 1 on success when @vertex not visited, 0 on failure
 */
int check_and_mark(int *seen, vertex_t *vertex)
{
	if (!vertex || !seen)
		return (0);

	if (seen[vertex->index])
		return (0);
	seen[vertex->index] = 1;
	return (1);
}

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
	size_t dp, tmp;

	if (!vertex || !check_and_mark(seen, vertex))
		return (0);
	action(vertex, depth);
	edge = vertex->edges;
	dp = 0;
	while (edge)
	{
		tmp = dfs(edge->dest, action, depth + 1, seen);
		dp = MAX(dp, tmp);
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
	size_t depth = 0, tmp;
	vertex_t *v;

	if (!graph || !action)
		return (0);
	seen = calloc(graph->nb_vertices, sizeof(*seen));
	if (!seen)
		return (0);
	v = graph->vertices;

	tmp = dfs(v, action, 0, seen);
	depth = MAX(depth, tmp);
	v = v->next;
	free(seen);
	return (depth > 0 ? depth - 1 : depth); /* TODO: Better way */
}
