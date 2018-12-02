#pragma once
#include "data.h"

namespace wally {
namespace data {

class TreeItem : public Data
{
public:
	using NameContainer = SinglePrimContainer<std::string>;

	TreeItem();
	virtual ~TreeItem();

	std::vector<Container const*> containers() const override;

	NameContainer const* nameContainer() const;
	NameContainer* nameContainer();

private:
	std::unique_ptr<NameContainer>
	m_nameContainer;
};

}}
