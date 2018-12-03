#pragma once
#include <string>
#include <QDir>
#include "context_holder.h"

namespace wally {

namespace data {
class Exam;
class Question;
class Context;
class BlockContext;
class TextBlock;
class ImageBlock;
class Resp;
class MultipleChoicesResp;
class MatchingResp;
class Choice;
class MatchingRespItem;
}

namespace qtfront {

class ExamHtmlExporter : public ContextHolder
{
public:
	ExamHtmlExporter(data::Exam* exam = nullptr);

	void setExam(data::Exam* one);
	void setPageTitle(std::string const& value);
	void setExamTitle(std::string const& value);
	void setRootDir(QDir const& value);

	QDir rootDir() const;

	void exportHtml() const;

protected:
	void initialized() override final;

private:
	bool hasRootDir() const;
	void makeRootDir() const;

	// Print exam.
	std::string printExam(data::Exam* one) const;

	// Print question.
	std::string printQuestion(data::Question* one) const;

	// Print question context.
	std::string printContext(data::Context* one) const;
	std::string printBlockContext(data::BlockContext* one) const;
	std::string printTextBlock(data::TextBlock* one) const;
	std::string printImageBlock(data::ImageBlock* block) const;

	// Print question response.
	std::string printResp(data::Resp* one) const;
	std::string printMultipleChoicesResp(data::MultipleChoicesResp* one) const;
	std::string printMatchingResp(data::MatchingResp* one) const;
	std::string printChoice(data::Choice* one) const;
	std::string printMatchingRespItem(data::MatchingRespItem* one) const;

	static std::string newLineToHtmlBr(std::string const& value);

	std::string
	m_pageTitle,
	m_examTitle;

	QDir
	m_rootDir;

	data::Exam*
	m_exam;

	// Context for exporting html and its resources belonging.
	// Should only be used when html() is called.
	void initContext() const;

	mutable size_t
	m_imageCount;

	mutable int
	m_curQuestionIndex;
};

}}
