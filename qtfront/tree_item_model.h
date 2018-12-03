#pragma once
#include <vector>
#include <memory>
#include <boost/signals2.hpp>
#include <QAbstractListModel>
#include "context_holder.h"

namespace wally {

namespace data {
class Dir;
class TreeItem;
}

namespace qtfront {

namespace tree_item_model_sub {
class TreeItemModelContextHolder;
class DirMimic;
class TreeItemMimic;
}

class TreeItemModel : public QAbstractListModel,
		public ContextHolder
{
public:
	using ContextHolder = tree_item_model_sub::TreeItemModelContextHolder;
	using DirMimic = tree_item_model_sub::DirMimic;
	using TreeItemMimic = tree_item_model_sub::TreeItemMimic;

	TreeItemModel();
	virtual ~TreeItemModel();

	static data::TreeItem* indexToData(QModelIndex const& index);
	QModelIndex dataToIndex(data::TreeItem* one);

	data::Dir* dir() const;
	void setValidDir(data::Dir* one);
	void setNullDir();

	int rowCount(const QModelIndex &parent) const override final;
	QModelIndex index(int row, int column, const QModelIndex &parent) const override final;
	QVariant data(const QModelIndex &index, int role) const override final;
	Qt::ItemFlags flags(const QModelIndex &index) const override final;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override final;

	using QAbstractListModel::beginInsertRows;
	using QAbstractListModel::endInsertRows;
	using QAbstractListModel::beginRemoveRows;
	using QAbstractListModel::endRemoveRows;
	using QAbstractListModel::beginResetModel;
	using QAbstractListModel::endResetModel;

	using QAbstractListModel::dataChanged;

protected:
	void initialized() override final;

private:
	std::unique_ptr<DirMimic>
	m_dirMimic;

	data::Dir*
	m_dir{};
};

}}
