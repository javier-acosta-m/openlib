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
#ifndef OPENLIB_ICD_BASE_PARSER_H
#define OPENLIB_ICD_BASE_PARSER_H

//-Supporting libraries
#include "openlib/icd/message_icd.h""
#include <string>
#include <map>
#include <set>

//-Namespace/s
namespace openlib
{
	namespace icd
	{
        enum ParserError
        {
            ParserError_None,
        };

		/**
		 * Parses a data field
		 */
		class BaseICDParser
		{
		    public:
                BaseICDParser(){};
				virtual ~BaseICDParser(){};

				virtual ParserError parse(const std::string& text, MessageICD& icd_message) = 0;
				virtual ParserError parse(const void* data, const size_t data_length, MessageICD& icd_message) = 0;

		}; /*class BaseICDParser*/





	};/*namespace icd*/
};/*namespace openlib*/

#endif /*OPENLIB_ICD_BASE_PARSER_H*/
