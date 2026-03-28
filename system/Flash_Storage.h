#ifndef __FLASH_STORAGE_H
#define __FLASH_STORAGE_H

#include <stdint.h>

/**
 * @brief   将字符串存储到Flash（最大19字符 + '\0'）
 * @param   str : 要存储的字符串指针（可为NULL，存储空串）
 * @note    该操作会擦除整个Flash页（1KB），请确保存储地址所在页无其他重要数据
 */
void Store_String_In_Flash(const char* str);



/**
 * @brief   从Flash读取字符串到指定缓冲区
 * @param   buffer : 接收字符串的缓冲区
 * @param   maxLen : 缓冲区大小（包括结尾'\0'），最多读取maxLen-1个字符
 */
void Get_String_From_Flash(char* buffer, uint8_t maxLen);

#endif
