#pragma once
#include <memory>

namespace wally {

namespace data {
class Root;
}

namespace qtfront {

class App;
class AppCmdManager;
class Loader;
class DirContextVar;
class OpenedTreeItemContextVar;
class DragContextVar;

class Context
{
public:
	Context();
	~Context();
	Context(Context const&) = delete;
	Context& operator =(Context const&) = delete;

	App* app();
	void setApp(App* one);

	// Getters for conveniences.
	data::Root* root();
	AppCmdManager* cmdManager();
	Loader* loader();

	DirContextVar* dirContextVar();
	OpenedTreeItemContextVar* openedTreeItemContextVar();
	DragContextVar* dragContextVar();

private:
	std::unique_ptr<DirContextVar>
	m_dirContextVar;
	std::unique_ptr<OpenedTreeItemContextVar>
	m_openedTreeItemContextVar;
	std::unique_ptr<DragContextVar>
	m_dragContextVar;

	App*
	m_app;
};

}}
