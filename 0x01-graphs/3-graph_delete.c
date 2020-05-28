#include "graphs.h"

/**
 * delete_edges - deletes all edges of a vertice
 * @head: edges
*/
void delete_edges(edge_t *head)
{
	edge_t *cur;

	if (!head)
		return;
	while (head)
	{
		cur = head;
		head = head->next;
		free(cur);
	}
}

/**
 * graph_delete - delete a graph
 * @graph: a graph
*/
void graph_delete(graph_t *graph)
{
	vertex_t *cur, *vertices;

	if (!graph)
		return;

	vertices = graph->vertices;
	while (vertices)
	{
		cur = vertices;
		vertices = vertices->next;
		free(cur->content);
		delete_edges(cur->edges);
		free(cur);
	}
	free(graph);
}
