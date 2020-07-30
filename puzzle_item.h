#pragma once

#include <QPushButton>
#include <QPoint>


class PuzzleItem: public QPushButton
{
public:
	PuzzleItem(QWidget *widget, QPoint startAbsPos, QPoint _startRelPos, unsigned int sideSize); // empty
	PuzzleItem(QWidget *widget, QPoint startAbsPos, QPoint _startRelPos, unsigned int sideSize, unsigned int _number);

	const QPoint startRelPos;
	QPoint currentRelPos() const;
	void setRelPos(QPoint newPosition);
	const bool isEmpty;
	const unsigned int number;

private:
	QPoint mCurrentRelPos;
};

