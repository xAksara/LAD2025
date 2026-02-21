#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned n;

enum Type {
    WALL,
    DOT,
    CORN
};

struct Edge {
    int v1, v2;
};

void get_neighbours(int v, int neigs[4]) {
    int row = v / n;
    int col = v % n;
    neigs[0] = (row > 0) ? v - n : -1;
    neigs[1] = (col > 0) ? v - 1 : -1;
    neigs[2] = (col < n-1) ? v + 1 : -1;
    neigs[3] = (row < n-1) ? v + n : -1;
}

int find(int v, int *v2comp) {
    while (v2comp[v] != v) {
        v = v2comp[v];
    }
    return v;
}

// total posible edges: 2 * n * (n - 1)
struct Edge *kraskal(size_t *size) {
    struct Edge edges[2 * n * (n - 1)];
    int edge_i = 0;
    for (int v = 0; v < n * n; ++v) {
        int row = v / n;
        int col = v % n;
        if (col < n - 1) { // right neigbour
            edges[edge_i].v1 = v;
            edges[edge_i++].v2 = v + 1;
        }
        if (row < n - 1) { // bottom neigbour
            edges[edge_i].v1 = v;
            edges[edge_i++].v2 = v + n;
        }
    }

    for (int i = edge_i - 1; i > 0; --i) { // shake
        int j = rand() % (i + 1);
        struct Edge tmp = edges[i];
        edges[i] = edges[j];
        edges[j] = tmp;
    }

    int v2comp[n * n];
    for (int i = 0; i < n * n; ++i) {
        v2comp[i] = i;
    }

    size_t min_edges = n * n - 1;
    size_t max_extra = 2 * n * (n - 1) - min_edges;
    size_t extra_edges = rand() % (max_extra + 1); // max(#edges) - min(#edges)
    *size = min_edges + extra_edges;
    struct Edge *result = malloc(*size * sizeof(struct Edge));
    size_t edges_added = 0;

    size_t i;
    for (i = 0; i < edge_i &&  edges_added < min_edges; ++i) {
        int v1 = edges[i].v1;
        int v2 = edges[i].v2;
        int comp1 = find(v1, v2comp);
        int comp2 = find(v2, v2comp);

        if (comp1 != comp2) {
            v2comp[comp1] = comp2;
            result[edges_added++] = edges[i];
        }
    }

    for (; i < edge_i && edges_added < *size; ++i) {
        result[edges_added++] = edges[i]; 
    }
    return result;
}

void draw(struct Edge *g, size_t g_size) {
    size_t size = 2 * n + 1;
    char field[size][size];
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            field[i][j] = '#';

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            field[2 * i + 1][2 * j + 1] = '.';

    for (size_t k = 0; k < g_size; ++k) {
        int v1 = g[k].v1;
        int v2 = g[k].v2;
        int row = v1 / n;
        int col = v1 % n;
        if (v2 == v1 + 1) {
            field[2 * row + 1][2 * col + 2] = '.';
        } else if (v2 == v1 + n) {
            field[2 * row + 2][2 * col + 1] = '.';
        }
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j)
            putchar(field[i][j]);
        putchar('\n');
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    n = 6;
    size_t size;
    struct Edge *graph = kraskal(&size);
    draw(graph, size);
    free(graph);
    return 0;
}