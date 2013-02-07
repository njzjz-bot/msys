#include "clone.hxx"
#include "append.hxx"
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

using namespace desres::msys;

namespace {
    /* a predicate that returns true if a term is not in a subset */
    struct BadTerm {
        TermTablePtr _table;
        IdList const& _atmmap;

        BadTerm( TermTablePtr table, IdList const& atmmap ) 
        : _table(table), _atmmap(atmmap) {}
        bool operator()( Id const& id ) {
            IdList atoms = _table->atoms(id);
            for (unsigned i=0; i<atoms.size(); i++) {
                if (bad(_atmmap[atoms[i]])) return true;
            }
            return false;
        }
    };
}

SystemPtr desres::msys::Clone( SystemPtr src, IdList const& atoms ) {

    /* check for duplicates */
    {
        IdList tmp(atoms);
        if (sort_unique(tmp)) MSYS_FAIL("atoms argument contains duplicates");
    }
    SystemPtr dst = System::create();

    /* copy selection macros */
    dst->copySelectionMacros(*src);

    /* Mappings from src ids to dst ids */
    IdList atmmap(src->maxAtomId(), BadId);
    IdList resmap(src->maxResidueId(), BadId);
    IdList chnmap(src->maxChainId(), BadId);
    IdList ctmap(src->maxCtId(), BadId);

    /* copy atom properties */
    Id nprops = src->atomPropCount();
    IdList propmap(nprops);
    for (Id i=0; i<nprops; i++) {
        propmap[i] = dst->addAtomProp(
                src->atomPropName(i), src->atomPropType(i));
    }

    /* copy bond properties */
    Id nbprops = src->bondPropCount();
    IdList bpropmap(nbprops);
    for (Id i=0; i<nbprops; i++) {
        bpropmap[i] = dst->addBondProp(
                src->bondPropName(i), src->bondPropType(i));
    }

    /* Build structure for subset of atoms */
    for (Id i=0; i<atoms.size(); i++) {
        Id srcatm = atoms[i];
        Id srcres = src->atom(srcatm).residue;
        Id srcchn = src->residue(srcres).chain;
        Id srcct  = src->chain(srcchn).ct;

        if (!src->hasAtom(srcatm)) {
            MSYS_FAIL("atoms argument contains deleted atom id " << srcatm);
        }

        Id dstct  = ctmap[srcct];
        Id dstchn = chnmap[srcchn];
        Id dstres = resmap[srcres];

        if (bad(dstres)) {
            if (bad(dstchn)) {
                if (bad(dstct)) {
                    dstct = ctmap[srcct] = dst->addCt();
                    dst->ct(dstct) = src->ct(srcct);
                }
                dstchn = chnmap[srcchn] = dst->addChain(dstct);
                dst->chain(dstchn) = src->chain(srcchn);
                dst->chain(dstchn).ct = dstct;
            }
            dstres = resmap[srcres] = dst->addResidue(dstchn);
            dst->residue(dstres) = src->residue(srcres);
            dst->residue(dstres).chain = dstchn;
        }
        Id dstatm = dst->addAtom(dstres);
        atmmap[srcatm] = dstatm;
        /* Copy built-in properties */
        dst->atom(dstatm) = src->atom(srcatm);
        /* Restore the overwritten residue id */
        dst->atom(dstatm).residue = dstres;
        /* Copy additional atom properties */
        for (Id j=0; j<nprops; j++) {
            dst->atomPropValue(dstatm,propmap[j]) = 
            src->atomPropValue(srcatm, j);
        }
    }

    /* Build bonds whose atoms are fully within the subset */
    for (Id i=0; i<atoms.size(); i++) {
        Id srcatm = atoms[i];
        IdList const& bonds = src->bondsForAtom(srcatm);
        for (Id j=0; j<bonds.size(); j++) {
            bond_t const& srcbond = src->bond(bonds[j]);
            Id srcother = srcbond.other(srcatm);
            Id dstother = atmmap[srcother];
            if (!bad(dstother)) {
                Id dstatm = atmmap[srcatm];
                Id dstbnd = dst->addBond(dstatm, dstother);
                dst->bond(dstbnd).order = srcbond.order;

                /* Copy additional bond properties */
                for (Id k=0; k<nbprops; k++) {
                    dst->bondPropValue(dstbnd,bpropmap[k]) = 
                    src->bondPropValue(bonds[j], k);
                }
            }
        }
    }

    /* Copy glue pairs whose atoms are fully within the subset */
    std::vector<glue_t> glue = src->gluePairs();
    for (Id i=0; i<glue.size(); i++) {
        Id idst = atmmap.at(glue[i].first);
        Id jdst = atmmap.at(glue[i].second);
        if (!bad(idst) && !bad(jdst)) {
            dst->addGluePair(idst,jdst);
        }
    }

    /* Detect when term tables share a ParamTable.  First pass: sort
     * by param table.  */
    typedef std::vector<std::string> StringList;
    typedef boost::unordered_map<ParamTablePtr, StringList> TableMap;
    TableMap tables;
    std::vector<String> tablenames = src->tableNames();
    for (unsigned i=0; i<tablenames.size(); i++) {
        std::string const& name = tablenames[i];
        TermTablePtr srctable = src->table(name);
        tables[srctable->params()].push_back(name);
    }

    /* process the unshared tables. */
    for (TableMap::const_iterator it=tables.begin(); it!=tables.end(); ++it) {
        if (it->second.size()>1) continue;
        std::string const& name = it->second.at(0);
        TermTablePtr srctable = src->table(name);
        TermTablePtr dsttable = dst->addTable(name, srctable->atomCount());
        dsttable->category = srctable->category;
        IdList terms = srctable->terms();
        IdList::iterator iter = std::remove_if( 
                terms.begin(), terms.end(), BadTerm(srctable, atmmap));
        terms.erase(iter, terms.end());
        AppendTerms( dsttable, srctable, atmmap, terms );
    }

    /* process the tables with shared params */
    for (TableMap::const_iterator it=tables.begin(); it!=tables.end(); ++it) {
        StringList const& s = it->second;
        if (it->second.size()<2) continue;
        ParamTablePtr dstparams = ParamTable::create();
        ParamTablePtr srcparams = src->table(s[0])->params();
        IdList src2dst(srcparams->paramCount(), BadId);
        for (unsigned i=0; i<s.size(); i++) {
            std::string const& name = s[i];
            TermTablePtr srctable = src->table(name);
            TermTablePtr dsttable = dst->addTable(name,
                                                  srctable->atomCount(),
                                                  dstparams);
            dsttable->category = srctable->category;

            /* get the terms included in the selection */
            IdList terms = srctable->terms();
            terms.erase(
                    std::remove_if( 
                        terms.begin(), terms.end(), BadTerm(srctable, atmmap)),
                    terms.end());
            /* get the set of parameters referenced by at least one term.
             * The reference counting in ParamTable doesn't help us here
             * because we aren't interested in params that are referenced
             * by tables outside of our System.  However, there is a fair
             * bit of duplication here of logic in append.cxx and that 
             * should be addressed at some point. */
            IdList params;
            for (Id i=0; i<terms.size(); i++) {
                Id p = srctable->param(terms[i]);
                if (!bad(p)) params.push_back(p);
            }
            sort_unique(params);

            /* Add to dstparams just the params that haven't already been
             * added. */
            IdList newsrcparams;
            for (Id i=0; i<params.size(); i++) {
                Id p = params[i];
                if (bad(src2dst.at(p))) newsrcparams.push_back(p);
            }
            IdList newdstparams = AppendParams(dstparams, srcparams, 
                                               newsrcparams);
            /* update the mapping */
            for (Id i=0; i<newdstparams.size(); i++) {
                src2dst.at(newsrcparams[i]) = newdstparams[i];
            }

            /* append the terms */
            AppendTerms(dsttable, srctable, atmmap, terms, src2dst);
        }
    }

    /* copy all top-level data */
    dst->name = src->name;
    dst->global_cell = src->global_cell;
    dst->nonbonded_info = src->nonbonded_info;
    BOOST_FOREACH(Provenance const& p, src->provenance()) dst->addProvenance(p);

    /* add/replace extra tables */
    std::vector<String> extras = src->auxTableNames();
    for (unsigned i=0; i<extras.size(); i++) {
        std::string const& name = extras[i];
        ParamTablePtr srcparams = src->auxTable(name);
        ParamTablePtr dstparams = ParamTable::create();
        AppendParams( dstparams, srcparams, srcparams->params() );
        dst->addAuxTable( name, dstparams );
    }
    dst->updateFragids();
    return dst;
}

