#include "editdialog.h"
#include <QMessageBox>
#include <QFormLayout>

EditDialog::EditDialog(Person* person, QWidget *parent)
    : QDialog(parent), m_person(person), m_isNew(person == nullptr)
{
    setupUi();
    if (!m_isNew) {
        loadFromPerson();
    }
    setWindowTitle(m_isNew ? "Добавление персонажа" : "Редактирование персонажа");
}

EditDialog::~EditDialog()
{
    if (m_isNew && m_person) {
        delete m_person;
    }
}

void EditDialog::setupUi()
{
    setMinimumSize(400, 500);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* formLayout = new QFormLayout();

    // Общие поля
    m_codeEdit = new QLineEdit();
    m_nameEdit = new QLineEdit();
    m_healthSpin = new QSpinBox();
    m_healthSpin->setRange(1, 10000);
    m_helmetSpin = new QSpinBox();
    m_helmetSpin->setRange(0, 1000);
    m_chestplateSpin = new QSpinBox();
    m_chestplateSpin->setRange(0, 1000);
    m_bootsSpin = new QSpinBox();
    m_bootsSpin->setRange(0, 1000);
    m_typeCombo = new QComboBox();
    m_typeCombo->addItems({"Маг", "Враг"});

    formLayout->addRow("Код:", m_codeEdit);
    formLayout->addRow("Имя:", m_nameEdit);
    formLayout->addRow("Здоровье:", m_healthSpin);
    formLayout->addRow("Тип:", m_typeCombo);
    formLayout->addRow("Броня - Шлем:", m_helmetSpin);
    formLayout->addRow("Броня - Кираса:", m_chestplateSpin);
    formLayout->addRow("Броня - Сапоги:", m_bootsSpin);

    // Специфичные поля для мага
    m_magWidget = new QWidget();
    QFormLayout* magLayout = new QFormLayout(m_magWidget);
    m_elementEdit = new QLineEdit();
    m_manaSpin = new QSpinBox();
    m_manaSpin->setRange(0, 10000);
    magLayout->addRow("Стихия:", m_elementEdit);
    magLayout->addRow("Мана:", m_manaSpin);
    formLayout->addRow(m_magWidget);

    // Специфичные поля для врага
    m_vragWidget = new QWidget();
    QFormLayout* vragLayout = new QFormLayout(m_vragWidget);
    m_rarityEdit = new QLineEdit();
    m_damageSpin = new QSpinBox();
    m_damageSpin->setRange(0, 10000);
    vragLayout->addRow("Редкость:", m_rarityEdit);
    vragLayout->addRow("Урон:", m_damageSpin);
    formLayout->addRow(m_vragWidget);

    mainLayout->addLayout(formLayout);

    // Кнопки
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* saveBtn = new QPushButton("Сохранить");
    QPushButton* cancelBtn = new QPushButton("Отмена");
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(cancelBtn);
    mainLayout->addLayout(buttonLayout);

    connect(m_typeCombo, &QComboBox::currentIndexChanged, this, &EditDialog::onTypeChanged);
    connect(saveBtn, &QPushButton::clicked, this, &EditDialog::onSaveClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &EditDialog::onCancelClicked);

    onTypeChanged(0);
}

void EditDialog::onTypeChanged(int index)
{
    m_magWidget->setVisible(index == 0);
    m_vragWidget->setVisible(index == 1);
}

void EditDialog::loadFromPerson()
{
    if (!m_person) return;

    m_codeEdit->setText(QString::number(m_person->getCode()));
    m_nameEdit->setText(m_person->getName());
    m_healthSpin->setValue(m_person->getHealth());
    Armor armor = m_person->getArmor();
    m_helmetSpin->setValue(armor.helmet);
    m_chestplateSpin->setValue(armor.chestplate);
    m_bootsSpin->setValue(armor.boots);

    if (MagP* mag = dynamic_cast<MagP*>(m_person)) {
        m_typeCombo->setCurrentIndex(0);
        m_elementEdit->setText(mag->getElement());
        m_manaSpin->setValue(mag->getMana());
    } else if (VragP* vrag = dynamic_cast<VragP*>(m_person)) {
        m_typeCombo->setCurrentIndex(1);
        m_rarityEdit->setText(vrag->getRarity());
        m_damageSpin->setValue(vrag->getDamage());
    }
}

void EditDialog::saveToPerson()
{
    int code = m_codeEdit->text().toInt();
    QString name = m_nameEdit->text();
    int health = m_healthSpin->value();
    Armor armor(m_helmetSpin->value(), m_chestplateSpin->value(), m_bootsSpin->value());

    if (m_typeCombo->currentIndex() == 0) {
        // Маг
        QString element = m_elementEdit->text();
        int mana = m_manaSpin->value();
        if (m_isNew) {
            m_person = new MagP(code, name, element, mana, health, armor);
        } else if (MagP* mag = dynamic_cast<MagP*>(m_person)) {
            mag->setCode(code);
            mag->setName(name);
            mag->setHealth(health);
            mag->setArmor(armor);
            mag->setElement(element);
            mag->setMana(mana);
        }
    } else {
        // Враг
        QString rarity = m_rarityEdit->text();
        int damage = m_damageSpin->value();
        if (m_isNew) {
            m_person = new VragP(code, name, rarity, damage, health, armor);
        } else if (VragP* vrag = dynamic_cast<VragP*>(m_person)) {
            vrag->setCode(code);
            vrag->setName(name);
            vrag->setHealth(health);
            vrag->setArmor(armor);
            vrag->setRarity(rarity);
            vrag->setDamage(damage);
        }
    }
}

void EditDialog::onSaveClicked()
{
    if (m_codeEdit->text().isEmpty() || m_nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Код и имя обязательны для заполнения");
        return;
    }

    if (m_typeCombo->currentIndex() == 0) {
        if (m_elementEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Стихия обязательна для мага");
            return;
        }
    } else {
        if (m_rarityEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Редкость обязательна для врага");
            return;
        }
    }

    saveToPerson();
    accept();
}

void EditDialog::onCancelClicked()
{
    reject();
}

Person* EditDialog::getPerson() const
{
    return m_person;
}