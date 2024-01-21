#include <document_factory.hpp>
#include <primitives.hpp>

#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<IDocument> doc =
      Factory::Document::create(DocumentTypes::Raw);

  std::unique_ptr<IPrimitive> circle =
      std::make_unique<Circle>(1.0, 2.1, Colour::Red, 5.5);
  circle.get()->draw();
  doc.get()->add_primitive(std::move(circle));

  doc.get()->export_to_file("file");

  return 0;
}
