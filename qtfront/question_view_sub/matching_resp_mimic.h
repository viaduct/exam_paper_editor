#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "resp_mimic.h"

namespace wally {

namespace data {
class MatchingResp;
class MatchingRespItem;
}

namespace qtfront {
namespace question_view_sub {

class MatchingRespItemMimic;
class Ui_MatchingRespMimic;

class MatchingRespMimic : public RespMimic
{
	Q_OBJECT

public:
	MatchingRespMimic(QWidget* parent = nullptr);
	virtual ~MatchingRespMimic();

	data::Resp* resp() const override final;

	data::MatchingResp* matchingResp() const;
	void setValidMatchingResp(data::MatchingResp* one);
	void setNullMatchingResp();

protected:
	void initialized() override final;

private slots:
	void on_btn_addFirstGroupItem_clicked();
	void on_btn_addSecondGroupItem_clicked();
	void on_btn_delete_clicked();

private:
	MatchingRespItemMimic* createMatchingRespItemMimic(data::MatchingRespItem* one);

	void appendFirstGroupItemMimic(MatchingRespItemMimic* one);
	void insertFirstGroupItemMimic(MatchingRespItemMimic* one, size_t at);
	MatchingRespItemMimic* removeGetFirstGroupItemMimic(size_t at);
	void removeFirstGroupItemMimic(size_t at);
	void moveFirstGroupItemMimic(size_t moveThis, size_t toHere);
	void clearFirstGroupItemMimics();
	void catchUpFirstGroupItemMimics();

	void appendSecondGroupItemMimic(MatchingRespItemMimic* one);
	void insertSecondGroupItemMimic(MatchingRespItemMimic* one, size_t at);
	MatchingRespItemMimic* removeGetSecondGroupItemMimic(size_t at);
	void removeSecondGroupItemMimic(size_t at);
	void moveSecondGroupItemMimic(size_t moveThis, size_t toHere);
	void clearSecondGroupItemMimics();
	void catchUpSecondGroupItemMimics();

	std::vector<MatchingRespItemMimic*>
	m_firstGroupItemMimics,
	m_secondGroupItemMimics;

	boost::signals2::scoped_connection
	m_con_firstGroupItemAdded,
	m_con_beforeFirstGroupItemRemoved,
	m_con_firstGroupItemMoved,
	m_con_beforeFirstGroupItemsCleared,

	m_con_secondGroupItemAdded,
	m_con_beforeSecondGroupItemRemoved,
	m_con_secondGroupItemMoved,
	m_con_beforeSecondGroupItemsCleared;

	std::unique_ptr<Ui_MatchingRespMimic>
	m_ui;

	data::MatchingResp*
	m_matchingResp{};
};

}}}
