#include <QMouseEvent>

#include "../../data/question.h"
#include "../exam_view.h"
#include "../exam_model.h"
#include "../context.h"
#include "../opened_tree_item_context_var.h"
#include "../drag_context_var.h"
#include "list_view.h"

namespace wally {
namespace qtfront {
namespace exam_view_sub {

ListView::ListView(QWidget* parent) : QListView(parent)
{
	setAcceptDrops(true);
}

ListView::~ListView()
{
}

void ListView::initialized()
{
	setModel(examView()->examModel());
}

void ListView::mouseDoubleClickEvent(QMouseEvent* event)
{
	auto index = indexAt(event->pos());
	if ( index.isValid() )
	{
		auto question = examView()->examModel()->indexToData(index);
		context()->openedTreeItemContextVar()->openTreeItem(question);
	}
}

void ListView::dragEnterEvent(QDragEnterEvent* event)
{
	if ( context()->dragContextVar()->isRightDrag(event) )
	{
		event->acceptProposedAction();
	}
}

void ListView::dragMoveEvent(QDragMoveEvent* e)
{
	(void)e;
}

void ListView::dragLeaveEvent(QDragLeaveEvent* e)
{
	(void)e;
}

void ListView::dropEvent(QDropEvent* e)
{
	// Append questions to the exam.
	{
		auto treeItems = context()->dragContextVar()->treeItems();
		std::vector<data::Question*> questions;
		for ( auto& one : treeItems )
		{
			if ( one->type() == data::DataType::Question )
			{
				questions.push_back(static_cast<data::Question*>(one));
			}
		}

		context()->act_appendExamQuestions(examView()->exam(), questions);
	}

	e->acceptProposedAction();
}

}}}
