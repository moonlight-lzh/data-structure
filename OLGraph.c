#define MAX_VERTEX_NUM  100     // 顶点结点最大数量
typedef int InfoType;           // 弧上权值类型
typedef char VertexType;        // 顶点中数据的类型

/**弧结点*/
struct ArcNode {
    int tailvex;                // 该弧的弧尾结点在图中的位置
    int headvex;                // 该弧的弧头结点在图中的位置
    struct ArcNode *hlink;      // 下一条与该弧有相同弧头结点的弧
    struct ArcNode *tlink;      // 下一条与该弧有相同弧尾结点的弧
    InfoType info;              //弧的相关信息
};

/**顶点结点*/
struct VertexNode {
    VertexType data;            //数据
    struct ArcNode *firstin;    //第一条以该节点为弧尾的弧
    struct ArcNode *firstout;   //第一条以该结点为弧头的弧
} VertexNode;

/**十字链表存储结构的有向图*/
typedef struct {
    struct VertexNode xlist[MAX_VERTEX_NUM];   // 存储顶点的结构体数组
    int vexnum;       // 顶点数
    int arcnum;       // 弧数
} OLGraph;

/// 定位顶点
/// \param G
/// \param data
/// \return
int locateVex(OLGraph G, VertexType data) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.xlist[i].data == data) {
            return i;
        }
    }
    return -1;
}

/// 创建十字链表的有向图
/// \param G
void createGraph(OLGraph *G) {
    printf("input vertex num & arc num\n");
    scanf("%d%d", &G->vexnum, &G->arcnum);
    printf("input vertex list:\n");
    for (int i = 0; i < G->vexnum; ++i) {
        scanf("%c", &G->xlist[i].data);
        G->xlist[i].firstin = G->xlist[i].firstout = NULL;
    }
    printf("input arc list:\n");
    VertexType v1, v2;
    InfoType info;
    int m, n;
    struct ArcNode *node;
    for (int i = 0; i < G->arcnum; ++i) {
        scanf("%c %c %d", &v1, &v2, &info);
        // 定位弧的起点和终点
        m = locateVex(*G, v1);
        n = locateVex(*G, v2);
        node = (struct ArcNode *) malloc(sizeof(struct ArcNode));
        node->headvex = m;      // 弧的起点
        node->tailvex = n;      // 弧的终点
        node->info = info;      // 弧上权值
        // 头插法
        node->hlink = G->xlist[m].firstin;
        node->tlink = G->xlist[n].firstout;
        G->xlist[m].firstin = node;
        G->xlist[n].firstout = node;
    }
}
