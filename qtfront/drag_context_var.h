#pragma once
#include <vector>
#include <QDragEnterEvent>

namespace wally {

namespace data {
class TreeItem;
}

namespace qtfront {

class DragContextVar
{
public:
	DragContextVar() = default;
	DragContextVar(DragContextVar const&) = delete;
	DragContextVar& operator =(DragContextVar const&) = delete;

	void execDrag(QObject* subject, std::vector<data::TreeItem*> const& ones);
	void execDrag(QObject* subject, std::vector<data::TreeItem*>&& ones);

	bool isRightDrag(QDragEnterEvent* event);

	std::vector<data::TreeItem*> treeItems() const;

private:
	std::vector<data::TreeItem*>
	m_treeItems;

	QMimeData const*
	m_currentMimeData{};
};

}}
