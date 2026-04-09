#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "carddialog.h"
#include "editdialog.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("НПС Карточки - Лабораторная работа 5");

    // Настройка таблицы
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"Код", "Имя", "Тип", "Атрибут", "Значение", "ХП"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Подключение сигналов
    connect(ui->loadDefaultButton, &QPushButton::clicked, this, &MainWindow::onLoadDefaultClicked);
    connect(ui->loadFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(ui->loadJsonButton, &QPushButton::clicked, this, &MainWindow::onLoadJsonClicked);
    connect(ui->saveJsonButton, &QPushButton::clicked, this, &MainWindow::onSaveJsonClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddPersonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditPersonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeletePersonClicked);
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &MainWindow::onTableDoubleClicked);

    // Загружаем данные по умолчанию
    loadDefaultData();
}

MainWindow::~MainWindow()
{
    for (Person* p : m_persons) {
        delete p;
    }
    delete ui;
}

void MainWindow::loadDefaultData()
{
    // Очищаем старых персонажей
    for (Person* p : m_persons) {
        delete p;
    }
    m_persons.clear();

    // Создаём тестовых персонажей
    Armor armor1(1, 3, 1);
    Armor armor2(0, 10, 5);
    Armor armor3(10, 30, 50);

    m_persons.append(new VragP(1, "Скелет", "Обычный", 12, 5, armor1));
    m_persons.append(new MagP(2, "Мэрлин", "Огонь", 120, 100, armor2));
    m_persons.append(new VragP(3, "Огр", "Редкий", 85, 150, armor3));

    updateTable();
}

void MainWindow::onLoadDefaultClicked()
{
    loadDefaultData();
    QMessageBox::information(this, "Успех", "Загружены данные по умолчанию");
}

void MainWindow::onLoadFileClicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Выберите txt файл с данными",
        "",
        "Текстовые файлы (*.txt);;Все файлы (*)");

    if (!filename.isEmpty()) {
        loadFromTxtFile(filename);
    }
}

void MainWindow::onLoadJsonClicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Выберите JSON файл с данными",
        "",
        "JSON файлы (*.json);;Все файлы (*)");

    if (!filename.isEmpty()) {
        loadFromJsonFile(filename);
    }
}

void MainWindow::onSaveJsonClicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
        "Сохранить в JSON файл",
        "data.json",
        "JSON файлы (*.json);;Все файлы (*)");

    if (!filename.isEmpty()) {
        saveToJsonFile(filename);
        QMessageBox::information(this, "Успех", "Данные сохранены в JSON");
    }
}

void MainWindow::loadFromTxtFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    // Очищаем старых персонажей
    for (Person* p : m_persons) {
        delete p;
    }
    m_persons.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split(',');
        if (parts.size() < 6) continue;

        int code = parts[0].toInt();
        QString name = parts[1];
        QString third = parts[2];
        int health = parts[4].toInt();

        // Разбор брони
        QString armorStr = parts[5];
        QStringList armorParts = armorStr.split('/');
        Armor armor;
        if (armorParts.size() >= 3) {
            armor.helmet = armorParts[0].toInt();
            armor.chestplate = armorParts[1].toInt();
            armor.boots = armorParts[2].toInt();
        }

        if (parts.size() >= 7) {
            int value = parts[3].toInt();

            // Определяем тип по третьему полю
            if (third == "Огонь" || third == "Вода" || third == "Земля" || third == "Воздух") {
                m_persons.append(new MagP(code, name, third, value, health, armor));
            } else {
                m_persons.append(new VragP(code, name, third, value, health, armor));
            }
        }
    }

    file.close();

    if (m_persons.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл не содержит корректных данных!");
        return;
    }

    updateTable();
    QMessageBox::information(this, "Успех", QString("Загружено %1 персонажей").arg(m_persons.size()));
}

void MainWindow::loadFromJsonFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть JSON файл!");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат JSON!");
        return;
    }

    QJsonArray arr = doc.array();

    // Очищаем старых персонажей
    for (Person* p : m_persons) {
        delete p;
    }
    m_persons.clear();

    for (const QJsonValue& val : arr) {
        QJsonObject obj = val.toObject();
        QString type = obj["type"].toString();
        int code = obj["code"].toInt();
        QString name = obj["name"].toString();
        int health = obj["health"].toInt();
        Armor armor = Armor::fromJson(obj["armor"].toObject());

        if (type == "mag") {
            QString element = obj["element"].toString();
            int mana = obj["mana"].toInt();
            m_persons.append(new MagP(code, name, element, mana, health, armor));
        } else if (type == "vrag") {
            QString rarity = obj["rarity"].toString();
            int damage = obj["damage"].toInt();
            m_persons.append(new VragP(code, name, rarity, damage, health, armor));
        }
    }

    updateTable();
    QMessageBox::information(this, "Успех", QString("Загружено %1 персонажей из JSON").arg(m_persons.size()));
}

void MainWindow::saveToJsonFile(const QString& filename)
{
    QJsonArray arr;
    for (Person* p : m_persons) {
        arr.append(p->toJson());
    }

    QJsonDocument doc(arr);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::updateTable()
{
    ui->tableWidget->setRowCount(m_persons.size());

    for (int i = 0; i < m_persons.size(); ++i) {
        Person* p = m_persons[i];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(p->getCode())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(p->getName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(p->getType()));

        if (MagP* mag = dynamic_cast<MagP*>(p)) {
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(mag->getElement()));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(mag->getMana())));
        } else if (VragP* vrag = dynamic_cast<VragP*>(p)) {
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(vrag->getRarity()));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(vrag->getDamage())));
        }

        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(p->getHealth())));
    }

    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::onTableDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    if (row >= 0 && row < m_persons.size()) {
        showCardDialog(m_persons[row], row);
    }
}

void MainWindow::onAddPersonClicked()
{
    EditDialog dialog(nullptr, this);
    if (dialog.exec() == QDialog::Accepted) {
        Person* newPerson = dialog.getPerson();
        if (newPerson) {
            m_persons.append(newPerson);
            updateTable();
            QMessageBox::information(this, "Успех", "Персонаж добавлен");
        }
    }
}

void MainWindow::onEditPersonClicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= m_persons.size()) {
        QMessageBox::warning(this, "Ошибка", "Выберите персонажа для редактирования");
        return;
    }

    EditDialog dialog(m_persons[row]->clone(), this);
    if (dialog.exec() == QDialog::Accepted) {
        Person* editedPerson = dialog.getPerson();
        if (editedPerson) {
            delete m_persons[row];
            m_persons[row] = editedPerson;
            updateTable();
            QMessageBox::information(this, "Успех", "Персонаж отредактирован");
        }
    }
}

void MainWindow::onDeletePersonClicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= m_persons.size()) {
        QMessageBox::warning(this, "Ошибка", "Выберите персонажа для удаления");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение",
                              QString("Удалить персонажа '%1'?").arg(m_persons[row]->getName()),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        delete m_persons[row];
        m_persons.removeAt(row);
        updateTable();
    }
}

void MainWindow::showCardDialog(Person* person, int row)
{
    CardDialog* dialog = new CardDialog(person->clone(), this);
    connect(dialog, &CardDialog::personRemoved, this, [this, row, dialog]() {
        delete m_persons[row];
        m_persons.removeAt(row);
        updateTable();
        dialog->accept();
    });
    dialog->exec();
}