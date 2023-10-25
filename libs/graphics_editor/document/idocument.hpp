#ifndef __IDOCUMENT__
#define __IDOCUMENT__

#include <memory>
#include <string_view>

#include <iprimitive.hpp>

class IDocument {
public:
  virtual void import_from_file(std::string_view doc_path) = 0;
  virtual void export_to_file(std::string_view doc_path) = 0;

  virtual void add_primitive(std::unique_ptr<IPrimitive>) = 0;
  virtual void remove_primitive(std::unique_ptr<IPrimitive>) = 0;

  virtual ~IDocument() = default;
};

#endif /* __IDOCUMENT__ */
