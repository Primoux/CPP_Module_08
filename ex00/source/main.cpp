#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"
#include "color.h"

template <typename T>
void print(T const &container)
{
	std::cout << LYELLOW << "[ " << RESET;
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << LYELLOW << "]" << RESET;
}

template <typename T>
void search(T &container, int value)
{
	std::cout << "easyfind(";
	print(container);
	std::cout << ", " << value << "): ";
	try
	{
		typename T::iterator it = easyfind(container, value);
		std::cout << LGREEN << "found " << *it << RESET
			<< " at index " << std::distance(container.begin(), it) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << BRED << e.what() << RESET << std::endl;
	}
}

void testVector(void)
{
	std::cout << BYELLOW "\n=== TEST 1: std::vector ===" RESET << std::endl;
	std::vector<int> v;

	for (int i = 0; i < 10; i++)
		v.push_back(i * 3);
	search(v, 0);
	search(v, 12);
	search(v, 27);
	search(v, 13);
	search(v, -1);
}

void testList(void)
{
	std::cout << BYELLOW "\n=== TEST 2: std::list ===" RESET << std::endl;
	std::list<int> l;

	l.push_back(42);
	l.push_back(-7);
	l.push_back(42);
	l.push_back(1000);
	search(l, 42);
	search(l, -7);
	search(l, 404);
}

void testDeque(void)
{
	std::cout << BYELLOW "\n=== TEST 3: std::deque ===" RESET << std::endl;
	std::deque<int> d;

	d.push_back(5);
	d.push_front(3);
	d.push_back(9);
	search(d, 3);
	search(d, 9);
	search(d, 4);
}

void testConst(void)
{
	std::cout << BYELLOW "\n=== TEST 4: const container ===" RESET << std::endl;
	std::vector<int> tmp;

	tmp.push_back(1);
	tmp.push_back(2);
	tmp.push_back(3);

	std::vector<int> const	v(tmp);

	std::cout << "const std::vector, easyfind(2): ";
	try
	{
		std::vector<int>::const_iterator it = easyfind(v, 2);
		std::cout << LGREEN << "found " << *it << RESET << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << BRED << e.what() << RESET << std::endl;
	}
}

void testEmpty(void)
{
	std::cout << BYELLOW "\n=== TEST 5: empty container ===" RESET << std::endl;
	std::vector<int> v;

	search(v, 0);
}

int main(int argc, char **argv)
{
	typedef void (*test_func)(void);
	static const test_func tests[] = {
		testVector,
		testList,
		testDeque,
		testConst,
		testEmpty,
	};
	const int num_tests = sizeof(tests) / sizeof(tests[0]);

	if (argc == 1)
	{
		std::cout << BYELLOW "=== Running all tests ===" RESET << std::endl;
		for (int i = 0; i < num_tests; i++)
			tests[i]();
		return 0;
	}

	std::cout << BYELLOW "=== Running selected tests ===" RESET << std::endl;
	for (int i = 1; i < argc; i++)
	{
		int test_num = atoi(argv[i]);
		if (test_num > 0 && test_num <= num_tests)
			tests[test_num - 1]();
		else
			std::cerr << BRED "Unknown test: " RESET << test_num << std::endl;
	}

	return 0;
}
