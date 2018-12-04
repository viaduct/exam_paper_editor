#pragma once
#include <memory>
#include <QMainWindow>
#include <boost/signals2.hpp>
#include "context_holder.h"

namespace wally {
namespace qtfront {

class TreeItemView;
class QuestionView;
class ExamView;
class PropertyView;
class Ui_MainWindow;

class MainWindow : public QMainWindow,
		public ContextHolder
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow();

protected:
	void initialized() override final;

private:
	void catchUpActiveDir();

	boost::signals2::scoped_connection
	m_con_validDirActivated,
	m_con_beforeNullDirActivated,
	m_con_treeItemOpened;

	std::unique_ptr<Ui_MainWindow>
	m_ui;
};

}}
