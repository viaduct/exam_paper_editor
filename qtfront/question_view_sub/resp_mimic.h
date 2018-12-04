#pragma once
#include <QGroupBox>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class Resp;
}

namespace qtfront {
namespace question_view_sub {

class RespMimic : public QGroupBox,
		public QuestionViewContextHolder
{
	Q_OBJECT

public:
	RespMimic(QWidget* parent = nullptr);
	virtual ~RespMimic();
	RespMimic(RespMimic const&) = delete;
	RespMimic& operator =(RespMimic const&) = delete;

	virtual data::Resp* resp() const = 0;
};

}}}
