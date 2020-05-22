# Graphs in C

## Tasks

### 0. Create graph mandatory

Write a function that allocates memory to store a graph_t structure, and initializes its content.

    Prototype: graph_t *graph_create(void);
    Your function must return a pointer to the allocated structure, or NULL on failure

``` shell
alex@~/0x01-graphs$ cat 0-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    printf("Successfully created graph\n");

    return (EXIT_SUCCESS);
}
alex@~/0x01-graphs$ gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-graph_create.c -o 0-graph_create
alex@~/0x01-graphs$ ./0-graph_create
Successfully created graph
alex@~/0x01-graphs$
```

Repo:

    GitHub repository: holbertonschool-system_algorithms
    Directory: 0x01-graphs
    File: 0-graph_create.c


### 1. Add a vertex mandatory

Write a function that adds a vertex to an existing graph

    Prototype: vertex_t *graph_add_vertex(graph_t *graph, const char *str);
    Where graph is a pointer to the graph to add the vertex to, and str is the string to store in the new vertex
    Your function must return a pointer to the created vertex, or NULL on failure
    The vertex must store a copy of the string str
    If a vertex in graph already stores the string str, your function must fail, and there must be no leak

NOTE: We will use our own graph_create function during the correction, meaning that your file 0-graph_create.c WON’T be compiled.

``` shell
alex@~/0x01-graphs$ cat 1-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    if (!graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    if (!graph_add_vertex(graph, "San Francisco"))
        fprintf(stderr, "Failed to add \"San Francisco\"\n");

    return (EXIT_SUCCESS);
}
alex@~/0x01-graphs$ gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c graph_create.c 1-graph_add_vertex.c graph_display.c -o 1-graph_add_vertex
alex@~/0x01-graphs$ ./1-graph_add_vertex
Number of vertices: 1
[0] San Francisco
Number of vertices: 8
[0] San Francisco
[1] Seattle
[2] New York
[3] Miami
[4] Chicago
[5] Houston
[6] Las Vegas
[7] Boston
Failed to add "San Francisco"
alex@~/0x01-graphs$
```

Repo:

    GitHub repository: holbertonschool-system_algorithms
    Directory: 0x01-graphs
    File: 1-graph_add_vertex.c


### 2. Add an edge mandatory

Write a function that adds an edge between two vertices to an existing graph

    Prototype: int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type);
    Where:
        graph is a pointer to the graph to add the edge to
        src is the string identifying the vertex to make the connection from
        dest is the string identifying the vertex to connect to
        type is the type of edge
            UNIDIRECTIONAL: Only one edge is created connecting src to dest
            BIDIRECTIONAL: Two edges are created, connecting src to dest AND dest to src.
    Your function must return 1 on success, or 0 on failure. On failure, no edge must have be created, and there must be no memory leak.
    If either src or dest are not found in any vertex of graph, your function must fail, and there must be no leak

NOTE: We will use our own graph_create and graph_add_vertex functions during the correction, meaning that your files 0-graph_create.c and 1-graph_add_vertex.c WON’T be compiled.

``` shell
alex@~/0x01-graphs$ cat 2-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    return (EXIT_SUCCESS);
}
alex@~/0x01-graphs$ gcc -Wall -Wextra -Werror -pedantic -g3 2-main.c graph_create.c graph_add_vertex.c 2-graph_add_edge.c graph_display.c -o 2-graph_add_edge
alex@~/0x01-graphs$ ./2-graph_add_edge
Number of vertices: 8
[0] San Francisco ->6->3->7
[1] Seattle ->4->3
[2] New York ->4->5
[3] Miami ->0->1
[4] Chicago ->2
[5] Houston ->1->2
[6] Las Vegas ->0->2
[7] Boston ->2->0
alex@~/0x01-graphs$
```

Repo:

    GitHub repository: holbertonschool-system_algorithms
    Directory: 0x01-graphs
    File: 2-graph_add_edge.c


### 3. Delete graph mandatory

