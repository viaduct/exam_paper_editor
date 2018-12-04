#pragma once
#include <QGroupBox>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class Context;
}

namespace qtfront {
namespace question_view_sub {

class ContextMimic : public QGroupBox,
		public QuestionViewContextHolder
{
	Q_OBJECT

public:
	ContextMimic(QWidget* parent = nullptr);
	virtual ~ContextMimic();
	ContextMimic(ContextMimic const&) = delete;
	ContextMimic& operator =(ContextMimic const&) = delete;

	virtual data::Context* dataContext() const = 0;
};

}}}
