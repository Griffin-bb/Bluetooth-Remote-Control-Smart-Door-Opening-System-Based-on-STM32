#include "stm32f10x.h"                  // Device header

#include <stdint.h>
#include <string.h>

// 字符串存储起始地址（选用Flash最后1KB区域，地址0x0800FC00）
#define STRING_STORAGE_ADDR ((uint32_t)0x0800FC00)

void Store_String_In_Flash(const char* str)
{
    uint8_t data[20] = {0};          // 固定20字节缓冲区，初始全0
    uint8_t len;
    uint32_t i;
    uint16_t halfword;

    // 若传入字符串非空，则复制并确保长度不超过19（留一位给'\0'）
    if (str != NULL)
    {
        len = strlen(str);
        if (len >= 20)
        {
            len = 19;                 // 截断
        }
        memcpy(data, str, len);
        data[len] = '\0';             // 手动添加结尾符
    }
    // 若str为NULL，data保持全0（空字符串）

    // 解锁Flash
    FLASH_Unlock();

    // 擦除包含存储地址的整个Flash页（1KB）
    FLASH_ErasePage(STRING_STORAGE_ADDR);

    // 按半字（16位）写入20字节数据（20为偶数，无需处理奇数字节）
    for (i = 0; i < 20; i += 2)
    {
        halfword = data[i] | (data[i + 1] << 8);
        FLASH_ProgramHalfWord(STRING_STORAGE_ADDR + i, halfword);
    }

    // 锁定Flash
    FLASH_Lock();
}


void Get_String_From_Flash(char* buffer, uint8_t maxLen)
{
    uint8_t i;
    uint8_t* p = (uint8_t*)STRING_STORAGE_ADDR;   // Flash映射地址

    if (buffer == NULL || maxLen == 0)
    {
        return;
    }

    // 逐字节复制，直到遇到'\0'或填满缓冲区（留一位给结尾符）
    for (i = 0; i < maxLen - 1; i++)
    {
        buffer[i] = p[i];
        if (p[i] == 0)
        {
            break;
        }
    }
    buffer[i] = '\0';   // 确保字符串以'\0'结尾
}
