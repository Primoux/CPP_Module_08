#ifndef SPAN_TPP
# define SPAN_TPP

template <typename Iterator>
void Span::addNumber(Iterator begin, Iterator end)
{
	std::size_t	toAdd = static_cast<std::size_t>(std::distance(begin, end));

	if (this->_numbers.size() + toAdd > this->_maxSize)
		throw FullException();
	this->_numbers.insert(this->_numbers.end(), begin, end);
}

#endif // !SPAN_TPP
