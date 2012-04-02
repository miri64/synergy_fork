#include "SetupWizard.h"
#include "MainWindow.h"

#include <QMessageBox>

SetupWizard::SetupWizard(MainWindow& mainWindow, bool startMain) :
	m_MainWindow(mainWindow),
	m_StartMain(startMain)
{
	setupUi(this);

#if !defined(Q_OS_WIN)
	m_pServiceRadioButton->setEnabled(false);
	m_pServiceRadioButton->setText(tr("Service (Windows only)"));
	m_pServiceLabel->setEnabled(false);
	m_pDesktopRadioButton->setChecked(true);
#endif

	connect(this, SIGNAL(finished(int)), this, SLOT(handlefinished()));
	connect(m_pServerRadioButton, SIGNAL(toggled(bool)), m_MainWindow.m_pGroupServer, SLOT(setChecked(bool)));
	connect(m_pClientRadioButton, SIGNAL(toggled(bool)), m_MainWindow.m_pGroupClient, SLOT(setChecked(bool)));
}

SetupWizard::~SetupWizard()
{
}

bool SetupWizard::validateCurrentPage()
{	
	QMessageBox message;
	message.setWindowTitle(tr("Setup Synergy"));
	message.setIcon(QMessageBox::Information);

	bool result = false;
	if (currentPage() == m_pNodePage)
	{
		result = m_pClientRadioButton->isChecked() ||
				 m_pServerRadioButton->isChecked();

		if (!result)
		{
			message.setText(tr("Please select an option."));
			message.exec();
		}
	}
	else if(currentPage() == m_pStartupPage)
	{
		result = m_pServiceRadioButton->isChecked() ||
				 m_pDesktopRadioButton->isChecked() ||
				 m_pNoneRadioButton->isChecked();

		if (!result)
		{
			message.setText(tr("Please select an option."));
			message.exec();
		}
	}
	return result;
}

void SetupWizard::handlefinished()
{
	close();

	if (m_StartMain)
	{
		m_MainWindow.start();
	}
}

