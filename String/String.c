#include "String.h"

/**
 * 初始化字符串
 * @param str 字符串结构体指针
 * @param capacity 最大容量
 */
void String_Initial(String *str, size_t capacity) {
    str->capacity = capacity;
    str->ch = malloc(sizeof(char) * str->capacity);
    *str->ch = '\0';
    str->length = 0;
}

/**
 * 字符串扩容
 * @param str 字符串结构体指针
 * @param capacity 目标容量
 */
void String_Expand(String *str, size_t capacity) {
    str->capacity = capacity;
    str->ch = realloc(str->ch, sizeof(char) * capacity);
}

/**
 * 字符串按比例自动扩容
 * @param str 字符串结构体指针
 */
void String_AutoExpand(String *str) {
    str->capacity = EXPANSION_RATIO(str->capacity);
    str->ch = realloc(str->ch, sizeof(char) * str->capacity);
}

/**
 * 打印字符串
 * @param str
 */
void String_Print(String str, char end) {
    printf("%s%c", str.ch, end);
}

/**
 * 字符串是否为空
 * @param str 字符串结构体
 * @return true：空，false：不为空
 */
bool String_IsEmpty(String str) {
    return str.length == 0 || *str.ch == '\0';
}

/**
 * 计算字符串长度
 * @param str 字符串结构体指针
 * @return 字符串长度
 */
size_t String_Length(String *str) {
    size_t len = 0;
    for (const char *ptr = str->ch; *ptr != '\0'; ptr++) {
        len++;
    }
    return str->length = len;
}

/**
 * 清空字符串
 * @param str 字符串结构体
 */
void String_Clear(String str) {
    str.length = 0;
    *str.ch = '\0';
}

/**
 * 销毁字符串所占内存
 * @param str 字符串结构体指针
 */
void String_Destroy(String **str) {
    free((*str)->ch);
    (*str)->ch = NULL;
    free(*str);
    *str = NULL;
}

/**
 * 字符串翻转
 * @param str 字符串结构体
 */
void String_Reverse(String str) {
    size_t i = 0, j = str.length - 1;
    while (i < j) {
        String_SwapChar(&str.ch[i++], &str.ch[j--]);
    }
}

/**
 * 交换两个字符
 * @param c1 字符1
 * @param c2 字符2
 */
void String_SwapChar(char *c1, char *c2) {
    char t = *c1;
    *c1 = *c2;
    *c2 = t;
}

/**
 * 字符串中的大写字母转为小写
 * @param str 字符串结构体
 */
void String_Lower(String str) {
    for (size_t i = 0; i < str.length; ++i) {
        if (str.ch[i] >= 'A' && str.ch[i] <= 'Z') {
            str.ch[i] += 32;
        }
    }
}

/**
 * 字符串中的小写字母转为大写
 * @param str
 */
void String_Upper(String str) {
    for (size_t i = 0; i < str.length; ++i) {
        if (str.ch[i] >= 'a' && str.ch[i] <= 'z') {
            str.ch[i] -= 32;
        }
    }
}

/**
 * 拷贝字符串
 * @param src
 * @return
 */
String *String_Copy(String src) {
    String *dest = (String *) malloc(sizeof(String));
    dest->capacity = src.capacity;
    dest->ch = (char *) malloc(sizeof(char) * dest->capacity);
    dest->length = src.length;
    for (size_t i = 0; i < dest->length; ++i) {
        dest->ch[i] = src.ch[i];
    }
    dest->ch[dest->length] = '\0';
    return dest;
}

/**
 * 比较两个字符串
 * @param str1 字符串1
 * @param str2 字符串2
 * @return 返回值（大于0，小于0，等于0）
 * 返回值大于0，str1大于str2；
 * 返回值小于0，str1小于str2；
 * 返回值等于0，str1等于str2；
 */
int String_Compare(String str1, String str2) {
    const char *p = str1.ch;
    const char *q = str2.ch;
    while (*p && *q && *p == *q) {
        p++;
        q++;
    }
    return *p - *q;
}

/**
 * 判断一个字符串是否以另一个字符串开头
 * @param str 主字符串
 * @param dest 查找的目标字符串
 * @return true/false
 */
bool String_StartsWith(String str, const char *dest) {
    if (String_IsEmpty(str) || *dest == '\0') {
        return false;
    }
    const char *src = str.ch;
    while (*dest && *dest == *src) {
        dest++;
        src++;
    }
    return !*dest;
}

/**
 * 判断一个字符串是否以另一个字符串结尾
 * @param str 主字符串
 * @param dest 查找的目标字符串
 * @return true/false
 */
bool String_EndsWith(String str, const char *dest) {
    if (String_IsEmpty(str) || *dest == '\0') {
        return false;
    }
    size_t len = strlen(dest);
    const char *src = str.ch + len;
    while (*dest && *src && *dest == *src) {
        dest++;
        src++;
    }
    return !*dest && !*src;     // 比较后两个指针是否都指向了\0
}

