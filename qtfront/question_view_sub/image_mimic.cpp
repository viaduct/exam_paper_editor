#include <QPainter>
#include "image_mimic.h"
#include "../../data/image.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

ImageMimic::ImageMimic()
{
}

ImageMimic::~ImageMimic()
{
}

data::Image*ImageMimic::image() const
{
	return m_image;
}

void ImageMimic::setValidImage(data::Image* one)
{
	m_image = one;

	auto imageUpdated = [this]
	{
		QLabel::setPixmap(QPixmap::fromImage(m_image->imageContainer()->single()).scaledToWidth(400));
	};
	m_con_imageUpdated = m_image->imageContainer()->sig_updated()->connect(std::move(imageUpdated));

	QLabel::setPixmap(QPixmap::fromImage(m_image->imageContainer()->single()).scaledToWidth(400));
}

void ImageMimic::setNullImage()
{
	QLabel::clear();

	m_con_imageUpdated.disconnect();
}

void ImageMimic::initialized()
{
}

}}}
