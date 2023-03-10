#include "texteditor.h"
#include "ui_texteditor.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrintDialog>
#include <QPrinter>
TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

TextEditor::~TextEditor()
{
    delete ui;
}


void TextEditor::on_actionNew_triggered()
{
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void TextEditor::on_actionOpen_triggered()
{

    QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home", "Text files (*.md *.txt)");
    opened_filename = filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        if (file.exists()) {
            QMessageBox::warning(this, "Erro ao abrir arquivo", "arquivo não pode ser aberto");
        }
        return;
    }
    QTextStream file_stream( &file );
    QString text = file_stream.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void TextEditor::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as", "/home", "Text files (*.md *.txt)");
    opened_filename = filename;

    if (opened_filename == "") {
        return;
    }




    QFile file( filename );

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (file.exists()) {
            QMessageBox::warning(this, "Erro ao salvar arquivo", "arquivo não pode ser salvo");
        }
        return;
    }


    QTextStream file_stream(&file);
    QString text = ui->textEdit->toPlainText();
    file_stream << text << "\n";
    file.close();
}

void TextEditor::on_actionSave_triggered()
{
    QFile file(opened_filename);

    if (file.exists()) {
        // save it
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Erro ao salvar arquivo", "arquivo não pode ser salvo");
            return;
        }

        QTextStream file_stream(&file);
        QString text = ui->textEdit->toPlainText();
        file_stream << text << "\n";

        file.close();

    } else {
        // save as
        on_actionSave_as_triggered();
    }

}





void TextEditor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void TextEditor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void TextEditor::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void TextEditor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void TextEditor::on_actionText_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Font Color");

    if (color.isValid()) {
        ui->textEdit->setTextColor(color);
    }
}


void TextEditor::on_actionBackground_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Background Color");

    if(color.isValid()) {
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void TextEditor::on_actionFont_Family_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);

    if (ok) {
        ui->textEdit->setFont(font);
    }
}


void TextEditor::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "Just a simple text editor to help me learn QT.");
}


void TextEditor::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog dialog_printer;

    if (dialog_printer.exec() == QDialog::Rejected) {
        return;
    }

    ui->textEdit->print(&printer);
}

