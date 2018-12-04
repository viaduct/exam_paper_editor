#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPointer>
#include "question_view_context_holder.h"

namespace wally {

namespace data {
class Question;
}

namespace qtfront {
namespace question_view_sub {

class Ui_QuestionMimic;
class ContextMimic;
class RespMimic;

class QuestionMimic : public QScrollArea,
		public QuestionViewContextHolder
{
	Q_OBJECT

public:
	QuestionMimic(QWidget* parent = nullptr);
	virtual ~QuestionMimic();
	QuestionMimic(QuestionMimic const&) = delete;
	QuestionMimic& operator =(QuestionMimic const&) = delete;

	data::Question* question() const;
	void setValidQuestion(data::Question* one);
	void setNullQuestion();

protected:
	void initialized() override final;

private slots:
	void on_btn_addBlockContext_clicked();
	void on_btn_addMultipleChoicesResp_clicked();
	void on_btn_addMatchingResp_clicked();

private:
	// For Context.
	void setValidContextMimic();
	void setNullContextMimic();
	void catchUpResp();
	void setNullRespMimicSafely();

	// For resp.
	void setValidRespMimic();
	void setNullRespMimic();
	void catchUpContext();
	void setNullContextMimicSafely();

	void setContextVisible(bool doThis);
	void setRespVisible(bool doThis);

	QVBoxLayout* rootLayout();

	boost::signals2::scoped_connection
	m_con_validContextSet,
	m_con_beforeNullContextSet,
	m_con_validRespSet,
	m_con_beforeNullRespSet;

	std::unique_ptr<Ui_QuestionMimic>
	m_ui;

	ContextMimic*
	m_contextMimic;
	RespMimic*
	m_respMimic;

	data::Question*
	m_question{};

	bool
	m_contextVisible = false,
	m_respVisible = false;
};

}}}
