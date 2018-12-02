#include "root.h"
#include "dir.h"

namespace wally {
namespace data {

Root::Root() :
	m_rootDirContainer(new RootDirContainer(this))
{
}

Root::~Root()
{
}

DataType Root::type() const
{
	return DataType::Root;
}

std::vector<const Container*> Root::containers() const
{
	std::vector<const Container*> result;

	result.push_back(m_rootDirContainer.get());

	return result;
}

const Root::RootDirContainer*Root::rootDirContainer() const
{
	return m_rootDirContainer.get();
}

Root::RootDirContainer*Root::rootDirContainer()
{
	return m_rootDirContainer.get();
}

}}
