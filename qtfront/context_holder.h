#pragma once

namespace wally {
namespace qtfront {

class Context;

class ContextHolder
{
public:
	void init(Context* context);

	Context* context() const;

protected:
	virtual void initialized() = 0;

private:
	Context*
	m_context;
};

}}
