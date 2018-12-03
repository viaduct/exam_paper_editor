#include "context_holder.h"

namespace wally {
namespace qtfront {

void ContextHolder::init(Context* context)
{
	m_context = context;
	initialized();
}

Context*ContextHolder::context() const
{
	return m_context;
}



}}
