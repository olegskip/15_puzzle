#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	for(int y = 0, number = 0; y < 4; ++y) {
		for(int x = 0; x < 4; ++x) {
			if(puzzleItems.size() == 15) break;
			number++;
			puzzleItems.push_back(QPointer<PuzzleItem>(new PuzzleItem(this, QPoint(config::sideSize * x, config::sideSize * y),
																	  QPoint(x, y), config::sideSize, number)));

		}
	}
	puzzleItems.push_back(QPointer<PuzzleItem>(new PuzzleItem(this, QPoint(config::sideSize * 3, config::sideSize * 3), QPoint(4, 4),
															  config::sideSize)));

	shuffle(puzzleItems);
	timer.setInterval(10);
	stopwatch.start();
	timer.start();
	connect(&timer, &QTimer::timeout, this, [this]()
	{
		setWindowTitle(QDateTime::fromTime_t(stopwatch.elapsed() / 1000).toUTC().toString("HH:mm:ss"));
	});
}

void MainWindow::shuffle(QVector<QPointer<PuzzleItem>> &puzzleItemsRef)
{
	const auto puzzleItemsRefSizeSqrt = std::sqrt(puzzleItemsRef.size());
	if(puzzleItemsRefSizeSqrt != std::floor(puzzleItemsRefSizeSqrt)) {
		qDebug() << "[CRASH] Puzzle isn't a square!";
		exit(EXIT_FAILURE);
	}

	QVector<QPoint> randomVec;
	for(int x = 0; x < puzzleItemsRefSizeSqrt; ++x) {
		for(int y = 0; y < puzzleItemsRefSizeSqrt; ++y) {
			randomVec.push_back(QPoint(x, y));
		}
	}

	static std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::shuffle(randomVec.begin(), randomVec.end(), generator);

	for(int i = 0; i < puzzleItemsRef.size(); ++i) {
		puzzleItemsRef[i]->setRelPos(randomVec[i]);
		puzzleItemsRef[i]->move(puzzleItemsRef[i]->currentRelPos().x() * config::sideSize,
								puzzleItemsRef[i]->currentRelPos().y() * config::sideSize);
	}
}

void MainWindow::swap(QVector<QPointer<PuzzleItem>> &puzzleItemsRef, QPointer<PuzzleItem> firstPuzzleItem, QPointer<PuzzleItem> secondPuzzleItem)
{

}

MainWindow::~MainWindow()
{
}
