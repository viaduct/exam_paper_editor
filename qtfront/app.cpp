#include <QApplication>
#include "app.h"
#include "loader.h"
#include "../data/root.h"
#include "app_cmd_manager.h"
#include "context.h"
#include "main_window.h"

namespace wally {
namespace qtfront {

Loader*App::loader()
{
	return m_loader.get();
}

data::Root*App::root()
{
	return m_root.get();
}

AppCmdManager*App::cmdManager()
{
	return m_cmdManager.get();
}

Context*App::context()
{
	return m_context.get();
}

MainWindow*App::mainWindow()
{
	return m_mainWindow.get();
}

int App::exec(int argc, char** argv)
{
	QApplication app(argc, argv);

	// Initialize Loader.
	m_loader = std::make_unique<Loader>();
	m_loader->load(); // Load resources.

	// Initialize data Root.
	m_root = std::make_unique<data::Root>();

	// Initialize AppCmdManager.
	m_cmdManager = std::make_unique<AppCmdManager>();

	// Initialize Context
	m_context = std::make_unique<Context>();
	m_context->setApp(this);

	// Initialize MainWindow.
	m_mainWindow = std::make_unique<MainWindow>();
	m_mainWindow->init(m_context.get());

	// Set mainWindow visible.
	m_mainWindow->show();

	// Start application.
	return app.exec();
}

}}
