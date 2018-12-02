#include "image_block.h"
#include "image.h"

namespace wally {
namespace data {

ImageBlock::ImageBlock() :
	m_imageContainer(new ImageContainer(this))
{
}

ImageBlock::~ImageBlock()
{
}

DataType ImageBlock::type() const
{
	return DataType::ImageBlock;
}

std::vector<const Container*> ImageBlock::containers() const
{
	auto result = Block::containers();

	return result;
}

const ImageBlock::ImageContainer*ImageBlock::imageContainer() const
{
	return m_imageContainer.get();
}

ImageBlock::ImageContainer*ImageBlock::imageContainer()
{
	return m_imageContainer.get();
}

}}
