#include "cmd_manager_mimic.h"
#include "../app_cmd_manager.h"
#include "../app_cmd_model.h"

namespace wally {
namespace qtfront {
namespace app_cmd_model_sub {

CmdManagerMimic::CmdManagerMimic()
{
}

CmdManagerMimic::~CmdManagerMimic()
{
}

AppCmdManager*CmdManagerMimic::cmdManager() const
{
	return m_manager;
}

void CmdManagerMimic::setValidCmdManager(AppCmdManager* one)
{
	m_manager = one;

	auto cmdRun = [this](AppCmd* one)
	{
		runCmd(one);
	};
	auto cmdsUndone = [this](size_t count)
	{
		undoCmds(count);
	};
	auto cmdsRedone = [this](size_t count)
	{
		redoCmds(count);
	};
	auto beforeCmdsReduced = [this](size_t count)
	{
		reduceCmds(count);
	};
	auto beforeUndoneCmdsDropped = [this]
	{
		dropUndoneCmds();
	};
	m_con_cmdRun = m_manager->sig_run()->connect(std::move(cmdRun));
	m_con_cmdsUndone = m_manager->sig_undone()->connect(std::move(cmdsUndone));
	m_con_cmdsRedone = m_manager->sig_redone()->connect(std::move(cmdsRedone));
	m_con_beforeCmdsReduced = m_manager->sig_beforeReduced()->connect(std::move(beforeCmdsReduced));
	m_con_beforeUndoneCmdsDropped = m_manager->sig_beforeUndoneCmdsDropped()->connect(std::move(beforeUndoneCmdsDropped));

	catchUpCmds();
}

void CmdManagerMimic::setNullCmdManager()
{
	clearCmds();

	m_con_beforeUndoneCmdsDropped.disconnect();
	m_con_beforeCmdsReduced.disconnect();
	m_con_cmdsRedone.disconnect();
	m_con_cmdsUndone.disconnect();
	m_con_cmdRun.disconnect();

	m_manager = nullptr;
}

size_t CmdManagerMimic::cmdsSize() const
{
	return m_cmds.size();
}

AppCmd*CmdManagerMimic::cmdAt(size_t at) const
{
	return m_cmds[at];
}

size_t CmdManagerMimic::cmdIndex(const AppCmd* one, bool* isValid) const
{
	if ( isValid ) { *isValid = true; }
	for ( size_t i = 0; i < m_cmds.size(); ++i )
	{
		if ( m_cmds[i] == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

bool CmdManagerMimic::isUndone(size_t at) const
{
	return m_firstUndoneCmdIndex <= at;
}

void CmdManagerMimic::initialized()
{
}

void CmdManagerMimic::runCmd(AppCmd* cmd)
{
	cmdModel()->beginInsertRows(QModelIndex(), m_cmds.size(), m_cmds.size());

	m_cmds.push_back(cmd);
	m_firstUndoneCmdIndex = m_cmds.size();

	cmdModel()->endInsertRows();
}

void CmdManagerMimic::undoCmds(size_t count)
{
	if ( count > 0 )
	{
		auto atBegin = m_firstUndoneCmdIndex - count;
		auto atEnd = atBegin + count - 1;

		auto indexBegin = cmdModel()->index(atBegin, 0, QModelIndex());
		auto indexEnd = cmdModel()->index(atEnd, 0, QModelIndex());

		m_firstUndoneCmdIndex -= count;

		cmdModel()->dataChanged(indexBegin, indexEnd, QVector<int>() << Qt::DecorationRole);
	}
}

void CmdManagerMimic::redoCmds(size_t count)
{
	if ( count > 0 )
	{
		auto atBegin = m_firstUndoneCmdIndex;
		auto atEnd = atBegin + count - 1;

		auto indexBegin = cmdModel()->index(atBegin, 0, QModelIndex());
		auto indexEnd = cmdModel()->index(atEnd, 0, QModelIndex());

		m_firstUndoneCmdIndex += count;

		cmdModel()->dataChanged(indexBegin, indexEnd, QVector<int>() << Qt::DecorationRole);
	}
}

void CmdManagerMimic::reduceCmds(size_t count)
{
	if ( count > 0 )
	{
		cmdModel()->beginRemoveRows(QModelIndex(), 0, count - 1);

		std::vector<AppCmd*> newVec(m_cmds.begin() + count, m_cmds.end());
		m_cmds = std::move(newVec);
		m_firstUndoneCmdIndex -= count;

		cmdModel()->endRemoveRows();
	}
}

void CmdManagerMimic::clearCmds()
{
	cmdModel()->beginResetModel();

	m_cmds.clear();
	m_firstUndoneCmdIndex = 0;

	cmdModel()->endResetModel();
}

void CmdManagerMimic::catchUpCmds()
{
	cmdModel()->beginResetModel();

	auto doneCmds = m_manager->doneCmds();
	auto undoneCmds = m_manager->undoneCmds();

	m_cmds.reserve(doneCmds.size() + undoneCmds.size());
	m_cmds.insert(m_cmds.end(), doneCmds.begin(), doneCmds.end());
	m_cmds.insert(m_cmds.end(), undoneCmds.begin(), undoneCmds.end());
	m_firstUndoneCmdIndex = doneCmds.size();

	cmdModel()->endResetModel();
}

void CmdManagerMimic::dropUndoneCmds()
{
	if ( m_firstUndoneCmdIndex != m_cmds.size() )
	{
		cmdModel()->beginRemoveRows(QModelIndex(), m_firstUndoneCmdIndex, m_cmds.size() - 1);

		m_cmds.erase(m_cmds.begin() + m_firstUndoneCmdIndex, m_cmds.end());

		cmdModel()->endRemoveRows();
	}
}

}}}
