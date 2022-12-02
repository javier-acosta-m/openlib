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
#include "openlib/utils/utils.h"
#include <algorithm>
#include <map>
#include <string>
#include <assert.h>

//-Namespace/s
namespace openlib
{
    namespace icd
    {
        /**
         * Represents a data descriptor
         */
        class DataDescriptor
        {
            public:
                //-Types
                typedef std::map<int,std::string> EnumMap;
                typedef EnumMap::const_iterator   EnumMapConstIterator;

                DataDescriptor( const DataType& data_type, const std::string& name,
                                const size_t& byte_offset, const size_t& bit_offset,
                                const size_t& num_bits, const openlib::Endianess& endianess):
                    data_type_(data_type),
                    name_(name),
                    byte_offset_(byte_offset),
                    bit_offset_(bit_offset),
                    num_bits_(num_bits),
                    endianess_(endianess),
                    data_(NULL),
                    data_length_(0)
                {
                    switch (data_type)
                    {
                        case DataType_uint8  : data_length_ = sizeof(uint8_t);    break;
                        case DataType_int8   : data_length_ = sizeof(int8_t);     break;
                        case DataType_uint16 : data_length_ = sizeof(uint16_t);   break;
                        case DataType_int16  : data_length_ = sizeof(int16_t);    break;
                        case DataType_uint32 : data_length_ = sizeof(uint32_t);   break;
                        case DataType_int32  : data_length_ = sizeof(int32_t);    break;
                        case DataType_enum   : data_length_ = sizeof(int);        break;
                        case DataType_ascii  : data_length_ = BIT2BYTE(num_bits); break;
                        case DataType_binary : data_length_ = BIT2BYTE(num_bits); break;
                        default:
                            //-Completeness
                            assert(false);
                    }
                    //-Allocate the data container
                    data_ = new uint8_t[data_length_];
                }

                /**
                 * Destructor
                 */
                ~DataDescriptor()
                {
                    DeleteArray(data_);
                }

                //-Accessor
                inline const DataType& data_type() const            {return this->data_type_;   }
                inline const std::string& name() const              {return this->name_;        }
                inline const size_t& byte_offset() const            { return byte_offset_;      }
                inline const size_t& bit_offset() const             { return bit_offset_;       }
                inline const size_t& num_bits() const               { return num_bits_;         }
                inline const openlib::Endianess& endianess() const  { return endianess_;        }
                inline const uint8_t* data() const                  { return data_;             }
                inline const size_t& data_length() const            { return data_length_;      }
                inline const EnumMap& enum_map() const              { return enum_map_;         }

                //-8bits
                inline uint8_t* as_uint8();
                inline int8_t*  as_int8();
                int8_t& int8()    {  return *(reinterpret_cast<int8_t*> (&data_[0])); }
                uint8_t& uint8()  {  return *(reinterpret_cast<uint8_t*> (&data_[0])); }

                //-16-bits
                inline uint16_t* as_uint16();
                inline int16_t*  as_int16();
                int16_t& int16()    {  return *(reinterpret_cast<int16_t*> (&data_[0])); }
                uint16_t& uint16()  {  return *(reinterpret_cast<uint16_t*> (&data_[0])); }


                //-32-bits
                inline uint32_t* as_uint32();
                inline int32_t*  as_int32();
                int32_t& int32()    {  return *(reinterpret_cast<int32_t*> (&data_[0])); }
                uint32_t& uint32()  {  return *(reinterpret_cast<uint32_t*> (&data_[0])); }

                //-Enummeration
                inline int* as_enum();
                int& enum_val()     {  return *(reinterpret_cast<int*> (&data_[0])); }

                //-ASCII
                inline char* as_ascii();

                //-Binary
                inline uint8_t* as_binary();

                //-Ancillary                
                inline void set(const std::string& hex_str);
                inline void set(const void* buffer, const size_t buffer_length);
                inline void set_enum(const int&, const std::string& str_value);
                inline std::string get_enum(const int& value, bool& found);
                

            protected:
                //-Fields
                DataType            data_type_;
                std::string         name_;
                size_t              byte_offset_;
                size_t              bit_offset_;
                size_t              num_bits_;
                openlib::Endianess  endianess_;
                uint8_t*            data_;
                size_t              data_length_;
                EnumMap             enum_map_;
        };/*DataDescriptor*/

        /**
         * Less Comparator for DataDescriptor
         */
        typedef struct DataDescriptorPtrCompareLess
        {
            bool operator()(const DataDescriptor* lhs, const DataDescriptor* rhs) const
            {
                if (lhs->byte_offset() == rhs->byte_offset())
                {
                    return lhs->bit_offset() < rhs->bit_offset();
                }
                else
                {
                    return lhs->byte_offset() < rhs->byte_offset();
                }
            }
        }DataDescriptorPtrCompareLess;


