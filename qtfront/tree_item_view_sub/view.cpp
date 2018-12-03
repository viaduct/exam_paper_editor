//#include <QMouseEvent>
#include <QMenu>
#include "view.h"
#include "../tree_item_view.h"
#include "../tree_item_model.h"
#include "../context.h"
#include "../opened_tree_item_context_var.h"
#include "../drag_context_var.h"
#include "../../data/tree_item.h"

namespace wally {
namespace qtfront {
namespace tree_item_view_sub {

View::View(QWidget* parent) : QListView(parent)
{
	/* This code is disabled because the class reimplements keyboard and mouse events.
	 * If later the code is changed to use default implementation of QListView for
	 * keyboard and mouse events, re-enable this code below.
	 */

	/* Starts from here. */

	// Opening context menu will call openContextMenu().
//	setContextMenuPolicy(Qt::CustomContextMenu);
//	connect(this, SIGNAL(customContextMenuRequested(QPoint)),
//			this, SLOT(openContextMenu(QPoint)));

	// Enable multiple selection.
//	setSelectionMode(ExtendedSelection);

	/* Ends in here. */
}

View::~View()
{
}

void View::initialized()
{
	// Set model.
	setModel(treeItemView()->treeItemModel());
}

void View::mousePressEvent(QMouseEvent* event)
{
	if ( event->button() == Qt::RightButton )
	{
		openContextMenu(event->pos());

		event->accept();
	}

	m_emitter.mousePressed(event);
}

void View::mouseReleaseEvent(QMouseEvent* e)
{
	m_emitter.mouseReleased(e);
}

void View::mouseMoveEvent(QMouseEvent* e)
{
	m_emitter.mouseMoved(e);
}

void View::mouseDoubleClickEvent(QMouseEvent* event)
{
	auto index = indexAt(event->pos());
	if ( index.isValid() )
	{
		auto model = treeItemView()->treeItemModel();
		auto treeItem = model->indexToData(index);
		context()->openedTreeItemContextVar()->openTreeItem(treeItem);

		event->accept();
	}
}

void View::openContextMenu(const QPoint& pos)
{
	enum class Action
	{
		Null,
		Rename
	};

	auto index = indexAt(pos);
	data::TreeItem* treeItem = nullptr; // index is valid if treeItem is valid.
	if ( index.isValid() )
	{
		treeItem = static_cast<data::TreeItem*>(treeItemView()->treeItemModel()->indexToData(index));
	}

	QMenu menu;
	if ( treeItem )
	{
		menu.addAction("Rename")->setData((int)Action::Rename);
	}

	auto triggeredAction = menu.exec(mapToGlobal(pos));

	if ( triggeredAction )
	{
		switch ( (Action)triggeredAction->data().toInt() )
		{
			case Action::Rename:
				edit(index);
				break;
			case Action::Null:
				break;
		}
	}
}

void View::emitter_clicked(QMouseEvent* event)
{
	if ( event->button() == Qt::LeftButton )
	{
		auto index = indexAt(event->pos());
		if ( index.isValid() )
		{
			selectionModel()->select(index, selectionModel()->ClearAndSelect);
			selectionModel()->setCurrentIndex(index, selectionModel()->Current);

			event->accept();
		}
	}
}

void View::emitter_dragStarted(QMouseEvent* event, Qt::MouseButton button)
{
	if ( button == Qt::LeftButton )
	{
		auto index = indexAt(event->pos());
		if ( index.isValid() )
		{
			auto treeItem = treeItemView()->treeItemModel()->indexToData(index);

			context()->dragContextVar()->execDrag(this, std::vector<data::TreeItem*>{treeItem});

			event->accept();
		}
	}
}

void View::emitter_dragReleased(QMouseEvent* event)
{
	(void)event;
}

void View::emitter_dragMoved(QMouseEvent* event)
{
	(void)event;
}

}}}
