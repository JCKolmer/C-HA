#include "video.h"

Video::Video(FileContent &&content, resolution_t resolution, double duration)
    : File{std::move(content)}, resolution{resolution}, duration{duration} {}

// TODO implement get_type function
std::string_view File::get_type() const {
  std::string_view type {"VID"};
  return type;
}

size_t Video::get_raw_size() const {
  // TODO size of raw 30 FPS RGB color video
  return 0;
}

auto Video::get_resolution() const -> resolution_t { return this->resolution; }

double Video::get_duration() const { return this->duration; }

// TODO implement content update function
