#pragma once
#include <QTabWidget>
#include <boost/signals2.hpp>
#include <list>
#include "context_holder.h"

namespace wally {

namespace data {
class Data;
class TreeItem;
class Question;
class Exam;
}

namespace qtfront {

class EditorView : public QTabWidget,
		public ContextHolder
{
	Q_OBJECT

public:
	EditorView(QWidget* parent = nullptr);
	virtual ~EditorView();

	void openTreeItem(data::TreeItem* one);

protected:
	void initialized() override final;

	void keyPressEvent(QKeyEvent* event) override final;

private slots:
	void closeDataTab(int index);

private:
	size_t correspondingInfo(data::Data const* one, bool* isValid = nullptr);
	size_t correspondingInfo(QWidget const* one, bool* isValid = nullptr);

	void openQuestion(data::Question* one);
	void openExam(data::Exam* one);

	void addQuestionWidget(data::Question* one);
	void addExamWidget(data::Exam* one);

	void removeDataWidget(int index);
	void removeCurrentDataWidget();

	struct WidgetInfo {
		QWidget* widget;
		data::Data* data;
	};
	std::vector<WidgetInfo>
	m_widgetInfos;
};

}}
