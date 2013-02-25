#include "elements.hxx"
#include <algorithm>
#include <string.h>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace desres::msys;

/* All radius data from Bondi 1964, except as noted.  Values of 2.0 by default.
 * a) Rowland and Taylor 1996
 * b) Mantina 2009
 * c) Charmm36 ion radii
 * d) VMD/molfile (unknown provenance)
 */

namespace {
    struct Element {
        int         anum;
        const char* abbr;
        double      radius;
        double      mass;

        Element() {}
        Element(double m) : mass(m) {}
        Element(int n, const char* a, double r, double m)
        : anum(n), abbr(a), radius(r), mass(m) {}
        bool operator<(Element const& e) const { return mass<e.mass; }
    };
}

static const Element elems[] = {
  {   0, "X",  0.00, 0.000000  },
  {   1, "H",  1.10, 1.007940  },   // a
  {   2, "He", 1.40, 4.002600  },
  {   3, "Li", 1.30, 6.941000  },   // c
  {   4, "Be", 1.53, 9.012182  },   // b
  {   5, "B",  1.92, 10.811000 },   // b
  {   6, "C",  1.70, 12.010700 },
  {   7, "N",  1.55, 14.006700 },
  {   8, "O",  1.52, 15.999400 },
  {   9, "F",  1.47, 18.998403 },
  {  10, "Ne", 1.54, 20.179700 },
  {  11, "Na", 1.41, 22.989770 },   // c
  {  12, "Mg", 1.18, 24.305000 },   // c
  {  13, "Al", 1.84, 26.981538 },   // b
  {  14, "Si", 2.10, 28.085500 },
  {  15, "P",  1.80, 30.973761 },
  {  16, "S",  1.80, 32.065000 },
  {  17, "Cl", 2.27, 35.453000 },   // c
  {  18, "Ar", 1.88, 39.948000 },
  {  19, "K",  1.76, 39.098300 },   // c
  {  20, "Ca", 1.37, 40.078000 },   // c
  {  21, "Sc", 2.00, 44.955910 },
  {  22, "Ti", 2.00, 47.867000 },
  {  23, "V",  2.00, 50.941500 },
  {  24, "Cr", 2.00, 51.996100 },
  {  25, "Mn", 2.00, 54.938049 },
  {  26, "Fe", 2.00, 55.845000 },
  {  27, "Co", 2.00, 58.933200 },
  {  28, "Ni", 1.09, 58.693400 },   // copied from Zn
  {  29, "Cu", 1.09, 63.546000 },   // copied from Zn
  {  30, "Zn", 1.09, 65.409000 },   // c
  {  31, "Ga", 1.87, 69.723000 },   // b
  {  32, "Ge", 2.11, 72.640000 },   // b
  {  33, "As", 1.85, 74.921600 },
  {  34, "Se", 1.90, 78.960000 },
  {  35, "Br", 1.83, 79.904000 },   // b
  {  36, "Kr", 2.02, 83.798000 },
  {  37, "Rb", 1.90, 85.467800 },   // c
  {  38, "Sr", 2.49, 87.620000 },   // b
  {  39, "Y",  2.00, 88.905850 },
  {  40, "Zr", 2.00, 91.224000 },
  {  41, "Nb", 2.00, 92.906380 },
  {  42, "Mo", 2.00, 95.940000 },
  {  43, "Tc", 2.00, 98.000000 },
  {  44, "Ru", 2.00, 101.070000 },
  {  45, "Rh", 2.00, 102.905500 },
  {  46, "Pd", 1.63, 106.420000 },
  {  47, "Ag", 1.72, 107.868200 },
  {  48, "Cd", 1.36, 112.411000 },  // c
  {  49, "In", 1.93, 114.818000 },
  {  50, "Sn", 2.17, 118.710000 },
  {  51, "Sb", 2.06, 121.760000 },  // b
  {  52, "Te", 2.06, 127.600000 },
  {  53, "I",  1.98, 126.904470 },
  {  54, "Xe", 2.16, 131.293000 },
  {  55, "Cs", 2.10, 132.905450 },  // c
  {  56, "Ba", 1.89, 137.327000 },  // c
  {  57, "La", 2.00, 138.905500 },
  {  58, "Ce", 2.00, 140.116000 },
  {  59, "Pr", 2.00, 140.907650 },
  {  60, "Nd", 2.00, 144.240000 },
  {  61, "Pm", 2.00, 145.000000 },
  {  62, "Sm", 2.00, 150.360000 },
  {  63, "Eu", 2.00, 151.964000 },
  {  64, "Gd", 2.00, 157.250000 },
  {  65, "Tb", 2.00, 158.925340 },
  {  66, "Dy", 2.00, 162.500000 },
  {  67, "Ho", 2.00, 164.930320 },
  {  68, "Er", 2.00, 167.259000 },
  {  69, "Tm", 2.00, 168.934210 },
  {  70, "Yb", 2.00, 173.040000 },
  {  71, "Lu", 2.00, 174.967000 },
  {  72, "Hf", 2.00, 178.490000 },
  {  73, "Ta", 2.00, 180.947900 },
  {  74, "W",  2.00, 183.840000 },
  {  75, "Re", 2.00, 186.207000 },
  {  76, "Os", 2.00, 190.230000 },
  {  77, "Ir", 2.00, 192.217000 },
  {  78, "Pt", 1.72, 195.078000 },  // d
  {  79, "Au", 1.66, 196.966550 },  // d
  {  80, "Hg", 1.55, 200.590000 },  // d
  {  81, "Tl", 1.96, 204.383300 },  // d
  {  82, "Pb", 2.02, 207.200000 },  // d
  {  83, "Bi", 2.07, 208.980380 },  // b
  {  84, "Po", 1.97, 209.000000 },  // b
  {  85, "At", 2.02, 210.000000 },  // b
  {  86, "Rn", 2.20, 222.000000 },  // b
  {  87, "Fr", 3.48, 223.000000 },  // b
  {  88, "Ra", 2.83, 226.000000 },  // b
  {  89, "Ac", 2.00, 227.000000 },
  {  90, "Th", 2.00, 232.038100 },
  {  91, "Pa", 2.00, 231.035880 },
  {  92, "U",  2.00, 238.028910 },
  {  93, "Np", 2.00, 237.000000 },
  {  94, "Pu", 2.00, 244.000000 },
  {  95, "Am", 2.00, 243.000000 },
  {  96, "Cm", 2.00, 247.000000 },
  {  97, "Bk", 2.00, 247.000000 },
  {  98, "Cf", 2.00, 251.000000 },
  {  99, "Es", 2.00, 252.000000 },
  { 100, "Fm", 2.00, 257.000000 },
  { 101, "Md", 2.00, 258.000000 },
  { 102, "No", 2.00, 259.000000 },
  { 103, "Lr", 2.00, 262.000000 },
  { 104, "Rf", 2.00, 261.000000 },
  { 105, "Db", 2.00, 262.000000 },
  { 106, "Sg", 2.00, 266.000000 },
  { 107, "Bh", 2.00, 264.000000 },
  { 108, "Hs", 2.00, 269.000000 },
  { 109, "Mt", 2.00, 268.000000 },
  { 110, "Ds", 2.00, 271.000000 },
  { 111, "Rg", 2.00, 272.000000 }
};

