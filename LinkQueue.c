#include <stdlib.h>     // 引入stdlib.h头文件中的malloc和free函数

/**
 * 链队列节点数据类型
 */
#define LinkQueue_DataType int

/**
 * 链队列中的节点结构体
 */
struct LinkNode {
    LinkQueue_DataType data;    // 数据域
    struct LinkNode *next;      // 指针域
};

/**
 * 链队列结构体
 */
struct LinkQueue {
    struct LinkNode *front;     // 队首指针，出队删除节点
    struct LinkNode *rear;      // 队尾指针，入队添加节点
    int size;
};

/**
 * malloc申请堆空间创建LinkNode指针
 */
#define NEW_NODE()((struct LinkNode *) malloc(sizeof(struct LinkNode)))

/**
 * 初始化带头结点的队列
 * @param queue 队列
 */
void LinkQueue_Init(struct LinkQueue *queue) {
    struct LinkNode *node = NEW_NODE();
    node->next = NULL;
    node->data = 0;
    queue->front = node;
    queue->size = 0;
}

/**
 * 判断队列是否为空
 * @param queue 队列
 * @return 返回1：队列为空，返回0：队列非空
 */
int LinkQueue_IsEmpty(struct LinkQueue queue) {
    return queue.front == queue.rear;
}

/**
 * 队列入队
 * @param queue 队列
 * @param x 待入队元素
 */
void LinkQueue_EnQueue(struct LinkQueue *queue, int x) {
    struct LinkNode *node = NEW_NODE();
    node->data = x;
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    queue->size++;
}

/**
 * 队列出队，并返回出队元素
 * @param queue 队列
 * @param x 返回的出队元素
 * @return 返回1：出队成功，返回0：出队失败，队列为空
 */
int LinkQueue_DeQueue(struct LinkQueue *queue, int *x) {
    if (LinkQueue_IsEmpty(*queue)) {
        return 0;
    }
    struct LinkNode *node = queue->front->next;
    *x = node->data;
    if (node == queue->rear) {
        queue->rear = queue->front;         // 队列中只有一个节点，出队后更新尾结点指针，队列变为空
    }
    queue->front->next = node->next;
    free(node);
    queue->size--;
    return 1;
}

