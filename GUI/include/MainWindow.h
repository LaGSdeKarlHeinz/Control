/**
    @authors M.Rochat & E.Dutruy (Co-TL GS 23-24)
    @date 06-02-2024
    @brief Main window of the application
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() {};

private:
    QHBoxLayout* createSectionsLayout();
};

#endif /* MAINWINDOW_H */
