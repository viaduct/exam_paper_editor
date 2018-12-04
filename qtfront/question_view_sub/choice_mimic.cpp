#include "choice_mimic.h"
#include "ui_choice_mimic.h"
#include "../../data/choice.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

ChoiceMimic::ChoiceMimic(QWidget* parent) :
	QGroupBox(parent),
	m_ui(new Ui_ChoiceMimic)
{
	m_ui->setupUi(this);
	m_ui->textEdit->setOwner(this);

	disableTextEdit();
}

ChoiceMimic::~ChoiceMimic()
{
}

data::Choice*ChoiceMimic::choice() const
{
	return m_choice;
}

void ChoiceMimic::setValidChoice(data::Choice* one)
{
	m_choice = one;

	auto textUpdated =[this]
	{
		pullText();
	};
	m_con_textUpdated = m_choice->textContainer()->sig_updated()->connect(std::move(textUpdated));

	enableTextEdit();
}

void ChoiceMimic::setNullChoice()
{
	pushText();

	disableTextEdit();

	m_con_textUpdated.disconnect();

	m_choice = nullptr;
}

void ChoiceMimic::initialized()
{
}

void ChoiceMimic::on_btn_delete_clicked()
{
	if ( m_choice )
	{
		context()->act_removeChoice(m_choice);
	}
}

void ChoiceMimic::on_btn_moveUp_clicked()
{
	if ( m_choice )
	{
		context()->act_moveChoiceUp(m_choice);
	}
}

void ChoiceMimic::on_btn_moveDown_clicked()
{
	if ( m_choice )
	{
		context()->act_moveChoiceDown(m_choice);
	}
}

void ChoiceMimic::enableTextEdit()
{
	m_ui->textEdit->setReadOnly(false);
	pullText();
}

void ChoiceMimic::disableTextEdit()
{
	m_ui->textEdit->setReadOnly(true);
	m_ui->textEdit->setPlainText("No Choice set.");
}

void ChoiceMimic::pullText()
{
	m_ui->textEdit->setPlainText(m_choice->textContainer()->single().c_str());
}

void ChoiceMimic::pushText()
{
	context()->act_setChoiceText(m_choice, m_ui->textEdit->toPlainText().toStdString());
}

ChoiceTextEdit::ChoiceTextEdit(QWidget* parent) :
	QPlainTextEdit(parent)
{
}

void ChoiceTextEdit::setOwner(ChoiceMimic* owner)
{
	m_owner = owner;
}

void ChoiceTextEdit::focusOutEvent(QFocusEvent* e)
{
	(void)e;
	if ( m_owner->m_choice )
	{
		m_owner->pushText();
	}
}

}}}
