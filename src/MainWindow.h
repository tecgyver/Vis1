
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Volume.h"
#include "VectorField.h"
#include "MultiSet.h"
#include "CPURenderer.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>
#include <QGraphicsPixmapItem>


class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		MainWindow(QWidget *parent = 0);
		~MainWindow();

	
	protected slots :

		void								 openFileAction();
		void								 closeAction();
		

	private:

		// USER INTERFACE ELEMENTS

		Ui_MainWindow						*m_Ui;


		// DATA 

		enum DataType
		{
			VOLUME					= 0,
			VECTORFIELD				= 1,
			MULTIVARIATE			= 2
		};

		struct FileType
		{
			QString			filename;
			DataType		type;
		}									 m_FileType;

		Volume								*m_Volume;						// for Volume-Rendering
		VectorField							*m_VectorField;					// for Flow-Visualisation
		MultiSet							*m_MultiSet;					// for Multivariate Data

		bool								m_volumeLoaded;
		QImage								*m_renderImage;
		CPURenderer							*m_renderer;
		QGraphicsScene						*m_renderImageScene;
		QGraphicsPixmapItem					*m_renderImageItem;


		void								render();
		void								initRendering();
};

#endif
