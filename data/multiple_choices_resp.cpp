#include "multiple_choices_resp.h"
#include "choice.h"

namespace wally {
namespace data {

MultipleChoicesResp::MultipleChoicesResp() :
	m_choiceContainer(new ChoiceContainer(this))
{
}

MultipleChoicesResp::~MultipleChoicesResp()
{
}

DataType MultipleChoicesResp::type() const
{
	return DataType::MultipleChoicesResp;
}

std::vector<const Container*> MultipleChoicesResp::containers() const
{
	auto result = Resp::containers();

	result.push_back(m_choiceContainer.get());

	return result;
}

const MultipleChoicesResp::ChoiceContainer*MultipleChoicesResp::choiceContainer() const
{
	return m_choiceContainer.get();
}

MultipleChoicesResp::ChoiceContainer*MultipleChoicesResp::choiceContainer()
{
	return m_choiceContainer.get();
}

}}
