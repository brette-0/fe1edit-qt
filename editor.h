#pragma once
#include <QApplication>
#include <QMainWindow>

class Editor : public QMainWindow {
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = nullptr);

private slots:
    void onOpen();
};
