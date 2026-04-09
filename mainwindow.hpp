#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QVector>
#include "models.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadDefaultClicked();
    void onLoadFileClicked();
    void onLoadJsonClicked();
    void onSaveJsonClicked();
    void onTableDoubleClicked(int row, int column);
    void onAddPersonClicked();
    void onEditPersonClicked();
    void onDeletePersonClicked();

private:
    void loadFromTxtFile(const QString& filename);
    void loadFromJsonFile(const QString& filename);
    void saveToJsonFile(const QString& filename);
    void loadDefaultData();
    void updateTable();
    void showCardDialog(Person* person, int row);

    Ui::MainWindow *ui;
    QVector<Person*> m_persons;
};

#endif // MAINWINDOW_H