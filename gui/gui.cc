#include "gui.h"

void Gui::SetupCentralWidget() {
    grid_->addWidget(image_, 3, 0, 1, 5);
    grid_->addWidget(browse_button_, 0, 0, 1, 1);
    grid_->addWidget(color_button_, 0, 1, 1, 2);
    grid_->addWidget(color_range_slider_, 1, 1, 1, 1);
    grid_->addWidget(color_slider_value_, 1, 2, 1, 1);
    grid_->addWidget(add_color_range_button_, 2, 1, 1, 1);
    grid_->addWidget(pop_color_range_button_, 2, 2, 1, 1);
    grid_->addWidget(generate_button_, 1, 0, 1, 1);
    grid_->addWidget(fractal_text_, 0, 3, 1, 1);
    grid_->addWidget(fractal_box_, 0, 4, 1, 1);
    grid_->addWidget(coloring_text_, 1, 3, 1, 1);
    grid_->addWidget(coloring_box_, 1, 4, 1, 1);
    grid_->addWidget(image_text_, 2, 3, 1, 1);
    grid_->addWidget(image_box_, 2, 4, 1, 1);
   

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
    CreateFractalGenerator();
    SetupColorRangeSlider();
    SetupSignals();
    FillComboBoxes();
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
    QWidget::connect(generate_button_, &QPushButton::released, this, &Gui::GenerateFractal);
    QWidget::connect(color_button_, &QPushButton::released, this, &Gui::ShowColorDialog);
    QWidget::connect(add_color_range_button_, &QPushButton::released, this, &Gui::AddColorRange);
    QWidget::connect(pop_color_range_button_, &QPushButton::released, this, &Gui::PopColorRange);
    QWidget::connect(color_range_slider_, &QSlider::valueChanged, this, &Gui::UpdateColorRangeValue);
    QWidget::connect(color_dialog_, &QColorDialog::colorSelected, this, &Gui::ChangeColorButton);
}

void Gui::FillComboBoxes() {
    fractal_box_->addItem("Mandelbrot", 'M');
    coloring_box_->addItem("Histogram", 'H');
    image_box_->addItem("Bitmap", 'B');
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

void AddQColorRange(const float& range, const QColor& qcolor, std::unique_ptr< FractalGenerator >& fg) {
    int r, g, b;
    qcolor.getRgb(&r, &g, &b);
    std:: cout << r << " " << g << " " << b << std::endl;
    fg->AddColorRange(range, r, g, b);
}

void Gui::AddColorRange() {
    auto range = color_slider_value_->text().toFloat();
    AddQColorRange(range, color_dialog_->selectedColor(), fg_);
}

void Gui::PopColorRange() {
    fg_->PopColorRange();
}
void Gui::CreateFractalGenerator() {
   fg_.reset();
   fg_ = std::make_unique<FractalGenerator>(fgb_
                                                .BitmapImage()
                                                .HistColoring()
                                                .MandelbrotFractal());
}


void Gui::GenerateFractal() {
    fg_->AddZoom(Zoom{kZoomStartX, kZoomStartY, kZoomStartSCale});
    fg_->Generate(kDataDirPath / kOutputFileName);
    LoadImage(kOutputFilePath.c_str());
}

void Gui::SetupColorRangeSlider() {
    color_range_slider_->setMaximumWidth(kColorRangeSliderWidth);
    color_range_slider_->setMaximum(kColorRangeSliderMaxVal);
    color_range_slider_->setTickPosition(QSlider::TicksBothSides);
}

void Gui::UpdateColorRangeValue() {
    float value = color_range_slider_->value();
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value / kColorRangeSliderMaxVal;
    color_slider_value_->setText(oss.str().c_str());
}
