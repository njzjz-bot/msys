"""
dms-info [ options ] [ dms files ]

Write a human-readable summary of the contents of a structure file to stdout.

"""

import sys, os

import msys
import io


def print_info(mol, ct=None):
    ctname = ":" if ct is None else "%d: %s" % (ct, mol.name)
    ax, ay, az = mol.cell[0]
    bx, by, bz = mol.cell[1]
    cx, cy, cz = mol.cell[2]
    npseudo = len(mol.selectIds("atomicnumber 0"))
    print("Structure", ctname)
    print("%12s: %8d (%d pseudo)" % ("Atoms", mol.natoms, npseudo))
    print("%12s: %8d" % ("Bonds", mol.nbonds))
    print("%12s: %8d" % ("Residues", mol.nresidues))
    print("%12s: %8d" % ("Chains", mol.nchains))
    print("%12s: %8d" % ("Components", mol.ncts))
    print()
    print("%12s: %10s %10s %10s" % ("Global cell", ax, ay, az))
    print("%12s  %10s %10s %10s" % ("", bx, by, bz))
    print("%12s  %10s %10s %10s" % ("", cx, cy, cz))
    print()
    for sel, title in (
        ("protein", "Protein"),
        ("lipid", "Lipid"),
        ("nucleic", "Nucleic"),
        ("ions", "Ions"),
        ("water", "Water"),
        ("not (protein or lipid or nucleic or ions or water)", "Other"),
    ):

        atoms = mol.select(sel)
        residues = set(a.residue for a in atoms)
        chains = set(r.chain for r in residues)
        print(
            "%12s: %8d atoms, %8d residues, %8d chains"
            % (title, len(atoms), len(residues), len(chains))
        )

    if ct is None:
        print()
        print("Ct composition:")
        for i, c in enumerate(mol.cts):
            print("%8d) %-24s %8d atoms" % (i + 1, c.name, c.natoms))

    tdict = dict()
    for table in mol.tables:
        tdict.setdefault(table.category, []).append(table)

    for cat in sorted(tdict.keys()):
        tables = tdict[cat]
        title = "%s tables" % cat
        print("\n%s Tables:" % cat.title())

        for table in tables:
            n = table.noverrides
            print(
                "%28s: %d sites, %6d params, %6d terms"
                % (table.name, table.natoms, table.params.nparams, table.nterms)
            )
            if table.noverrides:
                print(
                    "%27s overrides: %6d params, %6d pairs"
                    % ("", table.noverrides, table.count_overrides())
                )

    nbinfo = mol.nonbonded_info
    print("\n%s:" % "Nonbonded Info")
    print("%20s: %s" % ("vdw_funct", nbinfo.vdw_funct))
    print("%20s: %s" % ("vdw_rule", nbinfo.vdw_rule))

    print("\n%s:" % "Auxiliary Tables")
    for name in mol.auxtable_names:
        if name == "forcefield":
            continue
        aux = mol.auxtable(name)
        print("%28s: %d properties, %6d rows" % (name, aux.nprops, aux.nparams))

    print("\n%s:" % "Forcefields")
    if "forcefield" in mol.auxtable_names:
        ff = mol.auxtable("forcefield")
        for p in ff.params:
            path = "<no path>" if "path" not in ff.props else p["path"]
            print("%4d) %s" % (p.id + 1, path))

    print("\n%s:" % "Provenance")
    for i, p in enumerate(mol.provenance):
        print("%4d) %16s %s" % (i + 1, p.timestamp, p.user))
        print("%12s: %s" % ("version", p.version))
        print("%12s: %s" % ("workdir", p.workdir))
        print("%12s: %s" % ("cmdline", p.cmdline))
        print("%12s: %s" % ("executable", p.executable))
        print()


def main():
    import optparse

    parser = optparse.OptionParser(__doc__)
    parser.add_option(
        "-m",
        "--multi-ct",
        action="store_true",
        default=False,
        help="Analyze each substructure (ct), instead of the full system",
    )
    parser.add_option(
        "--ignore-empty",
        action="store_true",
        default=False,
        help="Skip over empty systems",
    )

    opts, args = parser.parse_args()
    errors = io.StringIO()
    for path in args:
        if opts.multi_ct:
            it = msys.LoadMany(path, error_writer=errors)
        else:
            it = [msys.Load(path)]
        print("-" * 75)
        print(path)
        print()
        for i, mol in enumerate(it):
            if mol is None:
                continue
            if opts.ignore_empty and mol.natoms == 0:
                continue
            print_info(mol, ct=i if opts.multi_ct else None)
            print()
            if opts.multi_ct:
                print("." * 75)

    errmsg = errors.getvalue()
    if errmsg:
        print(errmsg)
