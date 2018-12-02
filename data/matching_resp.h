#pragma once
#include "resp.h"

namespace wally {
namespace data {

class MatchingRespItem;

class MatchingResp : public Resp
{
public:
	using FirstGroupContainer = ListContainer<MatchingRespItem, std::shared_ptr<MatchingRespItem>>;
	using SecondGroupContainer = ListContainer<MatchingRespItem, std::shared_ptr<MatchingRespItem>>;

	MatchingResp();
	virtual ~MatchingResp();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	FirstGroupContainer const* firstGroupContainer() const;
	FirstGroupContainer* firstGroupContainer();
	SecondGroupContainer const* secondGroupContainer() const;
	SecondGroupContainer* secondGroupContainer();

private:
	std::unique_ptr<FirstGroupContainer>
	m_firstGroupContainer;
	std::unique_ptr<SecondGroupContainer>
	m_secondGroupContainer;
};

}}
