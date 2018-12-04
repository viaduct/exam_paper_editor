#pragma once
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <boost/signals2.hpp>
#include <memory>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class Choice;
}

namespace qtfront {
namespace question_view_sub {

class ChoiceTextEdit;
class ChoiceMimic;
class Ui_ChoiceMimic;

class ChoiceTextEdit : public QPlainTextEdit
{
public:
	ChoiceTextEdit(QWidget* parent = nullptr);

	void setOwner(ChoiceMimic* owner);

protected:
	void focusOutEvent(QFocusEvent *e) override final;

private:
	ChoiceMimic* m_owner;
};

class ChoiceMimic : public QGroupBox,
		public QuestionViewContextHolder
{
	Q_OBJECT

public:
	friend ChoiceTextEdit;

	ChoiceMimic(QWidget* parent = nullptr);
	~ChoiceMimic();
	ChoiceMimic(ChoiceMimic const&) = delete;
	ChoiceMimic& operator =(ChoiceMimic const&) = delete;

	data::Choice* choice() const;
	void setValidChoice(data::Choice* one);
	void setNullChoice();

protected:
	void initialized() override final;

private slots:
	void on_btn_delete_clicked();
	void on_btn_moveUp_clicked();
	void on_btn_moveDown_clicked();

private:
	void enableTextEdit();
	void disableTextEdit();
	void pullText();
	void pushText();

	boost::signals2::scoped_connection
	m_con_textUpdated;

	std::unique_ptr<Ui_ChoiceMimic>
	m_ui;

	data::Choice*
	m_choice{};
};

}}}
