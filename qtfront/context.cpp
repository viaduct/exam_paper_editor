#include "context.h"
#include "app.h"

namespace wally {
namespace qtfront {

App*Context::app()
{
	return m_app;
}

void Context::setApp(App* one)
{
	m_app = one;
}

data::Root*Context::root()
{
	return m_app->root();
}

AppCmdManager*Context::cmdManager()
{
	return m_app->cmdManager();
}

Loader*Context::loader()
{
	return m_app->loader();
}

}}
