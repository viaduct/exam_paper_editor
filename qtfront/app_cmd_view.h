#pragma once
#include <QWidget>
#include <memory>
#include "context_holder.h"

namespace wally {
namespace qtfront {

class Ui_AppCmdView;
class AppCmdModel;

class AppCmdView : public QWidget,
		public ContextHolder
{
	Q_OBJECT

public:
	AppCmdView(QWidget* parent = nullptr);
	virtual ~AppCmdView();

	void setAppCmdModel(AppCmdModel* one);
	void takeAppCmdModelFromContext();

protected:
	void initialized() override final;

private slots:
	void on_btn_undo_clicked();
	void on_btn_redo_clicked();
	void on_btn_undoUntil_clicked();
	void on_btn_redoUntil_clicked();

private:
	std::unique_ptr<Ui_AppCmdView>
	m_ui;
};

}}
