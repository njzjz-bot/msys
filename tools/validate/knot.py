

"""
Given a system, find any instances where a bond is 'threaded' through a ring, 
like so

                /-------\
       \       /         \
        \     /           \
         \----\  ---------------\
               \         /       \
                \-------/         \

The algorithm works as follows:

    1. Produce a list of all cycles in the bond topology (i.e. rings)
    2. For each ring:
        a. Use boxing and distance cutoffs to reduce the number of bonds to check against
        b. Divide the ring into N triangles
        c. Check for a triangle-line intersection between the triangle and each relevant bond
"""
# Copyright (C) 2010 D.E. Shaw Research
# @author Adam Lerer
# @author Justin Gullingsrud (converted to msys)


import numpy
import sys
import math
import msys
from msys.wrap import Wrapper

from time import time

def ut_intersection():
    t0 = numpy.array([0.0, 0.0, 0.0]);
    t1 = numpy.array([0.0, 3.0, 3.0]);
    t2 = numpy.array([0.0, 2.0, 0.0]);

    l0 = numpy.array([-1.0, 1.0, 1.0]);
    l1n = numpy.array([1.0, 0.5, 1.0]);
    l1p = numpy.array([1.0, 1.5, 1.0]);
    
    assert msys.LineIntersectsTriangle(l0,l1n,t0,t1,t2) == False
    assert msys.LineIntersectsTriangle(l0,l1p,t0,t1,t2) == True

#######################################################################
#######################################################################
#######################################################################
#######################################################################


# returns a list of 3-tuples of the form (cycle, bond, idx) 

# where bond intersects with cycle, and idx is an index into cycle
# such that the triangle cycle[idx], cycle[idx+1], cycle[0] intersects
# with the bond.
def FindKnots(mol, max_cycle_size=None, selection='all', verbose=False):

    from msys import LineIntersectsTriangle
    t0=time()

    mol = mol.clone()
    if selection is None: selection = 'all'
    atoms = mol.select(selection) 
    cycles = msys.GetSSSR(atoms)
    if verbose: print "Found %d cycles" % len(cycles)
    if not cycles: return []
    if verbose: print "Largest cycle has size %d" % max(map(len,cycles))
    cycles = [tuple(a.id for a in c) for c in cycles]
    if max_cycle_size is not None:
        max_cycle_size = int(max_cycle_size)
        cycles = [c for c in cycles if len(c) <= max_cycle_size]
        if verbose:
            print "Reduced to %d cycles of length <= %d" % (
                    len(cycles), max_cycle_size)
  
    t1=time()

    # cache bonds
    bonds=[]
    ptr = mol._ptr
    for i, ai in enumerate(ptr.atoms()):
        bonds.append([aj for aj in ptr.bondedAtoms(ai) if aj<ai])

    t2=time()

    results = list()
    found = set()
    box = mol.getCell()
    wrapper = Wrapper(mol)

    t3=time()

    # apply shift of half the box size in all directions to catch knots that
    # cross periodic boundaries.
    for ishift in range(2):
        if ishift>0:
            mol.translate(0.5*(box[0]+box[1]+box[2]))
            if verbose:
                print "Checking for knots crossing periodic boundaries."
        else:
            if verbose:
                print "Checking for non-periodic knots."
        wrapper.wrap()
        pos = mol.getPositions()

        for icycle, cycle in enumerate(cycles):
            cycle_sel='index ' + ' '.join(map(str,cycle))
            sel = '(%s) and exwithin 10 of %s' % (selection, cycle_sel)
            ids = set(mol.selectIds(sel))
            cp = [pos[i] for i in cycle]
            cycle_inds = range(1,len(cycle)-1)
            for ai in ids:
                for aj in bonds[ai]:
                    if aj not in ids: continue
                    ipos = pos[ai]
                    jpos = pos[aj]
                    for idx in cycle_inds:
                        key = (ai,aj,0,idx,idx+1)
                        if key in found: continue
                        if LineIntersectsTriangle(
                                ipos, jpos, cp[0], cp[idx], cp[idx+1]):
                            bond = (ai,aj)
                            if verbose: print "==> intersection:",cycle,bond
                            results.append((cycle, bond, idx))
                            found.add(key)
    if verbose: print "Total intersections: %d" % len(found)

    t4=time()

    if False:
        print "Time: %8.3f %8.3f %8.3f %8.3f" % (
                (t1-t0)*1000,
                (t2-t1)*1000,
                (t3-t2)*1000,
                (t4-t3)*1000,)

    return results

def get_lipid_atoms(cycle, bond, dms):
    cycle_ids = [atom.id for atom in dms.select('lipid and same residue as index %d' % cycle[0])]
    bond_ids  = [atom.id for atom in dms.select('lipid and same residue as index %d' % bond[0] )]
    assert cycle_ids or bond_ids, "Neither the cycle %s or the bond %s was part of a lipid" % (cycle_ids,bond_ids)
    if cycle_ids and bond_ids:
        print "WARNING: Both the cycle %s and the bond %s were part of a lipid. Will only move the bond molecule." % (cycle_ids,bond_ids)
    return bond_ids if bond_ids else cycle_ids

def fix_thread(mol, cycle, bond, idx, move_lipid, dirty):
    assert idx+1 < len(cycle)
    pos = mol.getPositions()
    
    b0, b1 = pos[bond[0]], pos[bond[1]]
    b01 = b1-b0

    c0, c1 = pos[cycle[idx]], pos[cycle[idx+1]]
    c01 = c1-c0
    
    normal = numpy.cross(b01, c01)
    normhat = normal / numpy.linalg.norm(normal)

    dv = numpy.dot(c0-b0, normhat)
    MUL = 2.0      # move the bond 2 times it's current distance from the ring
    dt = MUL * dv
    
    if move_lipid:
        atomsel = get_lipid_atoms(cycle, bond, mol)
    else:
        atomsel = bond

    if set(atomsel) & dirty:
        print "Will not fix %s %s this iteration because atoms that must be moved have been moved earlier this pass." \
            % (cycle, bond)
        return []

    print "Moved particles %s a distance of %.2gA" % (atomsel, abs(dt))
    
    for atom in atomsel:
        p_prime = pos[atom] + dt*normhat
        mol.atom(atom).pos = p_prime

    return atomsel

def fix_all_threads(mol, intersections, move_lipid=False):
    if not intersections:
        return

    dirty = set()
    for cycle,bond,idx in intersections:
        moved = fix_thread(mol, cycle, bond, idx, move_lipid, dirty)
        dirty |= set(moved)
    
# returns True if converged within iteration_limit iterations
def UntieKnots(mol, max_cycle_size=None, selection="all", move_lipid=False, iteration_limit=20, verbose=True):
    for iteration_number in range(iteration_limit):
        intersections = FindKnots(mol, max_cycle_size=max_cycle_size, selection=selection, verbose=verbose)
        if not intersections:
            return True
        fix_all_threads(mol, intersections, move_lipid=move_lipid)
    return False
