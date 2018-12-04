#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class AppCmdView;

namespace app_cmd_view_sub {

class AppCmdViewContextHolder : public ContextHolder
{
public:
	void init(Context* context, AppCmdView* view);

	AppCmdView* cmdView() const;

private:
	using ContextHolder::init;

	AppCmdView*
	m_view;
};

}}}
