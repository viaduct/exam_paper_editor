#pragma once
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <boost/signals2.hpp>
#include <memory>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class MatchingRespItem;
}

namespace qtfront {
namespace question_view_sub {

class MatchingRespItemMimic;
class MatchingRespItemTextEdit;
class Ui_MatchingRespItemMimic;

class MatchingRespItemTextEdit : public QPlainTextEdit
{
public:
	MatchingRespItemTextEdit(QWidget* parent = nullptr);
	void setOwner(MatchingRespItemMimic* one);

protected:
	void focusOutEvent(QFocusEvent *e) override final;

private:
	MatchingRespItemMimic* m_owner;
};

class MatchingRespItemMimic : public QGroupBox,
		public QuestionViewContextHolder
{
	Q_OBJECT

public:
	friend class MatchingRespItemTextEdit;

	MatchingRespItemMimic(QWidget* parent = nullptr);
	virtual ~MatchingRespItemMimic();
	MatchingRespItemMimic(MatchingRespItemMimic const&) = delete;
	MatchingRespItemMimic& operator =(MatchingRespItemMimic const&) = delete;

	data::MatchingRespItem* matchingRespItem() const;
	void setValidMatchingRespItem(data::MatchingRespItem* one);
	void setNullMatchingRespItem();

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

	std::unique_ptr<Ui_MatchingRespItemMimic>
	m_ui;

	data::MatchingRespItem*
	m_matchingRespItem{};
};

}}}
