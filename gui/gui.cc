#include "gui.h"

void Gui::SetupCentralWidget() {
    grid_->addWidget(image_, 3, 0, 1, 7);
    grid_->addWidget(browse_button_, 0, 0, 1, 1);
    grid_->addWidget(save_as_button_, 1, 0, 1, 1);
    grid_->addWidget(generate_button_, 2, 0, 1, 1);
    grid_->addWidget(color_button_, 0, 1, 1, 2);
    grid_->addWidget(color_range_slider_, 1, 1, 1, 2);
    grid_->addWidget(color_slider_value_, 1, 2, 1, 1, Qt::AlignRight);
    grid_->addWidget(add_color_range_button_, 2, 1, 1, 1);
    grid_->addWidget(pop_color_range_button_, 2, 2, 1, 1);
    grid_->addWidget(zoom_offset_, 0, 3, 1, 2, Qt::AlignCenter);
    grid_->addWidget(zoom_scale_slider_, 1, 3, 1, 2);
    grid_->addWidget(add_zoom_button_, 2, 3, 1, 1);
    grid_->addWidget(pop_zoom_button_, 2, 4, 1, 1);
    grid_->addWidget(fractal_text_, 0, 5, 1, 1, Qt::AlignRight);
    grid_->addWidget(fractal_box_, 0, 6, 1, 1);
    grid_->addWidget(coloring_text_, 1, 5, 1, 1, Qt::AlignRight);
    grid_->addWidget(coloring_box_, 1, 6, 1, 1);
    grid_->addWidget(image_text_, 2, 5, 1, 1, Qt::AlignRight);
    grid_->addWidget(image_box_, 2, 6, 1, 1);

    grid_->setColumnMinimumWidth(5, 50);
    central_->setLayout(grid_);

    setCentralWidget(central_);
}

Gui::GuiPtr Gui::CreateGui(QWidget* parent) {
    auto gui = std::make_unique<Gui>(parent);

    gui->CreateFractalGenerator();
    gui->SetupColorRangeSlider();
    gui->SetupZoomScaleSlider();
    gui->SetupSignals();
    gui->FillComboBoxes();
    gui->LoadImage(kTestFilePath.c_str());
    gui->SetupCentralWidget();
    gui->setWindowTitle("Fractal Generator");

    gui->show();
    return gui;
}

Gui::Gui(QWidget* parent) : QMainWindow(parent) { 
    color_dialog_->setOption(QColorDialog::DontUseNativeDialog);
    zooms_.Add(Zoom{kZoomStartX, kZoomStartY, kZoomStartSCale});
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

void swap(Gui& lhs, Gui& rhs) noexcept { lhs.swap(rhs); }

Gui::~Gui() { qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly)); }

void Gui::SetupSignals() {
    QWidget::connect(browse_button_, &QPushButton::released, this, &Gui::BrowseFile);
    QWidget::connect(save_as_button_, &QPushButton::released, this, &Gui::SaveAs);
    QWidget::connect(generate_button_, &QPushButton::released, this, &Gui::GenerateFractal);
    QWidget::connect(color_button_, &QPushButton::released, this, &Gui::ShowColorDialog);
    QWidget::connect(add_color_range_button_, &QPushButton::released, this, &Gui::AddColorRange);
    QWidget::connect(pop_color_range_button_, &QPushButton::released, this, &Gui::PopColorRange);
    QWidget::connect(color_range_slider_, &QSlider::valueChanged, this, &Gui::UpdateColorRangeValue);
    QWidget::connect(color_range_slider_, &QSlider::sliderReleased, this, &Gui::ValidateColorRangeSlider);
    QWidget::connect(zoom_scale_slider_, &QSlider::valueChanged, this, &Gui::UpdateZoomScaleValue);
    QWidget::connect(color_dialog_, &QColorDialog::colorSelected, this, &Gui::ChangeColorButton);
    QWidget::connect(add_zoom_button_, &QPushButton::released, this, &Gui::AddZoom);
    QWidget::connect(pop_zoom_button_, &QPushButton::released, this, &Gui::PopZoom);
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
    auto file = QFileDialog::getOpenFileName(this, tr("Open File"), kDataDirPath.c_str(), tr("Images (*.bmp)"),
                                             nullptr ,QFileDialog::DontUseNativeDialog);
    if (!file.isEmpty()) {
        LoadImage(file);
    }
}

void WriteLabelImageToFile(QLabel* image, QString file, std::string image_type) {
    image->pixmap()->save(file, image_type.c_str());
}

void Gui::SaveAs() {
    auto file = QFileDialog::getSaveFileName(this, tr("Save file"), kDataDirPath.c_str(), tr("Images (*.bmp)"),
                                             nullptr ,QFileDialog::DontUseNativeDialog);
    if (!file.isEmpty()) {
        WriteLabelImageToFile(image_, file, "BMP");
    }
}

