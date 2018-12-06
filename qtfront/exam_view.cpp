#include <QFileDialog>
#include "../data/tree_item.h"
#include "../data/exam.h"
#include "exam_view.h"
#include "context.h"
#include "ui_exam_view.h"
#include "exam_model.h"
#include "exam_view_sub/list_view.h"
#include "exam_html_exporter.h"

namespace wally {
namespace qtfront {

class ExamView::SetNullExam : public data::DataCmd
{
public:
	SetNullExam(ExamView* owner) : m_owner(owner) {}
	void run() override final
	{
		m_prev = m_owner->exam();
		m_owner->setNullExam();
	}
	void undo() override final
	{
		m_owner->setValidExam(m_prev);
	}

private:
	ExamView*
	m_owner;

	data::Exam*
	m_prev;
};

ExamView::ExamView(QWidget* parent) : QWidget(parent),
	m_ui(new Ui_ExamView),
	m_model(new ExamModel)
{
	m_ui->setupUi(this);
}

ExamView::~ExamView()
{
	if ( m_exam )
	{
		m_exam->purgeDepended(dependencyKeyFromPtr(this));
	}
}

void ExamView::initialized()
{
	m_ui->edit_name->init(context(), this);
	m_ui->listView->init(context(), this);
	m_model->init(context());
}

void ExamView::on_btn_export_clicked()
{
	if ( m_exam )
	{
		runExport();
	}
}

void ExamView::on_btn_removeSelectedQuestions_clicked()
{
	if ( m_exam )
	{
		auto selectedIndexes = m_ui->listView->selectionModel()->selectedIndexes();
		std::vector<data::Question*> questions;
		for ( auto const& index : selectedIndexes )
		{
			auto question = m_model->indexToData(index);
			questions.push_back(question);
		}
		context()->act_removeExamQuestions(m_exam, questions);
	}
}

void ExamView::on_btn_moveUp_clicked()
{
	if ( m_exam )
	{
		auto curIndex = m_ui->listView->selectionModel()->currentIndex();
		if ( curIndex.isValid() )
		{
			auto curQuestion = m_model->indexToData(curIndex);
			context()->act_moveExamQuestionUp(m_exam, curQuestion);
		}
	}
}

void ExamView::on_btn_moveDown_clicked()
{
	if ( m_exam )
	{
		auto curIndex = m_ui->listView->selectionModel()->currentIndex();
		if ( curIndex.isValid() )
		{
			auto curQuestion = m_model->indexToData(curIndex);
			context()->act_moveExamQuestionDown(m_exam, curQuestion);
		}
	}
}

void ExamView::runExport(const std::string& pageTitle, const std::string& examTitle)
{
	auto rootDirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if ( rootDirPath.isNull() == false )
	{
		QDir rootDir;
		rootDir.setPath(rootDirPath);

		ExamHtmlExporter exporter;
		exporter.init(context());
		exporter.setPageTitle(pageTitle);
		exporter.setExamTitle(examTitle);
		exporter.setExam(m_exam);
		exporter.setRootDir(rootDir);
		exporter.exportHtml();
	}
}

data::Exam*ExamView::exam() const
{
	return m_exam;
}

ExamModel*ExamView::examModel()
{
	return m_model.get();
}

const ExamModel*ExamView::examModel() const
{
	return m_model.get();
}

void ExamView::setExam(data::Exam* one)
{
	if ( one )
	{
		if ( m_exam == nullptr )
		{
			setValidExam(one);
		}
		else if ( m_exam != one )
		{
			setNullExam();
			setValidExam(one);
		}
	}
	else
	{
		setExam(nullptr);
	}
}

void ExamView::setExam(nullptr_t)
{
	if ( m_exam )
	{
		setNullExam();
	}
}

void ExamView::setValidExam(data::Exam* one)
{
	m_exam = one;
	m_exam->addDepended(dependencyKeyFromPtr(this), std::make_shared<SetNullExam>(this));

	m_ui->edit_name->setValidExam(one);

	m_model->setValidExam(one);
}

void ExamView::setNullExam()
{
	m_model->setNullExam();

	m_ui->edit_name->setNullExam();

	m_exam->purgeDepended(dependencyKeyFromPtr(this));
	m_exam = nullptr;
}

}}
