#include "text_block.h"

namespace wally {
namespace data {

TextBlock::TextBlock() :
	m_textContainer(new TextContainer)
{
}

TextBlock::~TextBlock()
{
}

DataType TextBlock::type() const
{
	return DataType::TextBlock;
}

std::vector<const Container*> TextBlock::containers() const
{
	auto result = Block::containers();

	return result;
}

const TextBlock::TextContainer*TextBlock::textContainer() const
{
	return m_textContainer.get();
}

TextBlock::TextContainer*TextBlock::textContainer()
{
	return m_textContainer.get();
}

}}
