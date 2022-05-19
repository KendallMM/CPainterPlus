#include <QPushButton>
#include <QRadioButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "dialog_windows.h"


/**
 * @brief CanvasSizeDialog::CanvasSizeDialog - Dialogue for creating a new
 *                                             canvas
 */
CanvasSizeDialog::CanvasSizeDialog(QWidget* parent, const char* name, int width, int height)
    :QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(createSpinBoxes(width,height));
    setLayout(layout);

    setWindowTitle(tr(name));
}

/**
 * @brief NewCanvasDialog::createSpinBoxes - Create the QSpinBoxes for the dialog
 *                                           box as well as the buttons
 */
QGroupBox* CanvasSizeDialog::createSpinBoxes(int width, int height)
{
    QGroupBox *spinBoxesGroup = new QGroupBox(tr("Image Size"), this);

    // the width field
    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setRange(MIN_IMG_WIDTH, MAX_IMG_WIDTH);
    widthSpinBox->setSingleStep(1);
    widthSpinBox->setValue(width);
    widthSpinBox->setSuffix("px");

    // the height field
    heightSpinBox = new QSpinBox(this);
    heightSpinBox->setRange(MIN_IMG_HEIGHT, MAX_IMG_HEIGHT);
    heightSpinBox->setSingleStep(1);
    heightSpinBox->setValue(height);
    heightSpinBox->setSuffix("px");

    // the buttons
    QPushButton *okButton = new QPushButton(tr("OK"), this);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    // put it all together
    QFormLayout *spinBoxLayout = new QFormLayout(spinBoxesGroup);
    spinBoxLayout->addRow(tr("Width: "), widthSpinBox);
    spinBoxLayout->addRow(tr("Height: "), heightSpinBox);
    spinBoxLayout->addRow(okButton);
    spinBoxLayout->addRow(cancelButton);
    spinBoxesGroup->setLayout(spinBoxLayout);

    return spinBoxesGroup;
}
