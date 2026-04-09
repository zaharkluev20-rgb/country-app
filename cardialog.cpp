#include "carddialog.h"
#include <QPixmap>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QBuffer>

QSet<QString> CardDialog::m_usedImages;

CardDialog::CardDialog(Person* person, QWidget *parent)
    : QDialog(parent), m_person(person), m_imageMode(1)
{
    setupUi();
    updateImage(m_imageMode);
    setWindowTitle("Карточка персонажа");
    setModal(true);
}

CardDialog::~CardDialog()
{
    delete m_person;
}

void CardDialog::setupUi()
{
    setMinimumSize(450, 600);
    setStyleSheet("background-color: #f5f5f5;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Имя
    m_nameLabel = new QLabel(m_person->getName());
    QFont nameFont = m_nameLabel->font();
    nameFont.setPointSize(22);
    nameFont.setBold(true);
    m_nameLabel->setFont(nameFont);
    m_nameLabel->setAlignment(Qt::AlignCenter);
    m_nameLabel->setStyleSheet("margin-top: 10px; color: #2c3e50;");
    mainLayout->addWidget(m_nameLabel);

    // Тип
    m_typeLabel = new QLabel(m_person->getType());
    QFont typeFont = m_typeLabel->font();
    typeFont.setPointSize(12);
    typeFont.setItalic(true);
    m_typeLabel->setFont(typeFont);
    m_typeLabel->setAlignment(Qt::AlignCenter);
    m_typeLabel->setStyleSheet("color: #7f8c8d; margin-bottom: 10px;");
    mainLayout->addWidget(m_typeLabel);

    // Картинка
    m_imageLabel = new QLabel();
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setFixedSize(200, 200);
    m_imageLabel->setStyleSheet("border: 2px solid #bdc3c7; border-radius: 10px; background-color: white;");
    mainLayout->addWidget(m_imageLabel, 0, Qt::AlignCenter);

    // Атрибут (стихия/редкость)
    m_attributeLabel = new QLabel();
    m_attributeLabel->setAlignment(Qt::AlignCenter);
    QFont attrFont = m_attributeLabel->font();
    attrFont.setPointSize(11);
    m_attributeLabel->setFont(attrFont);
    mainLayout->addWidget(m_attributeLabel);

    // HP
    m_healthLabel = new QLabel(QString("❤️ Здоровье: %1").arg(m_person->getHealth()));
    m_healthLabel->setAlignment(Qt::AlignCenter);
    QFont healthFont = m_healthLabel->font();
    healthFont.setPointSize(13);
    healthFont.setBold(true);
    m_healthLabel->setFont(healthFont);

    if (dynamic_cast<MagP*>(m_person)) {
        m_healthLabel->setStyleSheet("color: #27ae60; margin: 5px;");
    } else if (dynamic_cast<VragP*>(m_person)) {
        m_healthLabel->setStyleSheet("color: #e74c3c; margin: 5px;");
    }
    mainLayout->addWidget(m_healthLabel);

    // Мана/Урон
    m_manaOrDamageLabel = new QLabel();
    m_manaOrDamageLabel->setAlignment(Qt::AlignCenter);
    QFont mdFont = m_manaOrDamageLabel->font();
    mdFont.setPointSize(13);
    mdFont.setBold(true);
    m_manaOrDamageLabel->setFont(mdFont);

    if (MagP* mag = dynamic_cast<MagP*>(m_person)) {
        m_manaOrDamageLabel->setText(QString("💙 Мана: %1").arg(mag->getMana()));
        m_manaOrDamageLabel->setStyleSheet("color: #2980b9; margin: 5px;");
        m_attributeLabel->setText(QString("✨ Стихия: %1").arg(mag->getElement()));

        if (mag->getElement() == "Огонь") {
            m_attributeLabel->setStyleSheet("color: #e67e22;");
        } else if (mag->getElement() == "Вода") {
            m_attributeLabel->setStyleSheet("color: #3498db;");
        } else if (mag->getElement() == "Земля") {
            m_attributeLabel->setStyleSheet("color: #27ae60;");
        } else {
            m_attributeLabel->setStyleSheet("color: #2c3e50;");
        }
    } else if (VragP* vrag = dynamic_cast<VragP*>(m_person)) {
        m_manaOrDamageLabel->setText(QString("⚔️ Урон: %1").arg(vrag->getDamage()));
        m_manaOrDamageLabel->setStyleSheet("color: #d35400; margin: 5px;");
        m_attributeLabel->setText(QString("🏷️ Редкость: %1").arg(vrag->getRarity()));

        if (vrag->getRarity() == "Редкий") {
            m_attributeLabel->setStyleSheet("color: #8e44ad; font-weight: bold;");
        } else if (vrag->getRarity() == "Обычный") {
            m_attributeLabel->setStyleSheet("color: #2ecc71;");
        } else if (vrag->getRarity() == "Легенда") {
            m_attributeLabel->setStyleSheet("color: #f1c40f; font-weight: bold;");
        } else {
            m_attributeLabel->setStyleSheet("color: #7f8c8d;");
        }
    }
    mainLayout->addWidget(m_manaOrDamageLabel);

    // Броня
    Armor armor = m_person->getArmor();
    m_armorLabel = new QLabel(QString("🛡️ Броня: Шлем:%1 | Кираса:%2 | Сапоги:%3")
                              .arg(armor.helmet).arg(armor.chestplate).arg(armor.boots));
    m_armorLabel->setAlignment(Qt::AlignCenter);
    m_armorLabel->setStyleSheet("color: #34495e; margin-top: 10px;");
    mainLayout->addWidget(m_armorLabel);

    mainLayout->addStretch();

    // Кнопки
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    m_printButton = new QPushButton("Печать (удалить)");
    m_cancelButton = new QPushButton("Отмена");
    m_saveImageButton = new QPushButton("Сохранить картинку");

    m_printButton->setStyleSheet("background-color: #e74c3c; color: white; padding: 8px; border-radius: 5px;");
    m_cancelButton->setStyleSheet("background-color: #95a5a6; color: white; padding: 8px; border-radius: 5px;");
    m_saveImageButton->setStyleSheet("background-color: #3498db; color: white; padding: 8px; border-radius: 5px;");

    buttonLayout->addWidget(m_printButton);
    buttonLayout->addWidget(m_cancelButton);
    buttonLayout->addWidget(m_saveImageButton);
    mainLayout->addLayout(buttonLayout);

    // Выбор режима картинки
    QHBoxLayout* imageModeLayout = new QHBoxLayout();
    QPushButton* staticBtn = new QPushButton("Статичная");
    QPushButton* randomBtn = new QPushButton("Рандомная");
    QPushButton* uniqueBtn = new QPushButton("Уникальная");

    staticBtn->setStyleSheet("background-color: #ecf0f1; padding: 5px;");
    randomBtn->setStyleSheet("background-color: #ecf0f1; padding: 5px;");
    uniqueBtn->setStyleSheet("background-color: #ecf0f1; padding: 5px;");

    connect(staticBtn, &QPushButton::clicked, this, [this]() { updateImage(1); });
    connect(randomBtn, &QPushButton::clicked, this, [this]() { updateImage(2); });
    connect(uniqueBtn, &QPushButton::clicked, this, [this]() { updateImage(3); });

    imageModeLayout->addWidget(staticBtn);
    imageModeLayout->addWidget(randomBtn);
    imageModeLayout->addWidget(uniqueBtn);
    mainLayout->addLayout(imageModeLayout);

    connect(m_printButton, &QPushButton::clicked, this, &CardDialog::onPrintClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &CardDialog::onCancelClicked);
    connect(m_saveImageButton, &QPushButton::clicked, this, &CardDialog::onSaveImageClicked);
}

void CardDialog::updateImage(int mode)
{
    m_imageMode = mode;
    if (mode == 1) {
        loadStaticImage();
    } else if (mode == 2) {
        loadRandomImage();
    } else if (mode == 3) {
        loadUniqueImage();
    }
}

void CardDialog::loadStaticImage()
{
    QString imagePath = QString("resources/%1.png").arg(dynamic_cast<MagP*>(m_person) ? "mag" : "vrag");

    if (QFileInfo::exists(imagePath)) {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            m_imageLabel->setPixmap(pixmap.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            return;
        }
    }
    m_imageLabel->setText("Изображение\nне найдено");
    m_imageLabel->setStyleSheet("border: 2px solid #bdc3c7; border-radius: 10px; background-color: #ecf0f1; color: #7f8c8d;");
    m_imageLabel->setAlignment(Qt::AlignCenter);
}

void CardDialog::loadRandomImage()
{
    QString folder = dynamic_cast<MagP*>(m_person) ? "mag_res" : "vrag_res";
    QDir dir(folder);

    if (!dir.exists()) {
        dir.mkpath(".");
        loadStaticImage();
        return;
    }

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    QStringList files = dir.entryList(filters, QDir::Files);

    if (files.isEmpty()) {
        loadStaticImage();
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(files.size());
    QString imagePath = folder + "/" + files[randomIndex];

    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        m_imageLabel->setPixmap(pixmap.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        loadStaticImage();
    }
}

void CardDialog::loadUniqueImage()
{
    QString folder = dynamic_cast<MagP*>(m_person) ? "mag_res" : "vrag_res";
    QDir dir(folder);

    if (!dir.exists()) {
        dir.mkpath(".");
        loadStaticImage();
        return;
    }

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    QStringList files = dir.entryList(filters, QDir::Files);

    for (const QString& file : files) {
        QString fullPath = folder + "/" + file;
        if (!m_usedImages.contains(fullPath)) {
            m_usedImages.insert(fullPath);
            QPixmap pixmap(fullPath);
            if (!pixmap.isNull()) {
                m_imageLabel->setPixmap(pixmap.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                return;
            }
        }
    }

    // Если все использованы или нет файлов
    loadRandomImage();
}

void CardDialog::saveCardAsImage()
{
    // Создаём скриншот виджета без кнопок
    QPixmap screenshot(this->size());
    this->render(&screenshot);

    // Обрезаем кнопки
    QPixmap cardOnly = screenshot.copy(0, 0, width(), height() - 100);

    QString filename = QFileDialog::getSaveFileName(this,
        "Сохранить карточку",
        QString("%1_card.png").arg(m_person->getName()),
        "PNG Image (*.png);;JPEG Image (*.jpg)");

    if (!filename.isEmpty()) {
        cardOnly.save(filename);
        QMessageBox::information(this, "Успех", "Карточка сохранена");
    }
}

void CardDialog::onPrintClicked()
{
    emit personRemoved();
}

void CardDialog::onCancelClicked()
{
    reject();
}

void CardDialog::onSaveImageClicked()
{
    saveCardAsImage();
}