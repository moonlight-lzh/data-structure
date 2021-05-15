/**
 * 顺序栈的最大长度
 */
#define SqStack_MaxSize 100

/**
 * 顺序栈中数据的数据类型
 */
#define SqStack_DataType int

/**
 * 顺序栈的结构体
 */
struct SqStack {
    SqStack_DataType data[SqStack_MaxSize];     // 栈数组
    int top;    // 栈顶指针
};

/**
 * 栈的初始化
 * @param stack 顺序栈
 */
void SqStack_Init(struct SqStack *stack) {
    stack->top = -1;
}

/**
 * 栈是否为空
 * @param stack 顺序栈
 * @return 返回1：栈为空，返回0：栈非空
 */
int SqStack_IsEmpty(struct SqStack stack) {
    return stack.top == -1;
}

/**
 * 入栈
 * @param stack 顺序栈
 * @param x 入栈的元素
 * @return 返回1：入栈成功，返回0：入栈失败，栈已满
 */
int SqStack_Push(struct SqStack *stack, int x) {
    if (stack->top == SqStack_MaxSize - 1) {
        return 0;
    }
    stack->data[++stack->top] = x;
    return 1;
}

/**
 * 出栈，并返回出栈元素
 * @param stack 顺序栈
 * @param x 返回的出栈元素
 * @return 返回1:：出栈成功，返回0：出栈失败，栈为空
 */
int SqStack_Pop(struct SqStack *stack, int *x) {
    if (SqStack_IsEmpty(*stack)) {
        return 0;
    }
    *x = stack->data[stack->top--];
    return 1;
}

/**
 * 获取栈顶元素
 * @param stack 顺序栈
 * @param x 返回的栈顶元素
 * @return 返回1：获取成功，返回0：获取失败，栈为空
 */
int SqStack_GetTop(struct SqStack stack, int *x) {
    if (SqStack_IsEmpty(stack)) {
        return 0;
    }
    *x = stack.data[stack.top];
    return 1;
}
