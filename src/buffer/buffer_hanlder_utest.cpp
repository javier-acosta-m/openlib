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
//-Supporting libraries
#include "buffer_handler.h"
#include <stdint.h>
#include <string.h>
#include "CppUTest/TestHarness.h"

//-Used namespaces
using namespace std;
using namespace openlib::buffer;

TEST_GROUP(buffer_hanlder)
{
	size_t		buffer_length;
	uint8_t* 	buffer;
	const uint8_t 	byte0 = 0b00010000;
	const uint8_t 	byte1 = 0b00011001;
	const uint8_t 	byte2 = 0b10000001;
	const uint8_t 	byte3 = 0b01111101;

  void setup()
  {
	  buffer_length = 4;
	  buffer = new uint8_t[buffer_length];
	  memset(buffer, 0x00, buffer_length);

	  //buffer[0] =  0b00010000;
	  buffer[0] =  byte0;
	  buffer[1] =  byte1;
	  buffer[2] =  byte2;
	  buffer[3] =  byte3;
	  //print_buffer(buffer, 3);
  }

  void teardown()
  {
	  delete[] buffer;
  }
};

//==========================
// TESTING UINT8
//==========================

TEST(buffer_hanlder, Test_uint8_aligned)
{
	//-Test uint8 aligned
	int ok;
	size_t byte_idx = 0;
	size_t bit_pos = 0;
	size_t bit_length = 8;

	uint8_t value_uint8_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_be) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL(0x10, value_uint8_be);

	uint8_t value_uint8_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_uint8_le);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_le) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL(0x10, value_uint8_le);

}

TEST(buffer_hanlder, Test_uint8_misaligned)
{
	//-Test uint8
	int ok;

	size_t byte_idx = 0;
	size_t bit_pos = 1;
	size_t bit_length = 8;

	uint8_t value_uint8_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_be) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL((byte0 << 1), value_uint8_be);

	uint8_t value_uint8_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_uint8_le);
	//std::cout << "\nOK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_be) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL((byte0 << 1), value_uint8_le);
}

TEST(buffer_hanlder, Test_uint8_misaligned_cross_boundary)
{
	//-Test uint8
	int ok;
	size_t byte_idx = 2;
	size_t bit_pos = 7;
	size_t bit_length = 8;

	uint8_t value_uint8_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_be) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL((byte2 & 0x01) << 7 | byte3 >> 1, value_uint8_be);

	uint8_t value_uint8_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_uint8_le);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_le) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL((byte2 & 0x01) << 7 | byte3 >> 1, value_uint8_le);
}

TEST(buffer_hanlder, Test_uint8_smaller_misaligned_cross_boundary)
{
	int ok;
	size_t byte_idx = 2;
	size_t bit_pos = 7;
	size_t bit_length = 4;

	uint8_t value_uint8_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_be) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL((byte2 & 0x01) << 3  | byte3 >> 5 , value_uint8_be);

	uint8_t value_uint8_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_uint8_le);
	//std::cout << "OK=" << ok << std::endl;
	//std::cout << "Values is 0x" << hex <<  static_cast<int>(value_uint8_le) << std::endl;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL((byte2 & 0x01) << 3  | byte3 >> 5 , value_uint8_le);
}

//==========================
// TESTING INT16
//==========================

TEST(buffer_hanlder, Test_int16_aligned)
{
	//-Test int16 aligned
	int ok;
	size_t byte_idx = 0;
	size_t bit_pos = 0;
	size_t bit_length = 16;

	int16_t value_int16_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_int16_be);
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL( (int16_t) (byte0 << 8 | byte1 << 0), value_int16_be);

	int16_t value_int16_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_int16_le);
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL( (int16_t) (byte0 << 0 | byte1 << 8), value_int16_le);
}

TEST(buffer_hanlder, Test_int16_misaligned)
{
	//-Test int16 aligned
	int ok;
	size_t byte_idx = 0;
	size_t bit_pos = 1;
	size_t bit_length = 16;

	int16_t value_int16_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_int16_be);
	uint8_t msb_byte_expected = (byte0 << 1 | byte1 >> 7);
	uint8_t lsb_byte_expected = (byte1 << 1 | byte2 >> 7);
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL( (int16_t) (msb_byte_expected << 8 | lsb_byte_expected << 0) , value_int16_be);

	int16_t value_int16_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_int16_le);
	msb_byte_expected = (byte0 << 1 | byte1 >> 7);
	lsb_byte_expected = (byte1 << 1 | byte2 >> 7);
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL( (int16_t) (lsb_byte_expected << 8 | msb_byte_expected << 0) , value_int16_le);
}

TEST(buffer_hanlder, Test_int16_negative)
{
	//-Test int16 aligned
	int ok;
	size_t byte_idx = 2;
	size_t bit_pos = 0;
	size_t bit_length = 16;

	int16_t value_int16_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_int16_be);
	uint8_t msb_byte_expected = byte2;
	uint8_t lsb_byte_expected = byte3;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL( (int16_t) (msb_byte_expected << 8 | lsb_byte_expected << 0) , value_int16_be);
	CHECK(value_int16_be < 0);

	int16_t value_int16_le = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::LITTLE_ENDIAN, &value_int16_le);
	msb_byte_expected = byte2;
	lsb_byte_expected = byte3;
	CHECK_EQUAL(ok, SUCCESS);
	CHECK_EQUAL( (int16_t) (lsb_byte_expected << 8 | msb_byte_expected << 0) , value_int16_le);
	CHECK(value_int16_le > 0);
}

//==========================
// ERROR TESTING
//==========================
TEST(buffer_hanlder, Test_error_null_parameter)
{
	int ok;
	size_t byte_idx = buffer_length-1;
	size_t bit_pos 	= 7;
	size_t bit_length = 4;

	uint8_t value_uint8_be = 0;
	ok = extract(NULL, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	CHECK_EQUAL(ok, ERROR_NULL_PARAMETER);
}

TEST(buffer_hanlder, Test_error_out_of_boundary)
{
	int ok;
	size_t byte_idx = buffer_length-1;
	size_t bit_pos 	= 7;
	size_t bit_length = 4;

	uint8_t value_uint8_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	CHECK_EQUAL(ok, ERROR_NOT_ENOUGH_DATA);
}

TEST(buffer_hanlder, Test_error_out_constainer_too_small)
{
	int ok;
	size_t byte_idx = 0;
	size_t bit_pos 	= 0;
	size_t bit_length = 9;

	uint8_t value_uint8_be = 0;
	ok = extract(buffer, buffer_length, byte_idx, bit_pos, bit_length, Endianess::BIG_ENDIAN, &value_uint8_be);
	//std::cout << "OK=" << ok << std::endl;
	CHECK_EQUAL(ok, ERROR_CONTAINER_TOO_SMALL);
}
