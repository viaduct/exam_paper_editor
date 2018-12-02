#include "container.h"

namespace wally {
namespace data {

Container::Container(Data* owner) :
	m_owner(owner)
{
}

Data*Container::owner() const
{
	return m_owner;
}

}}
