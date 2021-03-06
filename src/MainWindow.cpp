#include "MainWindow.h"

#include <QFileDialog>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <qdial.h>
#include <qpixmap.h>

Ui_MainWindow* MainWindow::m_Ui;
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), m_VectorField(0)
{
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);
	
	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));
	connect(m_Ui->bu_render, SIGNAL(clicked()), this, SLOT(clickedSlot()));
}

MainWindow::~MainWindow()
{
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
	m_Ui->openGLWidget->setVolume(m_Volume);
	m_Ui->openGLWidget->update();
}

void MainWindow::render()
{
	/*if (m_volumeLoaded)
	{
		m_renderer->mipEnabled = m_Ui->cb_MIP->isChecked();
		m_renderer->alphaCompositingEnabled = m_Ui->cb_AlphaCompositing->isChecked();
		m_renderer->alphaCompositingTreshold = m_Ui->sl_AlphaCompositing->value();

		m_renderer->sampleSize = m_Ui->te_sampleSize->toPlainText().toInt();

		m_renderer->xTranslate = m_Ui->sl_xTranslate->value();
		m_renderer->yTranslate = m_Ui->sl_yTranslate->value();

		m_renderer->xRotateEnabled = m_Ui->cb_rotateX->isChecked();
		m_renderer->yRotateEnabled = m_Ui->cb_rotateY->isChecked();
		m_renderer->xRotateDeg = m_Ui->sl_xRotate->value();
		m_renderer->yRotateDeg = m_Ui->sl_yRotate->value();

		m_renderer->sampleAndRender(*m_renderImage, *m_Volume);

		m_renderImageItem->setPixmap(QPixmap::fromImage(*m_renderImage));
	}*/
}

void MainWindow::closeAction()
{
	close();
}

void MainWindow::clickedSlot()
{
	render();
}
