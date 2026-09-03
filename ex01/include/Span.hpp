#ifndef SPAN_HPP
# define SPAN_HPP

#include <vector>
#include <iterator>
#include <stdexcept>
#include <iostream>

class Span
{
  private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

  public:
	// CONSTRUCTOR
	Span();
	Span(unsigned int n);
	Span(Span const &original);
	~Span();

	// OPERATOR
	Span &operator=(Span const &other);

	// FUNCTION MEMBER
	void			addNumber(int number);
	unsigned int	shortestSpan() const;
	unsigned int	longestSpan() const;
	unsigned int	size() const;
	unsigned int	maxSize() const;

	template <typename Iterator>
	void addNumber(Iterator begin, Iterator end);

	// EXCEPTION
	class FullException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	class NoSpanException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, Span const &span);

#include "Span.tpp"

#endif // !SPAN_HPP
