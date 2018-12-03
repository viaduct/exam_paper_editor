#include <fstream>
#include "loader.h"

namespace wally {
namespace qtfront {

Loader::~Loader()
{
	if ( isLoaded() )
	{
		unload();
	}
}

bool Loader::isLoaded() const
{
	return m_isLoaded;
}

void Loader::load()
{
	//Load htmls.

	auto readTextFile = [](char const* path)
	{
		std::ifstream file(path);
		std::string buffer, result;

		while ( std::getline(file, buffer) )
		{
			result += buffer + "\n";
		}

		return result;
	};

	m_html_exam = readTextFile("html/exam.html").c_str();
	m_html_question = readTextFile("html/question.html");
	m_html_questionParagraph = readTextFile("html/question_paragraph.html");
	m_html_questionImage = readTextFile("html/question_image.html");
	m_html_choiceResponse = readTextFile("html/question_choice_response.html");
	m_html_choice = readTextFile("html/question_choice.html");
	m_html_matchingResponse = readTextFile("html/question_matching_response.html");
	m_html_matchingItem = readTextFile("html/question_matching_item.html");
}

void Loader::unload()
{
	// Do nothing.
}

std::string Loader::html_exam() const
{
	return m_html_exam;
}

std::string Loader::html_question() const
{
	return m_html_question;
}

std::string Loader::html_questionParagraph() const
{
	return m_html_questionParagraph;
}

std::string Loader::html_questionImage() const
{
	return m_html_questionImage;
}

std::string Loader::html_choiceResponse() const
{
	return m_html_choiceResponse;
}

std::string Loader::html_choice() const
{
	return m_html_choice;
}

std::string Loader::html_matchingResponse() const
{
	return m_html_matchingResponse;
}

std::string Loader::html_matchingItem() const
{
	return m_html_matchingItem;
}

}}
