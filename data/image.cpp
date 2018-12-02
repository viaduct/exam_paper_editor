#include "image.h"

namespace wally {
namespace data {

Image::Image() :
	m_imageContainer(new ImageContainer)
{
}

Image::~Image()
{
}

DataType Image::type() const
{
	return DataType::Image;
}

std::vector<const Container*> Image::containers() const
{
	auto result = File::containers();

	return result;
}

const Image::ImageContainer*Image::imageContainer() const
{
	return m_imageContainer.get();
}

Image::ImageContainer*Image::imageContainer()
{
	return m_imageContainer.get();
}

}}
