#if !defined(OBJPARSER_HPP)
#define OBJPARSER_HPP

#include <memory>
#include <string>
#include <istream>
#include "Geometry.hpp"

namespace cg
{
namespace objparser
{
    std::unique_ptr<trimesh> parse(std::istream &in);

    // Convenience function to use filename string instead of explicit stream
    std::unique_ptr<trimesh> parse_file(const std::string &fname);

} // end namespace objparser
} // end namespace cg

#endif // end include guard
