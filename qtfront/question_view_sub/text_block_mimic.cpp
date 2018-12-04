#include "text_block_mimic.h"
#include "ui_text_block_mimic.h"
#include "../../data/text_block.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

TextBlockMimic::TextBlockMimic(QWidget* parent) :
	BlockMimic(parent),
	m_ui(new Ui_TextBlockMimic)
{
	m_ui->setupUi(this);
	m_ui->textEdit->setOwner(this);
}

TextBlockMimic::~TextBlockMimic()
{
}

data::Block*TextBlockMimic::block() const
{
	return m_textBlock;
}

data::TextBlock*TextBlockMimic::textBlock()
{
	return m_textBlock;
}

void TextBlockMimic::setValidTextBlock(data::TextBlock* one)
{
	m_textBlock = one;

	auto textUpdated = [this]{pullText();};
	m_con_textUpdated = m_textBlock->textContainer()->sig_updated()->connect(std::move(textUpdated));

	enableTextEdit();
}

void TextBlockMimic::setNullTextBlock()
{
	pushText();
	disableTextEdit();

	m_con_textUpdated.disconnect();

	m_textBlock = nullptr;
}

void TextBlockMimic::initialized()
{
}

void TextBlockMimic::on_btn_delete_clicked()
{
	if ( m_textBlock )
	{
		context()->act_removeBlock(m_textBlock);
	}
}

void TextBlockMimic::on_btn_moveUp_clicked()
{
	if ( m_textBlock )
	{
		context()->act_moveBlockUp(m_textBlock);
	}
}

void TextBlockMimic::on_btn_moveDown_clicked()
{
	if ( m_textBlock )
	{
		context()->act_moveBlockDown(m_textBlock);
	}
}

void TextBlockMimic::enableTextEdit()
{
	m_ui->textEdit->setReadOnly(false);
	pullText();
}

void TextBlockMimic::disableTextEdit()
{
	m_ui->textEdit->setReadOnly(true);
	m_ui->textEdit->setPlainText("No Text Block set.");
}

void TextBlockMimic::pullText()
{
	m_ui->textEdit->setPlainText(m_textBlock->textContainer()->single().c_str());
}

void TextBlockMimic::pushText()
{
	context()->act_setTextBlockText(m_textBlock, m_ui->textEdit->toPlainText().toStdString());
}

TextBlockTextEdit::TextBlockTextEdit(QWidget* parent) :
	QPlainTextEdit(parent)
{
}

void TextBlockTextEdit::setOwner(TextBlockMimic* one)
{
	m_owner = one;
}

void TextBlockTextEdit::focusOutEvent(QFocusEvent* e)
{
	(void)e;
	if ( m_owner->textBlock() )
	{
		m_owner->pushText();
	}
}

}}}
