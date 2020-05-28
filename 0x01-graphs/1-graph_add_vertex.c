#include "graphs.h"

/**
 * graph_add_vertex - adds a new vertex to @graph
 * @graph: graph
 * @str: content of a new vertex
 * Return: pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *new;

	if (!graph || !str)
		return (NULL);
	vertex = graph->vertices;
	while (vertex)
	{
		if (!strcmp(vertex->content, str))
			return (NULL);
		if (vertex->next)
			vertex = vertex->next;
		else
			break;
	}

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = strdup(str);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->nb_edges = 0;
	new->edges = NULL;
	new->next = NULL;

	graph->nb_vertices += 1;
	if (!vertex)
	{
		new->index = 0;
		graph->vertices = new;
	}
	else
	{
		new->index = vertex->index + 1;
		vertex->next = new;
	}
	return (new);
}
