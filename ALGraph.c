#define MaxVertexNum 100                        // 图中顶点数目的最大值
typedef struct ArcNode {                        // 边表结点
    int adjvex;                                 // 该弧所指向的顶点的位置，即AdjList中的索引下标
    struct ArcNode *next;                       // 指向下一条弧的指针
    // InfoType info ;                          // 网的权值
} ArcNode;

typedef char VertexType;
typedef struct VNode {                          // 顶点表结点
    VertexType data;                            // 顶点信息
    ArcNode *first;                             // 指向第一条依附该顶点的弧的指针
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList adjList;                            // 邻接表
    int vexnum, arcnum;                         // 图的顶点数和弧数
} ALGraph;                                      // ALGraph 是以邻接表存储的图类型

/// 从图中查找顶点索引
/// \param G
/// \param data
/// \return
int indexOfVex(ALGraph G, VertexType data) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.adjList[i].data == data) {
            return i;
        }
    }
    return -1;
}

/// 创建有向图
/// \param G
void createGraph(ALGraph *G) {
    printf("input arc num & vertex num:\n");
    scanf("%d%d", &G->arcnum, &G->vexnum);
    printf("input vertex list:\n");
    for (int i = 0; i < G->vexnum; i++) {
        scanf("%s", &G->adjList[i].data);
        G->adjList[i].first = NULL;
    }
    printf("input arc list:\n");
    VertexType v1, v2;
    int m, n;
    struct ArcNode *arcNode;
    for (int i = 0; i < G->arcnum; i++) {
        scanf("%c%c", &v1, &v2);
        // index of vertex
        m = indexOfVex(*G, v1);
        n = indexOfVex(*G, v2);
        // 有向图，添加m->n的信息
        arcNode = (struct ArcNode *) malloc(sizeof(struct ArcNode));
        arcNode->adjvex = n;
        arcNode->next = G->adjList[m].first;        // 头插法
        G->adjList[m].first = arcNode;
        // 无向图还需要添加n->m的信息
    }
}
