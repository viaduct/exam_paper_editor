#pragma once
#include <memory>
#include <vector>

namespace wally {
namespace data {

class DataCmd : public std::enable_shared_from_this<DataCmd>
{
public:
	DataCmd() = default;
	virtual ~DataCmd() = default;
	DataCmd(DataCmd const&) = delete;
	DataCmd& operator =(DataCmd const&) = delete;

	virtual void run() = 0;
	virtual void undo() = 0;

	void ignore();
	bool isIgnored() const;

private:
	bool
	m_isIgnored = false;
};

class DataCmdList : public DataCmd
{
public:
	// Run commands in order.
	void run() override final;
	// Undo commands in reverse order.
	void undo() override final;

	size_t size() const;
	bool isEmpty() const;

	void append(std::shared_ptr<DataCmd> const& cmd);
	void append(std::shared_ptr<DataCmd>&& cmd);
	void reserve(size_t size); // Call std::vector::reserve() function.

private:
	std::vector<std::shared_ptr<DataCmd>>
	m_cmds;
};

}}
