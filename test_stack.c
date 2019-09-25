#include "cutest/CuTest.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Add your tests here
 * A few sample tests
 * are provided
 */


// Tests for integer equals
void TestOne(CuTest *tc) {
  int two = 2;
  int four = 4;
  CuAssertIntEquals(tc, four, two+two);
}

// Test for string equals
void TestTwo(CuTest *tc) {
  char* lol = "lol";
  char* alsoLol = "lol";
  CuAssertStrEquals(tc, lol, alsoLol);
}

/*
Tests for True and False
pay attention to cleanStack function call as
you will be using it in your every test case
*/
void TestTrueFalse(CuTest *tc) {
  Stack* s = makeStack(10);
  CuAssertTrue(tc, isEmpty(s));
  push(s, 1, "black");
  CuAssertFalse(tc, isEmpty(s));
  cleanStack(s);
}


// Tests for Pointer equals
void TestPtrEquals(CuTest *tc) {
  Element* e = NULL;
  CuAssertPtrEquals(tc, NULL, e);
}

CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();

  /** ADD YOUR TESTS HERE **/
  SUITE_ADD_TEST(suite, TestOne);
  SUITE_ADD_TEST(suite, TestTwo);
  SUITE_ADD_TEST(suite, TestTrueFalse);
  SUITE_ADD_TEST(suite, TestPtrEquals);

  return suite;
}

// Don't edit anything below this line

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  CuSuite* ourSuite = StrUtilGetSuite();

  CuSuiteAddSuite(suite, ourSuite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuStringDelete(output);
  CuSuiteDelete(suite);
  free(ourSuite);
}

int main(void) {
  RunAllTests();
  return 0;
}
