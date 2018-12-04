#include "ui_block_context_mimic.h"
#include "block_context_mimic.h"
#include "block_list_mimic.h"
#include "../../data/block_context.h"
#include "../../data/question.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

BlockContextMimic::BlockContextMimic(QWidget* parent) :
	ContextMimic(parent),
	m_ui(new Ui_BlockContextMimic)
{
	m_ui->setupUi(this);
}

BlockContextMimic::~BlockContextMimic()
{
}

data::Context*BlockContextMimic::dataContext() const
{
	return m_blockContext;
}

data::BlockContext*BlockContextMimic::blockContext() const
{
	return m_blockContext;
}

void BlockContextMimic::setValidBlockContext(data::BlockContext* one)
{
	m_blockContext = one;

	auto validRootSet = [this]
	{
		setValidBlockListMimic();
	};
	auto beforeNullRootSet = [this]
	{
		setNullBlockListMimic();
	};
	m_con_validRootSet = m_blockContext->rootBlockContainer()->sig_validSet()->connect(std::move(validRootSet));
	m_con_beforeNullRootSet = m_blockContext->rootBlockContainer()->sig_beforeNullSet()->connect(std::move(beforeNullRootSet));

	catchUpBlockListMimic();
}

void BlockContextMimic::setNullBlockContext()
{
	setNullBlockListMimicSafely();

	m_con_beforeNullRootSet.disconnect();
	m_con_validRootSet.disconnect();

	m_blockContext = nullptr;
}

void BlockContextMimic::initialized()
{
}

void BlockContextMimic::on_btn_del_clicked()
{
	if ( m_blockContext )
	{
		context()->act_removeContext(m_blockContext->parentContainer());
	}
}

QVBoxLayout*BlockContextMimic::rootLayout()
{
	return static_cast<QVBoxLayout*>(layout());
}

void BlockContextMimic::catchUpBlockListMimic()
{
	if ( m_blockContext->rootBlockContainer()->isValid() )
	{
		setValidBlockListMimic();
	}
}

void BlockContextMimic::setNullBlockListMimicSafely()
{
	if ( m_blockListMimic )
	{
		setNullBlockListMimic();
	}
}

void BlockContextMimic::setValidBlockListMimic()
{
	// Create mimic.
	m_blockListMimic = new BlockListMimic;
	m_blockListMimic->init(context(), questionView());
	m_blockListMimic->setValidBlockList(m_blockContext->rootBlockContainer()->single());

	rootLayout()->insertWidget(0, m_blockListMimic);
}

void BlockContextMimic::setNullBlockListMimic()
{
	delete m_blockListMimic;
}

}}}
