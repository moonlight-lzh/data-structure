#include "SkipList.h"


/// <summary>
/// �����������
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
/// ��������
/// </summary>
/// <returns></returns>
SkipList* SL_CreateList()
{
	SkipList* list = (SkipList*)malloc(sizeof(SkipList));
	if (list == NULL)
	{
		return NULL;
	}
	list->level = 0;		// ��ǰ����Ĳ���

	SLNode* head = NEW_NODE(MAX_LEVEL);
	if (head == NULL)
	{
		free(list);
		return NULL;
	}

	list->head = head;
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		list->head->next[i] = NULL;			// ͷ����ÿ��nextָ��Ϊ��
	}
	srand((unsigned int)time(0));		// ���������
	return list;
}

/// <summary>
/// ��������
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
/// ����������
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
/// ����������
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
		while (current->next[i] != NULL && current->next[i]->key < key)			// �ҵ���ǰ��һ�����λ�õ�ǰһ�����
		{
			current = current->next[i];
		}
		update[i] = current;		// ��¼���еĲ���λ�õ�ǰ�����
	}

	if (current && current->next[0] && current->next[0]->key == key)					// �Ѿ����ڣ������ֵ
	{
		current->next[0]->value = value;
		return true;
	}

	int level = SL_RandomLevel();			// �������
	if (level > list->level)		// ����������ڵ�ǰ�������
	{
		for (int i = list->level; i < level; i++)		// �����ϲ����ָ��
		{
			update[i] = list->head;
		}
		list->level = level;			// ���µ�ǰ����Ĳ���
	}

	SLNode* node = SL_CreateNode(level, key, value);		// ����һ�����
	if (node == NULL)
	{
		return false;
	}

	for (int i = 0; i < level; i++)
	{
		if (update[i] != NULL)
		{
			node->next[i] = update[i]->next[i];			// ÿһ�������
			update[i]->next[i] = node;
		}
	}
	return true;
}

/// <summary>
/// ɾ�����
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

	current = current != NULL ? current->next[0] : NULL;			// currentָ��ǰ��ɾ���Ľ��
	if (current == NULL || current->key != key)		// û���ҵ�
	{
		return false;
	}

	for (int i = list->level - 1; i >= 0; i--)
	{
		if (update[i]->next[i] == current)
		{
			update[i]->next[i] = current->next[i];
			if (list->head->next[i] == NULL)		// ɾ������һ��û�н��
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
/// ���ҽ��
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

		if (current && current->next[i] && current->next[i]->key == key)			// ����һ���ҵ�
		{
			*value = current->next[i]->value;
			return true;
		}
	}
	return false;
}
