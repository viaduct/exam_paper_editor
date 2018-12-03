#pragma once
#include <QApplication>
#include <QMouseEvent>

namespace wally {
namespace qtfront {

template <
		typename Owner,
		void (Owner::*Clicked)(QMouseEvent*),
		void (Owner::*DragStarted)(QMouseEvent*, Qt::MouseButton),
		void (Owner::*DragReleased)(QMouseEvent*),
		void (Owner::*DragMoved)(QMouseEvent*)>
class ClickEventEmitter
{
public:
	ClickEventEmitter(Owner* owner, int limit = QApplication::startDragDistance()) :
		m_owner(owner),
		m_limit(limit) {}

	void mousePressed(QMouseEvent* e);
	void mouseReleased(QMouseEvent* e);
	void mouseMoved(QMouseEvent* e);

private:
	bool isDrag(QPoint const& first, QPoint const& second) const
	{
		return (first - second).manhattanLength() > m_limit;
	}

	Owner*
	m_owner;

	QPoint
	m_leftPressedPos,
	m_rightPressedPos;

	int const
	m_limit;

	bool
	m_doesLeftStay = false,
	m_doesRightStay = false;
};

template <
		typename Owner,
		void (Owner::*Clicked)(QMouseEvent*),
		void (Owner::*DragStarted)(QMouseEvent*, Qt::MouseButton),
		void (Owner::*DragReleased)(QMouseEvent*),
		void (Owner::*DragMoved)(QMouseEvent*)>
void ClickEventEmitter<Owner, Clicked, DragStarted, DragReleased, DragMoved>::mousePressed(QMouseEvent* e)
{
	switch ( e->button() )
	{
		case Qt::LeftButton:
		{
			m_doesLeftStay = true;
			m_leftPressedPos = e->pos();
		}
			break;

		case Qt::RightButton:
		{
			m_doesRightStay = true;
			m_rightPressedPos = e->pos();
		}
			break;

		default:
			; // Just ignore.
	}
}

template <
		typename Owner,
		void (Owner::*Clicked)(QMouseEvent*),
		void (Owner::*DragStarted)(QMouseEvent*, Qt::MouseButton),
		void (Owner::*DragReleased)(QMouseEvent*),
		void (Owner::*DragMoved)(QMouseEvent*)>
void ClickEventEmitter<Owner, Clicked, DragStarted, DragReleased, DragMoved>::mouseReleased(QMouseEvent* e)
{
	switch ( e->button() )
	{
		case Qt::LeftButton:
		{
			if ( m_doesLeftStay )
			{
				(m_owner->*Clicked)(e);
			}
			else
			{
				(m_owner->*DragReleased)(e);
			}

			m_doesLeftStay = false;
		}
			break;

		case Qt::RightButton:
		{
			if ( m_doesRightStay )
			{
				(m_owner->*Clicked)(e);
			}
			else
			{
				(m_owner->*DragReleased)(e);
			}

			m_doesRightStay = false;
		}
			break;

		default:
			; // Just ignore.
	}
}

template <
		typename Owner,
		void (Owner::*Clicked)(QMouseEvent*),
		void (Owner::*DragStarted)(QMouseEvent*, Qt::MouseButton),
		void (Owner::*DragReleased)(QMouseEvent*),
		void (Owner::*DragMoved)(QMouseEvent*)>
void ClickEventEmitter<Owner, Clicked, DragStarted, DragReleased, DragMoved>::mouseMoved(QMouseEvent* e)
{
	if ( e->buttons() & Qt::LeftButton )
	{
		if ( m_doesLeftStay )
		{
			if ( isDrag(m_leftPressedPos, e->pos()) )
			{
				// Now it's drag, deactivate.
				m_doesLeftStay = false;
				(m_owner->*DragStarted)(e, Qt::LeftButton);
			}
		}
		else
		{
			(m_owner->*DragMoved)(e);
		}
	}
	if ( e->buttons() & Qt::RightButton )
	{
		if ( m_doesRightStay )
		{
			if ( isDrag(m_rightPressedPos, e->pos()) )
			{
				// Now it's drag, deactivate right.
				m_doesRightStay = false;
				(m_owner->*DragStarted)(e, Qt::RightButton);
			}
		}
		else
		{
			(m_owner->*DragMoved)(e);
		}
	}
}

}}
