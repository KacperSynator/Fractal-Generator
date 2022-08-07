#include "gui.h"

void Gui::SetupCentralWidget() {
    grid_->addWidget(image_, 1, 0, 1, 1);
    grid_->addWidget(browse_button_, 0, 0, 1, 1);

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
    std::cout << kTestFilePath << " \n";
    QWidget::connect(browse_button_, &QPushButton::released, this, &Gui::BrowseFile);
    QImage img{kTestFilePath.c_str()};
    image_->setPixmap(QPixmap::fromImage(img));
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
}

void swap(Gui& lhs, Gui& rhs) noexcept {
    lhs.swap(rhs);
}

Gui::~Gui() {
    delete image_;
    delete browse_button_;
    delete central_;
    delete grid_;
}

void Gui::BrowseFile() {
    auto file = QFileDialog::getOpenFileName(this, tr("Open File"), kDataDirPath.c_str(), "Images (*.bmp)");
    if (!file.isEmpty()) {
        QImage img{file};
        image_->setPixmap(QPixmap::fromImage(img));
    }
}
