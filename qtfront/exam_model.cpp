#include "exam_model.h"
#include "context.h"
#include "../data/question.h"
#include "exam_model_sub/exam_mimic.h"
#include "exam_model_sub/question_mimic.h"

#include <iostream>

namespace wally {
namespace qtfront {

ExamModel::ExamModel()
{
}

ExamModel::~ExamModel()
{
}

data::Question*ExamModel::indexToData(const QModelIndex& index)
{
	auto questionMimic = static_cast<QuestionMimic*>(index.internalPointer());
	auto question = questionMimic->question();
	return question;
}

QModelIndex ExamModel::dataToIndex(data::Question* one)
{
	if ( m_exam )
	{
		bool isValid;
		auto at = m_examMimic->index(one, &isValid);

		if ( isValid )
		{
			return this->index(at, 0, QModelIndex());
		}
		else { return QModelIndex(); }
	}
	else { return QModelIndex(); }
}

data::Exam*ExamModel::exam() const
{
	return m_exam;
}

void ExamModel::setValidExam(data::Exam* one)
{
	m_exam = one;

	m_examMimic = std::make_unique<ExamMimic>();
	m_examMimic->init(context(), this);
	m_examMimic->setValidExam(m_exam);
}

void ExamModel::setNullExam()
{
	beginResetModel();
	m_examMimic = nullptr;
	endResetModel();

	m_exam = nullptr;
}

int ExamModel::rowCount(const QModelIndex& parent) const
{
	if ( m_exam )
	{
		if ( parent.isValid() == false )
		{
			return m_examMimic->size();
		}
		else { return 0; }
	}
	else { return 0; }
}

QModelIndex ExamModel::index(int row, int column, const QModelIndex& parent) const
{
	if ( m_exam )
	{
		if ( parent.isValid() == false )
		{
			if ( column == 0 )
			{
				if ( row < (int)m_examMimic->size() )
				{
					auto questionMimic = m_examMimic->at(row);
					return createIndex(row, 0, questionMimic);
				}
				else { return QModelIndex(); }
			}
			else { return QModelIndex(); }
		}
		else { return QModelIndex(); }
	}
	else { return QModelIndex(); }
}

QVariant ExamModel::data(const QModelIndex& index, int role) const
{
	auto question = indexToData(index);

	switch ( role )
	{
		case Qt::DisplayRole:
		case Qt::EditRole:
			return QString(question->nameContainer()->single().c_str());
			break;
		default:
			return QVariant();
			break;
	}
}

Qt::ItemFlags ExamModel::flags(const QModelIndex& index) const
{
	// To enable question name edit, uncomment below.
	return QAbstractListModel::flags(index)/* | Qt::ItemIsEditable*/;
}

bool ExamModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	auto question = indexToData(index);

	if ( role == Qt::EditRole )
	{
		context()->act_setTreeItemName(question, value.toString().toStdString());
		return true;
	}
	else { return false; }
}

void ExamModel::initialized()
{
}

}}
