#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include "pointofinterest.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreatePoint();
    void onLoadFromTxt();
    void onLoadFromJson();
    void onSaveToJson();

private:
    void setupUI();
    void loadPointsToTables(const QList<PointOfInterest> &points);
    void loadBrokenPointsToTable(const QList<QString> &brokenLines);
    void addPointToTables(const PointOfInterest &poi);
    void clearTables();

    // Вкладка 1: создание нового объекта
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QSpinBox *difficultySpin;
    QDoubleSpinBox *xSpin;
    QDoubleSpinBox *ySpin;
    QPushButton *createBtn;
    QPushButton *loadTxtBtn;
    QPushButton *saveJsonBtn;

    // Вкладка 2: вывод данных
    QTableWidget *validTable;
    QTableWidget *brokenTable;
    QPushButton *loadJsonBtn;

    QList<PointOfInterest> validPoints;
    QList<QString> brokenPoints; // для хранения "битых" строк из txt
};

#endif // MAINWINDOW_H