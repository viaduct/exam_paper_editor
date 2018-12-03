#pragma once
#include <QAbstractListModel>
#include <memory>
#include "context_holder.h"

namespace wally {

namespace data {
class Exam;
class Question;
}

namespace qtfront {

namespace exam_model_sub {
class ExamMimic;
class QuestionMimic;
}

class ExamModel : public QAbstractListModel,
		public ContextHolder
{
public:
	using ExamMimic = exam_model_sub::ExamMimic;
	using QuestionMimic = exam_model_sub::QuestionMimic;

	ExamModel();
	virtual ~ExamModel();

	static data::Question* indexToData(QModelIndex const& index);
	QModelIndex dataToIndex(data::Question* one);

	data::Exam* exam() const;
	void setValidExam(data::Exam* one);
	void setNullExam();

	// From QAbstractListModel.
	int rowCount(const QModelIndex &parent) const override final;
	QModelIndex index(int row, int column, const QModelIndex &parent) const override final;
	QVariant data(const QModelIndex &index, int role) const override final;
	Qt::ItemFlags flags(const QModelIndex &index) const override final;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override final;

	using QAbstractListModel::beginInsertRows;
	using QAbstractListModel::endInsertRows;
	using QAbstractListModel::beginRemoveRows;
	using QAbstractListModel::endRemoveRows;
	using QAbstractListModel::beginMoveRows;
	using QAbstractListModel::endMoveRows;

	using QAbstractListModel::dataChanged;

protected:
	void initialized() override final;

private:
	std::unique_ptr<ExamMimic>
	m_examMimic;

	data::Exam*
	m_exam{};
};

}}
