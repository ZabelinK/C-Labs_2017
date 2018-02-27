#define BOOST_TEST_MODULE testPart1

#define _USE_MATH_DEFINES
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <iostream>
#include "book.h"
#include "impl.h"

BOOST_AUTO_TEST_CASE(back_action)
{
  std::stringstream in("add 123 \"qwe\"\nshow current\nback\nshow current"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "123 qwe\n<EMPTY>\n");
}

BOOST_AUTO_TEST_CASE(back_and_forward_action)
{
  std::stringstream in("add 123 \"qwe\"\nshow current\nback\nshow current\nforward\nshow current"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "123 qwe\n<EMPTY>\n123 qwe\n");
}

BOOST_AUTO_TEST_CASE(two_back__action)
{
  std::stringstream in("add 1 \"q\"\nadd 2 \"w\"\nadd 3 \"e\"\nmove current 1\nmove current 1\n"
                       "show current\nback\nshow current\nback\nshow current\n"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "3 e\n2 w\n1 q\n");
}

BOOST_AUTO_TEST_CASE(different_action_back)
{
  std::stringstream in("add 1 \"q\"\ndelete current\nshow current\nback\nshow current\n"
                       "back\nshow current"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "<EMPTY>\n1 q\n<EMPTY>\n");
}

BOOST_AUTO_TEST_CASE(differen_action_back_with_forward)
{
  std::stringstream in("add 1 \"q\"\ndelete current\nshow current\nback\nshow current\n"
                       "back\nshow current\nforward\nshow current\nforward\nshow current"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "<EMPTY>\n1 q\n<EMPTY>\n1 q\n<EMPTY>\n");
}

BOOST_AUTO_TEST_CASE(back_insert_action)
{
  std::stringstream in("add 1 \"q\"\ninsert before current 2 \"w\"\nmove current first\nshow current\n"
                       "back\nshow current"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "2 w\n1 q\n");
}

BOOST_AUTO_TEST_CASE(back_and_forward_insert_action)
{
  std::stringstream in("add 1 \"q\"\ninsert before current 2 \"w\"\nmove current first\nshow current"
                       "\nback\nshow current\nforward\nmove current first\nshow current"), out;

  doPart1(in, out);

  BOOST_CHECK_EQUAL(out.str(), "2 w\n1 q\n2 w\n");
}

BOOST_AUTO_TEST_CASE(robust_add)
{
  PhoneBook book;
  PhoneBook::robust_iterator it = book.begin();
  book.add(note_t{"1", "a"});
  BOOST_CHECK(it == book.begin());
}

BOOST_AUTO_TEST_CASE(robust_insert)
{
  PhoneBook book;
  PhoneBook::robust_iterator it = book.begin();
  book.insert(it, note_t{"1", "a"});
  BOOST_CHECK(it == book.begin());
}

BOOST_AUTO_TEST_CASE(robus_erase)
{
  PhoneBook book;
  PhoneBook::robust_iterator it = book.begin();
  book.insert(it, note_t{"1", "a"});
  book.insert(it, note_t{"2", "b"});
  book.erase(it);
  BOOST_CHECK(it == book.begin());
}
