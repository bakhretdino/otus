#ifndef __DOCUMENT_FACTORY__
#define __DOCUMENT_FACTORY__

#include <document_types.hpp>
#include <idocument.hpp>

#include <memory>
#include <stdexcept>

namespace Factory::Document {

std::unique_ptr<IDocument> create(DocumentTypes type);

} // namespace Factory::Document

#endif /* __DOCUMENT_FACTORY__ */
