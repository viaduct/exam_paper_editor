#pragma once
#include <string>

namespace wally {
namespace qtfront {

class Loader
{
public:
	Loader() = default;
	~Loader();
	Loader(Loader const&) = delete;
	Loader& operator =(Loader const&) = delete;

	bool isLoaded() const;

	void load();
	void unload();

	std::string html_exam() const;
	std::string html_question() const;
	std::string html_questionParagraph() const;
	std::string html_questionImage() const;
	std::string html_choiceResponse() const;
	std::string html_choice() const;
	std::string html_matchingResponse() const;
	std::string html_matchingItem() const;

private:
	std::string
	m_html_exam,
	m_html_question,
	m_html_questionParagraph,
	m_html_questionImage,
	m_html_choiceResponse,
	m_html_choice,
	m_html_matchingResponse,
	m_html_matchingItem;

	bool
	m_isLoaded = false;
};

}}
