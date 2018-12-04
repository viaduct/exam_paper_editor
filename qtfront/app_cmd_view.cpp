#include "app_cmd_view.h"
#include "ui_app_cmd_view.h"
#include "app_cmd_model.h"
#include "context.h"
#include "app_cmd_manager.h"

namespace wally {
namespace qtfront {

AppCmdView::AppCmdView(QWidget* parent) : QWidget(parent),
	m_ui(new Ui_AppCmdView)
{
	m_ui->setupUi(this);
}

AppCmdView::~AppCmdView()
{
}

void AppCmdView::setAppCmdModel(AppCmdModel* one)
{
	m_ui->listView->setModel(one);
}

void AppCmdView::takeAppCmdModelFromContext()
{
	m_ui->listView->setModel(context()->cmdModel());
}

void AppCmdView::initialized()
{
	m_ui->listView->init(context(), this);
}

void AppCmdView::on_btn_undo_clicked()
{
	context()->cmdManager()->undo();
}

void AppCmdView::on_btn_redo_clicked()
{
	context()->cmdManager()->redo();
}

void AppCmdView::on_btn_undoUntil_clicked()
{
	auto curIndex = m_ui->listView->selectionModel()->currentIndex();
	if ( curIndex.isValid() )
	{
		auto model = static_cast<AppCmdModel*>(this->m_ui->listView->model());
		auto appCmd = model->indexToAppCmd(curIndex);
		context()->cmdManager()->undoUntil(appCmd);
	}
}

void AppCmdView::on_btn_redoUntil_clicked()
{
	auto curIndex = m_ui->listView->selectionModel()->currentIndex();
	if ( curIndex.isValid() )
	{
		auto model = static_cast<AppCmdModel*>(this->m_ui->listView->model());
		auto appCmd = model->indexToAppCmd(curIndex);
		context()->cmdManager()->redoUntil(appCmd);
	}
}

}}
