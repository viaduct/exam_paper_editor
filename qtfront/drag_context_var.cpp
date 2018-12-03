#include <QDrag>
#include <QMimeData>
#include "drag_context_var.h"

namespace wally {
namespace qtfront {

void DragContextVar::execDrag(QObject* subject, const std::vector<data::TreeItem*>& ones)
{
	m_treeItems = ones;

	auto drag = new QDrag(subject);
	auto mime = new QMimeData;
	drag->setMimeData(mime);
	m_currentMimeData = mime;
	drag->exec();
}

void DragContextVar::execDrag(QObject* subject, std::vector<data::TreeItem*>&& ones)
{
	m_treeItems = std::move(ones);

	auto drag = new QDrag(subject);
	auto mime = new QMimeData;
	drag->setMimeData(mime);
	m_currentMimeData = mime;
	drag->exec();
}

bool DragContextVar::isRightDrag(QDragEnterEvent* event)
{
	return event->mimeData() == m_currentMimeData;
}

std::vector<data::TreeItem*> DragContextVar::treeItems() const
{
	return m_treeItems;
}

}}
