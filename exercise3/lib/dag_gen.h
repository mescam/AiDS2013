#include <queue>
#include <vector>
#include <list>
typedef std::queue<int> bfs_queue;
int** dag_gen_matrix(int v);
int **dag_gen_matrix2(int v);
void dag_gen_free(int **matrix, int v);
std::list<int> bfs_unconnected(int **matrix, int v);
void bfs_linker(int **matrix, int v, int bfs_first)
