#pragma once
#include <QWidget>
#include <boost/signals2.hpp>
#include "context_holder.h"

namespace wally {

namespace data {
class Exam;
}

namespace qtfront {

class Ui_ExamView;
class ExamModel;

class ExamView : public QWidget,
		public ContextHolder
{
	Q_OBJECT

	class SetNullExam;

public:
	ExamView(QWidget* parent = nullptr);
	virtual ~ExamView();

	data::Exam* exam() const;
	void setExam(data::Exam* one);
	void setExam(nullptr_t);
	void setValidExam(data::Exam* one);
	void setNullExam();

	ExamModel* examModel();
	ExamModel const* examModel() const;

protected:
	void initialized() override final;

private slots:
	void on_btn_export_clicked();
	void on_btn_removeSelectedQuestions_clicked();
	void on_btn_moveUp_clicked();
	void on_btn_moveDown_clicked();

private:
	void runExport(std::string const& pageTitle = "Exam",
				   std::string const& examTitle = "Title");

	std::unique_ptr<Ui_ExamView>
	m_ui;
	std::unique_ptr<ExamModel>
	m_model;

	data::Exam*
	m_exam{};
};

}}
