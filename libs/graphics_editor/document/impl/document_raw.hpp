#ifndef __DOCUMENT_RAW__
#define __DOCUMENT_RAW__

#include <idocument.hpp>
#include <iprimitive.hpp>

#include <memory>
#include <vector>

class DocumentRaw : public IDocument {
private:
  std::vector<std::unique_ptr<IPrimitive>> primitives_storage;

public:
  void import_from_file(std::string_view doc_path) override;
  void export_to_file(std::string_view doc_path) override;

  void add_primitive(std::unique_ptr<IPrimitive>) override;
  void remove_primitive(std::unique_ptr<IPrimitive>) override;
};

#endif /* __DOCUMENT_RAW__ */
