#include <QTabBar>
#include <QKeyEvent>
#include "editor_view.h"
#include "context.h"
#include "dir_context_var.h"
#include "question_view.h"
#include "exam_view.h"
#include "../data/exam.h"
#include "../data/question.h"

namespace wally {
namespace qtfront {

EditorView::EditorView(QWidget* parent) :
	QTabWidget(parent)
{
	tabBar()->setTabsClosable(true);
	connect(tabBar(), SIGNAL(tabCloseRequested(int)),
			this, SLOT(closeDataTab(int)));
}

EditorView::~EditorView()
{
}

void EditorView::openTreeItem(data::TreeItem* one)
{
	switch ( one->type() )
	{
		case data::DataType::Question:
			openQuestion(static_cast<data::Question*>(one));
			break;
		case data::DataType::Exam:
			openExam(static_cast<data::Exam*>(one));
			break;
		default:
			break;
	}
}

void EditorView::initialized()
{
}

void EditorView::keyPressEvent(QKeyEvent* event)
{
	// Take Ctrl+W
	if ( event->key() == Qt::Key_W )
	{
		if ( (Qt::ShiftModifier | event->modifiers()) != 0 )
		{
			removeCurrentDataWidget();
			event->accept();
		}
		else { event->ignore(); }
	}
	else { event->ignore(); }
}

void EditorView::closeDataTab(int index)
{
	removeDataWidget(index);
}

size_t EditorView::correspondingInfo(const data::Data* one, bool* isValid)
{
	if ( isValid ) { *isValid = true; }
	for ( size_t i = 0; i < m_widgetInfos.size(); ++i )
	{
		if ( m_widgetInfos[i].data == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

size_t EditorView::correspondingInfo(const QWidget* one, bool* isValid)
{
	if ( isValid ) { *isValid = true; }
	for ( size_t i = 0; i < m_widgetInfos.size(); ++i )
	{
		if ( m_widgetInfos[i].widget == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

void EditorView::openQuestion(data::Question* one)
{
	bool hasQuestion;
	auto index = correspondingInfo(one, &hasQuestion);
	if ( hasQuestion )
	{
		setCurrentWidget(m_widgetInfos[index].widget);
	}
	else
	{
		addQuestionWidget(one);
	}
}

void EditorView::openExam(data::Exam* one)
{
	bool hasExam;
	auto index = correspondingInfo(one, &hasExam);
	if ( hasExam )
	{
		setCurrentWidget(m_widgetInfos[index].widget);
	}
	else
	{
		addExamWidget(one);
	}
}

void EditorView::addQuestionWidget(data::Question* one)
{
	auto qWidget = new QuestionView;
	qWidget->init(context());
	qWidget->setValidQuestion(one);
	qWidget->setMaximumWidth(600);

	addTab(qWidget, "Question");
	setCurrentWidget(qWidget);

	WidgetInfo info;
	info.data = one;
	info.widget = qWidget;
	m_widgetInfos.push_back(info);
}

void EditorView::addExamWidget(data::Exam* one)
{
	auto eWidget = new ExamView;
	eWidget->init(context());
	eWidget->setValidExam(one);
	eWidget->setMaximumWidth(600);

	addTab(eWidget, "Exam");
	setCurrentWidget(eWidget);

	WidgetInfo info;
	info.data = one;
	info.widget = eWidget;
	m_widgetInfos.push_back(info);
}

void EditorView::removeDataWidget(int index)
{
	auto curWidget = this->widget(index);
	auto infoIndex = correspondingInfo(curWidget);

	m_widgetInfos.erase(m_widgetInfos.begin() + infoIndex);

	removeTab(indexOf(curWidget));
}

void EditorView::removeCurrentDataWidget()
{
	auto curIndex = this->currentIndex();
	if ( curIndex != -1 )
	{
		removeDataWidget(curIndex);
	}
}

}}
