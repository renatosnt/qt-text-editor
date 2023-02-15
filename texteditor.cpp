#include "texteditor.h"
#include "ui_texteditor.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
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

    QString file_name = QFileDialog::getOpenFileName(this, "Open File", "/home", "Text files (*.md *.txt)");

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Erro ao abrir arquivo", "Arquivo não pode ser aberto");
        return;
    }
    QTextStream stream( &file );
    QString text = stream.readAll();
    ui->textEdit->setText(text);
    file.close();
}

