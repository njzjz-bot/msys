import msys

# convert residue name to one-letter code
code = {
    "ALA": "A",
    "ARG": "R",
    "ASH": "D",  # neutral Asp
    "ASN": "N",
    "ASP": "D",
    "ASX": "B",  # Asn/Asp
    "CYM": "C",  # Negative Cys
    "CYS": "C",
    "CYX": "C",  # S-S bonded Cys
    "GLH": "E",  # neutral Glu
    "GLN": "Q",
    "GLU": "E",
    "GLX": "Z",  # Gln/Glu
    "GLY": "G",
    "HID": "H",  # Delta His
    "HIE": "H",  # Epsilon His
    "HIP": "H",  # Positive His
    "HIS": "H",
    "HSD": "H",  # Delta His
    "HSE": "H",  # Epsilon His
    "ILE": "I",
    "LEU": "L",
    "LYN": "K",  # neutral Lys
    "LYS": "K",
    "MET": "M",
    "PHE": "F",
    "PRO": "P",
    "SER": "S",
    "THR": "T",
    "TRP": "W",
    "TYM": "Y",  # Negative Tyr
    "TYR": "Y",
    "UNK": "X",
    "VAL": "V",
}


def Sequences(system_or_chain, distinct=True):
    """return list of sequences, one for each chain, for the given input.
    The sequence will be returned as a string, with characters corresponding
    to the 1-letter sequence codes.  If a Chain is provided instead of a
    System, only one sequence will be returned.

    If distinct is True, only distinct sequences will be returned.
    """
    if isinstance(system_or_chain, msys.Chain):
        chains = [system_or_chain]
    elif isinstance(system_or_chain, msys.System):
        chains = system_or_chain.chains
    else:
        t = type(system_or_chain)
        raise TypeError("Expected System or Chain, got %s" % t)
    seqs = []
    for c in chains:
        seq = "".join(code.get(r.name, "X") for r in c.residues)
        seq = seq.strip("X")
        if set(seq) == {"X"}:
            seq = ""
        seqs.append(seq)
    if distinct:
        seqs = sorted(set(seqs))
    return seqs


doc = """
dms-sequence [--with-duplicates] [--without-duplicates] [ dms files ]
Write sequences in a dms file to stdout.
"""


def main():
    import optparse

    parser = optparse.OptionParser(doc)
    parser.add_option(
        "--with-duplicates",
        action="store_false",
        default=True,
        dest="distinct",
        help="Print duplicate sequences",
    )
    parser.add_option(
        "--without-duplicates",
        action="store_true",
        dest="distinct",
        help="Don't print duplicate sequences",
    )

    opts, args = parser.parse_args()
    for path in args:
        mol = msys.Load(path)
        for s in Sequences(mol, **opts.__dict__):
            print(s)
