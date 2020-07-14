#include "pathfinding.h"
#include "queues.h"

/**
 * add_point - creates a point and adds to a queue
 * @queue: queue
 * @x: X coordinate
 * @y: Y coordinate
 * Return: 1 if success, 0 if failed
 */
int add_point(queue_t **queue, int x, int y)
{
	point_t *p;

	p = malloc(sizeof(*p));
	if (!p)
		return (0);
	p->x = x;
	p->y = y;
	queue_push_front(*queue, p);
	return (1);
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
int backtracking_helper(queue_t **queue, int *visited, char **map, int rows,
			int cols, int x, int y, point_t const *target)
{
	int arr[][2] = {RIGHT, BOTTOM, LEFT, TOP}, i;

	if (x < 0 || x >= cols || y < 0 || y >= rows ||
	    map[y][x] == '1' || *(visited + y * cols + x) == 1)
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y)
		return (add_point(queue, x, y));
	*(visited + y * cols + x) = 1;

	for (i = 0; i < 4; ++i)
		if (backtracking_helper(queue, visited, map, rows, cols,
					x + arr[i][0], y + arr[i][1], target))
			return (add_point(queue, x, y));
	return (0);
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
	int ret;

	if (!map || !*map || !start || !target || rows < 1 || cols < 1)
		return (NULL);
	visited = calloc(rows * cols, sizeof(*visited));
	if (!visited)
		return (NULL);
	queue = queue_create();
	if (!queue)
	{
		free(visited);
		return (NULL);
	}
	ret = backtracking_helper(&queue, visited, map, rows, cols,
				  start->x, start->y, target);
	if (!ret)
	{
		queue_delete(queue);
		queue = NULL;
	}
	free(visited);
	return (queue);
}
