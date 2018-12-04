#include "matching_resp_mimic.h"
#include "matching_resp_item_mimic.h"
#include "ui_matching_resp_mimic.h"
#include "../context.h"
#include "../../data/matching_resp.h"

namespace wally {
namespace qtfront {
namespace question_view_sub {

MatchingRespMimic::MatchingRespMimic(QWidget* parent) :
	RespMimic(parent),
	m_ui(new Ui_MatchingRespMimic)
{
	m_ui->setupUi(this);
}

MatchingRespMimic::~MatchingRespMimic()
{
}

data::Resp*MatchingRespMimic::resp() const
{
	return m_matchingResp;
}

data::MatchingResp*MatchingRespMimic::matchingResp() const
{
	return m_matchingResp;
}

void MatchingRespMimic::setValidMatchingResp(data::MatchingResp* one)
{
	m_matchingResp = one;

	auto firstGroupItemAdded = [this](data::MatchingRespItem* one, size_t at)
	{
		insertFirstGroupItemMimic(createMatchingRespItemMimic(one), at);
	};
	auto beforeFirstGroupItemRemoved = [this](data::MatchingRespItem* one, size_t at)
	{
		(void)one;
		removeFirstGroupItemMimic(at);
	};
	auto firstGroupItemMoved = [this](data::MatchingRespItem* one, size_t moveThis, size_t toHere)
	{
		(void)one;
		moveFirstGroupItemMimic(moveThis, toHere);
	};
	auto beforeFirstGroupItemsCleared = [this]
	{
		clearFirstGroupItemMimics();
	};

	auto secondGroupItemAdded = [this](data::MatchingRespItem* one, size_t at)
	{
		insertSecondGroupItemMimic(createMatchingRespItemMimic(one), at);
	};
	auto beforeSecondGroupItemRemoved = [this](data::MatchingRespItem* one, size_t at)
	{
		(void)one;
		removeSecondGroupItemMimic(at);
	};
	auto secondGroupItemMoved = [this](data::MatchingRespItem* one, size_t moveThis, size_t toHere)
	{
		(void)one;
		moveSecondGroupItemMimic(moveThis, toHere);
	};
	auto beforeSecondGroupItemsCleared = [this]
	{
		clearSecondGroupItemMimics();
	};

	m_con_firstGroupItemAdded = m_matchingResp->firstGroupContainer()->sig_added()->connect(std::move(firstGroupItemAdded));
	m_con_beforeFirstGroupItemRemoved = m_matchingResp->firstGroupContainer()->sig_beforeRemoved()->connect(std::move(beforeFirstGroupItemRemoved));
	m_con_firstGroupItemMoved = m_matchingResp->firstGroupContainer()->sig_moved()->connect(std::move(firstGroupItemMoved));
	m_con_beforeFirstGroupItemsCleared = m_matchingResp->firstGroupContainer()->sig_beforeCleared()->connect(std::move(beforeFirstGroupItemsCleared));

	m_con_secondGroupItemAdded = m_matchingResp->secondGroupContainer()->sig_added()->connect(std::move(secondGroupItemAdded));
	m_con_beforeSecondGroupItemRemoved = m_matchingResp->secondGroupContainer()->sig_beforeRemoved()->connect(std::move(beforeSecondGroupItemRemoved));
	m_con_secondGroupItemMoved = m_matchingResp->secondGroupContainer()->sig_moved()->connect(std::move(secondGroupItemMoved));
	m_con_beforeSecondGroupItemsCleared = m_matchingResp->secondGroupContainer()->sig_beforeCleared()->connect(std::move(beforeSecondGroupItemsCleared));

	catchUpFirstGroupItemMimics();
	catchUpSecondGroupItemMimics();
}

void MatchingRespMimic::setNullMatchingResp()
{
	clearSecondGroupItemMimics();
	clearFirstGroupItemMimics();

	m_con_beforeSecondGroupItemsCleared.disconnect();
	m_con_secondGroupItemMoved.disconnect();
	m_con_beforeSecondGroupItemRemoved.disconnect();
	m_con_secondGroupItemAdded.disconnect();

	m_con_beforeFirstGroupItemsCleared.disconnect();
	m_con_firstGroupItemMoved.disconnect();
	m_con_beforeFirstGroupItemRemoved.disconnect();
	m_con_firstGroupItemAdded.disconnect();

	m_matchingResp = nullptr;
}

void MatchingRespMimic::initialized()
{
}

void MatchingRespMimic::on_btn_addFirstGroupItem_clicked()
{
	if ( m_matchingResp )
	{
		context()->act_appendMatchingRespItem(m_matchingResp->firstGroupContainer(), "New Matching Response Item.");
	}
}

void MatchingRespMimic::on_btn_addSecondGroupItem_clicked()
{
	if ( m_matchingResp )
	{
		context()->act_appendMatchingRespItem(m_matchingResp->secondGroupContainer(), "New Matching Response Item.");
	}
}

void MatchingRespMimic::on_btn_delete_clicked()
{
	if ( m_matchingResp )
	{
		context()->act_removeResp(m_matchingResp->parentContainer());
	}
}

MatchingRespItemMimic* MatchingRespMimic::createMatchingRespItemMimic(data::MatchingRespItem* one)
{
	auto mimic = new MatchingRespItemMimic;
	mimic->init(context(), questionView());
	mimic->setValidMatchingRespItem(one);
	return mimic;
}

void MatchingRespMimic::appendFirstGroupItemMimic(MatchingRespItemMimic* one)
{
	m_firstGroupItemMimics.push_back(one);

	m_ui->layout_firstGroupItems->addWidget(one);
}

void MatchingRespMimic::insertFirstGroupItemMimic(MatchingRespItemMimic* one, size_t at)
{
	m_firstGroupItemMimics.insert(m_firstGroupItemMimics.begin() + at, one);

	m_ui->layout_firstGroupItems->insertWidget(at, one);
}

MatchingRespItemMimic* MatchingRespMimic::removeGetFirstGroupItemMimic(size_t at)
{
	auto one = m_firstGroupItemMimics[at];

	m_firstGroupItemMimics.erase(m_firstGroupItemMimics.begin() + at);

	return one;
}

void MatchingRespMimic::removeFirstGroupItemMimic(size_t at)
{
	auto one = m_firstGroupItemMimics[at];

	m_firstGroupItemMimics.erase(m_firstGroupItemMimics.begin() + at);

	delete one;
}

void MatchingRespMimic::moveFirstGroupItemMimic(size_t moveThis, size_t toHere)
{
	auto one = removeGetFirstGroupItemMimic(moveThis);
	insertFirstGroupItemMimic(one, toHere);
}

void MatchingRespMimic::clearFirstGroupItemMimics()
{
	m_firstGroupItemMimics.clear();
}

void MatchingRespMimic::catchUpFirstGroupItemMimics()
{
	for ( auto& matItem : m_matchingResp->firstGroupContainer()->list() )
	{
		appendFirstGroupItemMimic(createMatchingRespItemMimic(matItem));
	}
}

void MatchingRespMimic::appendSecondGroupItemMimic(MatchingRespItemMimic* one)
{
	m_secondGroupItemMimics.push_back(one);

	m_ui->layout_secondGroupItems->addWidget(one);
}

void MatchingRespMimic::insertSecondGroupItemMimic(MatchingRespItemMimic* one, size_t at)
{
	m_secondGroupItemMimics.insert(m_secondGroupItemMimics.begin() + at, one);

	m_ui->layout_secondGroupItems->insertWidget(at, one);
}

MatchingRespItemMimic* MatchingRespMimic::removeGetSecondGroupItemMimic(size_t at)
{
	auto one = m_secondGroupItemMimics[at];

	m_secondGroupItemMimics.erase(m_secondGroupItemMimics.begin() + at);

	return one;
}

void MatchingRespMimic::removeSecondGroupItemMimic(size_t at)
{
	auto one = m_secondGroupItemMimics[at];

	m_secondGroupItemMimics.erase(m_secondGroupItemMimics.begin() + at);

	delete one;
}

void MatchingRespMimic::moveSecondGroupItemMimic(size_t moveThis, size_t toHere)
{
	auto one = removeGetSecondGroupItemMimic(moveThis);
	insertSecondGroupItemMimic(one, toHere);
}

void MatchingRespMimic::clearSecondGroupItemMimics()
{
	m_secondGroupItemMimics.clear();
}

void MatchingRespMimic::catchUpSecondGroupItemMimics()
{
	for ( auto& matItem : m_matchingResp->secondGroupContainer()->list() )
	{
		appendSecondGroupItemMimic(createMatchingRespItemMimic(matItem));
	}
}

}}}
