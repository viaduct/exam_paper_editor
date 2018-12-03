#pragma once
#include <string>

namespace wally {
namespace qtfront {

class AppCmdInfo
{
public:
	std::string brief() const;
	void setBrief(std::string const& value);
	void setBrief(std::string&& value);

private:
	std::string
	m_brief;
};

}}