        uint8_t* DataDescriptor::as_uint8()
        {
            uint8_t* retval = NULL;
            if (DataType_uint8 == data_type_){
                retval = reinterpret_cast<uint8_t* > (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }

        int8_t* DataDescriptor::as_int8()
        {
            int8_t* retval = NULL;
            if (DataType_int8 == data_type_){
                retval = reinterpret_cast<int8_t* > (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }


        uint16_t* DataDescriptor::as_uint16()
        {
            uint16_t* retval = NULL;
            if (DataType_uint16 == data_type_){
                retval = reinterpret_cast<uint16_t* > (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }

        int16_t* DataDescriptor::as_int16()
        {
            int16_t* retval = NULL;
            if (DataType_int16 == data_type_){
                retval = reinterpret_cast<int16_t* > (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }

        uint32_t* DataDescriptor::as_uint32()
        {
            uint32_t* retval = NULL;
            if (DataType_uint32 == data_type_){
                retval = reinterpret_cast<uint32_t* > (data_);
            }
            return retval;
        }

        int32_t* DataDescriptor::as_int32()
        {
            int32_t* retval = NULL;
            if (DataType_int32 == data_type_){
                retval = reinterpret_cast<int32_t*> (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }

        int* DataDescriptor::as_enum()
        {
            int* retval = NULL;
            if (DataType_enum == data_type_){
                retval = reinterpret_cast<int*> (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }

        char* DataDescriptor::as_ascii()
        {
            char* retval = NULL;
            if (DataType_ascii == data_type_){
                retval = reinterpret_cast<char*> (data_);
            }
            else{
                assert(false);
            }
            return retval;
        }

        //-Binary
        uint8_t* DataDescriptor::as_binary()
        {
            uint8_t* retval = NULL;
            if (DataType_binary == data_type_){
                retval = data_;
            }
            else{
                assert(false);
            }
            return retval;
        }

        /**
         * Set the value from a hex string
         * @param hex_str
         */
        void DataDescriptor::set(const std::string& hex_str)
        {
            switch (data_type_)
            {
                case DataType_uint8  :
                    *as_uint8() = openlib::convert<uint8_t>(hex_str);
                    break;

                case DataType_int8   :
                    *as_int8()  = openlib::convert<int8_t>(hex_str);
                    break;

                case DataType_uint16 :
                    *as_uint16() = openlib::convert<uint16_t>(hex_str);
                    break;

                case DataType_int16  :
                    *as_int16()  = openlib::convert< int16_t>(hex_str);
                    break;

                case DataType_uint32 :
                    *as_uint32() = openlib::convert<uint32_t>(hex_str);
                    break;

                case DataType_int32  :
                    *as_int32()  = openlib::convert<int32_t>(hex_str);
                    break;

                case DataType_enum   :
                    *as_enum()   = openlib::convert<int>(hex_str);
                    break;

                case DataType_ascii  :
                    memcpy(data_, hex_str.c_str(), std::min(hex_str.length(), data_length_));
                    break;

                case DataType_binary :

                    break;

                default:
                    //-Completeness
                    assert(false);
            }
        }

        /**
         * Copy a buffer onto the field
         * @param buffer The buffer from where to copy
         * @param buffer_length The length of the buffer to copy
         */
        void DataDescriptor::set(const void* buffer, const size_t buffer_length)
        {
            assert(buffer_length <= this->data_length_);
            memcpy(data_, buffer, std::min(buffer_length, data_length_));
        }

        /**
         * Set an enumeration map
         * @param value The integer that represents the enum
         * @param str_value The string value map
         */
        void DataDescriptor::set_enum(const int& value, const std::string& str_value)
        {
            if (DataType_enum == data_type_)
            {
                this->enum_map_[value] = str_value;
            }
            else{
                assert(false);
            }
        }

        /**
         * Retrieve the string enum mapped
         * @param value The value to be retrieved
         * @param found (output) whether the string mapped was found for the given 'value'
         * @return string containing the mapped 'value' (@invalid type) if trying to access a non-enum type
         */
        std::string DataDescriptor::get_enum(const int& value, bool& found)
        {
            std::string retval = "";
            found = false;
            if (DataType_enum == data_type_)
            {
                EnumMapConstIterator it = enum_map_.find(value);
                if (it != enum_map_.end())
                {
                    found = true;
                    retval = it->second;
                }
            }else
            {
                retval = "@invalid type:" + to_string(data_type_);
                assert(false);
            }
            return retval;
        }

    };/*namespace icd*/
};/*namespace openlib*/

#endif /*OPENLIB_ICD_ATTRIBUTES_H*/
