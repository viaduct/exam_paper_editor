#pragma once
#include <memory>

namespace wally {

namespace data {
class Root;
}

namespace qtfront {

class MainWindow;
class AppCmdManager;
class AppCmdModel;
class Loader;
class Context;

class App
{
public:
	App() = default;
	App(App const&) = delete;
	App& operator =(App const&) = delete;

	Loader* loader();
	data::Root* root();
	AppCmdManager* cmdManager();
	Context* context();
	AppCmdModel* cmdModel();
	MainWindow* mainWindow();

	int exec(int argc, char** argv);

private:
	std::unique_ptr<Loader>
	m_loader;
	std::unique_ptr<data::Root>
	m_root;
	std::unique_ptr<AppCmdManager>
	m_cmdManager;
	std::unique_ptr<Context>
	m_context;
	std::unique_ptr<AppCmdModel>
	m_cmdModel;
	std::unique_ptr<MainWindow>
	m_mainWindow;
};

}}
