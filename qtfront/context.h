#pragma once

namespace wally {

namespace data {
class Root;
}

namespace qtfront {

class App;
class AppCmdManager;
class Loader;

class Context
{
public:
	Context() = default;
	Context(Context const&) = delete;
	Context& operator =(Context const&) = delete;

	App* app();
	void setApp(App* one);

	// Getters for conveniences.
	data::Root* root();
	AppCmdManager* cmdManager();
	Loader* loader();

private:
	App*
	m_app;
};

}}
