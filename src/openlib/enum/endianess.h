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
#ifndef OPENLIB_ENUM_ENDIANESS_H
#define OPENLIB_ENUM_ENDIANESS_H

//-Suporting libraries
#include <string>

//-Namespace/s
namespace openlib
{
        /**
         * Endianess
         */
        enum Endianess
        {
            //-Safety
            Endianess_Min   = -1,

            //-Type
            Endianess_BigEndian = 0,
            Endianess_LittleEndian,

            //-Safety
            Endianess_Max,
            Endianess_Undefined,     /**< DataType_undefined */


        }; /*enum Endianess*/


        /**
         * Converts a Endianess top a human readable form std::string
         * @param value The Endianess type to be converted
         * @return std::string containing the human-readable string
         */
        inline std::string to_string(const Endianess& value)
        {
            switch (value)
            {
                case Endianess_BigEndian    : return "Big-Endian";
                case Endianess_LittleEndian : return "Little-Endian";
                default:
                    return "Invalid";
            }
        }

        /**
         * Returns an Endianess enum type from an integer
         * @param value The integer value to be converted
         * @return Endianess type representation of the given value
         */
        inline Endianess endianess_from_int(const int &value)
        {

            //-Check range
            if (value <= Endianess_Min || value >= Endianess_Max)
            {
                return Endianess_Undefined;
            }
            return (Endianess) value;
        }

        /**
         * Returns the current system endianess
         * @return Endianess of the system
         */
        inline Endianess system_endianess()
        {
            int n = 1;
            if(*(char *)&n == 1)
            {
                return Endianess_LittleEndian;
            }
            else
            {
                return Endianess_BigEndian;
            }
        }

};/*namespace openlib*/

#endif /*OPENLIB_ENUM_ENDIANESS_H*/
