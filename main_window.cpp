#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	for(int y = 0, number = 0; y < 4; ++y) {
		for(int x = 0; x < 4; ++x) {
			if(puzzleItems.size() == 15) break;
			number++;
			puzzleItems.push_back(QSharedPointer<PuzzleItem>(new PuzzleItem(this, QPoint(config::sideSize * x, config::sideSize * y),
																	  QPoint(x, y), config::sideSize, number)));

		}
	}
	emptyPuzzleItem = QSharedPointer<PuzzleItem>(new PuzzleItem(this, QPoint(config::sideSize * 3, config::sideSize * 3), QPoint(3, 3),
															  config::sideSize));
	puzzleItems.push_back(emptyPuzzleItem);

	for(auto &puzzleItem: puzzleItems) {
		connect(puzzleItem.data(), &QPushButton::clicked, this, [this, &puzzleItem]()
		{
			onPuzzeItemClicked(puzzleItem);
		});
	}

	timer.setInterval(10);
	stopwatch.start();
	timer.start();
	connect(&timer, &QTimer::timeout, this, [this]()
	{
		if(!isGameStopped)
			setWindowTitle(QDateTime::fromTime_t(stopwatch.elapsed() / 1000).toUTC().toString("HH:mm:ss"));
	});

	resize(4 * config::sideSize, 4 * config::sideSize);
	setMinimumSize(size());
	setMaximumSize(size());

	restart();
}

// ---private functions---
void MainWindow::shuffle(QVector<QSharedPointer<PuzzleItem> > &puzzleItemsRef)
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

void MainWindow::swap(QSharedPointer<PuzzleItem> firstPuzzleItem, QSharedPointer<PuzzleItem> secondPuzzleItem)
{
	const auto firstPuzzleItemRelPos = firstPuzzleItem->currentRelPos();
	firstPuzzleItem->setRelPos(secondPuzzleItem->currentRelPos());
	firstPuzzleItem->move(config::sideSize * firstPuzzleItem->currentRelPos().x(), config::sideSize * firstPuzzleItem->currentRelPos().y());
	secondPuzzleItem->setRelPos(firstPuzzleItemRelPos);
	secondPuzzleItem->move(config::sideSize * secondPuzzleItem->currentRelPos().x(), config::sideSize * secondPuzzleItem->currentRelPos().y());
}

QSharedPointer<PuzzleItem> MainWindow::getPuzzleItem(unsigned int number)
{
	if(number == 16)
		number = 0;
	return *std::find_if(puzzleItems.begin(), puzzleItems.end(), [number](QSharedPointer<PuzzleItem> item)
	{
		return number == item->number;
	});
}

QSharedPointer<PuzzleItem> MainWindow::getPuzzleItem(QPoint relPos)
{
	return *std::find_if(puzzleItems.begin(), puzzleItems.end(), [&relPos](QSharedPointer<PuzzleItem> item)
	{
		return relPos == item->currentRelPos();
	});
}

bool MainWindow::isGameOver()
{
	const auto puzzleItemsSizeSqrt = std::sqrt(puzzleItems.size());
	if(puzzleItemsSizeSqrt != std::floor(puzzleItemsSizeSqrt)) {
		qDebug() << "[CRASH] Puzzle isn't a square!";
		exit(EXIT_FAILURE);
		return false;
	}

	const auto &firstPuzzleItem = getPuzzleItem(1);

	for(int y = 0, n = 1; y < puzzleItemsSizeSqrt; ++y) {
		for(int x = 0; x < puzzleItemsSizeSqrt; ++x, ++n) {
			if(getPuzzleItem(n)->currentRelPos() != QPoint(x, y))
				return false;
		}
	}

	return true;
}

void MainWindow::restart()
{
	stopwatch.restart();
	shuffle(puzzleItems);
	isGameStopped = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event) // override
{
	if(event->key() == Qt::Key_F5)
		restart();
	QWidget::keyPressEvent(event);
}
// ---private functions---

// ---private slots---
void MainWindow::onPuzzeItemClicked(QSharedPointer<PuzzleItem> &puzzleItem)
{
	if(puzzleItem->isEmpty || isGameStopped)
		return;

	// check is there empty puzzleItem near
	const QPoint puzzleItemRelPosition = puzzleItem->currentRelPos();

	if(emptyPuzzleItem->isEmpty && ((emptyPuzzleItem->currentRelPos().x() == puzzleItemRelPosition.x() &&
								 std::abs(emptyPuzzleItem->currentRelPos().y() - puzzleItemRelPosition.y()) == 1) ||
								(std::abs(emptyPuzzleItem->currentRelPos().x() - puzzleItemRelPosition.x()) == 1 &&
								 emptyPuzzleItem->currentRelPos().y() == puzzleItemRelPosition.y()))) {

		swap(puzzleItem, emptyPuzzleItem);
		if(isGameOver()) {
			isGameStopped = true;
			setWindowTitle("GAME OVER - " + windowTitle());
			qDebug() << "Game over!";
		}
	}
}
// ---private slots---

MainWindow::~MainWindow()
{
}
