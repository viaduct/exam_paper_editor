#include <QColor>
#include "app_cmd_model.h"
#include "app_cmd.h"
#include "app_cmd_model_sub/cmd_manager_mimic.h"

namespace wally {
namespace qtfront {

AppCmdModel::AppCmdModel()
{
}

AppCmdModel::~AppCmdModel()
{
}

AppCmd*AppCmdModel::indexToAppCmd(const QModelIndex& index)
{
	return static_cast<AppCmd*>(index.internalPointer());
}

int AppCmdModel::rowCount(const QModelIndex& parent) const
{
	if ( m_managerMimic )
	{
		if ( parent.isValid() == false )
		{
			return m_managerMimic->cmdsSize();
		}
		else { return 0; }
	}
	else { return 0; }
}

QModelIndex AppCmdModel::index(int row, int column, const QModelIndex& parent) const
{
	if ( m_managerMimic )
	{
		if ( parent.isValid() == false )
		{
			if ( column == 0 )
			{
				if ( (size_t)row < m_managerMimic->cmdsSize() )
				{
					return createIndex(row, 0, m_managerMimic->cmdAt(row));
				}
				else { return QModelIndex(); }
			}
			else { return QModelIndex(); }
		}
		else { return QModelIndex(); }
	}
	else { return QModelIndex(); }
}

QVariant AppCmdModel::data(const QModelIndex& index, int role) const
{
	if ( m_managerMimic )
	{
		auto appCmd = indexToAppCmd(index);
		switch ( role )
		{
			case Qt::DisplayRole:
				return QString(appCmd->info()->brief().c_str());
			case Qt::DecorationRole:
			{
				auto index = m_managerMimic->cmdIndex(appCmd);
				auto isUndone = m_managerMimic->isUndone(index);
				return isUndone ? QColor(255, 119, 19) : QColor(Qt::white);
			}
			default:
				return QVariant();
		}
	}
	else { return QVariant(); }
}

AppCmdManager*AppCmdModel::appCmdManager() const
{
	return m_manager;
}

void AppCmdModel::setAppCmdManager(AppCmdManager* one)
{
	if ( one )
	{
		if ( m_manager == nullptr )
		{
			setValidAppCmdManager(one);
		}
		else if ( m_manager == one )
		{
			setNullAppCmdManager();
			setValidAppCmdManager(one);
		}
	}
	else
	{
		setAppCmdManager(nullptr);
	}
}

void AppCmdModel::setAppCmdManager(nullptr_t)
{
	if ( m_manager )
	{
		setNullAppCmdManager();
	}
}

void AppCmdModel::setValidAppCmdManager(AppCmdManager* one)
{
	m_manager = one;

	m_managerMimic = std::make_unique<CmdManagerMimic>();
	m_managerMimic->init(context(), this);
	m_managerMimic->setValidCmdManager(m_manager);
}

void AppCmdModel::setNullAppCmdManager()
{
	beginResetModel();
	m_managerMimic = nullptr;
	endResetModel();

	m_manager = nullptr;
}

void AppCmdModel::initialized()
{
}

}}
