/*************************************************************************
	> File Name: crc.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 30/03/2018
 ************************************************************************/

#include "crc.h"

#ifdef __CREATE_CRC_TABLE
#include <stdio.h>

static uint8_t  crc8_table[256];
static uint16_t crc16_table[256];
static uint32_t crc32_table[256];

void crc8_init_table(void)
{
    int i;
    int j;
    uint8_t data;
    uint8_t crc;

    for(i = 0; i <= 0xFF; i++)    
    {
        crc = 0;
        data = i;
        for(j = 0; j < 8; j++)
        {
            if((data^crc) & 0x80)
            {
                crc = (crc << 1) ^ CRC8_POLY;
            }
            else
            {
                crc <<= 1;
            }

            data <<= 1;
        }

        crc8_table[i] = crc;
    }
}

void crc8_init_table_ref(void)
{
    int i;
    int j;
    uint8_t crc;

    for(i = 0; i <= 0xFF; i++)
    {
        crc = i;
        for(j = 0; j < 8; j++)
        {
            if(crc & 0x01)
            {
                crc = (crc >> 1) ^ CRC8_POLY_REF;
            }
            else
            {
                crc >>= 1;
            }
        }

        crc8_table[i] = crc;
    }
}


void crc16_init_table(void)
{
    int i;
    int j;
    uint16_t data;
    uint16_t crc;

    for(i = 0; i <= 0xFF; i++)    
    {
        crc = 0;
        data = i << 8;
        for(j = 0; j < 8; j++)
        {
            if((data^crc) & 0x8000)
            {
                crc = (crc << 1) ^ CRC16_POLY;
            }
            else
            {
                crc <<= 1;
            }

            data <<= 1;
        }

        crc16_table[i] = crc;
    }
}

void crc16_init_table_ref(void)
{
    int i;
    int j;
    uint16_t crc;

    for(i = 0; i <= 0xFF; i++)
    {
        crc = i;
        for(j = 0; j < 8; j++)
        {
            if(crc & 0x01)
            {
                crc = (crc >> 1) ^ CRC16_POLY_REF;
            }
            else
            {
                crc >>= 1;
            }
        }

        crc16_table[i] = crc;
    }
}

void crc32_init_table(void)
{
    int i;
    int j;
    uint32_t data;
    uint32_t crc;

    for(i = 0; i <= 0xFF; i++)
    {
        data = i << 24;
        crc = 0;
        
        for(j = 0; j < 8; j++)
        {
            if((data^crc) & 0x80000000)
            {
                crc = (crc << 1) ^ CRC32_POLY;
            }
            else
            {
                crc <<= 1;
            }

            data <<= 1;
        }

        crc32_table[i] = crc;
    }
}

void crc32_init_table_ref(void)
{
    int i;
    int j;
    uint32_t crc;

    for(i = 0; i <= 0xFF; i++)
    {
        crc = i;
        for(j = 0; j < 8; j++)
        {
            if(crc & 0x01)
            {
                crc = (crc >> 1) ^ CRC32_POLY_REF;
            }
            else
            {
                crc >>= 1;
            }
        }

        crc32_table[i] = crc;
    }
}

