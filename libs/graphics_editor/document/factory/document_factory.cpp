#include <document_factory.hpp>
#include <document_raw.hpp>

std::unique_ptr<IDocument> Factory::Document::create(DocumentTypes type) {
  switch (type) {
  case DocumentTypes::Raw: {
    return std::make_unique<DocumentRaw>();
  }
  default:
    throw std::invalid_argument("Invalid document type");
  }
}
