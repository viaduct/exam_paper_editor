#pragma once
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <boost/signals2.hpp>
#include "block_mimic.h"

namespace wally {

namespace data {
class TextBlock;
}

namespace qtfront {
namespace question_view_sub {

class TextBlockMimic;
class TextBlockTextEdit;
class Ui_TextBlockMimic;

class TextBlockTextEdit : public QPlainTextEdit
{
public:
	TextBlockTextEdit(QWidget* parent = nullptr);
	void setOwner(TextBlockMimic* one);

protected:
	void focusOutEvent(QFocusEvent *e) override final;

private:
	TextBlockMimic*
	m_owner;
};

class TextBlockMimic : public BlockMimic
{
	Q_OBJECT

	friend class TextBlockTextEdit;

public:
	TextBlockMimic(QWidget* parent = nullptr);
	virtual ~TextBlockMimic();
	TextBlockMimic(TextBlockMimic const&) = delete;
	TextBlockMimic& operator =(TextBlockMimic const&) = delete;

	data::Block* block() const override final;

	data::TextBlock* textBlock();
	void setValidTextBlock(data::TextBlock* one);
	void setNullTextBlock();

protected:
	void initialized() override final;

private slots:
	void on_btn_delete_clicked();
	void on_btn_moveUp_clicked();
	void on_btn_moveDown_clicked();

private:
	void enableTextEdit();
	void disableTextEdit();
	void pullText();
	void pushText();

	boost::signals2::scoped_connection
	m_con_textUpdated;

	std::unique_ptr<Ui_TextBlockMimic>
	m_ui;

	data::TextBlock*
	m_textBlock{};
};

}}}
