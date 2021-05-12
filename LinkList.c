#include <stdlib.h>
#include <stdbool.h>

/**
 * 单链表节点数据类型
 */
#define LNode_DataType int

/**
 * 单链表节点的结构体
 */
typedef struct LNode {
    LNode_DataType data;    // 数据域
    struct LNode *next;     // 指针域
} LNode, *LinkList;

/**
 * 创建新的单链表节点的宏
 */
#define New_LNode()((LNode *)malloc(sizeof(LNode)))

/**
 * 初始化单链表，置为NULL
 * @param L 单链表
 */
void LinkList_Init(LinkList *L) {
    *L = NULL;
}

/**
 * 从单链表中获取位序为pos的节点
 * @param L 单链表
 * @param pos 位序，从1开始
 * @return 获取到的节点指针
 */
LNode *LinkList_GetNode(LinkList L, int pos) {
    LNode *cur = L;
    for (int i = 1; cur && i < pos; i++, cur = cur->next);
    return cur;
}

/**
 * 在单链表中根据值查找节点
 * @param L 单链表
 * @param data 待查找的数据域
 * @return 找到的节点
 */
LNode *LinkList_Locate(LinkList L, LNode_DataType data) {
    LNode *cur = L;
    for (; cur && cur->data != data; cur = cur->next);
    return cur;
}

/**
 * 获取单链表的表长
 * @param L 单链表
 * @return 表长
 */
int LinkList_Length(LinkList L) {
    if (L == NULL) {
        return 0;
    }
    int i = 1;
    for (LNode *cur = L; cur && cur->next; cur = cur->next, i++);
    return i;
}

/**
 * 在节点的下一个位置插入节点
 * @param node 当前节点指针
 * @param data 下一个节点的数据域
 * @return 插入是否成功，成功返回true，失败返回false
 */
bool LinkList_InsertNext(LNode *node, LNode_DataType data) {
    if (node == NULL) {
        return false;
    }
    LNode *newNode = New_LNode();
    newNode->next = node->next;
    newNode->data = data;
    node->next = newNode;
    return true;
}

/**
 * 删除单链表中位序为pos的节点，并返回节点值
 * @param L 单链表
 * @param pos 删除节点的位序
 * @param val 删除节点的数据域
 * @return 删除是否成功，成功返回true，失败返回false
 */
bool LinkList_Remove(LinkList *L, int pos, int *val) {
    if (L == NULL || pos < 1) {
        return false;
    }
    if (pos == 1) {
        LNode *node = *L;
        *L = (*L)->next;
        *val = node->data;
        free(node);
    } else {
        LNode *node = LinkList_GetNode(*L, pos - 1);
        if (!node) {
            return false;
        }
        LNode *next = node->next;
        node->next = next ? next->next : NULL;
        if (next) {
            *val = next->data;
            free(next);
        }
    }
    return true;
}
