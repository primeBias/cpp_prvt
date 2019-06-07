#include <vector>
#include <string>

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;
double epsilon = .000001;
std::vector<std::string> failed_tests;

#define ASSERT(function, result, test_case)\
	try {\
		++tests_run;\
		if (function == result) ++tests_passed;\
		else { ++tests_failed; failed_tests.push_back(test_case); }\
		cin.clear();\
		cin.ignore(cin.rdbuf()->in_avail(), '\n');\
	} catch (exception& e) {\
		++tests_failed; failed_tests.push_back(test_case);\
		cin.clear();\
		cin.ignore(cin.rdbuf()->in_avail(), '\n');\
	} catch (...) {\
		++tests_failed; failed_tests.push_back(test_case);\
		cin.clear();\
		cin.ignore(cin.rdbuf()->in_avail(), '\n');\
	}

#define ASSERT_ERROR(exception_name, function, test_case)\
	bool exception_name = false;\
	try { function; }\
	catch (exception& e) { exception_name = true; }\
	catch (...) { exception_name = true; }\
	ASSERT(exception_name, 1, test_case);\
	cin.clear();\
	cin.ignore(cin.rdbuf()->in_avail(), '\n');

#define ASSERT_DOUBLE(function, result, test_case)\
	try {\
		++tests_run;\
		if (function - result < epsilon) ++tests_passed;\
		else { ++tests_failed; failed_tests.push_back(test_case); }\
		cin.clear();\
		cin.ignore(cin.rdbuf()->in_avail(), '\n');\
	} catch (exception& e) {\
		++tests_failed; failed_tests.push_back(test_case);\
		cin.clear();\
		cin.ignore(cin.rdbuf()->in_avail(), '\n');\
	} catch (...) {\
		++tests_failed; failed_tests.push_back(test_case);\
		cin.clear();\
		cin.ignore(cin.rdbuf()->in_avail(), '\n');\
	}

#define TEST_SUMMARY(file_name)\
	cout << "*** " << file_name << " TEST SUMMARY***" << endl;\
	for (string test : failed_tests) cout << "***FAILED*** " << test << endl;\
	cout << "Tests PASSED: " << tests_passed << endl;\
	cout << "Tests FAILED: " << tests_failed << endl;\
	cout << "Tests run: " << tests_run << endl;
