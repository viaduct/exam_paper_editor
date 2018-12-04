#include "app_cmd_view_context_holder.h"

namespace wally {
namespace qtfront {
namespace app_cmd_view_sub {

void AppCmdViewContextHolder::init(Context* context, AppCmdView* view)
{
	m_view = view;
	ContextHolder::init(context);
}

AppCmdView*AppCmdViewContextHolder::cmdView() const
{
	return m_view;
}

}}}
