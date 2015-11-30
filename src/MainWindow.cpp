#include "MainWindow.h"

#include <QFileDialog>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <qpixmap.h>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), m_VectorField(0)
{
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);

	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));
}

MainWindow::~MainWindow()
{
	delete m_renderer;
	delete m_renderImage;
	delete m_renderImageItem;
	delete m_renderImageScene;
	delete m_Volume;
	delete m_VectorField;
	delete m_MultiSet;
}


//-------------------------------------------------------------------------------------------------
// Slots
//-------------------------------------------------------------------------------------------------

void MainWindow::openFileAction()
{
	QString filename = QFileDialog::getOpenFileName(this, "Data File", 0, tr("Data Files (*.dat *.gri *.csv)"));

	if (!filename.isEmpty())
	{
		// store filename
		m_FileType.filename = filename;
		std::string fn = filename.toStdString();
		bool success = false;

		// progress bar and top label
		m_Ui->progressBar->setEnabled(true);
		m_Ui->labelTop->setText("Loading data ...");
		m_volumeLoaded = false;

		// load data according to file extension
		if (fn.substr(fn.find_last_of(".") + 1) == "dat")		// LOAD VOLUME
		{
			// create VOLUME
			m_FileType.type = VOLUME;
			m_Volume = new Volume();

			// load file
			success = m_Volume->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "gri")		// LOAD VECTORFIELD
		{
			// create VECTORFIELD
			m_FileType.type = VECTORFIELD;
			m_VectorField = new VectorField();

			// load file
			success = m_VectorField->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "csv")		// LOAD MULTIVARIATE DATA
		{
			// create MULTIVARIATE
			m_FileType.type = MULTIVARIATE;
			m_MultiSet = new MultiSet();

			// load file
			success = m_MultiSet->loadFromFile(filename, m_Ui->progressBar);
		}

		m_Ui->progressBar->setEnabled(false);

		// status message
		if (success)
		{
			QString type;
			if (m_FileType.type == VOLUME)
			{
				type = "VOLUME";
				m_volumeLoaded = true;
				initRendering();
				render();
			}
			else if (m_FileType.type == VECTORFIELD) type = "VECTORFIELD";
			else if (m_FileType.type == MULTIVARIATE) type = "MULTIVARIATE";
			m_Ui->labelTop->setText("File LOADED [" + filename + "] - Type [" + type + "]");
		}
		else
		{
			m_Ui->labelTop->setText("ERROR loading file " + filename + "!");
			m_Ui->progressBar->setValue(0);
		}
	}
}

void MainWindow::initRendering()
{
	delete m_renderer;
	delete m_renderImage;
	delete m_renderImageItem;
	delete m_renderImageScene;

	m_renderer = new CPURenderer();
	m_renderImage = new QImage(m_Ui->graphicsView->width() - (2 * m_Ui->graphicsView->frameWidth()), m_Ui->graphicsView->height() - (2 * m_Ui->graphicsView->frameWidth()), QImage::Format::Format_RGB888);
	m_renderImageScene = new QGraphicsScene(m_Ui->graphicsView->sceneRect());
	m_renderImageItem = new QGraphicsPixmapItem(QPixmap::fromImage(*m_renderImage));

	m_renderImageScene->addItem(m_renderImageItem);
	m_Ui->graphicsView->setScene(m_renderImageScene);
	

	//std::cout << m_Ui->graphicsView->width() << std::endl;
	//std::cout << m_Ui->graphicsView->frameWidth() << std::endl;

	/*
	m_renderer = new CPURenderer();
	m_renderImage = new QImage(m_Ui->openGLWidget->width(), m_Ui->openGLWidget->height(), QImage::Format::Format_RGB888);
	m_renderImageScene = new QGraphicsScene(m_Ui->openGLWidget->sceneRect());
	m_renderImageItem = new QGraphicsPixmapItem(QPixmap::fromImage(*m_renderImage));

	m_renderImageScene->addItem(m_renderImageItem);
	m_Ui->graphicsView->setScene(m_renderImageScene);
	*/
}

void MainWindow::render()
{
	if (m_volumeLoaded)
	{
		m_renderer->mipEnabled = m_Ui->cb_MIP->isChecked();
		m_renderer->alphaCompositingEnabled = m_Ui->cb_AlphaCompositing->isChecked();
		m_renderer->alphaCompositingTreshold = m_Ui->sl_AlphaCompositing->value();

		m_renderer->xTranslate = m_Ui->sl_xTranslate->value();
		m_renderer->yTranslate = m_Ui->sl_yTranslate->value();

		std::cout << m_renderer->alphaCompositingTreshold << std::endl;

		m_renderer->sampleAndRender(*m_renderImage, *m_Volume);

		m_renderImageItem->setPixmap(QPixmap::fromImage(*m_renderImage));
	}
}

void MainWindow::closeAction()
{
	close();
}