/*
    opt: 
        0 - Create normal table
        1 - Create reflected table
*/
void create_table(uint8_t opt)
{
    char *f_name_p = "./crc.c";
    FILE *fp;
    int i;
    char buf[1024*8];
    char *buf_p;
    int res;

    fp = fopen(f_name_p, "a+");
    if(NULL == fp)
        return;

    crc8_init_table();
    crc16_init_table();
    crc32_init_table();

    buf_p = buf;

    buf_p += sprintf(buf_p, 
        "\n\n\n"
        "/*************************************************************************\n"
        "                                CRC Table\n"
        " ************************************************************************/\n"
        "/*\n"
        "   CRC-8-Dallas/Maxim\n"
        "   Poly: 0x%x\n"
        "   Init: 0x%x\n"
        "   Ref:  %s\n"
        "*/\n", opt ? CRC8_POLY_REF : CRC8_POLY, CRC8_INIT, opt ? "yes" : "no");
    buf_p += sprintf(buf_p, "unsigned char crc8_table[] = {");
    for(i = 0; i <= 0xFF; i++)
    {
        if(0 == i%8)
        {
            buf_p += sprintf(buf_p, "\n    ");
        }

        buf_p += sprintf(buf_p, "0x%02x, ", crc8_table[i]);
    }
    buf_p += sprintf(buf_p, "\n};\n\n");

    buf_p += sprintf(buf_p, 
        "/*\n"
        "   CRC-16-IBM\n"
        "   Poly: 0x%x\n"
        "   Init: 0x%x\n"
        "   Ref:  %s\n"
        "*/\n", opt ? CRC16_POLY_REF : CRC16_POLY, CRC16_INIT, opt ? "yes" : "no");
    buf_p += sprintf(buf_p, "unsigned short crc16_table[] = {");
    for(i = 0; i <= 0xFF; i++)
    {
        if(0 == i%8)
        {
            buf_p += sprintf(buf_p, "\n    ");
        }

        buf_p += sprintf(buf_p, "0x%04x, ", crc16_table[i]);
    }
    buf_p += sprintf(buf_p, "\n};\n\n");

    buf_p += sprintf(buf_p, 
        "/*\n"
        "   CRC-32\n"
        "   Poly: 0x%x\n"
        "   Init: 0x%x\n"
        "   Ref:  %s\n"
        "*/\n", opt ? CRC32_POLY_REF : CRC32_POLY, CRC32_INIT, opt ? "yes" : "no");
    buf_p += sprintf(buf_p, "unsigned int crc32_table[] = {");
    for(i = 0; i <= 0xFF; i++)
    {
        if(0 == i%8)
        {
            buf_p += sprintf(buf_p, "\n    ");
        }

        buf_p += sprintf(buf_p, "0x%08x, ", crc32_table[i]);
    }
    buf_p += sprintf(buf_p, "\n};\n#endif\n");

    res = fwrite(buf, 1, buf_p-buf, fp);
    if(res != (buf_p-buf))
    {
        fclose(fp);
        return;
    }

    fclose(fp);
}
#endif