/**
 * 从原字符串中指定位置开始截取定长的字符为新的字符串
 * @param src 原字符串
 * @param start 截取的开始位置，从0开始
 * @param len 截取的长度
 * @return 返回截取后的字符串指针
 */
String *String_SubStr(String src, int start, int len) {
    String *str = (String *) malloc(sizeof(String));
    str->length = len;
    String_Initial(str, str->length + 1);

    const char *ptr = src.ch + start;
    char *dest = str->ch;
    for (size_t i = 0; i < len; i++) {
        *dest++ = *ptr++;       // 拷贝指定长度个字符
    }
    *dest = '\0';       // 设置\0终止符
    return str;
}

/**
 * 拼接两个字符串，将str2附加到str1的末尾，形成一个新的字符串
 * @param str1 字符串1
 * @param str2 字符串2
 * @return 拼接后的字符串指针
 */
String *String_Concat(String str1, String str2) {
    String *str = (String *) malloc(sizeof(String));
    str->length = str1.length + str2.length;        // 更新长度
    String_Initial(str, str->length + 1);

    const char *ptr1 = str1.ch;
    const char *ptr2 = str2.ch;
    char *dest = str->ch;

    while (*ptr1) {
        *dest++ = *ptr1++;      // 先复制str1
    }
    while (*ptr2) {
        *dest++ = *ptr2++;      // 再复制str2
    }
    *dest = '\0';       // 放上终止符\0
    return str;
}

/**
 * 查找字符串中第一次出现指定字符的位置
 * @param str 字符串
 * @param ch 待查找的字符
 * @return 查找到的字符索引，未找到返回-1
 */
int String_IndexOfChar(String str, char ch) {
    int i;
    for (i = 0; i < str.length && str.ch[i] != ch; ++i);
    return i == str.length ? -1 : i;        // i移动到了\0的位置，表示查找失败返回-1
}

/**
 * 在目标字符串的指定位置插入一个字符串
 * @param dest 目标字符串
 * @param src 待插入的字符串
 * @param position 插入的位置
 */
void String_Insert(String *dest, String src, int position) {
    if (String_IsEmpty(src)) {
        return;
    }
    if (dest->length + src.length + 1 > dest->capacity) {       // 原有容量不够则扩容
        String_Expand(dest, dest->length + src.length + 1);
    }
    dest->length += src.length;     // 插入新的字符串后的长度
    for (size_t i = dest->length - 1; i >= position; i--) {
        dest->ch[i] = dest->ch[i - src.length];         // 倒序遍历字符串，将指定位置后面的字符全部后移
    }
    for (size_t i = 0; i < src.length; i++) {
        dest->ch[position + i] = src.ch[i];         // 再从前向后把待插入的字符串放入目标字符串
    }
    dest->ch[dest->length] = '\0';      // 设置
}

/**
 * 删除字符串中指定的字符
 * @param str 字符串
 * @param ch 待删除的字符
 */
void String_DeleteChar(String *str, char ch) {
    char *cursor;
    char *search;
    for (cursor = str->ch; *cursor != '\0'; cursor++) {
        if (*cursor != ch) {            // 不是删除的字符，则跳过
            continue;
        }
        // 查找指针移动到一下个不为删除字符的位置
        for (search = cursor + 1; *search == ch; search++);

        // 交换指针内容
        *cursor = *search;
        *search = ch;
        if (*cursor == '\0') {      // 把前面搜索指针的\0交换到了游标指针处，遍历结束
            break;
        }
    }
}

/**
 * 去掉字符串的首尾空格
 * @param str 字符串
 */
void String_Trim(String *str) {
    if (String_IsEmpty(*str)) {
        return;
    }
    String_RTrim(str);      // 去掉尾部空格
    String_LTrim(str);      // 去掉首部空格
}

/**
 * 去掉字符串首部空格
 * @param str 字符串
 */
void String_LTrim(String *str) {
    if (String_IsEmpty(*str)) {
        return;
    }
    char *base = str->ch;
    const char *cursor = str->ch;
    while (isspace(*cursor)) {      // 指针从前向后移动到第一个不是空白符的位置
        cursor++;
    }
    size_t len = 0;
    while (*cursor) {
        *base++ = *cursor++;        // 双指针移动字符，实现删除前面空白符的功能
        len++;
    }
    str->length = len;      // 更新字符串长度
    str->ch[str->length] = '\0';        // 设置\0终止字符串
}

/**
 * 去掉字符串尾部的空格
 * @param str 字符串
 */
void String_RTrim(String *str) {
    if (String_IsEmpty(*str)) {
        return;
    }
    char *tail = str->ch + str->length - 1;
    while (tail >= str->ch && isspace(*tail)) {         // 倒序遍历字符串
        str->length--;
        tail--;
    }
    *++tail = '\0';         // 标记\0终止
}

/**
 * 将一个字符串数组使用分隔符拼接为一个新的字符串
 * @param strs 字符串数组
 * @param strs_size 字符串数组大小
 * @param separator 拼接的分隔符
 * @return 拼接后的字符串
 */
