#include "PngCrc32.h"
namespace trx
{
    PngCrc32::PngCrc32(void)
    {
        unsigned int poly = 0xedb88320;
        unsigned int temp = 0;
        unsigned int i;
        for(i = 0; i < CRC32_TABLE_CT; i++)
        {
            temp = i;
            for(int j = 8; j > 0; j--)
            {
                if((temp & 1) == 1)
                {
                    temp = (unsigned int)((temp >> 1) ^ poly);
                }
                else
                {
                    temp >>= 1;
                }
            }
            table[i] = temp;
        }
    }
    
    PngCrc32::~PngCrc32(void)
    {
        
    }
    
    unsigned int PngCrc32::ComputeChecksum(ubyte* bytes, size_t length)
    {
        unsigned int crc = 0xffffffff;
        for(int i = 0; i < length; i++)
        {
            ubyte index = (ubyte)(((crc) & 0xff) ^ bytes[i]);
            crc = (unsigned int)((crc >> 8) ^ table[index]);
        }
        return ~crc;
    }
}