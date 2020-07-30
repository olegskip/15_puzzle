#pragma once

#include "puzzle_item.h"
#include "config.h"

#include <QRandomGenerator>
#include <QSharedPointer>
#include <QMessageBox>
#include <QDateTime>
#include <QKeyEvent>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QTime>


class MainWindow: public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private:
	QVector<QSharedPointer<PuzzleItem>> puzzleItems; // one must be empty
	QSharedPointer<PuzzleItem> emptyPuzzleItem;

	void shuffle(QVector<QSharedPointer<PuzzleItem>> &puzzleItemsRef);
	void swap(QSharedPointer<PuzzleItem> firstPuzzleItem, QSharedPointer<PuzzleItem> secondPuzzleItem);
	QTimer timer;
	QTime stopwatch;

	QSharedPointer<PuzzleItem> getPuzzleItem(unsigned int number);
	QSharedPointer<PuzzleItem> getPuzzleItem(QPoint relPos);

	bool isGameOver();
	bool isGameStopped = false;

	void restart();
	void keyPressEvent(QKeyEvent *event) override;

private slots:
	void onPuzzeItemClicked(QSharedPointer<PuzzleItem> &puzzleItem);
};
