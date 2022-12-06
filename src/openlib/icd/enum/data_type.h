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
#ifndef OPENLIB_ICD_ENUM_DATA_TYPE_H
#define OPENLIB_ICD_ENUM_DATA_TYPE_H

//-Used namespaces
#include <string>

//-Namespace/s
namespace openlib
{
    namespace icd
    {

        /**
         * Basic Data Type
         */
        enum DataType
        {
            DataType_Min   = -1,

            DataType_uint8 = 0,     /**< DataType_uint8 */
            DataType_int8,          /**< DataType_int8 */
            DataType_uint16,        /**< DataType_uint16 */
            DataType_int16,         /**< DataType_int16 */
            DataType_uint32,        /**< DataType_uint32 */
            DataType_int32,         /**< DataType_int32 */
            DataType_enum,          /**< DataType_enum */
            DataType_ascii,         /**< DataType_ascii */
            DataType_binary,        /**< DataType_binary */

            DataType_Max,
            DataType_Undefined,     /**< DataType_undefined */


        }; /*enum DataType*/

        //-Supporting functions
        inline std::string to_string(const DataType &value)
        {
            switch (value)
            {
                case DataType_uint8  : return "uint8";
                case DataType_int8   : return "int8";
                case DataType_uint16 : return "uint16";
                case DataType_int16  : return "int16";
                case DataType_uint32 : return "uint32";
                case DataType_int32  : return "int32";
                case DataType_ascii  : return "ascii";
                case DataType_enum   : return "enum";
                case DataType_binary : return "binary";
                default:
                    return "invalid";
            }
        }

        inline DataType data_type_from_int(const int &value)
        {
            //-Check range
            if (value <= DataType_Min || value >= DataType_Max)
            {
                return DataType_Undefined;
            }
            return (DataType) value;
        }

    };/*namespace icd*/
};/*namespace openlib*/

#endif /*OPENLIB_ICD_ENUM_DATA_TYPE_H*/
