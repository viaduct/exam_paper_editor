#pragma once
#include <boost/signals2.hpp>
#include <vector>
#include <memory>
#include "tree_item_model_context_holder.h"

namespace wally {

namespace data {
class Dir;
class TreeItem;
}

namespace qtfront {
namespace tree_item_model_sub {

class TreeItemMimic;

class DirMimic : public TreeItemModelContextHolder
{
public:
	DirMimic();
	virtual ~DirMimic();

	data::Dir* dir() const;
	void setValidDir(data::Dir* one);
	void setNullDir();

	size_t size() const;
	size_t index(TreeItemMimic const* one, bool* isValid = nullptr) const;
	size_t index(data::TreeItem const* one, bool* isValid = nullptr) const;
	TreeItemMimic* at(size_t at) const;

protected:
	void initialized() override final;

private:
	std::unique_ptr<TreeItemMimic> createTreeItemMimic(data::TreeItem* one);
	void append(std::unique_ptr<TreeItemMimic>&& one);
	void remove(size_t at);
	void catchUp();
	void clear();

	std::vector<std::unique_ptr<TreeItemMimic>>
	m_treeItemMimics;

	boost::signals2::scoped_connection
	m_con_added,
	m_con_beforeRemoved,
	m_con_beforeCleared;

	data::Dir*
	m_dir{};
};

}}}
