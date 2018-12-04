#include "block_list_mimic.h"
#include "text_block_mimic.h"
#include "image_block_mimic.h"
#include "ui_block_list_mimic.h"
#include "../../data/block_list.h"
#include "../../data/text_block.h"
#include "../../data/image_block.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

BlockListMimic::BlockListMimic(QWidget* parent) :
	BlockMimic(parent),
	m_ui(new Ui_BlockListMimic)
{
	m_ui->setupUi(this);
}

BlockListMimic::~BlockListMimic()
{
}

data::Block*BlockListMimic::block() const
{
	return m_blockList;
}

data::BlockList*BlockListMimic::blockList() const
{
	return m_blockList;
}

void BlockListMimic::setValidBlockList(data::BlockList* one)
{
	m_blockList = one;

	auto blockAdded = [this](data::Block* one, size_t at)
	{
		auto mimic = createBlockMimic(one);
		insertBlockMimic(std::move(mimic), at);
	};
	auto beforeBlockRemoved = [this](data::Block* one, size_t at)
	{
		(void)one;
		removeBlockMimic(at);
	};
	auto blockMoved = [this](data::Block* one, size_t moveThis, size_t toHere)
	{
		(void)one;
		moveBlockMimic(moveThis, toHere);
	};
	auto beforeBlocksCleared = [this]
	{
		clearBlockMimics();
	};

	m_con_blockAdded = m_blockList->subBlockContainer()->sig_added()->connect(std::move(blockAdded));
	m_con_beforeBlockRemoved = m_blockList->subBlockContainer()->sig_beforeRemoved()->connect(std::move(beforeBlockRemoved));
	m_con_blockMoved = m_blockList->subBlockContainer()->sig_moved()->connect(std::move(blockMoved));
	m_con_beforeBlocksCleared = m_blockList->subBlockContainer()->sig_beforeCleared()->connect(std::move(beforeBlocksCleared));

	catchUpBlockMimics();
}

void BlockListMimic::setNullBlockList()
{
	clearBlockMimics();

	m_con_beforeBlocksCleared.disconnect();
	m_con_blockMoved.disconnect();
	m_con_beforeBlockRemoved.disconnect();
	m_con_blockAdded.disconnect();

	m_blockList = nullptr;
}

void BlockListMimic::initialized()
{
}

void BlockListMimic::on_btn_addTextBlock_clicked()
{
	if ( m_blockList )
	{
		context()->act_appendTextBlock(m_blockList->subBlockContainer(), "New Text Block.");
	}
}

void BlockListMimic::on_btn_addImageBlock_clicked()
{
	if ( m_blockList )
	{
		context()->act_appendImageBlock(m_blockList->subBlockContainer());
	}
}

BlockMimic* BlockListMimic::createBlockMimic(data::Block* one)
{
	switch ( one->type() )
	{
		case data::DataType::BlockList:
			return createBlockListMimic(static_cast<data::BlockList*>(one));
			break;
		case data::DataType::TextBlock:
			return createTextBlockMimic(static_cast<data::TextBlock*>(one));
			break;
		case data::DataType::ImageBlock:
			return createImageBlockMimic(static_cast<data::ImageBlock*>(one));
			break;
		default:
			assert(false);
			break;
	}
}

BlockMimic* BlockListMimic::createBlockListMimic(data::BlockList* one)
{
	auto mimic = new BlockListMimic;
	mimic->init(context(), questionView());
	mimic->setValidBlockList(one);
	return mimic;
}

BlockMimic* BlockListMimic::createTextBlockMimic(data::TextBlock* one)
{
	auto mimic = new TextBlockMimic;
	mimic->init(context(), questionView());
	mimic->setValidTextBlock(one);
	return mimic;
}

BlockMimic* BlockListMimic::createImageBlockMimic(data::ImageBlock* one)
{
	auto mimic = new ImageBlockMimic;
	mimic->init(context(), questionView());
	mimic->setValidImageBlock(one);
	return mimic;
}

void BlockListMimic::appendBlockMimic(BlockMimic* one)
{
	m_blockMimics.push_back(one);

	m_ui->layout_blocks->addWidget(one);
}

void BlockListMimic::insertBlockMimic(BlockMimic* one, size_t at)
{
	m_blockMimics.insert(m_blockMimics.begin() + at, one);

	m_ui->layout_blocks->insertWidget(at, one);
}

BlockMimic* BlockListMimic::removeGetBlockMimic(size_t at)
{
	auto copy = m_blockMimics[at];

	m_blockMimics.erase(m_blockMimics.begin() + at);

	return copy;
}

void BlockListMimic::removeBlockMimic(size_t at)
{
	auto copy = m_blockMimics[at];

	m_blockMimics.erase(m_blockMimics.begin() + at);

	delete copy;
}

void BlockListMimic::moveBlockMimic(size_t moveThis, size_t toHere)
{
	auto copy = removeGetBlockMimic(moveThis);
	insertBlockMimic(copy, toHere);
}

void BlockListMimic::clearBlockMimics()
{
	m_blockMimics.clear();
}

void BlockListMimic::catchUpBlockMimics()
{
	for ( auto& block : m_blockList->subBlockContainer()->list() )
	{
		appendBlockMimic(createBlockMimic(block));
	}
}

}}}