uint8_t crc8_calculate_directly(void *data, int size)
{
    int i;
    uint8_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC8_INIT;

    while(0 < size--)
    {
        crc ^= *data_p++;
        for(i = 0; i < 8; i++)
        {
            if(crc & 0x80)
            {
                crc = (crc << 1) ^ CRC8_POLY;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

uint8_t crc8_calculate_directly_ref(void *data, int size)
{
    int i;
    uint8_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC8_INIT;

    while(0 < size--)
    {
        crc ^= *data_p++;
        for(i = 0; i < 8; i++)
        {
            if (crc & 0x01)
            {
                crc = (crc >> 1) ^ CRC8_POLY_REF;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}

uint8_t crc8_calculate(void *data, int size)
{
    uint8_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC8_INIT;

    while(0 < size--)
    {
        crc = (crc << 8) ^ crc8_table[crc ^ *data_p++];
    }

    return crc;
}

uint8_t crc8_calculate_ref(void *data, int size)
{
    uint8_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC8_INIT;

    while(0 < size--)
    {
        crc = crc8_table[*data_p++ ^ crc];
    }

    return ~crc;
}

uint16_t crc16_calculate_directly(void *data, int size)
{
    int i;
    uint16_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC16_INIT;

    while(0 < size--)
    {
        crc ^= (*data_p++ << 8);
        for(i = 0; i < 8; i++)
        {
            if(crc & 0x8000)
            {
                crc = (crc << 1) ^ CRC16_POLY;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

uint16_t crc16_calculate_directly_ref(void *data, int size)
{
    int i;
    uint16_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC16_INIT;

    while(0 < size--)
    {
        crc ^= *data_p++;
        for(i = 0; i < 8; i++)
        {
            if (crc & 0x01)
            {
                crc = (crc >> 1) ^ CRC16_POLY_REF;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}

uint16_t crc16_calculate(void *data, int size)
{
    uint16_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC16_INIT;

    while(0 < size--)
    {
        crc = (crc << 8) ^ crc16_table[((crc >> 8) ^ *data_p++) & 0xFF];
    }

    return crc;
}

uint16_t crc16_calculate_ref(void *data, int size)
{
    uint16_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC16_INIT;

    while(0 < size--)
    {
        crc = (crc >> 8) ^ crc16_table[*data_p++ ^ (crc & 0xFF)];
    }

    return ~crc;
}

uint32_t crc32_calculate_directly(void *data, int size)
{
    int i;
    uint32_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC32_INIT;

    while(0 < size--)
    {
        crc ^= (*data_p++ << 24);
        for(i = 0; i < 8; i++)
        {
            if(crc & 0x80000000)
            {
                crc = (crc << 1) ^ CRC32_POLY;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

uint32_t crc32_calculate_directly_ref(void *data, int size)
{
    int i;
    uint32_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC32_INIT;

    while(0 < size--)
    {
        crc ^= *data_p++;
        for(i = 0; i < 8; i++)
        {
            if (crc & 0x01)
            {
                crc = (crc >> 1) ^ CRC32_POLY_REF;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}

uint32_t crc32_calculate(void *data, int size)
{
    uint32_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC32_INIT;

    while(0 < size--)
    {
        crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ *data_p++) & 0xFF];
    }

    return crc;
}

uint32_t crc32_calculate_ref(void *data, int size)
{
    uint32_t crc;
    uint8_t *data_p = (uint8_t *)data;

    crc = CRC32_INIT;

    while(0 < size--)
    {
        crc = (crc >> 8) ^ crc32_table[*data_p++ ^ (crc & 0xFF)];
    }

    return ~crc;
}



#ifndef __CREATE_CRC_TABLE
/*************************************************************************
                                CRC Table
 ************************************************************************/
/*
   CRC-8-Dallas/Maxim
   Poly: 0x31
   Init: 0xff
   Ref:  no
*/
unsigned char crc8_table[] = {
    0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97, 
    0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e, 
    0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4, 
    0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d, 
    0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11, 
    0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8, 
    0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52, 
    0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb, 
    0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa, 
    0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13, 
    0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9, 
    0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50, 
    0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c, 
    0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95, 
    0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f, 
    0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6, 
    0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed, 
    0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54, 
    0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae, 
    0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17, 
    0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b, 
    0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2, 
    0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28, 
    0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91, 
    0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0, 
    0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69, 
    0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93, 
    0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a, 
    0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56, 
    0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef, 
    0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15, 
    0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac, 
};

/*
   CRC-16-IBM
   Poly: 0x8005
   Init: 0xffff
   Ref:  no
*/
unsigned short crc16_table[] = {
    0x0000, 0x8005, 0x800f, 0x000a, 0x801b, 0x001e, 0x0014, 0x8011, 
    0x8033, 0x0036, 0x003c, 0x8039, 0x0028, 0x802d, 0x8027, 0x0022, 
    0x8063, 0x0066, 0x006c, 0x8069, 0x0078, 0x807d, 0x8077, 0x0072, 
    0x0050, 0x8055, 0x805f, 0x005a, 0x804b, 0x004e, 0x0044, 0x8041, 
    0x80c3, 0x00c6, 0x00cc, 0x80c9, 0x00d8, 0x80dd, 0x80d7, 0x00d2, 
    0x00f0, 0x80f5, 0x80ff, 0x00fa, 0x80eb, 0x00ee, 0x00e4, 0x80e1, 
    0x00a0, 0x80a5, 0x80af, 0x00aa, 0x80bb, 0x00be, 0x00b4, 0x80b1, 
    0x8093, 0x0096, 0x009c, 0x8099, 0x0088, 0x808d, 0x8087, 0x0082, 
    0x8183, 0x0186, 0x018c, 0x8189, 0x0198, 0x819d, 0x8197, 0x0192, 
    0x01b0, 0x81b5, 0x81bf, 0x01ba, 0x81ab, 0x01ae, 0x01a4, 0x81a1, 
    0x01e0, 0x81e5, 0x81ef, 0x01ea, 0x81fb, 0x01fe, 0x01f4, 0x81f1, 
    0x81d3, 0x01d6, 0x01dc, 0x81d9, 0x01c8, 0x81cd, 0x81c7, 0x01c2, 
    0x0140, 0x8145, 0x814f, 0x014a, 0x815b, 0x015e, 0x0154, 0x8151, 
    0x8173, 0x0176, 0x017c, 0x8179, 0x0168, 0x816d, 0x8167, 0x0162, 
    0x8123, 0x0126, 0x012c, 0x8129, 0x0138, 0x813d, 0x8137, 0x0132, 
    0x0110, 0x8115, 0x811f, 0x011a, 0x810b, 0x010e, 0x0104, 0x8101, 
    0x8303, 0x0306, 0x030c, 0x8309, 0x0318, 0x831d, 0x8317, 0x0312, 
    0x0330, 0x8335, 0x833f, 0x033a, 0x832b, 0x032e, 0x0324, 0x8321, 
    0x0360, 0x8365, 0x836f, 0x036a, 0x837b, 0x037e, 0x0374, 0x8371, 
    0x8353, 0x0356, 0x035c, 0x8359, 0x0348, 0x834d, 0x8347, 0x0342, 
    0x03c0, 0x83c5, 0x83cf, 0x03ca, 0x83db, 0x03de, 0x03d4, 0x83d1, 
    0x83f3, 0x03f6, 0x03fc, 0x83f9, 0x03e8, 0x83ed, 0x83e7, 0x03e2, 
    0x83a3, 0x03a6, 0x03ac, 0x83a9, 0x03b8, 0x83bd, 0x83b7, 0x03b2, 
    0x0390, 0x8395, 0x839f, 0x039a, 0x838b, 0x038e, 0x0384, 0x8381, 
    0x0280, 0x8285, 0x828f, 0x028a, 0x829b, 0x029e, 0x0294, 0x8291, 
    0x82b3, 0x02b6, 0x02bc, 0x82b9, 0x02a8, 0x82ad, 0x82a7, 0x02a2, 
    0x82e3, 0x02e6, 0x02ec, 0x82e9, 0x02f8, 0x82fd, 0x82f7, 0x02f2, 
    0x02d0, 0x82d5, 0x82df, 0x02da, 0x82cb, 0x02ce, 0x02c4, 0x82c1, 
    0x8243, 0x0246, 0x024c, 0x8249, 0x0258, 0x825d, 0x8257, 0x0252, 
    0x0270, 0x8275, 0x827f, 0x027a, 0x826b, 0x026e, 0x0264, 0x8261, 
    0x0220, 0x8225, 0x822f, 0x022a, 0x823b, 0x023e, 0x0234, 0x8231, 
    0x8213, 0x0216, 0x021c, 0x8219, 0x0208, 0x820d, 0x8207, 0x0202, 
};

/*
   CRC-32
   Poly: 0x4c11db7
   Init: 0xffffffff
   Ref:  no
*/
unsigned int crc32_table[] = {
    0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005, 
    0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 
    0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75, 
    0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd, 
    0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 
    0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d, 
    0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95, 
    0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1, 0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 
    0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072, 
    0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca, 
    0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 
    0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba, 
    0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692, 
    0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 
    0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2, 
    0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a, 
    0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 
    0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53, 
    0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b, 
    0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 
    0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b, 
    0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3, 
    0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7, 0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 
    0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3, 
    0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c, 
    0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 
    0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec, 
    0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654, 
    0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 
    0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4, 
    0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c, 
    0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4, 
};
#endif
