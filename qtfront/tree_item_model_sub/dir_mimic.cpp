#include "dir_mimic.h"
#include "tree_item_mimic.h"
#include "../tree_item_model.h"
#include "../../data/dir.h"

namespace wally {
namespace qtfront {
namespace tree_item_model_sub {

DirMimic::DirMimic()
{
}

DirMimic::~DirMimic()
{
}

data::Dir*DirMimic::dir() const
{
	return m_dir;
}

void DirMimic::setValidDir(data::Dir* one)
{
	m_dir = one;

	auto added = [this](data::TreeItem* one)
	{
		append(createTreeItemMimic(one));
	};
	auto beforeRemoved = [this](data::TreeItem* one)
	{
		remove(index(one));
	};
	auto beforeCleared = [this]
	{
		clear();
	};
	m_con_added = m_dir->subItemContainer()->sig_added()->connect(added);
	m_con_beforeRemoved = m_dir->subItemContainer()->sig_beforeRemoved()->connect(beforeRemoved);
	m_con_beforeCleared = m_dir->subItemContainer()->sig_beforeCleared()->connect(beforeCleared);

	catchUp();
}

void DirMimic::setNullDir()
{
	clear();

	m_con_beforeCleared.disconnect();
	m_con_beforeRemoved.disconnect();
	m_con_added.disconnect();

	m_dir = nullptr;
}

size_t DirMimic::size() const
{
	return m_treeItemMimics.size();
}

void DirMimic::catchUp()
{
	// Sort by type, then name.
	auto list = m_dir->subItemContainer()->list();
	auto compare = [](data::TreeItem* first, data::TreeItem* second)
	{
		if ( (int)first->type() < (int)second->type() )
		{
			return true;
		}
		else if ( (int)second->type() < (int)first->type() )
		{
			return false;
		}
		else
		{
			return first->nameContainer()->single() < second->nameContainer()->single();
		}
	};
	std::sort(list.begin(), list.end(), compare);

	for ( auto& treeItem : m_dir->subItemContainer()->list() )
	{
		auto item = std::make_unique<TreeItemMimic>();
		item->init(context(), treeItemModel());
		item->setValidTreeItem(treeItem);
		append(std::move(item));
	}
}

size_t DirMimic::index(const TreeItemMimic* one, bool* isValid) const
{
	return index(one->treeItem(), isValid);
}

size_t DirMimic::index(const data::TreeItem* one, bool* isValid) const
{
	if ( isValid) { *isValid = true; }
	for ( size_t i = 0; i < m_treeItemMimics.size(); ++i )
	{
		if ( m_treeItemMimics[i]->treeItem() == one )
		{
			return i;
		}
	}
	assert(isValid);
	*isValid = false;
	return 0;
}

TreeItemMimic*DirMimic::at(size_t at) const
{
	return m_treeItemMimics[at].get();
}

void DirMimic::initialized()
{
}

std::unique_ptr<TreeItemMimic> DirMimic::createTreeItemMimic(data::TreeItem* one)
{
	auto mimic = std::make_unique<TreeItemMimic>();
	mimic->init(context(), treeItemModel());
	mimic->setValidTreeItem(one);
	return mimic;
}

void DirMimic::append(std::unique_ptr<TreeItemMimic>&& one)
{
	auto at = m_treeItemMimics.size();
	treeItemModel()->beginInsertRows(QModelIndex(), at, at);

	m_treeItemMimics.push_back(std::move(one));

	treeItemModel()->endInsertRows();
}

void DirMimic::remove(size_t at)
{
	treeItemModel()->beginRemoveRows(QModelIndex(), at, at);

	m_treeItemMimics.erase(m_treeItemMimics.begin() + at);

	treeItemModel()->endRemoveRows();
}

void DirMimic::clear()
{
	treeItemModel()->beginResetModel();

	m_treeItemMimics.clear();

	treeItemModel()->endResetModel();
}

}}}
