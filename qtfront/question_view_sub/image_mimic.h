#pragma once
#include <QLabel>
#include <boost/signals2.hpp>
#include <memory>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class Image;
}

namespace qtfront {
namespace question_view_sub {

class ImageMimic : public QLabel,
		public QuestionViewContextHolder
{
public:
	ImageMimic();
	~ImageMimic();
	ImageMimic(ImageMimic const&) = delete;
	ImageMimic& operator =(ImageMimic const&) = delete;

	data::Image* image() const;
	void setValidImage(data::Image* one);
	void setNullImage();

protected:
	void initialized() override final;

private:
	void initUi();

	boost::signals2::scoped_connection
	m_con_imageUpdated;

	data::Image*
	m_image{};
};

}}}
