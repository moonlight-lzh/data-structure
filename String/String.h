#ifndef STRINGPROJECT_STRING_H
#define STRINGPROJECT_STRING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// 扩容比例1.5
#define EXPANSION_RATIO(cap) (cap + (cap >> 1u))

/// 容量默认值
#define DEFAULT_CAP 128

/// 最大拆分数
#define SPLIT_MAXSIZE 16

/// 拷贝占用的空间
#define COPY_CAP 1024

/// 字符串结构体
typedef struct _String {
    char *ch;
    size_t length;
    size_t capacity;
} String;

/// 初始化字符串
void String_Initial(String *str, size_t capacity);

/// 根据指定的容量扩容
void String_Expand(String *str, size_t capacity);

/// 按比例自动扩容
void String_AutoExpand(String *str);

/// 打印字符串
void String_Print(String str, char end);

/// 判断字符串是否为空
bool String_IsEmpty(String str);

/// 计算返回字符串的长度
size_t String_Length(String *str);

/// 清空字符串
void String_Clear(String str);

/// 销毁字符串
void String_Destroy(String **str);

/// 判断字符串是否以某一字符串开头
bool String_StartsWith(String str, const char *dest);

/// 判断字符串是否以某一字符串结尾
bool String_EndsWith(String str, const char *dest);

/// 字符串翻转
void String_Reverse(String str);

/// 将字符串中所有的大写字母转为小写
void String_Lower(String str);

/// 将字符串中所有的小写字母转为大写
void String_Upper(String str);

/// 交换两个字符
void String_SwapChar(char *c1, char *c2);

/// 去掉字符串的收尾空格
void String_Trim(String *str);

/// 去掉字符串首部的空格
void String_LTrim(String *str);

/// 去掉字符串尾部的空格
void String_RTrim(String *str);

/// 拷贝字符串，返回字符串指针
String *String_Copy(String src);

/// 比较两个字符串(大于0：str1 > str2；小于0：str1 < str2；等于0：str1==str2)
int String_Compare(String str1, String str2);

/// 将源字符串在指定位置截取len长度的字符串
String *String_SubStr(String src, int start, int len);

/// 将第二个字符串附加到第一个的末尾
String *String_Concat(String str1, String str2);

/// 在主串中从指定位置开始搜索目标字符串（简单模式匹配），
/// 并返回查找到的字符串首部的位置，查找失败则返回-1
int String_StrStr(String str, String search, int start);

/// 查找返回第一次出现指定字符的位置
int String_IndexOfChar(String str, char ch);

/// 在目标字符串指定位置插入另一个字符串
void String_Insert(String *dest, String src, int position);

/// 删除字符串中指定字符
void String_DeleteChar(String *str, char ch);

/// 将字符串根据指定分隔符拆分成多个字符串
String **String_Split(String src, const char *separator, int *output_size);

/// 使用分隔符将多个字符串合并为一个
String *String_Join(String strs[], size_t strs_size, char separator);

/// 将字符串中指定的字符串替换为目标字符串
void String_Replace(String *str, String substr, String tostr);

#endif //STRINGPROJECT_STRING_H