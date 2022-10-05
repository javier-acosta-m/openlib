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
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <climits>


//-Ancillary macros
#define BYTE2BIT(b) (b*8)
#define GET_BIT(array, n) ((((uint8_t*)array)[n/8] >> ((7-n)%8)) & 0x01)

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

		enum Endianess
		{
			BIG_ENDIAN,
			LITTLE_ENDIAN
		};

		//-Functions
		template <typename T> T swap_endian(T u);
		void print_buffer(void* buffer, const size_t& length);
		template <typename T> int extract(void* buffer, const size_t length, const size_t& byte_idx, const size_t& bit_pos, const size_t& bit_length, const Endianess& endianess, T* value);

		/**
		 * Returns the swaps byte orders of the value
		 * @tparam T Integral type
		 * @param value The value to flip the bytes
		 * @return the value with the bytes swapped
		 */
		template <typename T>
		T swap_endian(T value)
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
		 * Print buffer binary content
		 * @param buffer The pointer to the buffer to print (byte array)
		 * @param length The length in bytes
		 */
		inline void print_buffer(void* buffer, const size_t& length)
		{
			if (NULL != buffer)
			{
				for (size_t bit_idx=0; bit_idx < 8*length; ++bit_idx)
				{
					std::cout <<"bit "<< std::dec << bit_idx << " is "<< GET_BIT(buffer, bit_idx) << std::endl;
				}
			}
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
		int extract(void* buffer, const size_t length, const size_t& byte_idx, const size_t& bit_pos, const size_t& bit_length, const Endianess& endianess, T* value)
		{
			//-Check buffer
			if (NULL == buffer)
			{
				return ERROR_NULL_PARAMETER;
			}

			//-Check length
			if (BYTE2BIT(length) < (BYTE2BIT(byte_idx)+ bit_pos + bit_length))
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

			//-Debug
			#ifndef NDEBUG
			std::cout << "Extract" << std::endl;
			#endif

			//-Extract bits
			*value =0;
			for (size_t bit_idx=0; bit_idx < bit_length; ++bit_idx)
			{
				size_t bit_num = BYTE2BIT(byte_idx) + bit_pos + bit_idx;
				*value |= (GET_BIT(buffer, bit_num) << ( BYTE2BIT(sizeof(T))-1-bit_idx));

				//-Debug
				#ifndef NDEBUG
					uint8_t bit_value = GET_BIT(buffer, bit_num);
					std::cout <<"bit "<< std::dec << bit_num << " is "<< (int) bit_value << std::endl;
				#endif

			}
			//-Shift if necessary
			*value = *value >> (BYTE2BIT(sizeof(T))-bit_length);

			switch (endianess)
			{
				case BIG_ENDIAN:
					//-Do nothing
					break;

				case LITTLE_ENDIAN:
					*value = swap_endian(*value);
					break;
			}

			return SUCCESS;

		}
	}; /*namespace buffer*/
}; /*namespace openlib*/

//-Cleanup macros
#undef GET_BIT

#endif /* OPENLIB_BUFFER_HANDLER_H */
