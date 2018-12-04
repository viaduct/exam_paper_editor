#include "main_window.h"
#include "ui_main_window.h"
#include "context.h"
#include "dir_context_var.h"
#include "opened_tree_item_context_var.h"
#include "editor_view.h"
#include "../data/tree_item.h"

namespace wally {
namespace qtfront {

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	m_ui(new Ui_MainWindow)
{
	m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initialized()
{
	m_ui->treeItemView->init(context());
	m_ui->cmdView->init(context());
	m_ui->tabView->init(context());

	auto validDirActivated = [this]
	{
		// Set activeDir to treeItemView.
		m_ui->treeItemView->setValidDir(context()->dirContextVar()->activeDir());
	};
	auto beforeNullDirActivated = [this]
	{
		// Call setNullDir() to treeItemView.
		m_ui->treeItemView->setNullDir();
	};
	auto treeItemOpened = [this](data::TreeItem* one)
	{
		// Open treeItem in EditorView.
		m_ui->tabView->openTreeItem(one);
	};
	m_con_treeItemOpened = context()->openedTreeItemContextVar()->sig_treeItemOpened()->connect(std::move(treeItemOpened));
	m_con_validDirActivated = context()->dirContextVar()->sig_validDirActivated()->connect(std::move(validDirActivated));
	m_con_beforeNullDirActivated = context()->dirContextVar()->sig_beforeNullDirActivated()->connect(std::move(beforeNullDirActivated));

	// treeItemOpened does not request catch up.
	catchUpActiveDir();

	// Set AppCmdView Model.
	m_ui->cmdView->takeAppCmdModelFromContext();
}

void MainWindow::catchUpActiveDir()
{
	auto activeDir = context()->dirContextVar()->activeDir();
	if ( activeDir )
	{
		m_ui->treeItemView->setValidDir(activeDir);
	}
}

}}
