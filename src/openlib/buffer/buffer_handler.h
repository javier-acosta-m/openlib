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
#ifndef OPENLIB_BUFFER_HANDLER_H
#define OPENLIB_BUFFER_HANDLER_H

//-Supporting libraries
#include "openlib/common.h"
#include "openlib/enum/endianess.h"
#include "openlib/buffer/bit.h"
#include "openlib/icd/data_descriptor.h"
#include "openlib/icd/struct/icd_data_entry.h"
#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <climits>

namespace openlib
{
    namespace buffer
    {
        /**
         * Error, constants definitions
         */
        enum Error
        {
            SUCCESS = 0,                  	 /**< SUCCESS */
            ERROR_GENERIC			  = 1,   /**< ERROR_GENERIC */
            ERROR_NULL_PARAMETER	  = 2,   /**< ERROR_NULL_PARAMETER */
            ERROR_NOT_ENOUGH_DATA	  = 3,   /**< ERROR_NOT_ENOUGH_DATA */
            ERROR_CONTAINER_TOO_SMALL = 5,   /**< ERROR_CONTAINER_TOO_SMALL */
        };

        /**
         * Print buffer binary content
         * @param buffer The pointer to the buffer to print (byte array)
         * @param length The length in bytes
         */
        inline void print_buffer(const void* buffer, const size_t& length)
        {
            if (NULL != buffer)
            {
                for (size_t bit_idx=0; bit_idx < 8*length; ++bit_idx)
                {
                    std::cout <<"bit "<< std::dec << bit_idx << " is "<< (int) bit::get_bit_array(buffer, bit_idx) << std::endl;
                }
            }
        }

        /**
         * Returns the swaps byte orders of the value
         * @tparam T Integral type
         * @param value The value to flip the bytes
         * @return the value with the bytes swapped
         */
        template <typename T>
        inline T swap_endian(T value)
        {
            union
            {
                T value;
                uint8_t u8[sizeof(T)];
            } source, dest;

            source.value = value;
            for (size_t i = 0; i < sizeof(T); ++i)
            {
                dest.u8[i] = source.u8[sizeof(T) - i - 1];
            }
            return dest.value;
        }

        /**
         * Extract an integral type from a byte array
         * @tparam T Template type (integral type)
         * @param buffer The buffer from where to extract the value
         * @param length The length of the buffer
         * @param byte_idx The byte index (0 based) from where to extract the value
         * @param bit_pos The bit position from where the value shall be extracted , assumes on the wire order bit 0 | bit 1 | bit 2... bit n
         * @param bit_length The number of bits the value will contain
         * @param endianess The endianess of the value to be extracted
         * @param value The output value
         * @return int containing the error code (@see Error, 0: SUCCESSS)
         */
        template <typename T>
        inline int extract(const void* buffer, const size_t buffer_length, const size_t& byte_idx, const size_t& bit_pos, const size_t& bit_length, const Endianess& buffer_endianess, T* value)
        {
            //-Check buffer
            if (NULL == buffer)
            {
                return ERROR_NULL_PARAMETER;
            }

            //-Check length
            if (BYTE2BIT(buffer_length) < (BYTE2BIT(byte_idx)+ bit_pos + bit_length))
            {
                return ERROR_NOT_ENOUGH_DATA;
            }

            //-Check recipient of data
            if (bit_length % 8 != 0 && sizeof (T) < 1 + (bit_length / 8))
            {
              return ERROR_CONTAINER_TOO_SMALL;
            }
            else if (bit_length % 8 == 0 && sizeof (T) < (bit_length / 8))
            {
              return ERROR_CONTAINER_TOO_SMALL;
            }

            //-Extract bits
            *value =0;
            const size_t bit_offset = BYTE2BIT(byte_idx) + bit_pos;
            for (size_t bit_idx=0; bit_idx < bit_length; ++bit_idx)
            {
                //-Get the bit from the buffer
                uint8_t bit_value = bit::get_bit_array(buffer, bit_offset + bit_idx);

                //-Set the bit in the value
                bit::set_bit_array(value, bit_idx, bit_value);
            }

            //-Shift if necessary
            *value = *value >> (BYTE2BIT(sizeof(T))-bit_length);

            //-Check endianess
            if (buffer_endianess != system_endianess())
            {
                *value = swap_endian(*value);
            }

            return SUCCESS;

        }

