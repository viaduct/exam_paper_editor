#pragma once
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QPushButton>
#include <memory>
#include <boost/signals2.hpp>
#include "block_mimic.h"

namespace wally {

namespace data {
class ImageBlock;
}

namespace qtfront {
namespace question_view_sub {

class ImageMimic;
class ImageBlockMimic;
class ImageBlockImageWidget;
class Ui_ImageBlockMimic;

class ImageBlockMimic : public BlockMimic
{
	Q_OBJECT

	friend ImageBlockImageWidget;

public:
	ImageBlockMimic(QWidget* parent = nullptr);
	virtual ~ImageBlockMimic();
	ImageBlockMimic(ImageBlockMimic const&) = delete;
	ImageBlockMimic& operator =(ImageBlockMimic const&) = delete;

	data::Block* block() const override final;

	data::ImageBlock* imageBlock() const;
	void setValidImageBlock(data::ImageBlock* one);
	void setNullImageBlock();

protected:
	void initialized() override final;

	void dragEnterEvent(QDragEnterEvent *event) override final;
	void dropEvent(QDropEvent *event) override final;

private slots:
	void on_btn_delete_clicked();
	void on_btn_moveUp_clicked();
	void on_btn_moveDown_clicked();

private:
	void setValidImageMimic();
	void setNullImageMimic();
	void catchUpImageMimic();
	void setNullImageMimicSafely();

	void showMimicAndHideNoImage();
	void hideMimicAndShowNoImage();

	boost::signals2::scoped_connection
	m_con_validImageSet,
	m_con_beforeNullImageSet;

	std::unique_ptr<Ui_ImageBlockMimic>
	m_ui;

	ImageMimic*
	m_imageMimic;

	data::ImageBlock*
	m_imageBlock{};
};

}}}
