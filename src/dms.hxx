#ifndef msys_dms_hxx
#define msys_dms_hxx

#include "load.hxx"
#include <iostream>

struct sqlite3;

namespace desres { namespace msys {

    LoadIteratorPtr DmsIterator(const std::string& path, 
                             bool structure_only=false);

    SystemPtr ImportDMS(const std::string& path, bool structure_only=false);

    SystemPtr ImportDMSFromBytes( const char* bytes, int64_t len,
                                  bool structure_only=false);

    void ExportDMS(SystemPtr sys, const std::string& path, 
                   Provenance const& provenance);

    void ExportDMSMany(std::vector<SystemPtr> const& cts,
                       std::string const& path,
                       Provenance const& provenance);

    namespace sqlite {
        SystemPtr ImportDMS(sqlite3* db, bool structure_only=false);
        void ExportDMS(SystemPtr sys, sqlite3* db,
                   Provenance const& provenance);
    }

}}

#endif
