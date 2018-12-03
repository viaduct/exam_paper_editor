#include "name_edit.h"
#include "../context.h"
#include "../../data/exam.h"

namespace wally {
namespace qtfront {
namespace exam_view_sub {

NameEdit::NameEdit(QWidget* parent) : QLineEdit(parent)
{
}

NameEdit::~NameEdit()
{
}

data::Exam*NameEdit::exam() const
{
	return m_exam;
}

void NameEdit::setValidExam(data::Exam* one)
{
	m_exam = one;

	auto nameUpdated = [this]
	{
		pullText();
	};
	m_con_nameUpdated = m_exam->nameContainer()->sig_updated()->connect(std::move(nameUpdated));

	pullText();
	setEnabled(true);
}

void NameEdit::setNullExam()
{
	pushText();
	setEnabled(false);

	m_con_nameUpdated.disconnect();

	m_exam = nullptr;
}

void NameEdit::initialized()
{
}

void NameEdit::focusOutEvent(QFocusEvent* event)
{
	(void)event;
	pushText();
}

void NameEdit::pullText()
{
	setText(m_exam->nameContainer()->single().c_str());
}

void NameEdit::pushText()
{
	context()->act_setTreeItemName(m_exam, text().toStdString());
}

}}}
