#include "../../data/exam.h"
#include "../exam_model.h"
#include "exam_mimic.h"
#include "question_mimic.h"

namespace wally {
namespace qtfront {
namespace exam_model_sub {

ExamMimic::ExamMimic()
{
}

ExamMimic::~ExamMimic()
{
}

data::Exam*ExamMimic::exam() const
{
	return m_exam;
}

void ExamMimic::setValidExam(data::Exam* one)
{
	m_exam = one;

	auto added = [this](data::Question* one, size_t at)
	{
		insertQuestionMimic(createQuestionMimic(one), at);
	};
	auto beforeRemoved = [this](data::Question* one, size_t at)
	{
		(void)one;
		removeQuestionMimic(at);
	};
	auto moved = [this](data::Question* one, size_t from, size_t to)
	{
		(void)one;
		moveQuestionMimic(from, to);
	};
	auto beforeCleared = [this]
	{
		clearQuestionMimics();
	};
	m_con_questionAdded = m_exam->questionContainer()->sig_added()->connect(std::move(added));
	m_con_beforeQuestionRemoved = m_exam->questionContainer()->sig_beforeRemoved()->connect(std::move(beforeRemoved));
	m_con_questionMoved = m_exam->questionContainer()->sig_moved()->connect(std::move(moved));
	m_con_beforeQuestionsCleared = m_exam->questionContainer()->sig_beforeCleared()->connect(std::move(beforeCleared));

	catchUpQuestionMimics();
}

void ExamMimic::setNullExam()
{
	clearQuestionMimics();

	m_con_beforeQuestionsCleared.disconnect();
	m_con_questionMoved.disconnect();
	m_con_beforeQuestionRemoved.disconnect();
	m_con_questionAdded.disconnect();

	m_exam = nullptr;
}

size_t ExamMimic::size() const
{
	return m_questionMimics.size();
}

size_t ExamMimic::index(const QuestionMimic* one, bool* isValid) const
{
	return index(one->question(), isValid);
}

size_t ExamMimic::index(const data::Question* one, bool* isValid) const
{
	if ( isValid ) { *isValid = true; }
	for ( size_t i = 0; i < m_questionMimics.size(); ++i )
	{
		if ( m_questionMimics[i]->question() == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

QuestionMimic*ExamMimic::at(size_t at)
{
	return m_questionMimics[at].get();
}

QuestionMimic const* ExamMimic::at(size_t at) const
{
	return m_questionMimics[at].get();
}

void ExamMimic::initialized()
{
}

std::unique_ptr<QuestionMimic> ExamMimic::createQuestionMimic(data::Question* one)
{
	auto mimic = std::make_unique<QuestionMimic>();
	mimic->init(context(), examModel());
	mimic->setParentExamMimic(this);
	mimic->setValidQuestion(one);
	return std::move(mimic);
}

void ExamMimic::appendQuestionMimic(std::unique_ptr<QuestionMimic>&& one)
{
	auto at = m_questionMimics.size();

	examModel()->beginInsertRows(QModelIndex(), at, at);

	m_questionMimics.push_back(std::move(one));

	examModel()->endInsertRows();
}

void ExamMimic::insertQuestionMimic(std::unique_ptr<QuestionMimic>&& one, size_t at)
{
	examModel()->beginInsertRows(QModelIndex(), at, at);

	m_questionMimics.insert(m_questionMimics.begin() + at, std::move(one));

	examModel()->endInsertRows();
}

void ExamMimic::removeQuestionMimic(size_t at)
{
	examModel()->beginRemoveRows(QModelIndex(), at, at);

	m_questionMimics.erase(m_questionMimics.begin() + at);

	examModel()->endRemoveRows();
}

void ExamMimic::moveQuestionMimic(size_t moveThis, size_t toHere)
{
	// Checked.
	if ( moveThis < toHere )
	{
		examModel()->beginMoveRows(
					QModelIndex(),
					moveThis, moveThis,
					QModelIndex(),
					toHere + 1);
	}
	else
	{
		examModel()->beginMoveRows(
					QModelIndex(),
					moveThis, moveThis,
					QModelIndex(),
					toHere);
	}

	auto one = std::move(m_questionMimics[moveThis]);
	m_questionMimics.erase(m_questionMimics.begin() + moveThis);
	m_questionMimics.insert(m_questionMimics.begin() + toHere, std::move(one));

	examModel()->endMoveRows();
}

void ExamMimic::catchUpQuestionMimics()
{
	auto questions = m_exam->questionContainer()->list();

	examModel()->beginInsertRows(QModelIndex(), 0, questions.size() - 1);

	for ( auto& question : questions )
	{
		m_questionMimics.push_back(createQuestionMimic(question));
	}

	examModel()->endInsertRows();
}

void ExamMimic::clearQuestionMimics()
{
	examModel()->beginRemoveRows(QModelIndex(), 0, m_questionMimics.size() - 1);

	m_questionMimics.clear();

	examModel()->endRemoveRows();
}

}}}
