#pragma once
#include <QAbstractListModel>
#include <memory>
#include "context_holder.h"

namespace wally {
namespace qtfront {

class AppCmdManager;
class AppCmd;

namespace app_cmd_model_sub {
class CmdManagerMimic;
}

class AppCmdModel : public QAbstractListModel,
		public ContextHolder
{
public:
	using CmdManagerMimic = app_cmd_model_sub::CmdManagerMimic;

	AppCmdModel();
	virtual ~AppCmdModel();

	static AppCmd* indexToAppCmd(QModelIndex const& index);

	int rowCount(const QModelIndex &parent) const override final;
	QModelIndex index(int row, int column, const QModelIndex &parent) const override final;
	QVariant data(const QModelIndex &index, int role) const override final;

	using QAbstractListModel::beginInsertRows;
	using QAbstractListModel::endInsertRows;
	using QAbstractListModel::beginRemoveRows;
	using QAbstractListModel::endRemoveRows;
	using QAbstractListModel::beginResetModel;
	using QAbstractListModel::endResetModel;

	using QAbstractListModel::dataChanged;

	AppCmdManager* appCmdManager() const;
	void setAppCmdManager(AppCmdManager* one);
	void setAppCmdManager(nullptr_t);
	void setValidAppCmdManager(AppCmdManager* one);
	void setNullAppCmdManager();

protected:
	void initialized() override final;

private:
	std::unique_ptr<CmdManagerMimic>
	m_managerMimic;

	AppCmdManager*
	m_manager{};
};

}}
