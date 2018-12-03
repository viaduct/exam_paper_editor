#include <fstream>
#include <regex>

#include <boost/format.hpp>

#include "exam_html_exporter.h"
#include "context.h"
#include "loader.h"

// datas.
#include "../data/block_context.h"
#include "../data/block_list.h"
#include "../data/text_block.h"
#include "../data/image_block.h"
#include "../data/image.h"
#include "../data/multiple_choices_resp.h"
#include "../data/matching_resp.h"
#include "../data/choice.h"
#include "../data/matching_resp_item.h"
#include "../data/question.h"
#include "../data/exam.h"

namespace wally {
namespace qtfront {

ExamHtmlExporter::ExamHtmlExporter(data::Exam* exam) :
	m_exam(exam)
{
}

void ExamHtmlExporter::setExam(data::Exam* one)
{
	m_exam = one;
}

void ExamHtmlExporter::setPageTitle(const std::string& value)
{
	m_pageTitle = value;
}

void ExamHtmlExporter::setExamTitle(const std::string& value)
{
	m_examTitle = value;
}

QDir ExamHtmlExporter::rootDir() const
{
	return m_rootDir;
}

void ExamHtmlExporter::initialized()
{
}

void ExamHtmlExporter::setRootDir(const QDir& value)
{
	m_rootDir = value;
}

void ExamHtmlExporter::exportHtml() const
{
	if ( hasRootDir() )
	{
		makeRootDir();
	}
	initContext();
	auto html = printExam(m_exam);

	// Write html file.
	std::ofstream file(m_rootDir.filePath("index.html").toStdString());
	if ( file )
	{
		for ( auto const& ch : html )
		{
			file << ch;
		}
	}
}

bool ExamHtmlExporter::hasRootDir() const
{
	return m_rootDir.exists();
}

void ExamHtmlExporter::makeRootDir() const
{
	m_rootDir.mkdir(".");
}

std::string ExamHtmlExporter::printExam(data::Exam* one) const
{
	auto eFormat = context()->loader()->html_exam();

	// Set page title.
	eFormat = std::regex_replace(eFormat, std::regex("%1%"), m_pageTitle);

	// Set exam title.
	eFormat = std::regex_replace(eFormat, std::regex("%2%"), m_examTitle);

	// Set questions.
	std::string qHtml;
	for ( auto const& question : one->questionContainer()->list() )
	{
		qHtml += printQuestion(question);
	}
	eFormat = std::regex_replace(eFormat, std::regex("%3%"), qHtml);

	return eFormat;
}

std::string ExamHtmlExporter::printQuestion(data::Question* one) const
{
	auto qFormat = context()->loader()->html_question();

	// Set question numbering.
	auto numberingText = boost::format("Q%1%.");
	numberingText % m_curQuestionIndex;
	++m_curQuestionIndex;

	qFormat = std::regex_replace(qFormat, std::regex("%1%"), numberingText.str());

	// Set context and resp.
	std::string contextNResp;
	if ( one->contextContainer()->isValid() )
	{
		contextNResp += printContext(one->contextContainer()->single());
	}
	if ( one->respContainer()->isValid() )
	{
		contextNResp += printResp(one->respContainer()->single());
	}
	qFormat = std::regex_replace(qFormat, std::regex("%2%"), contextNResp);

	return qFormat;
}

std::string ExamHtmlExporter::printContext(data::Context* one) const
{
	switch ( one->type() )
	{
		case data::DataType::BlockContext:
			return printBlockContext(static_cast<data::BlockContext*>(one));
		default:
			assert(false);
	}
}

std::string ExamHtmlExporter::printBlockContext(data::BlockContext* one) const
{
	std::string result;

	for ( data::Block* block : one->rootBlockContainer()->single()->subBlockContainer()->list() )
	{
		switch ( block->type() )
		{
			case data::DataType::TextBlock:
				result += printTextBlock(static_cast<data::TextBlock*>(block));
				break;
			case data::DataType::ImageBlock:
				result += printImageBlock(static_cast<data::ImageBlock*>(block));
				break;
			default:
				result += "<h1 style='color:red'>UNSUPPORTED BLOCK TYPE</h1>";
				break;
		}
	}

	return result;
}

std::string ExamHtmlExporter::printTextBlock(data::TextBlock* one) const
{
	// Take format for text block from context.
	auto format = context()->loader()->html_questionParagraph();

	// Take text from text block.
	auto text = one->textContainer()->single();

	// Change new line character to html <br> tag.
	auto htmlText = newLineToHtmlBr(text);

	// Apply block text to format.
	auto result = std::regex_replace(format, std::regex("%1%"), htmlText);

	return result;
}

std::string ExamHtmlExporter::printImageBlock(data::ImageBlock* block) const
{
	// Export(save) image.
	// Make unique image name with m_imageCount.
	auto imageName = std::to_string(m_imageCount) + ".png";
	++m_imageCount;
	auto imagePath = m_rootDir.filePath(imageName.c_str());

	// Take QImage from image which is linked with image block.
	QImage image;
	if ( block->imageContainer()->isValid() )
	{
		image = block->imageContainer()->single()->imageContainer()->single();
	}

	// Save image.
	image.save(imagePath);

	// Make html.
	auto format = context()->loader()->html_questionImage();
	auto result = std::regex_replace(format, std::regex("%1%"), imagePath.toStdString());
	return result;
}

std::string ExamHtmlExporter::printResp(data::Resp* one) const
{
	switch ( one->type() )
	{
		case data::DataType::MultipleChoicesResp:
			return printMultipleChoicesResp(static_cast<data::MultipleChoicesResp*>(one));
			break;
		case data::DataType::MatchingResp:
			return printMatchingResp(static_cast<data::MatchingResp*>(one));
			break;
		default:
			assert(false);
	}
}

std::string ExamHtmlExporter::printMultipleChoicesResp(data::MultipleChoicesResp* one) const
{
	auto format = context()->loader()->html_choiceResponse();

	std::string choiceHtml;
	for ( data::Choice* choice : one->choiceContainer()->list() )
	{
		choiceHtml += printChoice(choice);
	}
	auto result = std::regex_replace(format, std::regex("%1%"), choiceHtml);

	return result;
}

std::string ExamHtmlExporter::printMatchingResp(data::MatchingResp* one) const
{
	auto format = context()->loader()->html_matchingResponse();

	// Fill first column.
	{
		std::string respHtml;
		for ( data::MatchingRespItem* item : one->firstGroupContainer()->list() )
		{
			respHtml += printMatchingRespItem(item);
		}
		format = std::regex_replace(format, std::regex("%1%"), respHtml);
	}

	// Fill second column;
	{
		std::string respHtml;
		for ( data::MatchingRespItem* item : one->secondGroupContainer()->list() )
		{
			respHtml += printMatchingRespItem(item);
		}
		format = std::regex_replace(format, std::regex("%2%"), respHtml);
	}

	return format;
}

std::string ExamHtmlExporter::printChoice(data::Choice* one) const
{
	auto format = context()->loader()->html_choice();
	auto text = one->textContainer()->single();
	auto textHtml = newLineToHtmlBr(text);
	auto result = std::regex_replace(format, std::regex("%1%"), textHtml);
	return result;
}

std::string ExamHtmlExporter::printMatchingRespItem(data::MatchingRespItem* one) const
{
	auto format = context()->loader()->html_matchingItem();
	auto text = one->textContainer()->single();
	auto textHtml = newLineToHtmlBr(text);
	auto result = std::regex_replace(format, std::regex("%1%"), textHtml);
	return result;
}

std::string ExamHtmlExporter::newLineToHtmlBr(const std::string& value)
{
	std::string result;
	for ( auto const& c : value )
	{
		if ( c == '\n' )
		{
			result += "<br>";
		}
		else
		{
			result.push_back(c);
		}
	}
	return result;
}

void ExamHtmlExporter::initContext() const
{
	m_imageCount = 0;
	m_curQuestionIndex = 1;
}

}}
