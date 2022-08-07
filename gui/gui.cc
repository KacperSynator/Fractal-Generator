#include "gui.h"

void Gui::SetupCentralWidget() {
    grid_->addWidget(image_, 1, 0, 1, 2);
    grid_->addWidget(browse_button_, 0, 0, 1, 1);
    grid_->addWidget(color_button_, 0, 1, 1, 1);

    central_->setLayout(grid_);
    
    setCentralWidget(central_);
}

Gui::GuiPtr Gui::CreateGui(QWidget* parent) {
    auto gui = std::make_unique<Gui>(parent);
    
    gui->SetupCentralWidget();
    gui->setWindowTitle("Fractal Generator");

    gui->show();
    return gui;
}

Gui::Gui(QWidget* parent) : QMainWindow(parent) {
    SetupSignals();
    LoadImage(kTestFilePath.c_str());
}

Gui::Gui(Gui&& other) noexcept {
    using std::exchange;

    grid_ = exchange(other.grid_, nullptr);
    central_ = exchange(other.central_, nullptr);
    image_ = exchange(other.image_, nullptr);
    browse_button_ = exchange(other.browse_button_, nullptr);
}

Gui& Gui::operator=(Gui&& other) noexcept {
    Gui copy{std::move(other)};
    copy.swap(*this);
    return *this;
}

void Gui::swap(Gui& other) noexcept {
    using std::swap;

    swap(grid_, other.grid_);
    swap(central_, other.central_);
    swap(image_, other.image_);
    swap(browse_button_, other.browse_button_);
    swap(color_button_, other.color_button_);
    swap(color_dialog_, other.color_dialog_);
}

void swap(Gui& lhs, Gui& rhs) noexcept {
    lhs.swap(rhs);
}

Gui::~Gui() {
    delete image_;
    delete browse_button_;
    delete color_button_;
    delete color_dialog_;
    delete grid_;
    delete central_;
}

void Gui::SetupSignals() {
    QWidget::connect(browse_button_, &QPushButton::released, this, &Gui::BrowseFile);
    QWidget::connect(color_button_, &QPushButton::released, this, &Gui::ShowColorDialog);
    QWidget::connect(color_dialog_, &QColorDialog::colorSelected, this, &Gui::ChangeColorButton);
}

void Gui::LoadImage(const QString& file_path) {
    QImage img{file_path};
    image_->setPixmap(QPixmap::fromImage(img));
}

void Gui::BrowseFile() {
    auto file = QFileDialog::getOpenFileName(this, tr("Open File"), kDataDirPath.c_str(), "Images (*.bmp)");
    if (!file.isEmpty()) {
        LoadImage(file);
    }
}

void Gui::ShowColorDialog() {
    color_dialog_->show();
}

void Gui::ChangeColorButton() {
    QPalette pal = color_button_->palette();
    pal.setColor(QPalette::Button, color_dialog_->selectedColor());
    color_button_->setAutoFillBackground(true);
    color_button_->setPalette(pal);
    color_button_->update();
    // qDebug() << color_dialog_->selectedColor();
}
