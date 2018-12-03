#include <boost/format.hpp>
#include "tree_item_model.h"
#include "context.h"
#include "../data/dir.h"
#include "../data/data_cmd.h"
#include "tree_item_model_sub/dir_mimic.h"
#include "tree_item_model_sub/tree_item_mimic.h"

namespace wally {
namespace qtfront {

TreeItemModel::TreeItemModel()
{
}

TreeItemModel::~TreeItemModel()
{
}

data::TreeItem*TreeItemModel::indexToData(const QModelIndex& index)
{
	return static_cast<TreeItemMimic*>(index.internalPointer())->treeItem();
}

QModelIndex TreeItemModel::dataToIndex(data::TreeItem* one)
{
	if ( m_dir )
	{
		bool isValid;
		auto index = m_dirMimic->index(one, &isValid);

		if ( isValid )
		{
			return this->index(index, 0, QModelIndex());
		}
		else
		{
			return QModelIndex();
		}
	}
	else
	{
		return QModelIndex();
	}
}

data::Dir*TreeItemModel::dir() const
{
	return m_dir;
}

void TreeItemModel::setValidDir(data::Dir* one)
{
	m_dir = one;

	m_dirMimic = std::make_unique<DirMimic>();
	m_dirMimic->init(context(), this);
	m_dirMimic->setValidDir(one);
}

void TreeItemModel::setNullDir()
{
	beginResetModel();
	m_dirMimic = nullptr;
	endResetModel();

	m_dir = nullptr;
}

int TreeItemModel::rowCount(const QModelIndex& parent) const
{
	if ( m_dir )
	{
		if ( parent.isValid() == false )
		{
			return m_dirMimic->size();
		}
		else { return 0; }
	}
	else { return 0; }
}

QModelIndex TreeItemModel::index(int row, int column, const QModelIndex& parent) const
{
	if ( m_dir )
	{
		if ( parent.isValid() == false )
		{
			if ( column == 0 )
			{
				if ( row < (int)m_dirMimic->size() )
				{
					auto newIndex = createIndex(row, column, m_dirMimic->at(row));
					return newIndex;
				}
				else { return QModelIndex(); }
			}
			else { return QModelIndex(); }
		}
		else { return QModelIndex(); }
	}
	else { return QModelIndex(); }
}

QVariant TreeItemModel::data(const QModelIndex& index, int role) const
{
	if ( m_dir )
	{
		if ( index.column() == 0 )
		{
			if ( index.row() < (int)m_dirMimic->size() )
			{
				switch ( role )
				{
					case Qt::DisplayRole:
					{
						auto treeItemMimic = static_cast<TreeItemMimic*>(index.internalPointer());
						boost::format text("[%1%]%2%");
						switch ( treeItemMimic->treeItem()->type() )
						{
							case data::DataType::Dir:
								text % "D";
								break;
							case data::DataType::Image:
								text % "I";
								break;
							case data::DataType::Question:
								text % "Q";
								break;
							case data::DataType::Exam:
								text % "E";
								break;
							default:
								text % "Unknown";
								break;
						}
						text % treeItemMimic->treeItem()->nameContainer()->single();
						return QString(text.str().c_str());
					}
						break;
					case Qt::EditRole:
					{
						auto treeItemMimic = static_cast<TreeItemMimic*>(index.internalPointer());
						return QString(treeItemMimic->treeItem()->nameContainer()->single().c_str());
					}
						break;
					default:
						return QVariant();
						break;
				}
			}
			else { return QVariant(); }
		}
		else { return QVariant(); }
	}
	else { return QVariant(); }
}

Qt::ItemFlags TreeItemModel::flags(const QModelIndex& index) const
{
	return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool TreeItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if ( m_dir )
	{
		if ( index.column() == 0 )
		{
			if ( index.row() < (int)m_dirMimic->size() )
			{
				switch ( role )
				{
					case Qt::EditRole:
					{
						auto treeItemMimic = static_cast<TreeItemMimic*>(index.internalPointer());
						context()->act_setTreeItemName(treeItemMimic->treeItem(), value.toString().toStdString());
						return true;
					}
						break;
					default:
						return false;
						break;
				}
			}
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
}

void TreeItemModel::initialized()
{
}

}}
