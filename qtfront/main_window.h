#pragma once
#include <QMainWindow>
#include "context_holder.h"

namespace wally {
namespace qtfront {

class MainWindow : public QMainWindow,
		public ContextHolder
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

protected:
	void initialized() override final;
};

}}
