#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/// <summary>
/// 结点中键的类型
/// </summary>
typedef int KeyType;

/// <summary>
/// 结点中值的类型
/// </summary>
typedef int ValueType;

/// 最大层数
#define MAX_LEVEL 8

/// 创建结点
#define  NEW_NODE(n)((SLNode*)((SLNode*)malloc(sizeof(SLNode) + n * sizeof(SLNode*))))

/// <summary>
/// 跳表结点
/// </summary>
typedef struct _Node {
    KeyType key;
    ValueType value;
    struct _Node *next[];
} SLNode;

/// <summary>
/// 跳表结构体
/// </summary>
typedef struct _SkipList {
    int level;
    SLNode *head;
} SkipList;

/*********************************** Definitions ***********************************/

int SL_RandomLevel();                                    // 随机生成层数
SkipList *SL_CreateList();                                // 创建跳表
void SL_DestroyList(SkipList *);                            // 销毁跳表
SLNode *SL_CreateNode(int, KeyType, ValueType);            // 创建结点
bool SL_InsertNode(SkipList *, KeyType, ValueType);        // 插入
bool SL_DeleteNode(SkipList *, KeyType, ValueType *);        // 删除
bool SL_SearchNode(SkipList *, KeyType, ValueType *);        // 查询


/*********************************** Definitions ***********************************/