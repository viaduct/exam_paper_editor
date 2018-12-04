#pragma once
#include <boost/signals2.hpp>
#include <memory>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "context_mimic.h"

namespace wally {

namespace data {
class BlockContext;
}

namespace qtfront {
namespace question_view_sub {

class Ui_BlockContextMimic;
class BlockListMimic;

class BlockContextMimic : public ContextMimic
{
	Q_OBJECT

public:
	BlockContextMimic(QWidget* parent = nullptr);
	virtual ~BlockContextMimic();

	data::Context* dataContext() const override final;

	data::BlockContext* blockContext() const;
	void setValidBlockContext(data::BlockContext* one);
	void setNullBlockContext();

protected:
	void initialized() override final;

private slots:
	void on_btn_del_clicked();

private:
	QVBoxLayout* rootLayout();

	void setValidBlockListMimic();
	void setNullBlockListMimic();
	void catchUpBlockListMimic();
	void setNullBlockListMimicSafely();

	boost::signals2::scoped_connection
	m_con_validRootSet,
	m_con_beforeNullRootSet;

	std::unique_ptr<Ui_BlockContextMimic>
	m_ui;

	BlockListMimic*
	m_blockListMimic;

	data::BlockContext*
	m_blockContext{};
};

}}}
