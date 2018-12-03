#include "app_cmd.h"
#include "../data/data_cmd.h"

namespace wally {
namespace qtfront {

AppDataCmd::AppDataCmd(const std::shared_ptr<data::DataCmd>& cmd) :
	m_cmd(cmd)
{
}

AppDataCmd::AppDataCmd(std::shared_ptr<data::DataCmd>&& cmd) :
	m_cmd(std::move(cmd))
{
}

void AppDataCmd::run()
{
	m_cmd->run();
}

void AppDataCmd::undo()
{
	m_cmd->undo();
}

void AppCmdList::run()
{
	for ( size_t i = 0; i < m_cmds.size(); ++i )
	{
		m_cmds.at(i)->run();
	}
}

void AppCmdList::undo()
{
	for ( size_t i = m_cmds.size(); i != 0; )
	{
		--i;
		m_cmds.at(i)->undo();
	}
}

size_t AppCmdList::size() const
{
	return m_cmds.size();
}

bool AppCmdList::isEmpty() const
{
	return m_cmds.empty();
}

void AppCmdList::append(const std::shared_ptr<AppCmd>& cmd)
{
	m_cmds.push_back(cmd);
}

void AppCmdList::append(std::shared_ptr<AppCmd>&& cmd)
{
	m_cmds.push_back(std::move(cmd));
}

void AppCmdList::reserve(size_t size)
{
	m_cmds.reserve(size);
}

}}
