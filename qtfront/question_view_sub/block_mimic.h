#pragma once
#include <QGroupBox>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class Block;
}

namespace qtfront {
namespace question_view_sub {

class BlockMimic : public QGroupBox,
		public QuestionViewContextHolder
{
	Q_OBJECT

public:
	BlockMimic(QWidget* parent = nullptr);
	virtual ~BlockMimic();
	BlockMimic(BlockMimic const&) = delete;
	BlockMimic& operator =(BlockMimic const&) = delete;

	virtual data::Block* block() const = 0;
};

}}}
