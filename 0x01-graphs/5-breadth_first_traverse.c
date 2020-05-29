#include "graphs.h"

/* void pq(queue_t *queue) */
/* { */
/*	edge_t *node; */

/*	node = queue->head; */

/*	printf("Printing queue\n"); */
/*	while (node) */
/*	{ */
/*		printf("Queue: [%lu] %s\n", node->dest->index, node->dest->content); */
/*		node = node->next; */
/*	} */
/* } */

/**
 * push - push vertex into @queue
 * @queue: queue
 * @v: vertex
 * Return: 1 on success, 0 on failure
*/
int push(queue_t *queue, vertex_t *v)
{
	edge_t *new;

	new = calloc(1, sizeof(*new));
	if (!new)
		return (0);
	new->dest = v;
	if (!queue->tail)
	{
		queue->head = queue->tail = new;
	}
	else
	{
		queue->tail->next = new;
		queue->tail = new;
	}
	queue->size += 1;
	return (1);
}

/**
 * pop - pop vertex from @queue
 * @queue: queue
 * Return: popped vertex on success, NULL on failure
*/
vertex_t *pop(queue_t *queue)
{
	vertex_t *v;
	edge_t *tmp;

	if (!queue || queue->size == 0 || !queue->head)
		return (NULL);
	v = queue->head->dest;
	tmp = queue->head;
	queue->head = queue->head->next;
	queue->size -= 1;
	if (queue->size == 0)
		queue->head = queue->tail = NULL;
	free(tmp);
	return (v);
}

/**
 * bfs - breadth first traversal of a graph
 * @vertex: starting vertex
 * @action: function to take action
 * @depth: current depth in bfs tree
 * @seen: table of seen vertices
 * Return: depth
*/
size_t bfs(vertex_t *vertex,
	   void (*action)(const vertex_t *v, size_t depth), size_t depth, int *seen)
{
	edge_t *edge;
	vertex_t *v;
	queue_t *queue;
	size_t dp = depth, size;

	queue = calloc(1, sizeof(*queue));
	if (!queue)
		return (0);
	if (!push(queue, vertex))
		return (0);
	while (queue->size)
	{
		size = queue->size;
		while (size--)
		{
			v = pop(queue);
			if (!v)
				return (0);
			action(v, dp);
			edge = v->edges;
			while (edge)
			{
				if (!seen[edge->dest->index])
				{
					seen[edge->dest->index] = 1;
					if (!push(queue, edge->dest))
						return (0);
				}
				edge = edge->next;
			}
		}
		dp += 1;
	}
	free(queue);
	return (dp == depth ? dp : dp - 1);
}

/**
 * breadth_first_traverse - depth first traverse of a graph
 * @graph: a graph to traverse
 * @action: function to take action
 * Return: max depth
*/
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	int *seen = NULL;
	vertex_t *v;
	size_t max = 0, ret;

	if (!graph || !action)
		return (0);
	seen = calloc(graph->nb_vertices, sizeof(*seen));
	if (!seen)
		return (0);
	v = graph->vertices;

	while (v)
	{
		if (!seen[v->index])
		{
			seen[v->index] = 1;
			ret = bfs(v, action, 0, seen);
			max = MAX(max, ret);
		}
		v = v->next;
	}
	free(seen);
	return (max);
}