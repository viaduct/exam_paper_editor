#pragma once
#include <QLineEdit>
#include "question_view_context_holder.h"

namespace wally {
namespace qtfront {

class QuestionView;

namespace question_view_sub {

class NameEdit : public QLineEdit,
		public QuestionViewContextHolder
{
public:
	NameEdit(QWidget* parent = nullptr);

protected:
	void focusOutEvent(QFocusEvent* event) override final;

	void initialized() override final;
};

}}}
