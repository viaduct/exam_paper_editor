#include "dir_context_var.h"

namespace wally {
namespace qtfront {

data::Dir*DirContextVar::activeDir() const
{
	return m_activeDir;
}

void DirContextVar::activateDir(data::Dir* dir)
{
	if ( dir )
	{
		if ( m_activeDir == nullptr )
		{
			activateValidDir(dir);
		}
		else if ( m_activeDir != dir )
		{
			activateNullDir();
			activateValidDir(dir);
		}
	}
	else
	{
		activateDir(nullptr);
	}
}

void DirContextVar::activateDir(nullptr_t)
{
	if ( m_activeDir )
	{
		activateNullDir();
	}
}

void DirContextVar::activateValidDir(data::Dir* one)
{
	m_activeDir = one;

	m_sig_validDirActivated();
}

void DirContextVar::activateNullDir()
{
	m_sig_beforeNullDirActivated();

	m_activeDir = nullptr;
}

boost::signals2::signal<void ()>*DirContextVar::sig_validDirActivated()
{
	return &m_sig_validDirActivated;
}

boost::signals2::signal<void ()>*DirContextVar::sig_beforeNullDirActivated()
{
	return &m_sig_beforeNullDirActivated;
}

}}
