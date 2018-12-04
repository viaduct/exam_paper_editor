#include <QDragEnterEvent>
#include "image_mimic.h"
#include "image_block_mimic.h"
#include "ui_image_block_mimic.h"
#include "../../data/image_block.h"
#include "../../data/image.h"
#include "../../data/tree_item.h"
#include "../context.h"
#include "../drag_context_var.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

ImageBlockMimic::ImageBlockMimic(QWidget* parent) :
	BlockMimic(parent),
	m_ui(new Ui_ImageBlockMimic)
{
	m_ui->setupUi(this);

	setAcceptDrops(true);
}

ImageBlockMimic::~ImageBlockMimic()
{
}

data::Block*ImageBlockMimic::block() const
{
	return m_imageBlock;
}

data::ImageBlock*ImageBlockMimic::imageBlock() const
{
	return m_imageBlock;
}

void ImageBlockMimic::setValidImageBlock(data::ImageBlock* one)
{
	m_imageBlock = one;

	auto validImageSet = [this]
	{
		setValidImageMimic();
	};
	auto beforeNullImageSet = [this]
	{
		setNullImageMimic();
	};
	m_con_validImageSet = m_imageBlock->imageContainer()->sig_validSet()->connect(std::move(validImageSet));
	m_con_beforeNullImageSet = m_imageBlock->imageContainer()->sig_beforeNullSet()->connect(std::move(beforeNullImageSet));

	catchUpImageMimic();
}

void ImageBlockMimic::setNullImageBlock()
{
	setNullImageMimicSafely();

	m_con_beforeNullImageSet.disconnect();
	m_con_validImageSet.disconnect();

	m_imageBlock = nullptr;
}

void ImageBlockMimic::initialized()
{
}

void ImageBlockMimic::on_btn_delete_clicked()
{
	if ( m_imageBlock )
	{
		context()->act_removeBlock(m_imageBlock);
	}
}

void ImageBlockMimic::on_btn_moveUp_clicked()
{
	if ( m_imageBlock )
	{
		context()->act_moveBlockUp(m_imageBlock);
	}
}

void ImageBlockMimic::on_btn_moveDown_clicked()
{
	if ( m_imageBlock )
	{
		context()->act_moveBlockDown(m_imageBlock);
	}
}

void ImageBlockMimic::catchUpImageMimic()
{
	if ( m_imageBlock->imageContainer()->isValid() )
	{
		setValidImageMimic();
	}
}

void ImageBlockMimic::setNullImageMimicSafely()
{
	if ( m_imageMimic )
	{
		setNullImageMimic();
	}
}

void ImageBlockMimic::showMimicAndHideNoImage()
{
	m_ui->noImage->hide();

	auto layout = static_cast<QVBoxLayout*>(this->layout());
	layout->insertWidget(0, m_imageMimic);
}

void ImageBlockMimic::hideMimicAndShowNoImage()
{
	auto layout = static_cast<QVBoxLayout*>(this->layout());
	layout->removeWidget(m_imageMimic);

	m_ui->noImage->show();
}

void ImageBlockMimic::setValidImageMimic()
{
	m_imageMimic = new ImageMimic;
	m_imageMimic->init(context(), questionView());
	m_imageMimic->setValidImage(m_imageBlock->imageContainer()->single());

	showMimicAndHideNoImage();
}

void ImageBlockMimic::setNullImageMimic()
{
	hideMimicAndShowNoImage();

	delete m_imageMimic;
}

void ImageBlockMimic::dragEnterEvent(QDragEnterEvent* event)
{
	if ( context()->dragContextVar()->isRightDrag(event) )
	{
		auto treeItems = context()->dragContextVar()->treeItems();
		if ( treeItems.size() == 1 )
		{
			auto treeItem = treeItems.front();
			if ( treeItem->type() == data::DataType::Image )
			{
				event->acceptProposedAction();
			}
		}
	}
}

void ImageBlockMimic::dropEvent(QDropEvent* event)
{
	if ( m_imageBlock )
	{
		auto treeItems = context()->dragContextVar()->treeItems();
		auto image = static_cast<data::Image*>(treeItems.front());

		context()->act_setImageBlockImage(m_imageBlock, image);
	}

	event->acceptProposedAction();
}

}}}
