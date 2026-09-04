#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <exception>

class NotFoundException : public std::exception
{
  public:
	virtual const char *what() const throw();
};

template <typename T>
typename T::iterator easyfind(T &container, int value);

template <typename T>
typename T::const_iterator easyfind(T const &container, int value);

const char *NotFoundException::what() const throw()
{
	return ("easyfind: value not found in container");
}


#include "easyfind.tpp"

#endif // !EASYFIND_HPP
