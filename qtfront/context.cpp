#include "context.h"
#include "app.h"
#include "dir_context_var.h"
#include "opened_tree_item_context_var.h"
#include "drag_context_var.h"

namespace wally {
namespace qtfront {

Context::Context() :
	m_dirContextVar(new DirContextVar),
	m_openedTreeItemContextVar(new OpenedTreeItemContextVar),
	m_dragContextVar(new DragContextVar)
{
}

Context::~Context()
{
}

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

DirContextVar*Context::dirContextVar()
{
	return m_dirContextVar.get();
}

OpenedTreeItemContextVar*Context::openedTreeItemContextVar()
{
	return m_openedTreeItemContextVar.get();
}

DragContextVar*Context::dragContextVar()
{
	return m_dragContextVar.get();
}

}}
