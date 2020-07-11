#include "pathfinding.h"
#include "queues.h"

/**
 * create_point - creates a point
 * @x: X coordinate
 * @y: Y coordinate
 * Return: a new point or NULL if failed
*/
point_t *create_point(int x, int y)
{
	point_t *p;

	p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	return (p);
}

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
 * backtracking_helper - backtracking helper function to find
 * a solution to a maze
 * @queue: queue with points
 * @visited: visited array
 * @map: map or maze
 * @rows: height of @map
 * @cols: width of @map
 * @x: current X coordinate
 * @y: current Y coordinate
 * @target: target point
 * Return: queue with points or NULL if failed
*/
queue_t *backtracking_helper(queue_t **queue, int *visited, char **map,
			     int rows, int cols, int x, int y,
			     point_t const *target)
{
	queue_t *q;
	point_t *p;

	if (x < 0 || x >= cols || y < 0 || y >= rows ||
	    map[y][x] == '1' || *(visited + y * cols + x) == 1)
	{
		queue_free(queue);
		return (NULL);
	}
	if (!*queue)
		*queue = queue_create();
	if (!*queue)
		return (NULL);
	p = create_point(x, y);
	if (!p)
	{
		queue_free(queue);
		return (NULL);
	}
	printf("Checking coordinates [%d, %d]\n", x, y);
	queue_push_back(*queue, p);
	if (x == target->x && y == target->y)
		return (*queue);
	*(visited + y * cols + x) = 1;
	q = queue_create();
	if (!q)
	{
		queue_free(queue);
		return (NULL);
	}
	if (backtracking_helper(&q, visited, map, rows, cols, x + 1, y, target))
		return (merge_queue(*queue, q));
	if (backtracking_helper(&q, visited, map, rows, cols, x, y + 1, target))
		return (merge_queue(*queue, q));
	if (backtracking_helper(&q, visited, map, rows, cols, x - 1, y, target))
		return (merge_queue(*queue, q));
	if (backtracking_helper(&q, visited, map, rows, cols, x, y - 1, target))
		return (merge_queue(*queue, q));
	*(visited + y * cols + x) = 0, queue_free(queue);
	return (NULL);
}

/**
 * backtracking_array - backtracking function to find
 * a solution to a maze
 * @map: map or maze
 * @rows: height of @map
 * @cols: width of @map
 * @start: start position on the @map
 * @target: target point
 * Return: queue with points or NULL if failed
*/
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	int *visited;
	queue_t *queue;

	visited = calloc(rows * cols, sizeof(*visited));
	queue = queue_create();
	if (!queue)
		return (NULL);
	queue = backtracking_helper(&queue, visited, map, rows, cols,
				    start->x, start->y, target);
	free(visited);
	return (queue);
}