static const int nelems = sizeof(elems)/sizeof(elems[0]);

static Element sorted_elems[nelems];

namespace {
    struct _ {
        _() {
            std::copy(elems, elems+nelems, sorted_elems);
            std::sort(sorted_elems, sorted_elems+nelems);
        }
    } sort_elems;
}

int desres::msys::GuessAtomicNumber( double mass ) {
    const Element* begin=sorted_elems, *end = sorted_elems+nelems;
    /* first element which is not less than mass */
    const Element* rhs = std::lower_bound(begin, end, Element(mass));
    /* greater than last value */
    if (rhs==end) return 0;
    /* zero or negative mass? */
    if (rhs==begin) return 0;
    /* take the closest */
    const Element* lhs = rhs-1;
    double ldiff = mass-lhs->mass;
    double rdiff = rhs->mass-mass;
    return ldiff < rdiff ? lhs->anum : rhs->anum;
}

const char* desres::msys::AbbreviationForElement(int anum) {
    if (anum<0 || anum>=nelems) return "";
    return elems[anum].abbr;
}

double desres::msys::MassForElement(int anum) {
    if (anum<=0 || anum>=nelems) return 0;
    return elems[anum].mass;
}

double desres::msys::RadiusForElement(int anum) {
    if (anum<0) return 0;
    if (anum>=nelems) return 2.0;
    return elems[anum].radius;
}

int desres::msys::ElementForAbbreviationSlow(const char* abbr) {
    std::string src(abbr);
    boost::to_upper(src);
    for (int i=1; i<nelems; i++) {
        std::string ref(elems[i].abbr);
        boost::to_upper(ref);
        if (ref==src) return i;
    }
    return 0;
}   

namespace {
    ChemData NODATA{0.0, 0, 0, 0, 6};

