#pragma once
#include <QLineEdit>
#include <boost/signals2.hpp>
#include "exam_view_context_holder.h"

namespace wally {

namespace data {
class Exam;
}

namespace qtfront {
namespace exam_view_sub {

class NameEdit : public QLineEdit,
		public ExamViewContextHolder
{
public:
	NameEdit(QWidget* parent = nullptr);
	virtual ~NameEdit();

	data::Exam* exam() const;
	void setValidExam(data::Exam* one);
	void setNullExam();

protected:
	void initialized() override final;

	void focusOutEvent(QFocusEvent* event) override final;

private:
	void pullText();
	void pushText();

	boost::signals2::scoped_connection
	m_con_nameUpdated;

	data::Exam*
	m_exam{};
};

}}}
