/**
 * 循环队列最大容量
 */
#define SqQueue_MaxSize 10

/**
 * 循环队列数据类型
 */
#define SqQueue_DataType int

/**
 * 循环队列结构体
 */
struct SqQueue {
    SqQueue_DataType data[SqQueue_MaxSize];     // 队列存放数据的数组
    int front;      // 队首指针，出队
    int rear;       // 队尾指针，入队
    int size;       // 由于队空和队慢时都有Queue.rear == Queue.front，这里增加一个size变量加以区分
};

/**
 * 循环队列初始化
 * @param queue 队列
 */
void SqQueue_Init(struct SqQueue *queue) {
    queue->front = queue->rear = 0;
    queue->size = 0;
}

/**
 * 循环队列入队
 * @param queue 队列
 * @param x 待入队的元素
 * @return 返回1：入队成功，返回0：入队失败，队列已满
 */
int SqQueue_EnQueue(struct SqQueue *queue, SqQueue_DataType x) {
    if (queue->size == SqQueue_MaxSize) {
        return 0;
    }
    queue->data[queue->rear] = x;
    queue->rear = (queue->rear + 1) % SqQueue_MaxSize;
    queue->size++;
    return 1;
}

/**
 * 循环队列出队
 * @param queue 队列
 * @param x 出队返回的元素值的指针
 * @return 返回1：出队成功，返回0：出队失败，队列为空
 */
int SqQueue_DeQueue(struct SqQueue *queue, SqQueue_DataType *x) {
    if (queue->size == 0) {
        return 0;
    }
    *x = queue->data[queue->front];
    queue->front = (queue->front + 1) % SqQueue_MaxSize;
    queue->size--;
    return 1;
}
