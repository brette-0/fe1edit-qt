#include <iostream>

#include "editor.h"

#include <QScreen>
#include <QStyle>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QtEndian>
#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>

#include "game.h"

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

    QDialog dlg(this);
    dlg.setWindowTitle(tr("Select Translation"));

    auto *combo = new QComboBox(&dlg);
    combo->addItem(tr("Japanese"), static_cast<int>(Game::eTranslation::JAPANESE));
    combo->addItem(tr("English"),  static_cast<int>(Game::eTranslation::ENGLISH));
    combo->addItem(tr("Italian"),  static_cast<int>(Game::eTranslation::ITALIAN));
    combo->addItem(tr("Spanish"),  static_cast<int>(Game::eTranslation::SPANISH));
    combo->addItem(tr("Arabic"),   static_cast<int>(Game::eTranslation::ARABIC));

    auto *buttons = new QDialogButtonBox(
    QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);

    auto *form = new QFormLayout(&dlg);
    form->addRow(tr("ROM language:"), combo);
    form->addRow(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() != QDialog::Accepted) return;
    const auto chosen = static_cast<Game::eTranslation>(combo->currentData().toInt());

    const QByteArray rom = file.readAll();

    if (const auto err = Game::Parse(rom, chosen); err != eError::OK) {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle(tr("Unsupported ROM"));
        box.setText(tr(GetErrorContext(err)));
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
    }


    // TODO: later identify which translation is being used (hard part)
}

Editor::Editor(QWidget *parent) : QMainWindow(parent) {
    session = { };

    QMenu *fileMenu         = menuBar()->addMenu(tr("&File"));
    QMenu *mapOption        = menuBar()->addMenu(tr("&Map"));
    QMenu *animOption       = menuBar()->addMenu(tr("&Animations"));
    QMenu *textOption       = menuBar()->addMenu(tr("&Text"));
    QMenu *shopOption       = menuBar()->addMenu(tr("&Shop"));
    QMenu *attributesOption = menuBar()->addMenu(tr("&Attributes"));
    QMenu *characterOption  = menuBar()->addMenu(tr("&Characters"));

    const QAction* open   = fileMenu->addAction(tr("&Open ROM"));
    const QAction* save   = fileMenu->addAction(tr("&Save"));
    const QAction* saveAs = fileMenu->addAction(tr("&Save As"));

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