#include "ui_question_view.h"
#include "question_view.h"
#include "question_view_sub/question_mimic.h"
#include "../data/question.h"
#include "context.h"

namespace wally {
namespace qtfront {

class QuestionView::SetNullQuestion : public data::DataCmd
{
public:
	SetNullQuestion(QuestionView* owner) : m_owner(owner) {}
	void run() override final
	{
		m_prev = m_owner->question();
		m_owner->setNullQuestion();
	}
	void undo() override final
	{
		m_owner->setValidQuestion(m_prev);
	}

private:
	QuestionView*
	m_owner;

	data::Question*
	m_prev;
};

QuestionView::QuestionView(QWidget* parent) : QWidget(parent),
	m_ui(new Ui_QuestionView)
{
	// Setup ui.
	m_ui->setupUi(this);

	// For NameEdit.
	disableNameEdit();

	// Creates default layout for central, null widget.
	m_ui->widget->setLayout(new QVBoxLayout);
}

QuestionView::~QuestionView()
{
	if ( m_question )
	{
		m_question->purgeDepended(dependencyKeyFromPtr(this));
	}
}

void QuestionView::initialized()
{
	m_ui->nameEdit->init(context(), this);
}

void QuestionView::enableNameEdit()
{
	pullName();
	m_ui->nameEdit->setEnabled(true);
}

void QuestionView::disableNameEdit()
{
	m_ui->nameEdit->setText("");
	m_ui->nameEdit->setEnabled(false);
}

void QuestionView::pullName()
{
	auto name = m_question->nameContainer()->single();
	m_ui->nameEdit->setText(name.c_str());
}

void QuestionView::pushName()
{
	auto name = m_ui->nameEdit->text();
	context()->act_setTreeItemName(m_question, name.toStdString());
}

std::unique_ptr<QuestionView::QuestionMimic> QuestionView::createQuestionMimic(data::Question* one)
{
	auto mimic = std::make_unique<QuestionMimic>();
	mimic->init(context(), this);
	mimic->setValidQuestion(one);
	return mimic;
}

data::Question*QuestionView::question() const
{
	return m_question;
}

void QuestionView::setQuestion(data::Question* one)
{
	if ( one )
	{
		if ( m_question == nullptr )
		{
			setValidQuestion(one);
		}
		else if ( m_question != one )
		{
			setNullQuestion();
			setValidQuestion(one);
		}
	}
	else
	{
		setQuestion(nullptr);
	}
}

void QuestionView::setQuestion(nullptr_t)
{
	if ( m_question )
	{
		setNullQuestion();
	}
}

void QuestionView::setValidQuestion(data::Question* one)
{
	m_question = one;
	m_question->addDepended(dependencyKeyFromPtr(this), std::make_shared<SetNullQuestion>(this));

	// For NameEdit.
	auto nameUpdated = [this]
	{
		pullName();
	};
	m_con_nameUpdated = m_question->nameContainer()->sig_updated()->connect(std::move(nameUpdated));

	enableNameEdit();

	// For QuestionMimic.
	m_questionMimic = new QuestionMimic;
	m_questionMimic->init(context(), this);
	m_questionMimic->setValidQuestion(one);

	m_ui->widget->layout()->addWidget(m_questionMimic);
}

void QuestionView::setNullQuestion()
{
	// For QuestionMimic.
	m_ui->widget->layout()->removeWidget(m_questionMimic->widget());
	delete m_questionMimic;

	// For NameEdit.
	disableNameEdit();
	m_con_nameUpdated.disconnect();

	m_question->purgeDepended(dependencyKeyFromPtr(this));
	m_question = nullptr;
}

}}