Write a function that completely deletes a graph

    Prototype: void graph_delete(graph_t *graph);
    Your function must delete all the vertices and edges of the graph, and the graph itself

NOTE: We will use our own graph_create, graph_add_vertex and graph_add_edge functions during the correction, meaning that your files 0-graph_create.c, 1-graph_add_vertex.c and 2-graph_add_edge.c WON’T be compiled.

``` shell
alex@~/0x01-graphs$ cat 3-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    graph_delete(graph);

    return (EXIT_SUCCESS);
}
alex@~/0x01-graphs$ gcc -Wall -Wextra -Werror -pedantic -g3 3-main.c graph_create.c graph_add_vertex.c graph_add_edge.c 3-graph_delete.c graph_display.c -o 3-graph_delete
alex@~/0x01-graphs$ valgrind ./3-graph_delete
==9712== Memcheck, a memory error detector
==9712== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==9712== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==9712== Command: ./3-graph_delete
==9712==
Number of vertices: 8
[0] San Francisco ->6->3->7
[1] Seattle ->4->3
[2] New York ->4->5
[3] Miami ->0->1
[4] Chicago ->2
[5] Houston ->1->2
[6] Las Vegas ->0->2
[7] Boston ->2->0
==9712==
==9712== HEAP SUMMARY:
==9712==     in use at exit: 0 bytes in 0 blocks
==9712==   total heap usage: X allocs, X frees, Y bytes allocated
==9712==
==9712== All heap blocks were freed -- no leaks are possible
==9712==
==9712== For counts of detected and suppressed errors, rerun with: -v
==9712== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
alex@~/0x01-graphs$
```

Repo:

    GitHub repository: holbertonschool-system_algorithms
    Directory: 0x01-graphs
    File: 3-graph_delete.c


### 4. Depth-first traversal mandatory

Write a function that goes through a graph using the depth-first algorithm.

    Prototype: size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));
    Where:
        graph is a pointer to the graph to traverse. The traversal must start from the first vertex in the vertices list.
        action is a pointer to a function to be called for each visited vertex, its parameters are:
            v -> A const pointer to the visited vertex
            depth -> The depth of v, from the starting vertex
    Your function must return the biggest vertex depth (See example), or 0 on failure

NOTE: We will use our own graph_create, graph_add_vertex, graph_add_edge and graph_delete functions during the correction, meaning that your files 0-graph_create.c, 1-graph_add_vertex.c, 2-graph_add_edge.c and 3-graph_delete.c WON’T be compiled.

``` shell
alex@~/0x01-graphs$ cat 4-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * traverse_action - Action to be executed for each visited vertex
 * during traversal
 *
 * @v: Pointer to the visited vertex
 * @depth: Depth of the vertex in graph from vertex 0
 */
void traverse_action(const vertex_t *v, size_t depth)
{
    printf("%*s[%lu] %s\n", (int)depth * 4, "", v->index, v->content);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;
    size_t depth;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    printf("\nDepth First Traversal:\n");
    depth = depth_first_traverse(graph, &traverse_action);
    printf("\nDepth: %lu\n", depth);

    graph_delete(graph);

    return (EXIT_SUCCESS);
}
alex@~/0x01-graphs$ gcc -Wall -Wextra -Werror -pedantic -g3 4-main.c graph_create.c graph_add_vertex.c graph_add_edge.c graph_delete.c 4-depth_first_traverse.c graph_display.c -o 4-depth_first_traverse
alex@~/0x01-graphs$ ./4-depth_first_traverse
Number of vertices: 8
[0] San Francisco ->6->3->7
[1] Seattle ->4->3
[2] New York ->4->5
[3] Miami ->0->1
[4] Chicago ->2
[5] Houston ->1->2
[6] Las Vegas ->0->2
[7] Boston ->2->0

Depth First Traversal:
[0] San Francisco
    [6] Las Vegas
        [2] New York
            [4] Chicago
            [5] Houston
                [1] Seattle
                    [3] Miami
    [7] Boston

Depth: 5
alex@~/0x01-graphs$
```

