#include <circle.hpp>
#include <document_raw.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

void DocumentRaw::import_from_file(std::string_view doc_path) {}

void DocumentRaw::export_to_file(std::string_view doc_path) {
  std::ofstream outfile(std::string(doc_path), std::ios::out | std::ios::trunc);

  if (!outfile) {
    std::cerr << "Error: Could not open file for writing.\n";
    return;
  }

  for (const auto &primitive : primitives_storage) {
    /* I don't like this approach.
     * I see 2 option and I don't like either
     * 1. Use std::variant for storing pointers of variant type in the document
     *    - It's not clear how to update variants when new primitive types are
     *      added an elegant way.
     * 2. Store PrimitiveBase pointers in the document.
     *    - It obviously breaks SOLID (all of the principles). */
    if (auto circlePtr = dynamic_cast<Circle *>(primitive.get())) {
      outfile << *circlePtr;
    }
  }
}

void DocumentRaw::add_primitive(std::unique_ptr<IPrimitive> primitive) {
  primitives_storage.push_back(std::move(primitive));
}

void DocumentRaw::remove_primitive(std::unique_ptr<IPrimitive> primitive) {
  auto it = std::find_if(
      primitives_storage.begin(), primitives_storage.end(),
      [&](const std::unique_ptr<IPrimitive> &ptr) { return ptr == primitive; });

  if (it != primitives_storage.end()) {
    primitives_storage.erase(it);
  }
}
