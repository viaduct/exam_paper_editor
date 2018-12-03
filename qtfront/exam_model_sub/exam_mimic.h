#pragma once
#include <vector>
#include <memory>
#include <boost/signals2.hpp>
#include "exam_model_context_holder.h"

namespace wally {

namespace data {
class Exam;
}

namespace qtfront {
namespace exam_model_sub {

class QuestionMimic;

class ExamMimic : public ExamModelContextHolder
{
public:
	ExamMimic();
	virtual ~ExamMimic();

	data::Exam* exam() const;
	void setValidExam(data::Exam* one);
	void setNullExam();

	size_t size() const;
	size_t index(QuestionMimic const* one, bool* isValid = nullptr) const;
	size_t index(data::Question const* one, bool* isValid = nullptr) const;
	QuestionMimic* at(size_t at);
	QuestionMimic const* at(size_t at) const;

protected:
	void initialized() override final;

private:
	std::unique_ptr<QuestionMimic> createQuestionMimic(data::Question* one);
	void appendQuestionMimic(std::unique_ptr<QuestionMimic>&& one);
	void insertQuestionMimic(std::unique_ptr<QuestionMimic>&& one, size_t at);
	void removeQuestionMimic(size_t at);
	void moveQuestionMimic(size_t moveThis, size_t toHere);
	void catchUpQuestionMimics();
	void clearQuestionMimics();

	std::vector<std::unique_ptr<QuestionMimic>>
	m_questionMimics;

	boost::signals2::scoped_connection
	m_con_questionAdded,
	m_con_beforeQuestionRemoved,
	m_con_questionMoved,
	m_con_beforeQuestionsCleared;

	data::Exam*
	m_exam{};
};

}}}
