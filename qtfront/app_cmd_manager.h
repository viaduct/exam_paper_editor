#pragma once
#include <boost/signals2.hpp>
#include <list>
#include <memory>

namespace wally {
namespace qtfront {

class AppCmd;

class AppCmdManager
{
public:
	AppCmdManager();
	AppCmdManager(AppCmdManager const&) = delete;
	AppCmdManager& operator =(AppCmdManager const&) = delete;

	size_t autoReduceLimit() const;
	void setAutoReduceLimit(size_t value);

	void run(std::shared_ptr<AppCmd> const& cmd);
	void run(std::shared_ptr<AppCmd>&& cmd);
	void undo();
	void redo();
	void undoUntil(AppCmd const* one);
	void redoUntil(AppCmd const* one);
	void reduce(size_t howMany);

	std::vector<AppCmd*> doneCmds();
	std::vector<AppCmd*> undoneCmds();

	boost::signals2::signal<void ()>* sig_beforeUndoneCmdsDropped();
	boost::signals2::signal<void (AppCmd*)>* sig_run();
	boost::signals2::signal<void (size_t)>* sig_undone();
	boost::signals2::signal<void (size_t)>* sig_redone();
	boost::signals2::signal<void (size_t)>* sig_beforeReduced();

private:
	size_t cmdsSize() const;
	void dropUndoneCmds();
	void tryAutoReduce();

	std::list<std::shared_ptr<AppCmd>>
	m_doneCmds,
	m_undoneCmds;

	boost::signals2::signal<void ()>
	m_sig_beforeUndoneCmdsDropped;
	boost::signals2::signal<void (AppCmd*)>
	m_sig_run;
	boost::signals2::signal<void (size_t)>
	m_sig_undone,
	m_sig_redone,
	m_sig_beforeReduced;

	size_t
	m_autoReduceLimit = 0;
};

}}
