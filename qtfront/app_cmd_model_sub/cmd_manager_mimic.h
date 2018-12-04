#pragma once
#include <vector>
#include <cstddef>
#include <boost/signals2.hpp>
#include "app_cmd_model_context_holder.h"

namespace wally {
namespace qtfront {

class AppCmdManager;
class AppCmd;

namespace app_cmd_model_sub {

class CmdManagerMimic : public AppCmdModelContextHolder
{
public:
	CmdManagerMimic();
	virtual ~CmdManagerMimic();

	AppCmdManager* cmdManager() const;
	void setValidCmdManager(AppCmdManager* one);
	void setNullCmdManager();

	size_t cmdsSize() const;
	AppCmd* cmdAt(size_t at) const;
	size_t cmdIndex(AppCmd const* one, bool* isValid = nullptr) const;
	bool isUndone(size_t at) const;

protected:
	void initialized() override final;

private:
	void runCmd(AppCmd* cmd);
	void undoCmds(size_t count);
	void redoCmds(size_t count);
	void reduceCmds(size_t count);
	void clearCmds();
	void catchUpCmds();

	void dropUndoneCmds();

	std::vector<AppCmd*>
	m_cmds;

	boost::signals2::scoped_connection
	m_con_cmdRun,
	m_con_cmdsUndone,
	m_con_cmdsRedone,
	m_con_beforeCmdsReduced,
	m_con_beforeUndoneCmdsDropped;

	size_t
	m_firstUndoneCmdIndex = 0;

	AppCmdManager*
	m_manager{};
};

}}}
