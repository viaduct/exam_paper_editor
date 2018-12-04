#include "app_cmd_model_context_holder.h"

namespace wally {
namespace qtfront {
namespace app_cmd_model_sub {

void AppCmdModelContextHolder::init(Context* context, AppCmdModel* model)
{
	m_model = model;
	ContextHolder::init(context);
}

AppCmdModel*AppCmdModelContextHolder::cmdModel() const
{
	return m_model;
}

}}}
