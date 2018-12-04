#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "block_mimic.h"

namespace wally {

namespace data {
class BlockList;
class TextBlock;
class ImageBlock;
}

namespace qtfront {
namespace question_view_sub {

class Ui_BlockListMimic;

class BlockListMimic : public BlockMimic
{
	Q_OBJECT

public:
	BlockListMimic(QWidget* parent = nullptr);
	virtual ~BlockListMimic();

	data::Block* block() const override final;

	data::BlockList* blockList() const;
	void setValidBlockList(data::BlockList* one);
	void setNullBlockList();

protected:
	void initialized() override final;

private slots:
	void on_btn_addTextBlock_clicked();
	void on_btn_addImageBlock_clicked();

private:
	BlockMimic* createBlockMimic(data::Block* one);
	BlockMimic* createBlockListMimic(data::BlockList* one);
	BlockMimic* createTextBlockMimic(data::TextBlock* one);
	BlockMimic* createImageBlockMimic(data::ImageBlock* one);

	void appendBlockMimic(BlockMimic* one);
	void insertBlockMimic(BlockMimic* one, size_t at);
	BlockMimic* removeGetBlockMimic(size_t at);
	void removeBlockMimic(size_t at);
	void moveBlockMimic(size_t moveThis, size_t toHere);
	void clearBlockMimics();
	void catchUpBlockMimics();

	std::vector<BlockMimic*>
	m_blockMimics;

	boost::signals2::scoped_connection
	m_con_blockAdded,
	m_con_beforeBlockRemoved,
	m_con_blockMoved,
	m_con_beforeBlocksCleared;

	std::unique_ptr<Ui_BlockListMimic>
	m_ui;

	data::BlockList*
	m_blockList{};
};

}}}
