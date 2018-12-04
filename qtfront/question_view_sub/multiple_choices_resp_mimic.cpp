#include "multiple_choices_resp_mimic.h"
#include "choice_mimic.h"
#include "ui_multiple_choices_resp_mimic.h"
#include "../../data/multiple_choices_resp.h"
#include "../context.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

MultipleChoicesRespMimic::MultipleChoicesRespMimic(QWidget* parent) :
	RespMimic(parent),
	m_ui(new Ui_MultipleChoicesRespMimic)
{
	m_ui->setupUi(this);
}

MultipleChoicesRespMimic::~MultipleChoicesRespMimic()
{
}

data::Resp*MultipleChoicesRespMimic::resp() const
{
	return m_multipleChoicesResp;
}

data::MultipleChoicesResp*MultipleChoicesRespMimic::multipleChoicesResp() const
{
	return m_multipleChoicesResp;
}

void MultipleChoicesRespMimic::setValidMultipleChoicesResp(data::MultipleChoicesResp* one)
{
	m_multipleChoicesResp = one;

	auto choiceAdded = [this](data::Choice* one, size_t at)
	{
		insertChoiceMimic(createChoiceMimic(one), at);
	};
	auto beforeChoiceRemoved = [this](data::Choice* one, size_t at)
	{
		(void)one;
		removeChoiceMimic(at);
	};
	auto choiceMoved = [this](data::Choice* one, size_t from, size_t to)
	{
		(void)one;
		moveChoiceMimic(from, to);
	};
	auto beforeChoicesCleared = [this]
	{
		clearChoiceMimics();
	};
	m_con_choiceAdded = m_multipleChoicesResp->choiceContainer()->sig_added()->connect(std::move(choiceAdded));
	m_con_beforeChoiceRemoved = m_multipleChoicesResp->choiceContainer()->sig_beforeRemoved()->connect(std::move(beforeChoiceRemoved));
	m_con_choiceMoved = m_multipleChoicesResp->choiceContainer()->sig_moved()->connect(std::move(choiceMoved));
	m_con_beforeChoicesCleared = m_multipleChoicesResp->choiceContainer()->sig_beforeCleared()->connect(std::move(beforeChoicesCleared));

	catchUpChoiceMimics();
}

void MultipleChoicesRespMimic::setNullMultipleChoicesResp()
{
	clearChoiceMimics();

	m_con_beforeChoicesCleared.disconnect();
	m_con_choiceMoved.disconnect();
	m_con_beforeChoiceRemoved.disconnect();
	m_con_choiceAdded.disconnect();

	m_multipleChoicesResp = nullptr;
}

void MultipleChoicesRespMimic::initialized()
{
}

void MultipleChoicesRespMimic::on_btn_addChoice_clicked()
{
	if ( m_multipleChoicesResp )
	{
		context()->act_appendChoice(m_multipleChoicesResp->choiceContainer(), "New Choice.");
	}
}

void MultipleChoicesRespMimic::on_btn_del_clicked()
{
	if ( m_multipleChoicesResp )
	{
		context()->act_removeResp(m_multipleChoicesResp->parentContainer());
	}
}

ChoiceMimic*MultipleChoicesRespMimic::createChoiceMimic(data::Choice* one)
{
	auto mimic = new ChoiceMimic;
	mimic->init(context(), questionView());
	mimic->setValidChoice(one);
	return mimic;
}

void MultipleChoicesRespMimic::appendChoiceMimic(ChoiceMimic* one)
{
	m_choiceMimics.push_back(one);

	m_ui->layout_choices->addWidget(one);
}

void MultipleChoicesRespMimic::insertChoiceMimic(ChoiceMimic* one, size_t at)
{
	m_choiceMimics.insert(m_choiceMimics.begin() + at, one);

	m_ui->layout_choices->insertWidget(at, one);
}

ChoiceMimic* MultipleChoicesRespMimic::removeGetChoiceMimic(size_t at)
{
	auto one = m_choiceMimics[at];

	m_choiceMimics.erase(m_choiceMimics.begin() + at);

	return one;
}

void MultipleChoicesRespMimic::removeChoiceMimic(size_t at)
{
	auto one = m_choiceMimics[at];

	m_choiceMimics.erase(m_choiceMimics.begin() + at);

	delete one;
}

void MultipleChoicesRespMimic::moveChoiceMimic(size_t moveThis, size_t toHere)
{
	auto mimic = removeGetChoiceMimic(moveThis);
	insertChoiceMimic(mimic, toHere);
}

void MultipleChoicesRespMimic::clearChoiceMimics()
{
	m_choiceMimics.clear();
}

void MultipleChoicesRespMimic::catchUpChoiceMimics()
{
	for ( auto& choice : m_multipleChoicesResp->choiceContainer()->list() )
	{
		appendChoiceMimic(createChoiceMimic(choice));
	}
}

}}}
