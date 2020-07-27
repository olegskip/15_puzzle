#include "puzzle_item.h"

#include <QFont>

PuzzleItem::PuzzleItem(QWidget *widget, QPoint startAbsPos, QPoint _startRelPos, unsigned int sideSize):
	QPushButton(widget), startRelPos(_startRelPos), isEmpty(false), number(0)
{
	move(startAbsPos);
	resize(sideSize, sideSize);
}

PuzzleItem::PuzzleItem(QWidget *widget, QPoint startAbsPos, QPoint _startRelPos, unsigned int sideSize, unsigned int _number):
	QPushButton(widget), startRelPos(_startRelPos), isEmpty(true), number(_number)
{
	move(startAbsPos);
	resize(sideSize, sideSize);
	mCurrentRelPos = startRelPos;
	setText(QString::number(_number));

	QFont currentFont = font();
	currentFont.setPixelSize(40);
	setFont(currentFont);
}

QPoint PuzzleItem::currentRelPos() const
{
	return mCurrentRelPos;
}

void PuzzleItem::moveRelPos(QPoint newPosition)
{

}

void PuzzleItem::setRelPos(QPoint newPosition)
{
	mCurrentRelPos = newPosition;
}
