#include "filecontent.h"

// TODO implement constructors
FileContent::FileContent(const std::string& content) : content_(std::make_shared<std::string> (content)) {};
   
FileContent::FileContent(std::string&& content) : content_{std::make_shared<std::string> (content)} {};

FileContent::FileContent(const char* content) : content_{std::make_shared<std::string> (content)} {};

// TODO implement member functions

std::size_t FileContent::get_size() const
{
    return content_->size();
}
 
std::shared_ptr<const std::string> FileContent::get() const
{
    return content_;
}