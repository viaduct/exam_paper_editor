#pragma once
#include "block.h"

namespace wally {
namespace data {

class TextBlock : public Block
{
public:
	using TextContainer = SinglePrimContainer<std::string>;

	TextBlock();
	virtual ~TextBlock();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	TextContainer const* textContainer() const;
	TextContainer* textContainer();

private:
	std::unique_ptr<TextContainer>
	m_textContainer;
};

}}
