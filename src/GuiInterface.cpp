#include "GuiInterface.h"

GuiInterface::GuiInterface(QMainWindow *MainWindow, QListWidget *listWidgetInput, QListWidget *listWidgetOutput) : CommunicationInterface()
{
    this->MainWindow = MainWindow;
    this->listWidgetInput = listWidgetInput;
    this->listWidgetOutput = listWidgetOutput;

    this->regExpBinary = 0;
    this->regExpInteger = 0;
    this->regExpFloat = 0;

    connect(this, SIGNAL(stop(QString)), this->MainWindow, SLOT(stop(QString)));
    connect(this, SIGNAL(halt(QString)), this->MainWindow, SLOT(halt(QString)));
}

void GuiInterface::sendSignal(unsigned char signal)
{
    this->sendSignal(signal, "");
}

void GuiInterface::sendSignal(unsigned char signal, QString message)
{
    switch (signal)
    {
        case CommunicationInterface::STP:
            emit stop(message);
            break;

        default:
        case CommunicationInterface::HLT:
            emit halt(message);
            break;
    }
}

void GuiInterface::sendString(QString message)
{
    this->listWidgetOutput->addItem(message);
}

qint32 GuiInterface::receiveInteger()
{
    qint32 res = 0;

    if (this->listWidgetInput->count())
    {
        if (!this->regExpInteger)
        {
            this->regExpInteger = new QRegularExpression("^[-+]?[0-9]+$");
        }

        QListWidgetItem *item = this->listWidgetInput->takeItem(0);
        if (this->regExpInteger->match(item->text()).hasMatch())
        {
            res = (qint32) item->text().toInt();
            delete item;
        }
        else
        {
            delete item;
            this->sendSignal(CommunicationInterface::HLT, "input error: invalid integer value");
        }
    }
    else
    {
        DialogInputInteger dialog("Eingabe", QString::fromUtf8("Integerwert:"), this->MainWindow);

        this->MainWindow->setEnabled(false);

        if (dialog.exec())
        {
            res = (qint32) dialog.lineEditInput->text().toInt();
        }
        else
        {
            this->sendSignal(CommunicationInterface::HLT, "input error: no input");
        }

        this->MainWindow->setEnabled(true);
    }

    return res;
}

float GuiInterface::receiveFloat()
{
    float res = 0;

    if (this->listWidgetInput->count())
    {
        if (!this->regExpFloat)
        {
            this->regExpFloat = new QRegularExpression("^[-+]?([0-9]*\\.?[0-9]*)$");
        }

        QListWidgetItem *item = this->listWidgetInput->takeItem(0);
        if (this->regExpFloat->match(item->text()).hasMatch())
        {
            res = item->text().toFloat();
            delete item;
        }
        else
        {
            delete item;
            this->sendSignal(CommunicationInterface::HLT, "input error: invalid float value");
        }
    }
    else
    {
        DialogInputFloat dialog("Eingabe", QString::fromUtf8("Floatwert:"), this->MainWindow);

        this->MainWindow->setEnabled(false);

        if (dialog.exec())
        {
            res = dialog.lineEditInput->text().toFloat();
        }
        else
        {
            this->sendSignal(CommunicationInterface::HLT, "input error: no input");
        }

        this->MainWindow->setEnabled(true);
    }

    return res;
}

QString GuiInterface::receiveBinary()
{
    QString res;

    if (this->listWidgetInput->count())
    {
        if (!this->regExpBinary)
        {
            this->regExpBinary = new QRegularExpression("^[01]+$");
        }

        QListWidgetItem *item = this->listWidgetInput->takeItem(0);
        if (this->regExpBinary->match(item->text()).hasMatch())
        {
            res = item->text();
            delete item;
        }
        else
        {
            delete item;
            this->sendSignal(CommunicationInterface::HLT, "input error: invalid binary value");
        }
    }
    else
    {
        DialogInputBinary dialog("Eingabe", QString::fromUtf8("Binärwert:"), this->MainWindow);

        this->MainWindow->setEnabled(false);

        if (dialog.exec())
        {
            res = dialog.lineEditInput->text();
        }
        else
        {
            this->sendSignal(CommunicationInterface::HLT, "input error: no input");
        }

        this->MainWindow->setEnabled(true);
    }

    return res;
}