        /**
         * Extract an integral type from a byte array
         * @tparam T Template type (integral type)
         * @param buffer The buffer from where to extract the value
         * @param length The length of the buffer
         * @param icd_entry The entry to be retrieved
         * @return int containing the error code (@see Error, 0: SUCCESSS)
         */
        template <typename T>
        inline int extract(const void* buffer, const size_t buffer_length, openlib::icd::ICDDataEntry<T>& icd_entry)
        {
            return extract(buffer, buffer_length, icd_entry.byte_offset, icd_entry.bit_offset, icd_entry.num_bits, icd_entry.endianess, &icd_entry.value);
        }

        /**
         * Insert an integral type from a byte array
         * @tparam T
         * @param buffer
         * @param buffer_length
         * @param byte_idx
         * @param bit_pos
         * @param bit_length
         * @param buffer_endianess
         * @param value
         * @return int containing the error code (@see Error, 0: SUCCESSS)
         */
        template <typename T>
        inline int insert(void* buffer, const size_t buffer_length, const size_t& byte_idx, const size_t& bit_pos, const size_t& bit_length, const Endianess& buffer_endianess, T* value)
        {
            //-Check buffer
            if (NULL == buffer)
            {
                return ERROR_NULL_PARAMETER;
            }

            //-Check length of teh buffer
            if (BYTE2BIT(buffer_length) < (BYTE2BIT(byte_idx) + bit_pos + bit_length))
            {
                return ERROR_NOT_ENOUGH_DATA;
            }

            //-Check recipient of data
            if (bit_length % 8 != 0 && sizeof(T) < 1 + (bit_length / 8))
            {
                return ERROR_CONTAINER_TOO_SMALL;
            }
            else if (bit_length % 8 == 0 && sizeof(T) < (bit_length / 8))
            {
                return ERROR_CONTAINER_TOO_SMALL;
            }

            //-Debug
            #ifndef NDEBUG
            std::cout << "Insert" << std::endl;
            #endif

            //-Check the buffer buffer_endianess vs the system
            T value_buffer_endianess = *value;
            if (system_endianess() != buffer_endianess)
            {
                value_buffer_endianess = swap_endian(value_buffer_endianess);
            }

            //-Set bits
            const size_t bit_offset = BYTE2BIT(byte_idx) + bit_pos;
            for (size_t bit_idx = 0; bit_idx < bit_length; ++bit_idx)
            {
                //-Get the buffer bit number
                uint8_t bit_value = bit::get_bit_array(&value_buffer_endianess, bit_idx);
                
                //-Set the bit in the buffer
                bit::set_bit_array(buffer, bit_offset + bit_idx, bit_value);
            }
            return SUCCESS;
        }


        /**
         * Insert (encodes) a data descriptor onto a buffer
         * @param buffer The buffer where to encode the data
         * @param buffer_length The buffer length
         * @param data_descriptor The data with descriptor
         * @return
         */
        inline int insert(void* buffer, const size_t buffer_length, openlib::icd::DataDescriptor& data_descriptor)
        {
            int retval = 0;
            using namespace openlib::icd;
            switch (data_descriptor.data_type())
            {
                case DataType_uint8:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_uint8());
                    break;

                case DataType_int8:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_int8());
                    break;


                case DataType_uint16:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_uint16());
                    break;

                case DataType_int16:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_int16());
                    break;

                case DataType_uint32:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_uint32());
                    break;

                case DataType_int32:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_int32());
                    break;

                case DataType_enum:
                    retval = insert(buffer, buffer_length,
                            data_descriptor.byte_offset(),
                            data_descriptor.bit_offset(),
                            data_descriptor.num_bits(),
                            data_descriptor.endianess(),
                            data_descriptor.as_enum());
                    break;

                case DataType_binary:
                case DataType_ascii:
                    memcpy(buffer, data_descriptor.as_binary(), std::min(buffer_length, data_descriptor.data_length()));
                    //retval = insert(buffer, buffer_length, data_descriptor.byte_offset, data_descriptor.bit_offset, data_descriptor.num_bits_, data_descriptor.endianess_, data_descriptor.as_uint8());
                    break;
                default:
                    break;
            }
            return retval;
        }

    }; /*namespace buffer*/
}; /*namespace openlib*/

//-Cleanup macros
#undef GET_BIT_ARRAY

#endif /* OPENLIB_BUFFER_HANDLER_H */
