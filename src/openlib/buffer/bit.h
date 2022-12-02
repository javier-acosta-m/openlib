/**
 * MIT License
 * Copyright (c) 2022 Javier I. Acosta M.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef OPENLIB_BUFFER_HANDLER_BIT_H
#define OPENLIB_BUFFER_HANDLER_BIT_H

//-Supporting libraries
#include "openlib/common.h"

#define BYTE2BIT(b) (b*8)
#define BIT2BYTE(b) (b/8)

namespace openlib
{
    namespace bit
    {
        /**
         * Sets a bit value on an contiguous piece of memory
         * IMPORTANT: NO CHECKS!!!!!!!!
         * @param buffer The pointer to the buffer
         * @param bit_num The bit number count assuming starting from 0...n i.e: setting bit 15 to 1 --> 0x0001
         * @param value The bit value (0 or 1)
         */
        inline void set_bit_array(void* buffer, const size_t& bit_num, const uint8_t& value)
        {
            uint8_t* buffer_ptr = (uint8_t*) buffer;
            const size_t byte_num = bit_num/8;
            const size_t bit_num_local  = 7-(bit_num%8);
            buffer_ptr[byte_num] = buffer_ptr[byte_num] & ~(0x01 << bit_num_local);
            buffer_ptr[byte_num] = buffer_ptr[byte_num] | (((value==0)?0:1) << bit_num_local);
        }

        /**
         * Get a bit value on an contiguous piece of memory
         * IMPORTANT: NO CHECKS!!!!!!!!
         * @param buffer The pointer to the buffer
         * @param bit_num The bit number count assuming starting from 0...n i.e: setting bit 15 to 1 --> 0x0001
         * @return The bit value (0 or 1)
         */
        inline uint8_t get_bit_array(const void* buffer, const size_t& bit_num)
        {
            uint8_t* buffer_ptr = (uint8_t*) buffer;
            const size_t byte_num_local = bit_num/8;
            const size_t bit_num_local  = 7-(bit_num%8);
            return (buffer_ptr[byte_num_local] & (0x01 << bit_num_local)) >> bit_num_local;
        }

    }; /*namespace bit*/
}; /*namespace openlib*/

//-Cleanup macros
#undef GET_BIT_ARRAY

#endif /* OPENLIB_BUFFER_HANDLER_BIT_H */
