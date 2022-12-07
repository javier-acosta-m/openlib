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
#ifndef OPENLIB_ICD_DATA_ENTRY_H
#define OPENLIB_ICD_DATA_ENTRY_H

//-Supporting libraries
#include "openlib/enum/endianess.h"
#include "openlib/icd/enum/data_type.h"
#include <string>
#include <map>
#include <set>

//-Namespace/s
namespace openlib
{
	namespace icd
	{
		/**
		 * A data field entry
		 */
	    template <typename T>
		struct ICDDataEntry
		{
            ICDDataEntry(const size_t& byte_offset, const size_t& bit_offset, const size_t& num_bits, const Endianess& endianess) :
                byte_offset(byte_offset),
                bit_offset(bit_offset),
                num_bits(num_bits),
                endianess(endianess)
            {
            }
			size_t              byte_offset;
			size_t              bit_offset;
			size_t              num_bits;
            openlib::Endianess  endianess;
			T                   value;

		};/*ICDDataEntry*/

        /**
         * Less Comparator for ICDDataEntry Pointer
         */
        struct ICDDataEntryPtrCompareLess
        {
	        template <typename T>
		    bool operator()(const ICDDataEntry<T>* lhs, const ICDDataEntry<T>* rhs) const
            {
		        if (lhs->byte_offset == rhs->byte_offset)
                {
		            return lhs->bit_offset < rhs->bit_offset;
                }
                else
                {
                    return lhs->byte_offset < rhs->byte_offset;
                }
            }
        };

	};/*namespace icd*/
};/*namespace openlib*/

#endif /*OPENLIB_ICD_DATA_PARSER_H*/