Repo:

    GitHub repository: holbertonschool-system_algorithms
    Directory: 0x01-graphs
    File: 4-depth_first_traverse.c


### 5. Breadth-first traversal mandatory

Write a function that goes through a graph using the breadth-first algorithm.

    Prototype: size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth));
    Where:
        graph is a pointer to the graph to traverse. The traversal must start from the first vertex in the vertices list.
        action is a pointer to a function to be called for each visited vertex, its parameters are:
            v -> A const pointer to the visited vertex
            depth -> The depth of v, fron the starting vertex
    Your function must return the biggest vertex depth (See example), or 0 on failure

NOTE: We will use our own graph_create, graph_add_vertex, graph_add_edge and graph_delete functions during the correction, meaning that your files 0-graph_create.c, 1-graph_add_vertex.c, 2-graph_add_edge.c and 3-graph_delete.c WON’T be compiled.

``` shell
alex@~/0x01-graphs$ cat 5-main.c
#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * traverse_action - Action to be executed for each visited vertex
 * during traversal
 *
 * @v: Pointer to the visited vertex
 * @depth: Depth of the vertex in graph from vertex 0
 */
void traverse_action(const vertex_t *v, size_t depth)
{
    printf("%*s[%lu] %s\n", (int)depth * 4, "", v->index, v->content);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    graph_t *graph;
    size_t depth;

    graph = graph_create();
    if (!graph)
    {
        fprintf(stderr, "Failed to create graph\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_vertex(graph, "San Francisco") ||
        !graph_add_vertex(graph, "Seattle") ||
        !graph_add_vertex(graph, "New York") ||
        !graph_add_vertex(graph, "Miami") ||
        !graph_add_vertex(graph, "Chicago") ||
        !graph_add_vertex(graph, "Houston") ||
        !graph_add_vertex(graph, "Las Vegas") ||
        !graph_add_vertex(graph, "Boston"))
    {
        fprintf(stderr, "Failed to add vertex\n");
        return (EXIT_FAILURE);
    }

    if (!graph_add_edge(graph, "San Francisco", "Las Vegas", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Boston", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Miami", "San Francisco", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Houston", "Seattle", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Chicago", "New York", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Las Vegas", "New York", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Chicago", UNIDIRECTIONAL) ||
        !graph_add_edge(graph, "New York", "Houston", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "Seattle", "Miami", BIDIRECTIONAL) ||
        !graph_add_edge(graph, "San Francisco", "Boston", BIDIRECTIONAL))
    {
        fprintf(stderr, "Failed to add edge\n");
        return (EXIT_FAILURE);
    }

    graph_display(graph);

    printf("\nBreadth First Traversal:\n");
    depth = breadth_first_traverse(graph, &traverse_action);
    printf("\nDepth: %lu\n", depth);

    graph_delete(graph);

    return (EXIT_SUCCESS);
}
alex@~/0x01-graphs$ gcc -Wall -Wextra -Werror -pedantic -g3 5-main.c graph_create.c graph_add_vertex.c graph_add_edge.c graph_delete.c 5-breadth_first_traverse.c graph_display.c -o 5-breadth_first_traverse
alex@~/0x01-graphs$ ./5-breadth_first_traverse
Number of vertices: 8
[0] San Francisco ->6->3->7
[1] Seattle ->4->3
[2] New York ->4->5
[3] Miami ->0->1
[4] Chicago ->2
[5] Houston ->1->2
[6] Las Vegas ->0->2
[7] Boston ->2->0

Breadth First Traversal:
[0] San Francisco
    [6] Las Vegas
    [3] Miami
    [7] Boston
        [2] New York
        [1] Seattle
            [4] Chicago
            [5] Houston

Depth: 3
alex@~/0x01-graphs$
```

Repo:

    GitHub repository: holbertonschool-system_algorithms
    Directory: 0x01-graphs
    File: 5-breadth_first_traverse.c

#### Copyright © 2020 Holberton School. All rights reserved.
