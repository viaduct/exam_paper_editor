#include "app_cmd_manager.h"
#include "app_cmd.h"

namespace wally {
namespace qtfront {

AppCmdManager::AppCmdManager()
{
}

size_t AppCmdManager::autoReduceLimit() const
{
	return m_autoReduceLimit;
}

void AppCmdManager::setAutoReduceLimit(size_t value)
{
	m_autoReduceLimit = value;
	tryAutoReduce();
}

void AppCmdManager::run(const std::shared_ptr<AppCmd>& cmd)
{
	dropUndoneCmds();

	cmd->run();

	m_doneCmds.push_back(cmd);

	m_sig_run(cmd.get());

	tryAutoReduce();
}

void AppCmdManager::run(std::shared_ptr<AppCmd>&& cmd)
{
	auto rawCmd = cmd.get();

	dropUndoneCmds();

	cmd->run();

	m_doneCmds.push_back(std::move(cmd));

	m_sig_run(rawCmd);

	tryAutoReduce();
}

void AppCmdManager::undo()
{
	if ( m_doneCmds.empty() == false )
	{
		auto cmd = std::move(m_doneCmds.back());

		m_doneCmds.pop_back();

		cmd->undo();

		m_undoneCmds.push_back(std::move(cmd));

		m_sig_undone(1);
	}
}

void AppCmdManager::redo()
{
	if ( m_undoneCmds.empty() == false )
	{
		auto cmd = std::move(m_undoneCmds.back());

		m_undoneCmds.pop_back();

		cmd->run();

		m_doneCmds.push_back(std::move(cmd));

		m_sig_redone(1);
	}
}

void AppCmdManager::undoUntil(const AppCmd* one)
{
	size_t count = 0;
	bool found = false;

	// Take how many commands should be undone.
	for ( auto i = m_doneCmds.rbegin(); i != m_doneCmds.rend(); ++i )
	{
		++count;
		if ( (*i).get() == one )
		{
			found = true;
			break;
		}
	}

	if ( found )
	{
		for ( size_t i = 0; i < count; ++i )
		{
			auto cmd = std::move(m_doneCmds.back());
			m_doneCmds.pop_back();

			cmd->undo();

			m_undoneCmds.push_back(std::move(cmd));
		}

		m_sig_undone(count);
	}
}

void AppCmdManager::redoUntil(const AppCmd* one)
{
	size_t count = 0;
	bool found = false;

	// Take how many commands should be redone.
	for ( auto i = m_undoneCmds.rbegin(); i != m_undoneCmds.rend(); ++i )
	{
		++count;
		if ( (*i).get() == one )
		{
			found = true;
			break;
		}
	}

	if ( found )
	{
		for ( size_t i = 0; i < count; ++i )
		{
			auto cmd = std::move(m_undoneCmds.back());
			m_undoneCmds.pop_back();

			cmd->run();

			m_doneCmds.push_back(std::move(cmd));
		}

		m_sig_redone(count);
	}
}

void AppCmdManager::reduce(size_t howMany)
{
	m_sig_beforeReduced(howMany);

	for ( size_t i = 0; i < howMany; ++i )
	{
		m_doneCmds.pop_front();
	}
}

std::vector<AppCmd*> AppCmdManager::doneCmds()
{
	std::vector<AppCmd*> result;
	result.reserve(m_doneCmds.size());
	for ( auto& one : m_doneCmds )
	{
		result.push_back(one.get());
	}
	return result;
}

std::vector<AppCmd*> AppCmdManager::undoneCmds()
{
	std::vector<AppCmd*> result;
	result.reserve(m_undoneCmds.size());
	for ( auto& one : m_undoneCmds )
	{
		result.push_back(one.get());
	}
	return result;
}

boost::signals2::signal<void ()>*AppCmdManager::sig_beforeUndoneCmdsDropped()
{
	return &m_sig_beforeUndoneCmdsDropped;
}

boost::signals2::signal<void (AppCmd*)>*AppCmdManager::sig_run()
{
	return &m_sig_run;
}

boost::signals2::signal<void (size_t)>*AppCmdManager::sig_undone()
{
	return &m_sig_undone;
}

boost::signals2::signal<void (size_t)>*AppCmdManager::sig_redone()
{
	return &m_sig_redone;
}

boost::signals2::signal<void (size_t)>*AppCmdManager::sig_beforeReduced()
{
	return &m_sig_beforeReduced;
}

size_t AppCmdManager::cmdsSize() const
{
	return m_doneCmds.size() + m_undoneCmds.size();
}

void AppCmdManager::dropUndoneCmds()
{
	m_sig_beforeUndoneCmdsDropped();

	m_undoneCmds.clear();
}

void AppCmdManager::tryAutoReduce()
{
	if ( m_autoReduceLimit != 0 )
	{
		int diff = (int)cmdsSize() - (int)m_autoReduceLimit;

		if ( diff > 0 )
		{
			reduce(diff);
		}
	}
}

}}
