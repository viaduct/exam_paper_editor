#include "matching_resp_item_mimic.h"
#include "ui_matching_resp_item_mimic.h"
#include "../../data/matching_resp_item.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

MatchingRespItemMimic::MatchingRespItemMimic(QWidget* parent) :
	QGroupBox(parent),
	m_ui(new Ui_MatchingRespItemMimic)
{
	m_ui->setupUi(this);
	m_ui->textEdit->setOwner(this);
	disableTextEdit();
}

MatchingRespItemMimic::~MatchingRespItemMimic()
{
}

data::MatchingRespItem*MatchingRespItemMimic::matchingRespItem() const
{
	return m_matchingRespItem;
}

void MatchingRespItemMimic::setValidMatchingRespItem(data::MatchingRespItem* one)
{
	m_matchingRespItem = one;

	auto textUpdated = [this]
	{
		pullText();
	};
	m_con_textUpdated = m_matchingRespItem->textContainer()->sig_updated()->connect(std::move(textUpdated));

	enableTextEdit();
}

void MatchingRespItemMimic::setNullMatchingRespItem()
{
	disableTextEdit();

	m_con_textUpdated.disconnect();

	m_matchingRespItem = nullptr;
}

void MatchingRespItemMimic::initialized()
{
}

void MatchingRespItemMimic::on_btn_delete_clicked()
{
	if ( m_matchingRespItem )
	{
		context()->act_removeMatchingRespItem(m_matchingRespItem);
	}
}

void MatchingRespItemMimic::on_btn_moveUp_clicked()
{
	if ( m_matchingRespItem )
	{
		context()->act_moveMatchingRespItemUp(m_matchingRespItem);
	}
}

void MatchingRespItemMimic::on_btn_moveDown_clicked()
{
	if ( m_matchingRespItem )
	{
		context()->act_moveMatchingRespItemDown(m_matchingRespItem);
	}
}

void MatchingRespItemMimic::enableTextEdit()
{
	m_ui->textEdit->setReadOnly(false);
	pullText();
}

void MatchingRespItemMimic::disableTextEdit()
{
	m_ui->textEdit->setReadOnly(true);
	m_ui->textEdit->setPlainText("No Matching Response Item.");
}

void MatchingRespItemMimic::pullText()
{
	m_ui->textEdit->setPlainText(m_matchingRespItem->textContainer()->single().c_str());
}

void MatchingRespItemMimic::pushText()
{
	context()->act_setMatchingRespItemText(m_matchingRespItem, m_ui->textEdit->toPlainText().toStdString());
}

MatchingRespItemTextEdit::MatchingRespItemTextEdit(QWidget* parent) :
	QPlainTextEdit(parent)
{
}

void MatchingRespItemTextEdit::setOwner(MatchingRespItemMimic* one)
{
	m_owner = one;
}

void MatchingRespItemTextEdit::focusOutEvent(QFocusEvent* e)
{
	(void)e;
	if ( m_owner->m_matchingRespItem )
	{
		m_owner->pushText();
	}
}

}}}
