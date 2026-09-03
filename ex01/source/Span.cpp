#include "Span.hpp"
#include "color.h"
#include <algorithm>

// CONSTRUCTOR

Span::Span() : _maxSize(0)
{
}

Span::Span(unsigned int n) : _maxSize(n)
{
	this->_numbers.reserve(n);
}

Span::Span(Span const &original) : _maxSize(original._maxSize), _numbers(original._numbers)
{
}

Span::~Span()
{
}

// OPERATOR

Span &Span::operator=(Span const &other)
{
	if (this != &other)
	{
		this->_maxSize = other._maxSize;
		this->_numbers = other._numbers;
	}
	return (*this);
}

// FUNCTION MEMBER

void Span::addNumber(int number)
{
	if (this->_numbers.size() >= this->_maxSize)
		throw FullException();
	this->_numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
	if (this->_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int>	sorted(this->_numbers);

	std::sort(sorted.begin(), sorted.end());

	long	shortest = static_cast<long>(sorted[1]) - static_cast<long>(sorted[0]);

	for (std::size_t i = 2; i < sorted.size(); i++)
	{
		long	span = static_cast<long>(sorted[i]) - static_cast<long>(sorted[i - 1]);

		if (span < shortest)
			shortest = span;
	}
	return (static_cast<unsigned int>(shortest));
}

unsigned int Span::longestSpan() const
{
	if (this->_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int>::const_iterator	min = std::min_element(this->_numbers.begin(), this->_numbers.end());
	std::vector<int>::const_iterator	max = std::max_element(this->_numbers.begin(), this->_numbers.end());

	return (static_cast<unsigned int>(static_cast<long>(*max) - static_cast<long>(*min)));
}

unsigned int Span::size() const
{
	return (static_cast<unsigned int>(this->_numbers.size()));
}

unsigned int Span::maxSize() const
{
	return (this->_maxSize);
}

// EXCEPTION

const char *Span::FullException::what() const throw()
{
	return ("Span: container is already full");
}

const char *Span::NoSpanException::what() const throw()
{
	return ("Span: not enough numbers stored to find a span");
}

std::ostream &operator<<(std::ostream &os, Span const &span)
{
	os << LYELLOW "[ " RESET << span.size() << "/" << span.maxSize() << LYELLOW " ]" RESET;
	return (os);
}
