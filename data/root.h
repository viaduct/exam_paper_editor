#pragma once
#include "data.h"

namespace wally {
namespace data {

class Dir;

class Root : public Data
{
public:
	using RootDirContainer = SingleContainer<Dir, std::shared_ptr<Dir>>;

	Root();
	virtual ~Root();

	DataType type() const override final;
	std::vector<Container const*> containers() const override final;

	RootDirContainer const* rootDirContainer() const;
	RootDirContainer* rootDirContainer();

private:
	std::unique_ptr<RootDirContainer>
	m_rootDirContainer;
};

}}
