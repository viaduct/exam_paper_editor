#pragma once
#include <boost/signals2.hpp>

namespace wally {

namespace data {
class Dir;
}

namespace qtfront {

class DirContextVar
{
public:
	DirContextVar() = default;
	DirContextVar(DirContextVar const&) = delete;
	DirContextVar& operator =(DirContextVar const&) = delete;

	data::Dir* activeDir() const;

	void activateDir(data::Dir* one);
	void activateDir(nullptr_t);
	void activateValidDir(data::Dir* one);
	void activateNullDir();

	boost::signals2::signal<void ()>* sig_validDirActivated();
	boost::signals2::signal<void ()>* sig_beforeNullDirActivated();

private:
	boost::signals2::signal<void ()>
	m_sig_validDirActivated,
	m_sig_beforeNullDirActivated;

	data::Dir*
	m_activeDir{};
};

}}
