#include "question_mimic.h"
#include "block_context_mimic.h"
#include "multiple_choices_resp_mimic.h"
#include "matching_resp_mimic.h"
#include "ui_question_mimic.h"
#include "../../data/question.h"
#include "../../data/block_context.h"
#include "../../data/multiple_choices_resp.h"
#include "../../data/matching_resp.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

QuestionMimic::QuestionMimic(QWidget* parent) :
	QScrollArea(parent),
	m_ui(new Ui_QuestionMimic)
{
	m_ui->setupUi(this);
}

QuestionMimic::~QuestionMimic()
{
}

data::Question*QuestionMimic::question() const
{
	return m_question;
}

void QuestionMimic::setValidQuestion(data::Question* one)
{
	m_question = one;

	auto validContextSet = [this]
	{
		setValidContextMimic();
	};
	auto beforeNullContextSet = [this]
	{
		setNullContextMimic();
	};
	auto validRespSet = [this]
	{
		setValidRespMimic();
	};
	auto beforeNullRespSet = [this]
	{
		setNullRespMimic();
	};
	m_con_validContextSet = m_question->contextContainer()->sig_validSet()->connect(std::move(validContextSet));
	m_con_beforeNullContextSet = m_question->contextContainer()->sig_beforeNullSet()->connect(std::move(beforeNullContextSet));
	m_con_validRespSet = m_question->respContainer()->sig_validSet()->connect(std::move(validRespSet));
	m_con_beforeNullRespSet = m_question->respContainer()->sig_beforeNullSet()->connect(std::move(beforeNullRespSet));

	catchUpContext();
	catchUpResp();
}

void QuestionMimic::setNullQuestion()
{
	setNullRespMimicSafely();
	setNullContextMimicSafely();

	m_con_beforeNullRespSet.disconnect();
	m_con_validRespSet.disconnect();
	m_con_beforeNullContextSet.disconnect();
	m_con_validContextSet.disconnect();

	m_question = nullptr;
}

void QuestionMimic::initialized()
{
}

void QuestionMimic::on_btn_addBlockContext_clicked()
{
	if ( question() )
	{
		context()->act_addBlockContext(question()->contextContainer());
	}
}

void QuestionMimic::on_btn_addMultipleChoicesResp_clicked()
{
	if ( question() )
	{
		context()->act_addMultipleChoicesResp(question()->respContainer());
	}
}

void QuestionMimic::on_btn_addMatchingResp_clicked()
{
	if ( question() )
	{
		context()->act_addMatchingResp(question()->respContainer());
	}
}

void QuestionMimic::catchUpContext()
{
	if ( m_question->contextContainer()->isValid() )
	{
		setValidContextMimic();
	}
}

void QuestionMimic::catchUpResp()
{
	if ( m_question->respContainer()->isValid() )
	{
		setValidRespMimic();
	}
}

void QuestionMimic::setNullContextMimicSafely()
{
	if ( m_contextMimic )
	{
		setNullContextMimic();
	}
}

void QuestionMimic::setNullRespMimicSafely()
{
	if ( m_respMimic )
	{
		setNullRespMimic();
	}
}

void QuestionMimic::setValidContextMimic()
{
	switch ( m_question->contextContainer()->single()->type() )
	{
		case data::DataType::BlockContext:
		{
			auto blockContext = static_cast<data::BlockContext*>(m_question->contextContainer()->single());

			// Create mimic.
			auto mimic = new BlockContextMimic;
			mimic->init(context(), questionView());
			mimic->setValidBlockContext(blockContext);

			m_contextMimic = mimic;
		}
			break;
		default:
			assert(false);
	}

	setContextVisible(true);
}

void QuestionMimic::setValidRespMimic()
{
	switch ( m_question->respContainer()->single()->type() )
	{
		case data::DataType::MultipleChoicesResp:
		{
			auto multipleChoicesResp = static_cast<data::MultipleChoicesResp*>(m_question->respContainer()->single());

			auto mimic = new MultipleChoicesRespMimic;
			mimic->init(context(), questionView());
			mimic->setValidMultipleChoicesResp(multipleChoicesResp);

			m_respMimic = mimic;
		}
			break;
		case data::DataType::MatchingResp:
		{
			auto matchingResp = static_cast<data::MatchingResp*>(m_question->respContainer()->single());

			auto mimic = new MatchingRespMimic;
			mimic->init(context(), questionView());
			mimic->setValidMatchingResp(matchingResp);

			m_respMimic = mimic;
		}
			break;
		default:
			assert(false);
	}

	setRespVisible(true);
}

void QuestionMimic::setNullContextMimic()
{
	setContextVisible(false);

	delete m_contextMimic;
}

void QuestionMimic::setNullRespMimic()
{
	setRespVisible(false);

	delete m_respMimic;
}

void QuestionMimic::setContextVisible(bool doThis)
{
	if ( doThis != m_contextVisible )
	{
		if ( doThis )
		{
			auto noContextIndex = rootLayout()->indexOf(m_ui->noContext);
			rootLayout()->insertWidget(noContextIndex, m_contextMimic);

			m_contextMimic->show();
			m_ui->noContext->hide();

			m_contextVisible = true;
		}
		else
		{
			rootLayout()->removeWidget(m_contextMimic);

			m_ui->noContext->show();
			m_contextMimic->hide();

			m_contextVisible = false;
		}
	}
}

void QuestionMimic::setRespVisible(bool doThis)
{
	if ( doThis != m_respVisible )
	{
		if ( doThis )
		{
			auto noRespIndex = rootLayout()->indexOf(m_ui->noResp);
			rootLayout()->insertWidget(noRespIndex, m_respMimic);

			m_respMimic->show();
			m_ui->noResp->hide();

			m_respVisible = true;
		}
		else
		{
			rootLayout()->removeWidget(m_respMimic);

			m_ui->noResp->show();
			m_respMimic->hide();

			m_respVisible = false;
		}
	}
}

QVBoxLayout*QuestionMimic::rootLayout()
{
	return static_cast<QVBoxLayout*>(m_ui->widget->layout());
}

}}}
