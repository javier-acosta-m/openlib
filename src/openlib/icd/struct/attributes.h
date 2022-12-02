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
#ifndef OPENLIB_ICD_ATTRIBUTES_H
#define OPENLIB_ICD_ATTRIBUTES_H

//-Supporting libraries
#include "openlib/common.h"
#include "openlib/enum/endianess.h"
#include "openlib/icd/enun/data_type.h"
#include <vector>
#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <new>
#include <assert.h>

//-Namespace/s
namespace openlib
{
	namespace icd
	{

        /**
         * Represents a data field descriptor
         * IMPORTAT: Does not have safety checks, ensure access matches the data type
         */
        class DataFieldDescriptor
        {
            public:
                DataFieldDescriptor( const DataType& data_type, const std::string& name,
                                const size_t& byte_offset, const size_t& bit_offset,
                                const size_t& num_bits, const openlib::Endianess& endianess):
                    data_type(data_type),
                    name(name),
                    byte_offset(byte_offset),
                    bit_offset(bit_offset),
                    num_bits(num_bits),
                    endianess(endianess),
                    data(NULL),
                    data_length(0)
                {
                    switch (data_type)
                    {
                        case DataType_uint8  : data_length = sizeof(uint8_t);    break;
                        case DataType_int8   : data_length = sizeof(int8_t);     break;
                        case DataType_uint16 : data_length = sizeof(uint16_t);   break;
                        case DataType_int16  : data_length = sizeof(int16_t);    break;
                        case DataType_uint32 : data_length = sizeof(uint32_t);   break;
                        case DataType_int32  : data_length = sizeof(int32_t);    break;
                        case DataType_enum   : data_length = sizeof(int);        break;
                        case DataType_ascii  : data_length = BIT2BYTE(num_bits); break;
                        case DataType_binary : data_length = BIT2BYTE(num_bits); break;
                        default:
                            //-Completeness
                            assert(false);
                    }
                    //-Allocate the data container
                    data = new uint8_t[data_length];
                }

                ~DataFieldDescriptor()
                {
                    DeleteArray(data);
                }

                //-8bits
                uint8_t* as_uint8()    { return reinterpret_cast<uint8_t*> (data);   }
                int8_t*  as_int8()     { return reinterpret_cast<int8_t* > (data);   }

                //-16-bits
                uint16_t* as_uint8()    { return reinterpret_cast<uint16_t*> (data); }
                int16_t*  as_int8()     { return reinterpret_cast<int16_t* > (data); }


                //-Fields
                DataType            data_type;
                std::string         name;
                size_t              byte_offset;
                size_t              bit_offset;
                size_t              num_bits;
                openlib::Endianess  endianess;      //-On the 'wire', used for loading and saving
                uint8_t*            data;           //-Holds the data
                size_t              data_length;    //-Length of the data
        };/*ICDDataEntry*/

        /**
         * Less Comparator for DataFieldDescriptor
         */
        struct DataDescriptorCompareLess
        {
            template <typename T>
            bool operator()(const DataFieldDescriptor* lhs, const DataFieldDescriptor* rhs) const
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


	    class Attributes
	    {
            typedef std::pair<DataFieldDescriptor*, void*>       DataValuePair;
            typedef std::vector<DataValuePair>              DataValuePairVector;
            typedef DataValuePairVector::const_iterator     DataValuePairVectorConstIterator;

	        public:
                Attributes(){}
                ~Attributes()
                {
                    //TODO: Cleanup
                }

                template<typename T>
                void add(DataFieldDescriptor* data_descriptor, T* value)
                {
                    if (NULL != data_descriptor && NULL != value)
                    {
                        DataValuePair pair = std::make_pair(data_descriptor, value);
                        fields.push_back(pair);
                    }
                }

                const DataValuePairVectorConstIterator begin() const
                {
                    return fields.begin();
                }

                const DataValuePairVectorConstIterator end() const
                {
                    return fields.end();
                }

	        private:
                DataValuePairVector fields;
	    };


	};/*namespace icd*/
};/*namespace openlib*/

#endif /*OPENLIB_ICD_ATTRIBUTES_H*/
