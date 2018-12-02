#pragma once
#include <boost/signals2.hpp>

namespace wally {
namespace data {

template <typename T>
class SinglePrimContainer
{
public:
	T single() const;

	void set(T const& value);
	void set(T&& value);

	boost::signals2::signal<void ()>* sig_updated();

private:
	boost::signals2::signal<void ()>
	m_sig_updated;

	T
	m_value{};
};

template<typename T>
T SinglePrimContainer<T>::single() const
{
	return m_value;
}

template<typename T>
void SinglePrimContainer<T>::set(const T& value)
{
	m_value = value;
	m_sig_updated();
}

template<typename T>
void SinglePrimContainer<T>::set(T&& value)
{
	m_value = std::move(value);
	m_sig_updated();
}

template<typename T>
boost::signals2::signal<void ()>*SinglePrimContainer<T>::sig_updated()
{
	return &m_sig_updated;
}

}}
