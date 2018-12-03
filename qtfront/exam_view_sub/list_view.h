#pragma once
#include <QListView>
#include "exam_view_context_holder.h"

namespace wally {

namespace data {
class Exam;
}

namespace qtfront {
namespace exam_view_sub {

class ListView : public QListView,
		public ExamViewContextHolder
{
public:
	ListView(QWidget* parent = nullptr);
	virtual ~ListView();

protected:
	void initialized() override final;

	void mouseDoubleClickEvent(QMouseEvent *event) override final;

	void dragEnterEvent(QDragEnterEvent *event) override final;
	void dragMoveEvent(QDragMoveEvent *e) override final;
	void dragLeaveEvent(QDragLeaveEvent *e) override final;
	void dropEvent(QDropEvent *e) override final;
};

}}}
