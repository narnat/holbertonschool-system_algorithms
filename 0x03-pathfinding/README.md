# Pathfinding
### Contains pathfinding algorithms like Dijkstra's shortest path and A* to get shortest path
## 0. Backtracking - Array
Write a function that searches for the first path from a starting point to a target point within a two-dimensional array.

    Prototype: queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target);
    Where:
        map is the pointer to a read-only two-dimensional array
            A 0 represents a walkable cell
            A 1 represents a blocked cell
        rows and cols are respectively the number of rows and columns of map
        start stores the coordinates of the starting point
        target stores the coordinates of the target point
    Your function must return a queue, in which each node is a point in the path from start to target (See example)
    You’ll have to use recursive backtracking to find the first working path from start to target
    For each visited cell, you’ll have to explore neighbour cells in the following order:
        RIGHT
        BOTTOM
        LEFT
        TOP
    You’ll have to print each visited cell as in the example below

## 1. Backtracking - Graph mandatory

Write a function that searches for the first path from a starting point to a target point in a graph.

    Prototype: queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);
    Where:
        graph is a pointer to the graph to go through
        start is a pointer to the starting vertex
        target is a pointer to the target vertex
    Your function must return a queue, in which each node is a char * corresponding to a vertex, forming a path from start to target (See example)
    You’ll have to use recursive backtracking to find the first working path from start to target
    You’ll have to print each visited vertex as in the example below

##  2. Dijkstra's - Graph mandatory

Write a function that searches for the shortest path from a starting point to a target point in a graph.

    Prototype: queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);
    Where:
        graph is a pointer to the graph to go through
        start is a pointer to the starting vertex
        target is a pointer to the target vertex
    Your function must return a queue, in which each node is a char * corresponding to a vertex, forming a path from start to target (See example)
    You’ll have to use Dijkstra’s algorithm to find the shortest path
    You’ll have to print each visited vertex as in the example below

## 3. A* - Graph #advanced

Write a function that searches for the shortest and fastest path from a starting point to a target point in a graph.

    Prototype: queue_t *a_star_graph(graph_t *graph, vertex_t const *start, vertex_t const *target);
    Where:
        graph is a pointer to the graph to go through
        start is a pointer to the starting vertex
        target is a pointer to the target vertex
    Your function must return a queue, in which each node is a char * corresponding to a vertex, forming a path from start to target (See example)
    You’ll have to use A* algorithm to find the shortest and fastest path, using the Euclidean distance to the target vertex as the heuristic
    You’ll have to print each visited vertex as in the example below
    You are allowed to use the math library (math.h). Your code will be linked with the math library using -lm
