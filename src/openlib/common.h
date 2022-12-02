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
#ifndef OPENLIB_COMMON_H
#define OPENLIB_COMMON_H

#include <stdint.h>

//-Ancillary macros
#define BYTE2BIT(b) (b*8)
#define BIT2BYTE(b) (b/8)
#define GET_BIT_ARRAY(array, n) ((((uint8_t*)array)[n/8] >> ((7-n)%8)) & 0x01)
#define SET_BIT_ARRAY(array, n, bit_value) ((((uint8_t*)array)[n/8] >> ((7-n)%8)) & 0x01)

#define CLR_BIT_VALUE(bit_num, value) (value &= ~(1 << bit_num))
#define SET_BIT_VALUE(bit_num, value) (value |=  (1 << bit_num))

namespace openlib
{
    /**
     * Safe delete of a pointer
     * @tparam T Parametric pointer type
     */
    template< class T > void Delete( T*& ptr )
    {
        if (0 != ptr){
            delete ptr;
            ptr = 0;
        }
    }

    /**
     * Safe delete of an array
     * @tparam T Parametric array pointer type
     */
    template< class T > void DeleteArray( T*& ptr_array )
    {
        if (0 != ptr_array)
        {
            delete[] ptr_array;
            ptr_array = 0;
        }
    }

};

#endif /* OPENLIB_COMMON_H */
