#pragma once
#include <memory>
#include <boost/signals2.hpp>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "resp_mimic.h"

namespace wally {

namespace data {
class MultipleChoicesResp;
class Choice;
}

namespace qtfront {
namespace question_view_sub {

class ChoiceMimic;
class Ui_MultipleChoicesRespMimic;

class MultipleChoicesRespMimic : public RespMimic
{
	Q_OBJECT

public:
	MultipleChoicesRespMimic(QWidget* parent = nullptr);
	virtual ~MultipleChoicesRespMimic();

	data::Resp* resp() const override final;

	data::MultipleChoicesResp* multipleChoicesResp() const;
	void setValidMultipleChoicesResp(data::MultipleChoicesResp* one);
	void setNullMultipleChoicesResp();

protected:
	void initialized() override final;

private slots:
	void on_btn_addChoice_clicked();
	void on_btn_del_clicked();

private:
	ChoiceMimic* createChoiceMimic(data::Choice* one);

	void appendChoiceMimic(ChoiceMimic* one);
	void insertChoiceMimic(ChoiceMimic* one, size_t at);
	ChoiceMimic* removeGetChoiceMimic(size_t at);
	void removeChoiceMimic(size_t at);
	void moveChoiceMimic(size_t moveThis, size_t toHere);
	void clearChoiceMimics();
	void catchUpChoiceMimics();

	std::vector<ChoiceMimic*>
	m_choiceMimics;

	boost::signals2::scoped_connection
	m_con_choiceAdded,
	m_con_beforeChoiceRemoved,
	m_con_choiceMoved,
	m_con_beforeChoicesCleared;

	std::unique_ptr<Ui_MultipleChoicesRespMimic>
	m_ui;

	data::MultipleChoicesResp*
	m_multipleChoicesResp{};
};

}}}
