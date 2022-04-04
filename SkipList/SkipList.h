#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/// <summary>
/// ����м�������
/// </summary>
typedef int KeyType;

/// <summary>
/// �����ֵ������
/// </summary>
typedef int ValueType;

/// ������
#define MAX_LEVEL 8

/// �������
#define  NEW_NODE(n)((SLNode*)((SLNode*)malloc(sizeof(SLNode) + n * sizeof(SLNode*))))

/// <summary>
/// ������
/// </summary>
typedef struct _Node {
    KeyType key;
    ValueType value;
    struct _Node *next[];
} SLNode;

/// <summary>
/// ����ṹ��
/// </summary>
typedef struct _SkipList {
    int level;
    SLNode *head;
} SkipList;

/*********************************** Definitions ***********************************/

int SL_RandomLevel();                                    // ������ɲ���
SkipList *SL_CreateList();                                // ��������
void SL_DestroyList(SkipList *);                            // ��������
SLNode *SL_CreateNode(int, KeyType, ValueType);            // �������
bool SL_InsertNode(SkipList *, KeyType, ValueType);        // ����
bool SL_DeleteNode(SkipList *, KeyType, ValueType *);        // ɾ��
bool SL_SearchNode(SkipList *, KeyType, ValueType *);        // ��ѯ


/*********************************** Definitions ***********************************/