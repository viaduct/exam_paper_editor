#pragma once
#include <QWidget>
#include <QStackedLayout>
#include <QScrollArea>
#include <boost/signals2.hpp>
#include <memory>
#include "context_holder.h"

namespace wally {

namespace data {
class Question;
}

namespace qtfront {

class Ui_QuestionView;

namespace question_view_sub {
class QuestionMimic;
class NameEdit;
}

class QuestionView : public QWidget,
		public ContextHolder
{
	Q_OBJECT

	class SetNullQuestion;

public:
	using QuestionMimic = question_view_sub::QuestionMimic;
	using NameEdit = question_view_sub::NameEdit;

	friend NameEdit;

	QuestionView(QWidget* parent = nullptr);
	virtual ~QuestionView();

	data::Question* question() const;
	void setQuestion(data::Question* one);
	void setQuestion(nullptr_t);
	void setValidQuestion(data::Question* one);
	void setNullQuestion();

protected:
	void initialized() override final;

private:
	// For NameEdit.
	void enableNameEdit();
	void disableNameEdit();
	void pullName();
	void pushName();

	std::unique_ptr<QuestionMimic> createQuestionMimic(data::Question* one);

	boost::signals2::scoped_connection
	m_con_nameUpdated;

	std::unique_ptr<Ui_QuestionView>
	m_ui;

	QuestionMimic*
	m_questionMimic;

	data::Question*
	m_question{};
};

}}
