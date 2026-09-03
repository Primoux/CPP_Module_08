#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <unistd.h>
#include "Span.hpp"
#include "color.h"

static void printSpans(Span const &span)
{
	try
	{
		std::cout << LGREEN "shortestSpan: " RESET << span.shortestSpan() << std::endl;
		std::cout << LGREEN "longestSpan:  " RESET << span.longestSpan() << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << BRED << e.what() << RESET << std::endl;
	}
}

void testSubject(void)
{
	std::cout << BYELLOW "\n=== TEST 1: subject example ===" RESET << std::endl;
	Span	sp(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << "span: " << sp << std::endl;
	printSpans(sp);
	std::cout << LYELLOW "expected: 2 and 14" RESET << std::endl;
}

void testErrors(void)
{
	std::cout << BYELLOW "\n=== TEST 2: exceptions ===" RESET << std::endl;
	Span	sp(3);

	std::cout << "empty span: ";
	printSpans(sp);

	sp.addNumber(42);
	std::cout << "one number: ";
	printSpans(sp);

	sp.addNumber(1);
	sp.addNumber(2);
	std::cout << "adding a 4th number in a Span(3): ";
	try
	{
		sp.addNumber(3);
		std::cout << BRED "no exception thrown!" RESET << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << LGREEN << e.what() << RESET << std::endl;
	}

	std::cout << "Span(0), addNumber: ";
	try
	{
		Span	empty(0);

		empty.addNumber(1);
		std::cout << BRED "no exception thrown!" RESET << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << LGREEN << e.what() << RESET << std::endl;
	}
}

void testRange(void)
{
	std::cout << BYELLOW "\n=== TEST 3: addNumber with iterators ===" RESET << std::endl;
	std::vector<int>	v;
	std::list<int>		l;

	for (int i = 0; i < 5; i++)
		v.push_back(i * 10);
	l.push_back(-3);
	l.push_back(7);
	l.push_back(100);

	Span	sp(8);

	sp.addNumber(v.begin(), v.end());
	sp.addNumber(l.begin(), l.end());
	std::cout << "span: " << sp << std::endl;
	printSpans(sp);

	std::cout << "range too big for the remaining space: ";
	try
	{
		sp.addNumber(v.begin(), v.end());
		std::cout << BRED "no exception thrown!" RESET << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << LGREEN << e.what() << RESET << std::endl;
	}
	std::cout << "span is unchanged: " << sp << std::endl;
}

void testBig(void)
{
	std::cout << BYELLOW "\n=== TEST 4: 100000 random numbers ===" RESET << std::endl;
	std::vector<int>	v;

	for (int i = 0; i < 100000; i++)
		v.push_back(rand());

	Span	sp(100000);

	sp.addNumber(v.begin(), v.end());
	std::cout << "span: " << sp << std::endl;
	printSpans(sp);
}

void testLimits(void)
{
	std::cout << BYELLOW "\n=== TEST 5: INT_MIN / INT_MAX ===" RESET << std::endl;
	Span	sp(3);

	sp.addNumber(-2147483647 - 1);
	sp.addNumber(0);
	sp.addNumber(2147483647);
	std::cout << "span: " << sp << std::endl;
	printSpans(sp);
	std::cout << LYELLOW "expected: 2147483647 and 4294967295" RESET << std::endl;

	std::cout << BYELLOW "\n--- duplicates ---" RESET << std::endl;
	Span	dup(4);

	dup.addNumber(5);
	dup.addNumber(5);
	dup.addNumber(-8);
	dup.addNumber(12);
	printSpans(dup);
	std::cout << LYELLOW "expected: 0 and 20" RESET << std::endl;
}

void testCopy(void)
{
	std::cout << BYELLOW "\n=== TEST 6: copy and assignment ===" RESET << std::endl;
	Span	sp(5);

	sp.addNumber(1);
	sp.addNumber(50);

	Span	copy(sp);
	Span	assigned(1);

	assigned = sp;

	sp.addNumber(25);
	std::cout << "original: " << sp << " ";
	printSpans(sp);
	std::cout << "copy:     " << copy << " ";
	printSpans(copy);
	std::cout << "assigned: " << assigned << " ";
	printSpans(assigned);
	std::cout << LYELLOW "copies must keep 2 numbers, span 49 / 49" RESET << std::endl;
}

int main(int argc, char **argv)
{
	srand(static_cast<unsigned int>(getpid() * time(NULL)));
	typedef void (*test_func)(void);
	static const test_func tests[] = {
		testSubject,
		testErrors,
		testRange,
		testBig,
		testLimits,
		testCopy,
	};
	const int num_tests = sizeof(tests) / sizeof(tests[0]) + 1;

	if (argc == 1)
	{
		std::cout << BYELLOW "=== Running all tests ===" RESET << std::endl;
		for (int i = 0; i < num_tests - 1; i++)
			tests[i]();
		return 0;
	}

	std::cout << BYELLOW "=== Running selected tests ===" RESET << std::endl;
	for (int i = 1; i < argc; i++)
	{
		int test_num = atoi(argv[i]);
		if (test_num > 0 && test_num < num_tests)
			tests[test_num - 1]();
		else
			std::cerr << BRED "Unknown test: " RESET << test_num << std::endl;
	}

	return 0;
}
