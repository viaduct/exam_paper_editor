#pragma once
#include "file.h"

namespace wally {
namespace data {

class Question;

class Exam : public File
{
public:
	using QuestionContainer = ListContainer<Question, TypeEnum::Ref>;

	Exam();
	virtual ~Exam();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	QuestionContainer const* questionContainer() const;
	QuestionContainer* questionContainer();

private:
	std::unique_ptr<QuestionContainer>
	m_questionContainer;
};

}}
