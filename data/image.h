#pragma once
#include <QImage>
#include "file.h"

namespace wally {
namespace data {

class Image : public File
{
public:
	using ImageContainer = SinglePrimContainer<QImage>;

	Image();
	virtual ~Image();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	ImageContainer const* imageContainer() const;
	ImageContainer* imageContainer();

private:
	std::unique_ptr<ImageContainer>
	m_imageContainer;
};

}}
