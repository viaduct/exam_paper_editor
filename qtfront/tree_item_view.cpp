#include "tree_item_view.h"
#include "tree_item_model.h"
#include "ui_tree_item_view.h"
#include "context.h"
#include "dir_context_var.h"
#include "../data/tree_item.h"
#include "../data/dir.h"

namespace wally {
namespace qtfront {

class TreeItemView::SetNullDir : public data::DataCmd
{
public:
	SetNullDir(TreeItemView* owner) : m_owner(owner) {}
	void run() override final
	{
		m_prev = m_owner->dir();
		m_owner->setNullDir();
	}
	void undo() override final
	{
		m_owner->setValidDir(m_prev);
	}

private:
	TreeItemView*
	m_owner;

	data::Dir*
	m_prev;
};

TreeItemView::TreeItemView(QWidget* parent) : QWidget(parent),
	m_ui(new Ui_TreeItemView),
	m_model(new TreeItemModel)
{
	m_ui->setupUi(this);
	updateCurDirLabel();
}

TreeItemView::~TreeItemView()
{
	if ( m_dir )
	{
		m_dir->removeDepended(dependencyKeyFromPtr(this));
	}
}

void TreeItemView::initialized()
{
	m_ui->view->init(context(), this);
	m_model->init(context());
}

void TreeItemView::on_btn_addDir_clicked()
{
	if ( context()->dirContextVar()->activeDir() )
	{
		context()->act_addDir(context()->dirContextVar()->activeDir(), "New Dir");
	}
}

void TreeItemView::on_btn_addExam_clicked()
{
	if ( context()->dirContextVar()->activeDir() )
	{
		context()->act_addExam(context()->dirContextVar()->activeDir(), "New Exam");
	}
}

void TreeItemView::on_btn_addQuestion_clicked()
{
	if ( context()->dirContextVar()->activeDir() )
	{
		context()->act_addQuestion(context()->dirContextVar()->activeDir(), "New Question");
	}
}

void TreeItemView::on_btn_addImage_clicked()
{
	if ( context()->dirContextVar()->activeDir() )
	{
		context()->act_addImageFromFile(context()->dirContextVar()->activeDir());
	}
}

void TreeItemView::on_btn_delete_clicked()
{
	if ( context()->dirContextVar()->activeDir() )
	{
		context()->act_removeFromDir(context()->dirContextVar()->activeDir(), selectedTreeItems());
	}
}

void TreeItemView::on_btn_toParentDirectory_clicked()
{
	auto dir = context()->dirContextVar()->activeDir();
	if ( dir )
	{
		auto parent = dir->parent();
		if ( parent )
		{
			if ( parent->type() == data::DataType::Dir )
			{
				auto parentDir = static_cast<data::Dir*>(parent);
				context()->dirContextVar()->activateDir(parentDir);
			}
		}
	}
}

data::Dir*TreeItemView::dir() const
{
	return m_dir;
}

void TreeItemView::setDir(data::Dir* one)
{
	if ( one )
	{
		if ( m_dir == nullptr )
		{
			setValidDir(one);
		}
		else if ( m_dir != one )
		{
			setNullDir();
			setValidDir(one);
		}
	}
	else
	{
		setDir(nullptr);
	}
}

void TreeItemView::setDir(nullptr_t)
{
	if ( m_dir )
	{
		setNullDir();
	}
}

void TreeItemView::setValidDir(data::Dir* one)
{
	m_dir = one;
	m_dir->addDepended(dependencyKeyFromPtr(this), std::make_shared<SetNullDir>(this));

	m_model->setValidDir(one);

	// Updates.
	updateCurDirLabel();
}

void TreeItemView::setNullDir()
{
	m_model->setNullDir();

	m_dir->removeDepended(dependencyKeyFromPtr(this));
	m_dir = nullptr;

	// Updates.
	updateCurDirLabel();
}

TreeItemModel*TreeItemView::treeItemModel()
{
	return m_model.get();
}

TreeItemModel const* TreeItemView::treeItemModel() const
{
	return m_model.get();
}

std::string TreeItemView::dirFullName(data::Dir* dir)
{
	// Dirs from child.
	std::vector<data::Dir*> dirs;
	{
		data::Dir* current = dir;
		do
		{
			dirs.push_back(current);

			auto parent = current->parent();
			if ( parent )
			{
				if ( parent->type() == data::DataType::Dir )
				{
					current = static_cast<data::Dir*>(parent);
				}
				else { current = nullptr; }
			}
			else { current = nullptr; }
		} while ( current );
	}

	std::string result;
	for ( auto i = dirs.rbegin(); i != dirs.rend(); ++i )
	{
		result += (*i)->nameContainer()->single() + "/";
	}
	return result;
}

void TreeItemView::updateCurDirLabel()
{
	auto dir = m_model->dir();
	if ( dir )
	{
		m_ui->curDir->setText(dirFullName(dir).c_str());
	}
	else
	{
		m_ui->curDir->setText("NO CURRENT DIR");
	}
}

std::vector<data::TreeItem*> TreeItemView::selectedTreeItems()
{
	auto selectedIndexes = m_ui->view->selectionModel()->selectedIndexes();

	std::vector<data::TreeItem*> result;
	result.reserve(selectedIndexes.size());
	for ( auto const& index : selectedIndexes )
	{
		result.push_back(m_model->indexToData(index));
	}
	return result;
}

}}
