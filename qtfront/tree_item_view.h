#pragma once
#include <QListView>
#include <memory>
#include <boost/signals2.hpp>
#include "context_holder.h"

namespace wally {

namespace data {
class Dir;
class TreeItem;
}

namespace qtfront {

class Ui_TreeItemView;
class TreeItemModel;

namespace tree_item_view_sub {
class View;
}

class TreeItemView : public QWidget,
		public ContextHolder
{
	Q_OBJECT

	class SetNullDir;

public:
	using View = tree_item_view_sub::View;

	static std::string dirFullName(data::Dir* dir);

	TreeItemView(QWidget* parent = nullptr);
	virtual ~TreeItemView();

	data::Dir* dir() const;
	void setDir(data::Dir* one);
	void setDir(nullptr_t);
	void setValidDir(data::Dir* one);
	void setNullDir();

	TreeItemModel* treeItemModel();
	TreeItemModel const* treeItemModel() const;

protected:
	void initialized() override final;

private slots:
	void on_btn_toParentDirectory_clicked();

	void on_btn_addDir_clicked();
	void on_btn_addExam_clicked();
	void on_btn_addQuestion_clicked();
	void on_btn_addImage_clicked();
	void on_btn_delete_clicked();

private:
	// This should be called when new dir is set.
	void updateCurDirLabel();

	std::vector<data::TreeItem*> selectedTreeItems();

	std::unique_ptr<Ui_TreeItemView>
	m_ui;

	std::unique_ptr<TreeItemModel>
	m_model;

	data::Dir*
	m_dir{};
};

}}
