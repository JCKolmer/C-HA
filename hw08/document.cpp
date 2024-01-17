#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {}

// TODO implement get_type function
std::string_view Document::get_type() const {
  std::string_view type {"DOC"};
  return type;
}


size_t Document::get_raw_size() const {
  // TODO get the document size
  return this->content.get_size();
}

unsigned Document::get_character_count() const {
  const std::string* toAnalyze = this->content.get().get();
  size_t counter = 0;
  for (int i = 0; i < toAnalyze->size();i++)
  {
    if( toAnalyze->at(i) == ' ' || toAnalyze->at(i) == '\n' || toAnalyze->at(i) == '\t' ) {
      continue;
    }
    else {
      counter++;
    }
  }
  return counter;
}

// TODO implement content update function
