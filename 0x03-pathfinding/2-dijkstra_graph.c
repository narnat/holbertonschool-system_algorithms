#include "graphs.h"
#include "pathfinding.h"
#include "queues.h"
#include <limits.h>
#include <string.h>

vertex_t *get_min(int *set, size_t *dist, graph_t *graph)
{
	size_t min = ULONG_MAX;
	size_t idx = ULONG_MAX, i;
	vertex_t *v = graph->vertices;

	for (i = 0; i < graph->nb_vertices; ++i)
		if (!set[i] && min > dist[i])
			min = dist[i], idx = i;
	if (idx == ULONG_MAX)
		return (NULL);
	for (i = 0; i < idx; ++i)
		v = v->next;
	return (v);

}

void calculate_distance(graph_t *graph, vertex_t const *start,
			int *set, size_t *dist, vertex_t **parent)
{
	vertex_t *vertex;
	edge_t *edge;

	if (!graph || !set || !dist)
		return;
	while ((vertex = get_min(set, dist, graph)))
	{
		/* vertex = get_min(set, dist, graph); */
		/* if (!vertex) */
		/* 	break; */
		set[vertex->index] = 1;
		edge = vertex->edges;
		printf("Checking %s, distance from %s is %lu\n",
		       vertex->content, start->content, dist[vertex->index]);
		for (edge = vertex->edges; edge; edge = edge->next)
		{
			if (!set[edge->dest->index] && dist[edge->dest->index]
			    > dist[vertex->index] + edge->weight)
			{
				parent[edge->dest->index] = vertex;
				dist[edge->dest->index] = dist[vertex->index] + edge->weight;
			}
		}
	}
}

queue_t *get_path(vertex_t **parent, vertex_t const *target)
{
	size_t i = target->index;
	queue_t *q;

	q = queue_create();
	if (!q)
	{
		free(parent);
		return (NULL);
	}
	if (!parent[i])
	{
		free(q);
		free(parent);
		return (NULL);
	}
	if (!queue_push_front(q, strdup(target->content)))
	{
		free(parent);
		queue_delete(q);
		return (NULL);
	}
	while (parent[i])
	{
		if (!queue_push_front(q, strdup(parent[i]->content)))
		{
			free(parent);
			queue_delete(q);
			return (NULL);
		}
		i = parent[i]->index;
	}
	free(parent);
	return (q);
}

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
int *set;
		size_t *dist;
		vertex_t **parent;

		if (!graph || !start || !target)
			return (NULL);
		set = calloc(graph->nb_vertices, sizeof(*set));
		if (!set)
		{
			return (NULL);
	}
	dist = malloc(graph->nb_vertices * sizeof(*dist));
	if (!dist)
	{
		free(set);
		return (NULL);
	}
	parent = calloc(graph->nb_vertices, sizeof(**parent));
	if (!parent)
	{
		free(set);
		free(dist);
		return (NULL);
	}
	/* Set all to UINT_MAX */
	memset(dist, 0xFF, graph->nb_vertices * sizeof(*dist));
	dist[start->index] = 0;
	calculate_distance(graph, start, set, dist, parent);
	free(set), free(dist);
	return (get_path(parent, target));
}
