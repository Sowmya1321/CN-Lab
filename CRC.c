#include<stdio.h>
#include<stdint.h>
#include<string.h>
#define CRC16_INIT 0x000
#define CRCCCITT_INIT 0xFFF
#define CRC12_INIT 0x000
uint16_t crc12(const uint8_t*data,size_t len)
{
    uint16_t crc=CRC12_INIT;
    uint16_t poly=0x180F;
    for(size_t i=0;i<len;i++)
    {
        crc^=data[i]<<4;
        for(int j=0;j<8;j++)
        {
            if(crc&0x800)
                crc=(crc<<1)^poly;
            else
                crc<<=1;
                crc&=0xFFF;
        }
    }
    return crc;
}
uint16_t crc16(const uint8_t*data,size_t len)
{
    uint16_t crc=CRC16_INIT;
    uint16_t poly=0x8005;
    for(size_t i=0;i<len;i++)
    {
        crc^=data[i]<<8;
        for(int j=0;j<8;j++)
        {
            if(crc&0x8000)
                crc=(crc<<1)^poly;
            else
                crc<<=1;
        }
    }
    return crc;
}
uint16_t crcccitt(const uint8_t*data,size_t len)
{
    uint16_t crc=CRCCCITT_INIT;
    uint16_t poly=0x1021;
    for(size_t i=0;i<len;i++)
    {
        crc^=data[i]<<8;
        for(int j=0;j<8;j++)
        {
            if(crc&0x8000)
                crc=(crc<<1)^poly;
            else
                crc<<=1;
        }
    }
    return crc;
}
int main()
{
    char input[128];
    printf("Enter data string:");
    scanf("%127s",input);
    size_t len=strlen(input);
    uint16_t c12=crc12((uint8_t*)input,len);
    uint16_t c16=crc16((uint8_t*)input,len);
    uint16_t cccitt=crcccitt((uint8_t*)input,len);
    printf("\n CRC Results:\n");
    printf("CRC-12: 0x%03X(12bits)\n",c12);
    printf("CRC-16: 0x%04X(16 bits)\n",c16);
    printf("CRC-CCITT: 0x%04X(16bits)\n",cccitt);
    return 0;
}

/*OUTPUT*/
Enter data string:1101011011

 CRC Results:
CRC-12: 0xD47(12bits)
CRC-16: 0x0496(16 bits)
CRC-CCITT: 0xA65E(16bits)
