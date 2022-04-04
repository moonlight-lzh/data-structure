#include "SkipList.h"


/// <summary>
/// 生成随机层数
/// </summary>
/// <returns></returns>
int SL_RandomLevel()
{
	int level = 1;

	while (rand() % 2 != 0)
	{
		if (level >= MAX_LEVEL)
		{
			break;
		}
		level++;
	}
	return level;
}

/// <summary>
/// 创建跳表
/// </summary>
/// <returns></returns>
SkipList* SL_CreateList()
{
	SkipList* list = (SkipList*)malloc(sizeof(SkipList));
	if (list == NULL)
	{
		return NULL;
	}
	list->level = 0;		// 当前跳表的层数

	SLNode* head = NEW_NODE(MAX_LEVEL);
	if (head == NULL)
	{
		free(list);
		return NULL;
	}

	list->head = head;
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		list->head->next[i] = NULL;			// 头结点的每层next指针为空
	}
	srand((unsigned int)time(0));		// 随机数种子
	return list;
}

/// <summary>
/// 销毁跳表
/// </summary>
/// <param name="list"></param>
void SL_DestroyList(SkipList* list)
{
	SLNode* head = list->head;
	SLNode* ptr;

	if (list == NULL)
	{
		return;
	}

	while (head != NULL && head->next[0] != NULL)
	{
		ptr = head->next[0];
		head->next[0] = head->next[0]->next[0];
		free(ptr);
	}
	free(head);
	free(list);
}

/// <summary>
/// 创建跳表结点
/// </summary>
/// <param name="level"></param>
/// <param name="k"></param>
/// <param name="v"></param>
/// <returns></returns>
SLNode* SL_CreateNode(int level, KeyType k, ValueType v)
{
	SLNode* node = NEW_NODE(level);
	if (node == NULL)
	{
		return NULL;
	}

	node->key = k;
	node->value = v;
	return node;
}

/// <summary>
/// 插入跳表结点
/// </summary>
/// <param name="list"></param>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
bool SL_InsertNode(SkipList* list, KeyType key, ValueType value)
{
	SLNode* current = list->head;
	SLNode* update[MAX_LEVEL];
	memset(update, 0, sizeof(SLNode*) * MAX_LEVEL);

	for (int i = list->level - 1; i >= 0; i--)
	{
		while (current->next[i] != NULL && current->next[i]->key < key)			// 找到当前这一层插入位置的前一个结点
		{
			current = current->next[i];
		}
		update[i] = current;		// 记录所有的插入位置的前驱结点
	}

	if (current && current->next[0] && current->next[0]->key == key)					// 已经存在，则更新值
	{
		current->next[0]->value = value;
		return true;
	}

	int level = SL_RandomLevel();			// 随机层数
	if (level > list->level)		// 随机层数大于当前跳表层数
	{
		for (int i = list->level; i < level; i++)		// 更新上层结点的指针
		{
			update[i] = list->head;
		}
		list->level = level;			// 更新当前跳表的层数
	}

	SLNode* node = SL_CreateNode(level, key, value);		// 创建一个结点
	if (node == NULL)
	{
		return false;
	}

	for (int i = 0; i < level; i++)
	{
		if (update[i] != NULL)
		{
			node->next[i] = update[i]->next[i];			// 每一层插入结点
			update[i]->next[i] = node;
		}
	}
	return true;
}

/// <summary>
/// 删除结点
/// </summary>
/// <param name="list"></param>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
bool SL_DeleteNode(SkipList* list, KeyType key, ValueType* value)
{
	SLNode* current = list->head;
	SLNode* update[MAX_LEVEL];
	memset(update, 0, sizeof(SLNode*) * MAX_LEVEL);
	for (int i = list->level - 1; i >= 0; i--)
	{
		while (current->next[i] != NULL && current->next[i]->key < key)
		{
			current = current->next[i];
		}
		update[i] = current;
	}

	current = current != NULL ? current->next[0] : NULL;			// current指向当前被删除的结点
	if (current == NULL || current->key != key)		// 没有找到
	{
		return false;
	}

	for (int i = list->level - 1; i >= 0; i--)
	{
		if (update[i]->next[i] == current)
		{
			update[i]->next[i] = current->next[i];
			if (list->head->next[i] == NULL)		// 删除后，这一层没有结点
			{
				list->level--;
			}
		}
	}
	*value = current->value;
	free(current);
	return true;
}

/// <summary>
/// 查找结点
/// </summary>
/// <param name="list"></param>
/// <param name="key"></param>
/// <param name="value"></param>
/// <returns></returns>
bool SL_SearchNode(SkipList* list, KeyType key, ValueType* value)
{
	SLNode* current = list->head;
	for (int i = list->level - 1; i >= 0; i--)
	{
		while (current->next[i] != NULL && current->next[i]->key < key)
		{
			current = current->next[i];
		}

		if (current && current->next[i] && current->next[i]->key == key)			// 任意一层找到
		{
			*value = current->next[i]->value;
			return true;
		}
	}
	return false;
}
