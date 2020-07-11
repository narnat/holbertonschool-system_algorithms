#include "graphs.h"
#include "pathfinding.h"
#include "queues.h"

/**
 * merge_queue - merges two queues
 * @q1: first queue
 * @q2: second queue
 * Return: @q1 with merged @q2
 */
queue_t *merge_queue(queue_t *q1, queue_t *q2)
{
	q1->back->next = q2->front;
	q2->front->prev = q1->back;
	free(q2);
	return (q1);
}

/**
 * queue_free - frees queue and sets its pointer to NULL
 * @q: queue to be freed
 */
void queue_free(queue_t **q)
{
	queue_node_t *node, *tmp;

	if (*q)
	{
		node = (*q)->front;
		while (node)
		{
			tmp = node;
			node = node->next;
			free(tmp->ptr);
			free(tmp);
		}
		free(*q);
	}
	*q = NULL;
}

/**
 * backtrack_graph_helper - backtracking graph to find a path, helper function
 * @queue: queue of path so far
 * @seen: seen cities on the current path
 * @cur: current city (vertex)
 * @target: target city (vertex)
 * Return: queue of full path, NULL if failed
 */
queue_t *backtrack_graph_helper(queue_t **queue, int *seen, vertex_t const *cur,
				vertex_t const *target)
{
	queue_t *q = NULL;
	edge_t *edge;

	if (!target || !cur || !seen || seen[cur->index])
	{
		queue_free(queue);
		return (NULL);
	}
	if (!*queue)
		*queue = queue_create();
	if (!*queue)
		return (NULL);
	printf("Checking %s\n", cur->content);
	queue_push_back(*queue, strdup(cur->content));
	if (!strcmp(cur->content, target->content))
		return (*queue);
	seen[cur->index] = 1;
	edge = cur->edges;
	while (edge)
	{
		if (backtrack_graph_helper(&q, seen, edge->dest, target))
			return (merge_queue(*queue, q));
		edge = edge->next;
	}
	seen[cur->index] = 0;
	queue_free(queue);
	return (NULL);
}

/**
 * backtracking_graph - backtracking graph to find a path
 * between two vertices
 * @graph: graph of cities
 * @start: starting city (vertex)
 * @target: target city
*/
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	int *seen = NULL;
	queue_t *q = NULL;

	if (!graph || !start || !target)
		return (NULL);
	seen = calloc(graph->nb_vertices, sizeof(*seen));
	if (!seen)
		return (NULL);
	q = backtrack_graph_helper(&q, seen, start, target);
	free(seen);
	return (q);
}
