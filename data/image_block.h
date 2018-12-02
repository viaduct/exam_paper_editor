#pragma once
#include "block.h"

namespace wally {
namespace data {

class Image;

class ImageBlock : public Block
{
public:
	using ImageContainer = SingleContainer<Image, TypeEnum::Ref>;

	ImageBlock();
	virtual ~ImageBlock();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	ImageContainer const* imageContainer() const;
	ImageContainer* imageContainer();

private:
	std::unique_ptr<ImageContainer>
	m_imageContainer;
};

}}
