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
#ifndef OPENLIB_UTILS_STRING_H
#define OPENLIB_UTILS_STRING_H

//-Supporting libraries
#include <stdint.h>
#include <sstream>
#include <iomanip>

//-Namespace/s
namespace openlib
{
    namespace string
    {

        /**
         * Converts a hex string to a binary form can have pre-appended 0x...
         * @param hex_str The source hex string
         * @param buffer The buffer where to store the converted data
         * @param buffer_length The buffer length
         */
        inline void hex_str_to_binary(const std::string& hex_str, void* buffer, const size_t& buffer_length)
        {
            //-Safety check
            if (NULL != buffer)
            {
                uint8_t* buffer_ptr = (uint8_t*) buffer;
                std::istringstream hex_chars_stream(hex_str);
                std::string tmp_two_characters;
                uint32_t value;
                size_t buffer_idx = 0;
                while (hex_chars_stream >> std::setw(2) >> tmp_two_characters && buffer_idx < buffer_length)
                {
                    if (tmp_two_characters == "0x")
                    {
                        continue;
                    }
                    std::istringstream ss2 (tmp_two_characters);
                    ss2 >> std::setbase(16) >> value;
                    buffer_ptr[buffer_idx++] = (uint8_t) value;
                }
            }
        }

    }; /*namespace string*/
};

#endif /* OPENLIB_UTILS_STRING_H */
