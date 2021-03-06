/*
   Drawpile - a collaborative drawing program.

   Copyright (C) 2014-2017 Calle Laakkonen

   Drawpile is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Drawpile is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Drawpile.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class Ui_LoginDialog;
class QAbstractButton;
class QSslCertificate;

namespace net {
	class LoginHandler;
	class LoginSessionModel;
}

namespace dialogs {

/**
 * @brief The dialog that is shown during the login process
 *
 * This dialog handles all the user interaction needed while logging in.
 * (Quite often, no interaction is needed at all.)
 */
class LoginDialog : public QDialog
{
	Q_OBJECT
public:
	explicit LoginDialog(net::LoginHandler *login, QWidget *parent = 0);
	~LoginDialog();

public slots:
	void catchupProgress(int value);
	void onLoginDone(bool join);

private slots:
	void onButtonClick(QAbstractButton*);

	void onPasswordNeeded(const QString &prompt);
	void onLoginNeeded(const QString &prompt);
	void onSessionChoiceNeeded(net::LoginSessionModel *sessions);
	void onCertificateCheckNeeded(const QSslCertificate &newCert, const QSslCertificate &oldCert);
	void onServerTitleChanged(const QString &title);
	void onReportClicked();

private:
	enum Mode {
		LABEL,    // Show "logging in..." label
		PASSWORD, // Ask for just the password
		LOGIN,    // Ask for username and password
		SESSION,  // Select sesssion
		CERT,     // Inspect a certificate
		CATCHUP   // "Catching up..." page with progress bar
	};

	void resetMode(Mode mode=LABEL);

	Mode m_mode;
	net::LoginHandler *m_login;
	Ui_LoginDialog *m_ui;
	QAbstractButton *m_reportButton;
	QMetaObject::Connection m_loginDestructConnection;
};

}

#endif // LOGINDIALOG_H
