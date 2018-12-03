#include "app_cmd_info.h"

namespace wally {
namespace qtfront {

std::string AppCmdInfo::brief() const
{
	return m_brief;
}

void AppCmdInfo::setBrief(const std::string& value)
{
	m_brief = value;
}

void AppCmdInfo::setBrief(std::string&& value)
{
	m_brief = std::move(value);
}

}}
