#pragma once
#include "../context_holder.h"

namespace wally {
namespace qtfront {

class AppCmdModel;

namespace app_cmd_model_sub {

class AppCmdModelContextHolder : public ContextHolder
{
public:
	void init(Context* context, AppCmdModel* model);

	AppCmdModel* cmdModel() const;

private:
	using ContextHolder::init;

	AppCmdModel*
	m_model;
};

}}}