    const ChemData atomInfo[] = { 
        NODATA,                            // PlaceHolder
        ChemData(2.300,  1,  2,  0,  1 ),  // H   1
        ChemData(4.160,  2,  2,  0,  0 ),  // He  2
        // Period 2
        ChemData(0.912,  1,  8,  0,  1 ),  // Li  3
        ChemData(1.576,  2,  8,  0,  2 ),  // Be  4
        ChemData(2.051,  3,  8,  0,  4 ),  // B   5 // sextet
        ChemData(2.544,  4,  8,  1,  4 ),  // C   6
        ChemData(3.066,  5,  8,  2,  4 ),  // N   7
        ChemData(3.610,  6,  8,  3,  3 ),  // O   8
        ChemData(4.193,  7,  8,  4,  1 ),  // F   9
        ChemData(4.789,  8,  8,  4,  0 ),  // Ne  10
        // Period 3
        ChemData(0.869,  1,  2,  0,  1 ),  // Na  11
        ChemData(1.293,  2,  4,  0,  2 ),  // Mg  12
        ChemData(1.613,  3,  6,  0,  6 ),  // Al  13 // sextet
        ChemData(1.916,  4,  8,  1,  6 ),  // Si  14
        ChemData(2.253,  5,  10, 2,  6 ),  // P   15
        ChemData(2.589,  6,  12, 3,  6 ),  // S   16
        ChemData(2.869,  7,  14, 4,  6 ),  // Cl  17
        ChemData(3.242,  8,  8,  4,  0 ),  // Ar  18
        // Period 4 - Groups 1 & 2
        ChemData( 0.734, 1,  8,  0,  1 ),  // K   19
        ChemData( 1.034, 2,  8,  0,  2 ),  // Ca  20
        // Period 4 - Transition Metals (most stable or lowest charge state is used)
        ChemData(1.190,  3,  8,  0,  6 ),  // Sc  21 (2 rare, 3 common)
        ChemData(1.380,  4,  8,  0,  6 ),  // Ti  22 (2-3 rare, 4 common)
        ChemData(1.530,  2,  8,  0,  6 ),  // V   23 (1 rare, 2-5 common)
        ChemData(1.650,  3,  8,  0,  6 ),  // Cr  24 (1,4-5 rare, 2-3,6 common, 3 most stable) 
        ChemData(1.750,  2,  8,  0,  6 ),  // Mn  25 (1,5 rare, 2-4,6-7 common, 2 most stable)
        ChemData(1.800,  2,  8,  0,  6 ),  // Fe  26 (1,4-6 rare, 2-3 common)
        ChemData(1.840,  2,  8,  0,  6 ),  // Co  27 (1,4-6 rare, 2-3 common)
        ChemData(1.880,  2,  8,  0,  6 ),  // Ni  28 (1,3-4 rare, 2 common)
        ChemData(1.850,  2,  8,  0,  6 ),  // Cu  29 (1 rare, 2 common)
        ChemData(1.590,  2,  8,  0,  6 ),  // Zn  30 (2 common)
        // Period 4 - Groups 13-18
        NODATA, NODATA,                    // Ga - Ge    31 - 32
        ChemData( 2.211, 5,  10, 2,  6 ),  // As  33
        ChemData( 2.434, 6,  12, 3,  6 ),  // Se  34
        ChemData( 2.685, 7,  14, 4,  6 ),  // Br  35
        ChemData( 2.966, 8,  8,  4,  0 ),  // Kr  36
        // Period 5 - Groups 1 & 2
        ChemData( 0.706, 1,  8,  0,  1 ),  // Rb  37
        ChemData( 0.963, 2,  8,  0,  2 ),  // Sr  38
        // Period 5 - Transition Metals
        // FIXME: should handle biocatalytic metals (Mo) 
        NODATA, NODATA, NODATA, NODATA, NODATA, //  Y - Tc  39-43
        NODATA, NODATA, NODATA, NODATA, NODATA, // Ru - Cd  44-48
        // Period 5 - Groups 13-18
        NODATA, NODATA, NODATA, NODATA,    // In - Te  49-52
        ChemData( 2.359, 7,  14, 4,  6 ),  // I   53
        ChemData( 2.582, 8,  8,  4,  0 ),  // Xe  54        
        // Period 6 - Groups 1 & 2
        ChemData( 0.659, 1,  8,  0,  1 ),  // Cs  55
        ChemData( 0.881, 2,  8,  0,  2 ),  // Ba  56
        // Period 6 - Lanthanides (all form M+3, some form M+2 or M+4)
        NODATA, NODATA, NODATA, NODATA, NODATA, NODATA, NODATA, // La - Eu  57 - 63
        NODATA, NODATA, NODATA, NODATA, NODATA, NODATA, NODATA, // Gd - Yb  64 - 70
        // Period 6 - Transition Metals
        NODATA, NODATA, NODATA, NODATA, NODATA, // Lu - Re 71-75
        NODATA, NODATA, NODATA, NODATA, NODATA, // Os - Hg 76-80
        // Period 6 - Groups 13-18
        NODATA, NODATA, NODATA, NODATA, NODATA, // Ti - At 81-85
        ChemData( 2.60,  8,  8,  4,  0 ),  // Rn  86     
        // Period 7 - Groups 1 & 2
        ChemData( 0.659, 1,  8,  0,  1 ),  // Fr  87
        ChemData( 0.881, 2,  8,  0,  2 )   // Ra  88
    };

    const int maxData = sizeof(atomInfo)/sizeof(atomInfo[0]);
}

ChemData const& desres::msys::DataForElement(int anum) {
    if (anum<0 || anum>=maxData) return NODATA;
    return atomInfo[anum];
}

