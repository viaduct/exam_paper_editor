#pragma once
#include <QListView>
#include <boost/signals2.hpp>
#include "../click_event_emitter.h"
#include "tree_item_view_context_holder.h"

namespace wally {
namespace qtfront {
namespace tree_item_view_sub {

class View : public QListView,
		public TreeItemViewContextHolder
{
	Q_OBJECT

public:
	View(QWidget* parent = nullptr);
	virtual ~View();

protected:
	void initialized() override final;

	void mousePressEvent(QMouseEvent *event) override final;
	void mouseReleaseEvent(QMouseEvent *e) override final;
	void mouseMoveEvent(QMouseEvent *e) override final;
	void mouseDoubleClickEvent(QMouseEvent *event) override final;

private slots:
	void openContextMenu(QPoint const& pos);

private:
	void emitter_clicked(QMouseEvent* event);
	void emitter_dragStarted(QMouseEvent* event, Qt::MouseButton button);
	void emitter_dragReleased(QMouseEvent* event);
	void emitter_dragMoved(QMouseEvent* event);

	ClickEventEmitter<
	View,
	&View::emitter_clicked,
	&View::emitter_dragStarted,
	&View::emitter_dragReleased,
	&View::emitter_dragMoved>
	m_emitter{this};
};

}}}
