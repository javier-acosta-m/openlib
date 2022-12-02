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
#ifndef OPENLIB_ICD_MESSAGE_ICD_H
#define OPENLIB_ICD_MESSAGE_ICD_H

//-Supporting libraries
#include "openlib/non-copyable/non_copyable.h"
#include "openlib/icd/struct/icd_data_entry.h"
#include "openlib/icd/enun/parser_error.h"
#include "openlib/icd/data_descriptor.h"
#include <string>
#include <map>
#include <set>

//-Namespace/s
namespace openlib
{
    namespace icd
    {
        /**
         * Represents an Message ICD object descriptor
         */
        class MessageICD
        {            
            public:
                typedef std::set<DataDescriptor*, DataDescriptorPtrCompareLess> DataFieldSet;
                typedef DataFieldSet::const_iterator                            DataFieldSetConstIterator;

                //-Constructor & Destructor
                MessageICD() {};
                virtual ~MessageICD(){};

                //-Accessor & Mutators
                inline const DataFieldSet& data_field_set() const;

                //-Ancillary functions
                ParserError encode(std::uint8_t* buffer, const size_t& buffer_length);
                ParserError decode(const std::uint8_t* buffer, const size_t& buffer_length);

            protected:
                //-Functions
                inline void add(DataDescriptor* data_descriptor);

                //-Fields
                DataFieldSet data_field_set_;

        }; /*class ICDMessage*/

        /**
         * Access to data field set of the ICD message
         * @return The reference to the 'data_field_set_'
         */
        const MessageICD::DataFieldSet& MessageICD::data_field_set() const
        {
            return data_field_set_;
        }

        /**
         * Add a data descriptor to the ICD Message        
         * @param data_descriptor The data descriptor to be added
         */
        void MessageICD::add(DataDescriptor* data_descriptor)
        {
            if (NULL != data_descriptor)
            {
                data_field_set_.insert(data_descriptor);
            }
        }

    };/*namespace icd*/
};/*namespace openlib*/

#endif /*OPENLIB_ICD_MESSAGE_ICD_H*/
