#ifndef TESTBENCODEDECODER_H
#define TESTBENCODEDECODER_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestBencodeDecoder : public CppUnit::TestFixture
{
public:
  void testDecodeLegalInts();
  void testDecodeIllegalInts();

private:
  CPPUNIT_TEST_SUITE(TestBencodeDecoder);
  CPPUNIT_TEST(testDecodeLegalInts);
  CPPUNIT_TEST(testDecodeIllegalInts);
  CPPUNIT_TEST_SUITE_END();
};

#endif