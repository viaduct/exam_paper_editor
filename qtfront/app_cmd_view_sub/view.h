#pragma once
#include <QListView>
#include "app_cmd_view_context_holder.h"

namespace wally {
namespace qtfront {
namespace app_cmd_view_sub {

class View : public QListView,
		public AppCmdViewContextHolder
{
public:
	View(QWidget* parent = nullptr);
	virtual ~View();

protected:
	void initialized() override final;
};

}}}