String *String_Join(String strs[], size_t strs_size, char separator) {
    size_t len = strs_size - 1;             // 连接的分隔符数
    for (size_t i = 0; i < strs_size; i++) {
        len += strs[i].length;
    }
    String *str = (String *) malloc(sizeof(String));
    str->capacity = len + 1;
    str->ch = (char *) malloc(sizeof(char) * str->capacity);

    char *dest = str->ch;
    const char *src;
    for (size_t i = 0; i < strs_size; i++) {
        src = strs[i].ch;
        while (*src) {              // 拷贝到目标字符串
            *dest++ = *src++;
        }
        if (i == strs_size - 1) {       // 最后一个字符串连接后，加上\0
            *dest = '\0';
        } else if (src != strs[i].ch && *strs[i + 1].ch) {      // 当前字符串不为空，且下一个连接的字符串不为空，添加分隔符
            *dest++ = separator;
        }
    }
    str->length = dest - str->ch;       // 计算字符串的长度
    return str;
}

/**
 * 将字符串根据分隔符拆分为多个字符串
 * @param src 原字符串
 * @param separator 拆分的分隔符指针，可以为多个
 * @param output_size 拆分后的字符串个数
 * @return 拆分后的字符串数组
 */
String **String_Split(String src, const char *separator, int *output_size) {
    *output_size = 0;
    if (String_IsEmpty(src)) {
        return NULL;
    }
    if (*separator == '\0') {           // 分隔符为空，则复制原字符串
        String **result = (String **) malloc(sizeof(String *));
        result[(*output_size)++] = String_Copy(src);
        return result;
    }

    const char *cursor = src.ch;
    const char *sep;                    // 分隔符指针（可能有多个分隔符）
    String **result = (String **) malloc(sizeof(String *) * SPLIT_MAXSIZE);
    *output_size = 0;
    String *str = NULL;
    char *dest = NULL;
    while (*cursor != '\0') {
        // 判断是否分隔符
        bool split = false;
        for (sep = separator; !split && *sep; sep++) {
            split = !split && *sep == *cursor;
        }
        // 遇到分隔符或者下一位是\0，则结束当前字符串赋值
        if (split || *(cursor + 1) == '\0') {
            if (*(cursor + 1) == '\0') {
                *dest++ = *cursor;      // 当前字符赋值后再结束
            }
            *dest = '\0';
            str->length = dest - str->ch;
            result[(*output_size)++] = str;     // 将字符串添加到结果字符串数组中
            str = NULL;     // 重置str，标记为NULL
        } else {
            if (str == NULL) {
                // 表示一个新的字符串
                str = (String *) malloc(sizeof(String));
                String_Initial(str, DEFAULT_CAP);
                dest = str->ch;
            }
            *dest++ = *cursor;
        }

        cursor++;
    }
    return result;
}

/**
 * 从主字符串中的指定位置开始查找目标字符串
 * @param str 字符串
 * @param search 查找的字符串
 * @param start 开始查找的位置
 * @return 查找到字符串的位置，查找失败返回-1
 */
int String_StrStr(String str, String search, int start) {
    if (String_IsEmpty(str) || String_IsEmpty(search)) {
        return -1;
    }

    int i, j;
    bool flag;
    for (i = start; i <= str.length - search.length; ++i) {
        flag = 1;
        for (j = 0; j < search.length; j++) {           // 从当前位置开始比较search.length个字符
            if (str.ch[i + j] != search.ch[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {         // 指定长度内所有字符全部相同
            return i;
        }
    }
    return -1;
}

/**
 * 将字符串中匹配到的所有子串替换为目标字符串
 * @param str 主字符串
 * @param substr 匹配的子串
 * @param tostr 替换的目标字符串
 */
void String_Replace(String *str, String substr, String tostr) {
    if (String_IsEmpty(*str) || String_IsEmpty(substr)) {
        return;
    }

    String *cpy = (String *) malloc(sizeof(String));        // 拷贝字符串
    String_Initial(cpy, COPY_CAP);
    char *dest = cpy->ch;
    for (const char *cursor = str->ch; *cursor;) {
        // 从cursor位置开始查找匹配字符串
        bool flag = true;
        for (int i = 0; i < substr.length; ++i) {
            if (substr.ch[i] != *(cursor + i)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            // 查找成功，则将替换的字符串复制到拷贝字符串
            for (int i = 0; i < tostr.length; ++i) {
                *dest++ = tostr.ch[i];
            }
            cursor += substr.length;
        } else {
            // 查找失败，复制当前指针所指向的字符至拷贝字符串
            *dest++ = *cursor++;
        }
    }
    *dest = '\0';
    str->length = dest - cpy->ch;           // 替换后的字符串长度
    if (str->capacity < str->length + 1) {
        String_Expand(str, str->length + 1);        // 是否需要扩容
    }

    for (size_t i = 0; i < str->length; ++i) {
        str->ch[i] = cpy->ch[i];            // 从cpy字符串拷贝回原字符串
    }
    str->ch[str->length] = '\0';        // 设置\0
    String_Destroy(&cpy);           // 释放
}