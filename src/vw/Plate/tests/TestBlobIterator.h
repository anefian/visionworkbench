// __BEGIN_LICENSE__
// Copyright (C) 2006, 2007 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


#include <cxxtest/TestSuite.h>

#include <vw/Plate/Blob.h>

using namespace std;
using namespace vw;
using namespace vw::platefile;

class TestBlobIterator : public CxxTest::TestSuite
{
  boost::shared_array<uint8> m_test_data;
  boost::shared_array<uint8> m_verify_data;
public:

  TestBlobIterator() {
    m_test_data = boost::shared_array<uint8>(new uint8[20]);
    for (int i = 0; i < 20; ++i) {
      m_test_data[i] = i;
    }
  }

  void test_iterator()
  {

    unlink("/tmp/foo.blob");
    boost::shared_ptr<Blob> blob(new Blob("/tmp/foo.blob"));

    // First, create some entries for the blob
    TileHeader dummy_header0;
    dummy_header0.set_col(0);
    dummy_header0.set_row(953);
    dummy_header0.set_depth(3);
    dummy_header0.set_transaction_id(1024);
    dummy_header0.set_filetype("foo");

    TileHeader dummy_header1;
    dummy_header1.set_col(33);
    dummy_header1.set_row(91);
    dummy_header1.set_depth(321);
    dummy_header1.set_transaction_id(1034);
    dummy_header1.set_filetype("bar");

    TileHeader dummy_header2;
    dummy_header2.set_col(22);
    dummy_header2.set_row(1);
    dummy_header2.set_depth(322);
    dummy_header2.set_transaction_id(1054);
    dummy_header2.set_filetype("baz");
    
    // Write some dummy data to the file with various index entries
    int64 offset = blob->write(dummy_header0, m_test_data, 20);
    offset = blob->write(dummy_header1, m_test_data, 20);
    offset = blob->write(dummy_header2, m_test_data, 20);
    
    // Create an iterator
    Blob::iterator iter = blob->begin();

    TileHeader result = *iter;
    TS_ASSERT_EQUALS(result.col(), dummy_header0.col());
    TS_ASSERT_EQUALS(result.row(), dummy_header0.row());
    TS_ASSERT_EQUALS(result.depth(), dummy_header0.depth());
    TS_ASSERT_EQUALS(result.transaction_id(), dummy_header0.transaction_id());
    TS_ASSERT_EQUALS(result.filetype(), dummy_header0.filetype());
    TS_ASSERT_DIFFERS(iter, blob->end());

    ++iter;
    result = *iter;
    TS_ASSERT_EQUALS(result.col(), dummy_header1.col());
    TS_ASSERT_EQUALS(result.row(), dummy_header1.row());
    TS_ASSERT_EQUALS(result.depth(), dummy_header1.depth());
    TS_ASSERT_EQUALS(result.transaction_id(), dummy_header1.transaction_id());
    TS_ASSERT_EQUALS(result.filetype(), dummy_header1.filetype());
    TS_ASSERT_DIFFERS(iter, blob->end());

    ++iter;
    result = *iter;
    TS_ASSERT_EQUALS(result.col(), dummy_header2.col());
    TS_ASSERT_EQUALS(result.row(), dummy_header2.row());
    TS_ASSERT_EQUALS(result.depth(), dummy_header2.depth());
    TS_ASSERT_EQUALS(result.transaction_id(), dummy_header2.transaction_id());
    TS_ASSERT_EQUALS(result.filetype(), dummy_header2.filetype());
    TS_ASSERT_DIFFERS(iter, blob->end());

    ++iter;
    TS_ASSERT_EQUALS(iter, blob->end());
  }

    
}; // class TestBlobIterator
