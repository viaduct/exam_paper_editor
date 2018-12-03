#include "../../data/question.h"
#include "../exam_model.h"
#include "question_mimic.h"
#include "exam_mimic.h"

namespace wally {
namespace qtfront {
namespace exam_model_sub {

QuestionMimic::QuestionMimic()
{
}

QuestionMimic::~QuestionMimic()
{
}

data::Question*QuestionMimic::question() const
{
	return m_question;
}

void QuestionMimic::setValidQuestion(data::Question* one)
{
	m_question = one;

	auto nameUpdated = [this]
	{
		auto at = m_parentExamMimic->index(this);
		auto qIndex = examModel()->index(at, 0, QModelIndex());
		examModel()->dataChanged(qIndex, qIndex, QVector<int>() << Qt::DisplayRole);
	};
	m_con_nameUpdated = m_question->nameContainer()->sig_updated()->connect(std::move(nameUpdated));
}

void QuestionMimic::setNullQuestion()
{
	m_con_nameUpdated.disconnect();

	m_question = nullptr;
}

void QuestionMimic::setParentExamMimic(ExamMimic* one)
{
	m_parentExamMimic = one;
}

void QuestionMimic::initialized()
{
}

}}}
