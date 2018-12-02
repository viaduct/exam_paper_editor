#include "exam.h"
#include "question.h"

namespace wally {
namespace data {

Exam::Exam() :
	m_questionContainer(new QuestionContainer(this))
{
}

Exam::~Exam()
{
}

DataType Exam::type() const
{
	return DataType::Exam;
}

std::vector<const Container*> Exam::containers() const
{
	auto result = File::containers();

	return result;
}

const Exam::QuestionContainer*Exam::questionContainer() const
{
	return m_questionContainer.get();
}

Exam::QuestionContainer*Exam::questionContainer()
{
	return m_questionContainer.get();
}

}}
