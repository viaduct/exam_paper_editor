#pragma once
#include <memory>
#include <vector>

namespace wally {

namespace data {
class DataCmd;
}

namespace qtfront {

class AppCmd : public std::enable_shared_from_this<AppCmd>
{
public:
	AppCmd() = default;
	virtual ~AppCmd() = default;
	AppCmd(AppCmd const&) = delete;
	AppCmd& operator =(AppCmd const&) = delete;

	virtual void run() = 0;
	virtual void undo() = 0;
};

class AppDataCmd : public AppCmd
{
public:
	AppDataCmd(std::shared_ptr<data::DataCmd> const& cmd);
	AppDataCmd(std::shared_ptr<data::DataCmd>&& cmd);

	void run() override final;
	void undo() override final;

private:
	std::shared_ptr<data::DataCmd>
	m_cmd;
};

class AppCmdList : public AppCmd
{
public:
	// Run commands in order.
	void run() override final;
	// Undo commands in reverse order.
	void undo() override final;

	size_t size() const;
	bool isEmpty() const;

	void append(std::shared_ptr<AppCmd> const& cmd);
	void append(std::shared_ptr<AppCmd>&& cmd);
	void reserve(size_t size); // Call std::vector::reserve() function.

private:
	std::vector<std::shared_ptr<AppCmd>>
	m_cmds;
};

}}
