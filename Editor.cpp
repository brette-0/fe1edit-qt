#include <iostream>

#include "editor.h"

#include <QScreen>
#include <QStyle>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

void Editor::onOpen() {
    QFileDialog dialog(this, tr("Open File"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("NES ROMs (*.nes *.NES)"));

    if (dialog.exec() == QDialog::Rejected) return;

    const QStringList files = dialog.selectedFiles();
    if (files.isEmpty()) return;
    const QString& path = files.first();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle(tr("Open ROM"));
        box.setText(tr("Could not read file %1").arg(path));
        box.setInformativeText(file.errorString());
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
    }

    const QByteArray rom = file.readAll();
    // open ROM into memory
    // identify which translation is being used (hard part)
}

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *open   = fileMenu->addAction(tr("&Open ROM"));
    QAction *save   = fileMenu->addAction(tr("&Save"));
    QAction *saveAs = fileMenu->addAction(tr("&Save As"));

    connect(open, &QAction::triggered, this, &Editor::onOpen);

    setWindowTitle(tr("fe1edit"));
    const auto *screen = QGuiApplication::screenAt(QCursor::pos());
    if (!screen)
        screen = QGuiApplication::primaryScreen();

    const auto available = screen->availableGeometry();
    const QSize targetSize(available.width() / 2, available.height() / 2);
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        targetSize,
        available
    ));
}