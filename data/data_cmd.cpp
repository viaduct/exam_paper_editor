#include "data_cmd.h"

namespace wally {
namespace data {

void DataCmdList::run()
{
	for ( size_t i = 0; i < m_cmds.size(); ++i )
	{
		m_cmds.at(i)->run();
	}
}

void DataCmdList::undo()
{
	for ( size_t i = m_cmds.size(); i != 0; )
	{
		--i;
		m_cmds.at(i)->undo();
	}
}

size_t DataCmdList::size() const
{
	return m_cmds.size();
}

bool DataCmdList::isEmpty() const
{
	return m_cmds.empty();
}

void DataCmdList::append(const std::shared_ptr<DataCmd>& cmd)
{
	m_cmds.push_back(cmd);
}

void DataCmdList::append(std::shared_ptr<DataCmd>&& cmd)
{
	m_cmds.push_back(std::move(cmd));
}

void DataCmdList::reserve(size_t size)
{
	m_cmds.reserve(size);
}

}}
