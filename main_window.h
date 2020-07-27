#pragma once

#include "puzzle_item.h"
#include "config.h"

#include <QRandomGenerator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPointer>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QDateTime>


class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	QVector<QPointer<PuzzleItem>> puzzleItems; // one must be empty

	void shuffle(QVector<QPointer<PuzzleItem>> &puzzleItemsRef);
	void swap(QVector<QPointer<PuzzleItem>> &puzzleItemsRef, QPointer<PuzzleItem> firstPuzzleItem, QPointer<PuzzleItem> secondPuzzleItem);
	QTimer timer;
	QTime stopwatch;
};
