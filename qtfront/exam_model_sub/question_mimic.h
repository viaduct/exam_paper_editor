#pragma once
#include <boost/signals2.hpp>
#include "exam_model_context_holder.h"

namespace wally {

namespace data {
class Question;
}

namespace qtfront {
namespace exam_model_sub {

class ExamMimic;

class QuestionMimic : public ExamModelContextHolder
{
public:
	QuestionMimic();
	virtual ~QuestionMimic();

	data::Question* question() const;
	void setValidQuestion(data::Question* one);
	void setNullQuestion();

	// Should be initialized right after constructor is called.
	void setParentExamMimic(ExamMimic* one);

protected:
	void initialized() override final;

private:
	boost::signals2::scoped_connection
	m_con_nameUpdated;

	data::Question*
	m_question{};

	ExamMimic*
	m_parentExamMimic;
};

}}}
