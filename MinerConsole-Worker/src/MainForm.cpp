#include "MainForm.h"
#include "ui_MainForm.h"
#include "AdminListener.h"
#include <QHostAddress>
#include "SettingsDlg.h"

MainForm::MainForm(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainForm)
{
    LOG_TRACE;

    ui->setupUi(this);

	_miner = new MinergateMiner(this);
	connect(_miner, SIGNAL(consoleWrite(QString)), this, SLOT(writeToConsole(QString)));
	
	connect(ui->action_Exit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
	connect(ui->actionStart, SIGNAL(triggered(bool)), _miner, SLOT(start()));
	connect(ui->actionStart_2, SIGNAL(triggered(bool)), _miner, SLOT(start()));
	connect(ui->actionStop, SIGNAL(triggered(bool)), _miner, SLOT(stop()));
	connect(ui->actionStop_2, SIGNAL(triggered(bool)), _miner, SLOT(stop()));
	connect(ui->actionSettings, SIGNAL(triggered(bool)), this, SLOT(openSettings()));
	
	StatusBarMinerState * mswgt = new StatusBarMinerState(this);
	ui->StatusBar->addWidget(new StatusBarTimeDisplay(this));
	ui->StatusBar->addWidget(mswgt);
	
	mswgt->setMiner(_miner);
	_miner->setPath("minergate-cli");
	_miner->setArguments("-user vin.kirill@gmail.com --bcn 3");
	
	_pipe = new AdminPipe(this);
	_pipe->setMiner(_miner);

	AdminListener *listener = new AdminListener(this);
	listener->setPipe(_pipe);
	listener->listen(QHostAddress::Any, 15987);
}

MainForm::~MainForm()
{
    LOG_TRACE;

    delete ui;
}

void MainForm::writeToConsole(QString text)
{
    LOG_TRACE;

    if (ui->txtConsole->toPlainText().length() > 1000000)
	{
		ui->txtConsole->clear();
	}
	setTextTermFormatting(ui->txtConsole, text);
}

void MainForm::openSettings()
{
    LOG_TRACE;

    SettingsDlg *dlg = new SettingsDlg(this);
	if (dlg->exec() == QDialog::Accepted)
	{
	}
	delete dlg;
}


// based on information: http://en.m.wikipedia.org/wiki/ANSI_escape_code http://misc.flogisoft.com/bash/tip_colors_and_formatting http://invisible-island.net/xterm/ctlseqs/ctlseqs.html
void MainForm::parseEscapeSequence(int attribute, QListIterator< QString > & i, QTextCharFormat & textCharFormat, QTextCharFormat const & defaultTextCharFormat)
{
    LOG_TRACE;

    switch (attribute) {
    case 0 : { // Normal/Default (reset all attributes)
        textCharFormat = defaultTextCharFormat;
        break;
    }
    case 1 : { // Bold/Bright (bold or increased intensity)
        textCharFormat.setFontWeight(QFont::Bold);
        break;
    }
    case 2 : { // Dim/Faint (decreased intensity)
        textCharFormat.setFontWeight(QFont::Light);
        break;
    }
    case 3 : { // Italicized (italic on)
        textCharFormat.setFontItalic(true);
        break;
    }
    case 4 : { // Underscore (single underlined)
        textCharFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
        textCharFormat.setFontUnderline(true);
        break;
    }
    case 5 : { // Blink (slow, appears as Bold)
        textCharFormat.setFontWeight(QFont::Bold);
        break;
    }
    case 6 : { // Blink (rapid, appears as very Bold)
        textCharFormat.setFontWeight(QFont::Black);
        break;
    }
    case 7 : { // Reverse/Inverse (swap foreground and background)
        QBrush foregroundBrush = textCharFormat.foreground();
        textCharFormat.setForeground(textCharFormat.background());
        textCharFormat.setBackground(foregroundBrush);
        break;
    }
    case 8 : { // Concealed/Hidden/Invisible (usefull for passwords)
        textCharFormat.setForeground(textCharFormat.background());
        break;
    }
    case 9 : { // Crossed-out characters
        textCharFormat.setFontStrikeOut(true);
        break;
    }
    case 10 : { // Primary (default) font
        textCharFormat.setFont(defaultTextCharFormat.font());
        break;
    }
    case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19 : {
        QFontDatabase fontDatabase;
        QString fontFamily = textCharFormat.fontFamily();
        QStringList fontStyles = fontDatabase.styles(fontFamily);
        int fontStyleIndex = attribute - 11;
        if (fontStyleIndex < fontStyles.length()) {
            textCharFormat.setFont(fontDatabase.font(fontFamily, fontStyles.at(fontStyleIndex), textCharFormat.font().pointSize()));
        }
        break;
    }
    case 20 : { // Fraktur (unsupported)
        break;
    }
    case 21 : { // Set Bold off
        textCharFormat.setFontWeight(QFont::Normal);
        break;
    }
    case 22 : { // Set Dim off
        textCharFormat.setFontWeight(QFont::Normal);
        break;
    }
    case 23 : { // Unset italic and unset fraktur
        textCharFormat.setFontItalic(false);
        break;
    }
    case 24 : { // Unset underlining
        textCharFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
        textCharFormat.setFontUnderline(false);
        break;
    }
    case 25 : { // Unset Blink/Bold
        textCharFormat.setFontWeight(QFont::Normal);
        break;
    }
    case 26 : { // Reserved
        break;
    }
    case 27 : { // Positive (non-inverted)
        QBrush backgroundBrush = textCharFormat.background();
        textCharFormat.setBackground(textCharFormat.foreground());
        textCharFormat.setForeground(backgroundBrush);
        break;
    }
    case 28 : {
        textCharFormat.setForeground(defaultTextCharFormat.foreground());
        textCharFormat.setBackground(defaultTextCharFormat.background());
        break;
    }
    case 29 : {
        textCharFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
        textCharFormat.setFontUnderline(false);
        break;
    }
    case 30: case 31: case 32: case 33: case 34: case 35: case 36: case 37 : {
        int colorIndex = attribute - 30;
        QColor color;
        if (QFont::Normal < textCharFormat.fontWeight()) {
            switch (colorIndex) {
            case 0 : {
                color = Qt::darkGray;
                break;
            }
            case 1 : {
                color = Qt::red;
                break;
            }
            case 2 : {
                color = Qt::green;
                break;
            }
            case 3 : {
                color = Qt::yellow;
                break;
            }
            case 4 : {
                color = Qt::blue;
                break;
            }
            case 5 : {
                color = Qt::magenta;
                break;
            }
            case 6 : {
                color = Qt::cyan;
                break;
            }
            case 7 : {
                color = Qt::white;
                break;
            }
            default : {
                Q_ASSERT(false);
            }
            }
        } else {
            switch (colorIndex) {
            case 0 : {
                color = Qt::black;
                break;
            }
            case 1 : {
                color = Qt::darkRed;
                break;
            }
            case 2 : {
                color = Qt::darkGreen;
                break;
            }
            case 3 : {
                color = Qt::darkYellow;
                break;
            }
            case 4 : {
                color = Qt::darkBlue;
                break;
            }
            case 5 : {
                color = Qt::darkMagenta;
                break;
            }
            case 6 : {
                color = Qt::darkCyan;
                break;
            }
            case 7 : {
                color = Qt::lightGray;
                break;
            }
            default : {
                Q_ASSERT(false);
            }
            }
        }
        textCharFormat.setForeground(color);
        break;
    }
    case 38 : {
        if (i.hasNext()) {
            bool ok = false;
            int selector = i.next().toInt(&ok);
            Q_ASSERT(ok);
            QColor color;
            switch (selector) {
            case 2 : {
                if (!i.hasNext()) {
                    break;
                }
                int red = i.next().toInt(&ok);
                Q_ASSERT(ok);
                if (!i.hasNext()) {
                    break;
                }
                int green = i.next().toInt(&ok);
                Q_ASSERT(ok);
                if (!i.hasNext()) {
                    break;
                }
                int blue = i.next().toInt(&ok);
                Q_ASSERT(ok);
                color.setRgb(red, green, blue);
                break;
            }
            case 5 : {
                if (!i.hasNext()) {
                    break;
                }
                int index = i.next().toInt(&ok);
                Q_ASSERT(ok);
                if (index >= 0x00 && index <= 0x07) {
                    return parseEscapeSequence(index - 0x00 + 30, i, textCharFormat, defaultTextCharFormat);
                } else if (index >= 0x08 && index <= 0x0F) {
                    return parseEscapeSequence(index - 0x08 + 90, i, textCharFormat, defaultTextCharFormat);
                } else if (index > 0x10 && index <= 0xE7) {
                    index -= 0x10;
                    int red = index % 6;
                    index /= 6;
                    int green = index % 6;
                    index /= 6;
                    int blue = index % 6;
                    index /= 6;
                    Q_ASSERT(index == 0);
                    color.setRgb(red, green, blue);
                    break;
                } else if (index >= 0xE8 && index <= 0xFF) {
                    qreal intensity = qreal(index - 0xE8) / (0xFF - 0xE8);
                    color.setRgbF(intensity, intensity, intensity);
                    break;
                }
                textCharFormat.setForeground(color);
                break;
            }
            default : {
                break;
            }
            }
        }
        break;
    }
    case 39 : {
        textCharFormat.setForeground(defaultTextCharFormat.foreground());
        break;
    }
    case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47 : {
        int colorIndex = attribute - 40;
        QColor color;
        switch (colorIndex) {
        case 0 : {
            color = Qt::darkGray;
            break;
        }
        case 1 : {
            color = Qt::red;
            break;
        }
        case 2 : {
            color = Qt::green;
            break;
        }
        case 3 : {
            color = Qt::yellow;
            break;
        }
        case 4 : {
            color = Qt::blue;
            break;
        }
        case 5 : {
            color = Qt::magenta;
            break;
        }
        case 6 : {
            color = Qt::cyan;
            break;
        }
        case 7 : {
            color = Qt::white;
            break;
        }
        default : {
            Q_ASSERT(false);
        }
        }
        textCharFormat.setBackground(color);
        break;
    }
    case 48 : {
        if (i.hasNext()) {
            bool ok = false;
            int selector = i.next().toInt(&ok);
            Q_ASSERT(ok);
            QColor color;
            switch (selector) {
            case 2 : {
                if (!i.hasNext()) {
                    break;
                }
                int red = i.next().toInt(&ok);
                Q_ASSERT(ok);
                if (!i.hasNext()) {
                    break;
                }
                int green = i.next().toInt(&ok);
                Q_ASSERT(ok);
                if (!i.hasNext()) {
                    break;
                }
                int blue = i.next().toInt(&ok);
                Q_ASSERT(ok);
                color.setRgb(red, green, blue);
                break;
            }
            case 5 : {
                if (!i.hasNext()) {
                    break;
                }
                int index = i.next().toInt(&ok);
                Q_ASSERT(ok);
                if (index >= 0x00 && index <= 0x07) {
                    return parseEscapeSequence(index - 0x00 + 30, i, textCharFormat, defaultTextCharFormat);
                } else if (index >= 0x08 && index <= 0x0F) {
                    return parseEscapeSequence(index - 0x08 + 90, i, textCharFormat, defaultTextCharFormat);
                } else if (index > 0x10 && index <= 0xE7) {
                    index -= 0x10;
                    int red = index % 6;
                    index /= 6;
                    int green = index % 6;
                    index /= 6;
                    int blue = index % 6;
                    index /= 6;
                    Q_ASSERT(index == 0);
                    color.setRgb(red, green, blue);
                    break;
                } else if (index >= 0xE8 && index <= 0xFF) {
                    qreal intensity = qreal(index - 0xE8) / (0xFF - 0xE8);
                    color.setRgbF(intensity, intensity, intensity);
                    break;
                }
                textCharFormat.setBackground(color);
                break;
            }
            default : {
                break;
            }
            }
        }
        break;
    }
    case 49 : {
        textCharFormat.setBackground(defaultTextCharFormat.background());
        break;
    }
    case 90: case 91: case 92: case 93: case 94: case 95: case 96: case 97 : {
        int colorIndex = attribute - 90;
        QColor color;
        switch (colorIndex) {
        case 0 : {
            color = Qt::darkGray;
            break;
        }
        case 1 : {
            color = Qt::red;
            break;
        }
        case 2 : {
            color = Qt::green;
            break;
        }
        case 3 : {
            color = Qt::yellow;
            break;
        }
        case 4 : {
            color = Qt::blue;
            break;
        }
        case 5 : {
            color = Qt::magenta;
            break;
        }
        case 6 : {
            color = Qt::cyan;
            break;
        }
        case 7 : {
            color = Qt::white;
            break;
        }
        default : {
            Q_ASSERT(false);
        }
        }
        color.setRedF(color.redF() * 0.8);
        color.setGreenF(color.greenF() * 0.8);
        color.setBlueF(color.blueF() * 0.8);
        textCharFormat.setForeground(color);
        break;
    }
    case 100: case 101: case 102: case 103: case 104: case 105: case 106: case 107 : {
        int colorIndex = attribute - 100;
        QColor color;
        switch (colorIndex) {
        case 0 : {
            color = Qt::darkGray;
            break;
        }
        case 1 : {
            color = Qt::red;
            break;
        }
        case 2 : {
            color = Qt::green;
            break;
        }
        case 3 : {
            color = Qt::yellow;
            break;
        }
        case 4 : {
            color = Qt::blue;
            break;
        }
        case 5 : {
            color = Qt::magenta;
            break;
        }
        case 6 : {
            color = Qt::cyan;
            break;
        }
        case 7 : {
            color = Qt::white;
            break;
        }
        default : {
            Q_ASSERT(false);
        }
        }
        color.setRedF(color.redF() * 0.8);
        color.setGreenF(color.greenF() * 0.8);
        color.setBlueF(color.blueF() * 0.8);
        textCharFormat.setBackground(color);
        break;
    }
    default : {
        break;
    }
    }
}

void MainForm::setTextTermFormatting(QPlainTextEdit * textEdit, QString const & text)
{
    LOG_TRACE;

    QTextDocument * document = textEdit->document();
    QRegExp const escapeSequenceExpression(R"(\x1B\[([\d;]+)m)");
    QTextCursor cursor(document);
    QTextCharFormat const defaultTextCharFormat = cursor.charFormat();
    cursor.beginEditBlock();
    int offset = escapeSequenceExpression.indexIn(text);
    cursor.insertText(text.mid(0, offset));
    QTextCharFormat textCharFormat = defaultTextCharFormat;
    while (!(offset < 0)) {
        int previousOffset = offset + escapeSequenceExpression.matchedLength();
        QStringList capturedTexts = escapeSequenceExpression.capturedTexts().back().split(';');
        QListIterator< QString > i(capturedTexts);
        while (i.hasNext()) {
            bool ok = false;
            int attribute = i.next().toInt(&ok);
            Q_ASSERT(ok);
            parseEscapeSequence(attribute, i, textCharFormat, defaultTextCharFormat);
        }
        offset = escapeSequenceExpression.indexIn(text, previousOffset);
        if (offset < 0) {
            cursor.insertText(text.mid(previousOffset), textCharFormat);
        } else {
            cursor.insertText(text.mid(previousOffset, offset - previousOffset), textCharFormat);
        }
    }
    cursor.setCharFormat(defaultTextCharFormat);
    cursor.endEditBlock();
    //cursor.movePosition(QTextCursor::Start);
    textEdit->setTextCursor(cursor);
}
