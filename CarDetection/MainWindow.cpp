#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), Watched()
{
	ui.setupUi(this);
	NotifyObserver();

}

void MainWindow::setImageInLabel(QImage *image) {
	ui.mylabel->setPixmap(QPixmap::fromImage(*image));
	ui.mylabel->show();
}

void MainWindow::NotifyObserver() {
	for (Observer* i : this->allObservers) {
		qDebug() << "update: " << i;
		i->update(returnComboBoxState());
	}
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
	this->NotifyObserver();
}

void MainWindow::on_actionOpen_2_triggered() {
	if (flagplay == 0) {
		player = Facade::getInstance();
		QString filename;
		filename = QFileDialog::getOpenFileName(
			this,
			tr("Open File"),
			"C:/Users/Wallace/Videos",
			"All files (*.*)"
		);

		player->loadVideo(filename);
		file = filename;
		QMessageBox::information(this, "", "Video was loaded correctly");
	}
	else {
		QMessageBox::information(this, "", "Video is playing!");
	
	}
}


void MainWindow::on_play_pressed() {
	this->NotifyObserver();
	if (file.endsWith(".mp4")&flagplay==0)
	{
		if (player->isOpened()) {
			flagplay = 1;
			player->startVideo();

			timer = new QTimer;
			connect(timer, SIGNAL(timeout()), this, SLOT(update()));
			timer->start(5);
		}
	}
	else {
	}
}


void MainWindow::update() {
	QImage img;
	player->updateFrame(img);
	cars.push_back(player->retNumbCars());
	if (cars.size() > 0 && cars.size() < 1000) {
		plot(&Customplot);
	
	}
	
	if (img.isNull()) {
		timer->stop();
	}
	else {
		setImageInLabel(&img);
	}
}

QString MainWindow::returnComboBoxState() {
	qDebug() << "returnComboBoxState";
	return ui.comboBox->currentText();
}

void MainWindow::on_stop_clicked() {
	if (flagplay == 1) {
		timer->stop();
		flagplay = 0;
	}
}
void MainWindow::on_clearvideo_clicked() {
	if (flagplay == 0) {
		player->closeVideo();
		player->loadVideo(file);
		cars.empty();
		ui.graph->clearGraphs();
		QImage gray;
		gray.load("gray.png");
		setImageInLabel(&gray);
	}
}

void MainWindow::plot(QCustomPlot * Customplot) {

	ui.graph->addGraph();
	QVector<qreal> Y;
	QVector<qreal> X;
	QColor color(20 + 200 / 4.0*0.2, 70 * (1.6 - 0.2 / 4.0), 150, 150);
	ui.graph->graph()->setLineStyle(QCPGraph::lsLine);
	ui.graph->graph()->setPen(QPen(color.lighter(200)));
	ui.graph->graph()->setBrush(QBrush(color));


	for (int i = 0; i < cars.size(); i++) {
		X.push_back(i);
		qDebug() <<"cars "<< cars[i];
		Y.push_back(cars[i]);
	}
	ui.graph->graph(0)->setData(X, Y);
	ui.graph->rescaleAxes();
	ui.graph->replot();
	ui.graph->xAxis->setLabel("Time");
	ui.graph->yAxis->setLabel("Detections");

}