#pragma once
#include "resp.h"

namespace wally {
namespace data {

class Choice;

class MultipleChoicesResp : public Resp
{
public:
	using ChoiceContainer = ListContainer<Choice, std::shared_ptr<Choice>>;

	MultipleChoicesResp();
	virtual ~MultipleChoicesResp();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	ChoiceContainer const* choiceContainer() const;
	ChoiceContainer* choiceContainer();

private:
	std::unique_ptr<ChoiceContainer>
	m_choiceContainer;
};

}}
