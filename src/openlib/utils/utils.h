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
#ifndef OPENLIB_UTILS__H
#define OPENLIB_UTILS__H

//-Supporting libraries
#include <stdint.h>
#include <sstream>

namespace openlib
{
    /**
     * Converts a hex string to a value
     * @tparam T2
     * @tparam T1
     * @param in
     * @return
     */
    template<typename T2, typename T1>
    inline T2 convert(const T1 &in) {
        T2 out;
        uint64_t tmp;
        std::stringstream ss;
        ss << std::hex << in;
        ss >> tmp;
        memcpy(&out, &tmp, sizeof(T2));
        return out;
    }

};

#endif /* OPENLIB_COMMON_H */