void Gui::ShowColorDialog() { color_dialog_->show(); }

void Gui::ChangeColorButton() {
    QPalette pal = color_button_->palette();
    pal.setColor(QPalette::Button, color_dialog_->selectedColor());
    color_button_->setAutoFillBackground(true);
    color_button_->setPalette(pal);
    color_button_->update();
    // qDebug() << color_dialog_->selectedColor();
}

void AddQColorRange(const float& range, const QColor& qcolor, std::unique_ptr<FractalGenerator>& fg) {
    int r, g, b;
    qcolor.getRgb(&r, &g, &b);
    std::cout << r << " " << g << " " << b << std::endl;
    fg->AddColorRange(range, r, g, b);
}

void Gui::AddColorRange() {
    auto range = color_slider_value_->text().toFloat();
    color_ranges_.emplace_back(range);
    AddQColorRange(range, color_dialog_->selectedColor(), fg_);
}

void Gui::PopColorRange() {
    if (color_ranges_.empty()) return;
    fg_->PopColorRange();
    color_ranges_.pop_back();
    color_range_slider_->setValue(color_ranges_.back() * kColorRangeSliderMaxVal);
}
void Gui::CreateFractalGenerator() {
    fg_.reset();
    fg_ = std::make_unique<FractalGenerator>(fgb_
                                                 .BitmapImage()
                                                 .HistColoring()
                                                 .MandelbrotFractal());
}

void Gui::GenerateFractal() {
    if (color_ranges_.empty()) {
        error_box_->setText("Error: color ranges are not specified!");
        error_box_->exec();
        return;
    }

    if (color_ranges_.back() != 1.0) {
        error_box_->setText("Error: last color range is not equal to 1.0!");
        error_box_->exec();
        return;
    }

    fg_->SetZooms(zooms_);
    fg_->Generate(kDataDirPath / kOutputFileName);
    LoadImage(kOutputFilePath.c_str());
}

void SetupSlider(QSlider* slider, int width, int max_val, QSlider::TickPosition tick_pos) {
    slider->setMaximumWidth(width);
    slider->setMaximum(max_val);
    slider->setTickPosition(tick_pos);
}

void Gui::SetupColorRangeSlider() {
    SetupSlider(color_range_slider_, kColorRangeSliderWidth, kColorRangeSliderMaxVal, QSlider::TicksBothSides);
}

void Gui::SetupZoomScaleSlider() {
    SetupSlider(zoom_scale_slider_, kZoomScaleSliderWidth, kZoomScaleSliderMaxVal, QSlider::TicksBothSides);
}

void Gui::UpdateColorRangeValue() {
    float value = color_range_slider_->value();

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value / kColorRangeSliderMaxVal;
    color_slider_value_->setText(oss.str().c_str());
}

void Gui::ValidateColorRangeSlider() {
    float value = color_range_slider_->value();

    if (color_ranges_.empty() && value != 0) {
        color_range_slider_->setValue(0);
        return;
    }

    float normalized_value = value / kColorRangeSliderMaxVal;

    if (!color_ranges_.empty() && normalized_value <= color_ranges_.back()) {
        color_range_slider_->setValue(color_ranges_.back() * kColorRangeSliderMaxVal);
        return;
    }
}

void SetZoomOffsetText(QLabel* text_label, const Zoom& zoom) {
    std::ostringstream oss;
    oss << "Zoom: x: " << zoom.x << " y: " << zoom.y << " scale: " << zoom.scale;
    text_label->setText(oss.str().c_str());
}

void Gui::UpdateZoomScaleValue() {
    float value = zoom_scale_slider_->value();

    current_zoom_.scale = value / kZoomScaleSliderMaxVal;
    SetZoomOffsetText(zoom_offset_, current_zoom_);
}

void Gui::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto img_pixel = (event->localPos() - image_->pos()).toPoint();
        // qDebug() << img_pixel;
        if (img_pixel.x() >= 0 && img_pixel.x() <= kImgWidth &&
            img_pixel.y() >= 0 && img_pixel.y() <= kImgHeight) {
            
            current_zoom_.x = img_pixel.x();
            current_zoom_.y = img_pixel.y();
            SetZoomOffsetText(zoom_offset_, current_zoom_);
        }
    }
}

void Gui::AddZoom() {
    if (current_zoom_.x > 0) {
        qDebug() << current_zoom_.x << " " << current_zoom_.y << " " << current_zoom_.scale;
        zooms_.Add(current_zoom_);
    }
}

void Gui::PopZoom() {
    if (zooms_.Size() <= 1) return;

    zooms_.Pop();
}

