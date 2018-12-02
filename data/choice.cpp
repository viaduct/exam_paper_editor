#include "choice.h"

namespace wally {
namespace data {

Choice::Choice() :
	m_textContainer(new TextContainer)
{
}

Choice::~Choice()
{
}

DataType Choice::type() const
{
	return DataType::Choice;
}

std::vector<const Container*> Choice::containers() const
{
	std::vector<const Container*> result;

	return result;
}

const Choice::TextContainer*Choice::textContainer() const
{
	return m_textContainer.get();
}

Choice::TextContainer*Choice::textContainer()
{
	return m_textContainer.get();
}

}}
